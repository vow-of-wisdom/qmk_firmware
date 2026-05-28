/* matrix.c */


#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"


#define ROWS_PER_HAND  (MATRIX_ROWS / 2)

#define DOUBLEDOWN_COL  5


static const pin_t col_pins[MATRIX_COLS]   = MATRIX_COL_PINS;
static const pin_t row_pins[ROWS_PER_HAND] = MATRIX_ROW_PINS;

static const uint8_t fingers_states[MATRIX_COLS] = { 0, 0, 1, 0, 0, 0 };
static const uint8_t thumbs_states[MATRIX_COLS]  = { 0, 0, 0, 0, 0, 0 };


static bool
select_row(uint8_t row) {
  if (row_pins[row] != NO_PIN) {
    ATOMIC_BLOCK_FORCEON {
      gpio_set_pin_output(row_pins[row]);
      gpio_write_pin_low(row_pins[row]);
    }
    return true;
  }
  return false;
}


static void
unselect_row(uint8_t row) {
  ATOMIC_BLOCK_FORCEON {
    gpio_set_pin_output(row_pins[row]);
    gpio_write_pin_high(row_pins[row]);
  }
}


static void
unselect_rows(void) {
  for (uint8_t x = 0; x < ROWS_PER_HAND; x++) {
    unselect_row(x);
  }
}


static void
matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t row) {
  static int8_t  scans_before_dd_detect = 3;
  static uint8_t dd_detected = 0;

  matrix_row_t row_value = 0;

  select_row(row);
  wait_us(90);

  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    uint8_t pin_state;
    if (row == 0) {
      pin_state = gpio_read_pin(col_pins[col]) == thumbs_states[col];
      if (col == DOUBLEDOWN_COL) {
        if (scans_before_dd_detect >= 0) {
          scans_before_dd_detect--;
        }
        if (scans_before_dd_detect == 0) {
          dd_detected = pin_state;
          scans_before_dd_detect--;
        }
        pin_state ^= dd_detected;
        pin_state &= 1;
      }
    } else {
      pin_state = gpio_read_pin(col_pins[col]) == fingers_states[col];
    }
    row_value |= (pin_state << col);
  }

  unselect_row(row);
  wait_us(90);

  current_matrix[row] = row_value;
}


void
matrix_init_custom(void) {
  unselect_rows();
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
      if (col == DOUBLEDOWN_COL){
        gpio_set_pin_input_high(pin);
      } else {
        gpio_set_pin_input(pin);
      }
    }
  }
}


bool
matrix_scan_custom(matrix_row_t raw_matrix[]) {
  static bool first_scan = true;

  matrix_row_t cur_matrix[ROWS_PER_HAND] = { 0 };
  for (uint8_t row = 0; row < ROWS_PER_HAND; row++) {
    matrix_read_cols_on_row(cur_matrix, row);
  }

  if (first_scan) {
    memset(raw_matrix, 0, sizeof cur_matrix);
    first_scan = false;
    return true;
  } else {
    bool changed = memcmp(raw_matrix, cur_matrix, sizeof cur_matrix) != 0;
    if (changed)
      memcpy(raw_matrix, cur_matrix, sizeof cur_matrix);
    return changed;
  }
}
