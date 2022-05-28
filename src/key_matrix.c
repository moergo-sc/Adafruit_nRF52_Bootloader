/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 Stephen Cheng for Innaworks Development Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "boards.h"

#if ENABLE_KEY_MATRIX==1

static bool matrix_state[KM_COL_COUNT][KM_ROW_COUNT] = {0};
static uint32_t key_combos[KM_COMBO_COUNT][2]=KM_COMBOS;
static uint32_t key_combo_count=KM_COMBO_COUNT;
static uint32_t row_pins[KM_ROW_COUNT]=KM_ROW_PINS;
static uint32_t col_pins[KM_COL_COUNT]=KM_COL_PINS;

static void km_init_scan_pin(uint32_t);
static void km_init_read_pin(uint32_t);

// The matrix may be scanned col to row or row to column, and is stored in
// `matrix_state` as [col][row].
#if KM_SCAN_DIR == 0
  #define SCAN_PINS row_pins
  #define SCAN_COUNT KM_ROW_COUNT
  #define READ_PINS col_pins
  #define READ_COUNT KM_COL_COUNT
  #define MATRIX_SCAN_SLOT(scan, read) matrix_state[read][scan]
#else
  #define SCAN_PINS col_pins
  #define SCAN_COUNT KM_COL_COUNT
  #define READ_PINS row_pins
  #define READ_COUNT KM_ROW_COUNT
  #define MATRIX_SCAN_SLOT(scan, read) matrix_state[scan][read]
#endif

void scan_key_matrix() {
    for (uint32_t scan = 0; scan < SCAN_COUNT; scan++){
        km_init_scan_pin(SCAN_PINS[scan]);
    }

    for (uint32_t read = 0; read < READ_COUNT; read++){
        km_init_read_pin(READ_PINS[read]);
    }

    for (uint32_t scan = 0; scan < SCAN_COUNT; scan++){
        // Drive the scan pin high
        nrf_gpio_pin_set(SCAN_PINS[scan]);

        // Read each read pin
        for (uint32_t read = 0; read < READ_COUNT; read++){
            bool read_result = (nrf_gpio_pin_read(READ_PINS[read]) == 1);
            if (read_result) {
                PRINTF("read=%i scan=%i pressed\r\n", read, scan);
            }
            MATRIX_SCAN_SLOT(scan, read) = read_result;
        }

        // Drive the scan pin low
        nrf_gpio_pin_clear(SCAN_PINS[scan]);
    }
}

/** Given a key matrix state, determine which key combo has been pressed
 * Currently only support combos of 2 keys
 * Returns:
 *  -1 = no_valid_combo_found
 *  >=0 = id of combo found
 */
int scan_key_matrix_for_key_combos() {
    
    // scan the key matrix
    scan_key_matrix();

    // Check the number of pressed keys
    uint32_t pressed_key_count = 0;
    uint32_t pressed_keys[3] = {0xFFFF};
    
    for (uint32_t col = 0; col < KM_COL_COUNT; col++){
        for (uint32_t row = 0; row < KM_ROW_COUNT; row++){
            if (matrix_state[col][row]) {
                pressed_keys[pressed_key_count] = _KEYID(col, row); 
                pressed_key_count++;
                if (pressed_key_count>2) {
                    PRINTF("pressed_key_count>2\r\n");
                    return -1;
                }
            }
        }
    }

    if (pressed_key_count!=2) {
        PRINTF("pressed_key_count=%i\r\n", pressed_key_count);
        return -1;
    }
    
    for (uint32_t combo = 0; combo < key_combo_count; combo++ ){
        if ((key_combos[combo][0]==pressed_keys[0] && key_combos[combo][1]==pressed_keys[1]) ||
            (key_combos[combo][0]==pressed_keys[1] && key_combos[combo][1]==pressed_keys[0])) {
            // Found the key combo
            PRINTF("Found matching key combo: %i\r\n", combo);
            return combo;
        }
    }

    PRINTF("No matching key combo\r\n");
    return -1;
};

/** Initialize a scan pin, and set to low  */
void km_init_scan_pin(uint32_t scan_pin)
{
  nrf_gpio_cfg_output(scan_pin);
  nrf_gpio_pin_clear(scan_pin);
}

/** Initialize a read pin  */
void km_init_read_pin(uint32_t read_pin)
{
  // Set to pull down
  nrf_gpio_cfg_input(read_pin, NRF_GPIO_PIN_PULLDOWN);
}

#else // ENABLE_KEY_MATRIX==1

// Dummy implementation
int scan_key_matrix_for_key_combos() {
    return -1;
}

#endif // ENABLE_KEY_MATRIX==1
