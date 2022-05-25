/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Stephen Cheng for Innaworks Development Limited
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

#ifdef ENABLE_KEY_MATRIX

static bool matrix_state[KM_COL_COUNT][KM_ROW_COUNT] = {0};
static uint32_t key_combos[][]=KM_KEY_COMBOS;
static uint32_t key_combo_count=KM_KEY_COMBO_COUNT;
static uint32_t row_pins[]=KM_ROW_PINS;
static uint32_t col_pins[]=KM_COL_PINS;

void scan_key_matrix() {

#if KM_SCAN_DIR==0
    // Scan with row pins, and read with col pins
 
    for (uint32_t row = 0; row < KM_ROW_COUNT; row++){
        km_init_scan_pin(row_pins[row])
    }
    for (uint32_t col = 0; col < KM_COL_COUNT; col++){
        km_init_read_pin(col_pins[col])
    }

    for (uint32_t row = 0; row < KM_ROW_COUNT; row++){
        // Drive the row pin high
        nrf_gpio_pin_set(row_pins[row]);

        // Read each col pin
        for (uint32_t col = 0; col < KM_COL_COUNT; col++){
            bool col_result = (nrf_gpio_pin_read(col_pins[col])==1); 
            if (col_result) {
                PRINTF("col=%i row=%i pressed\r\n", col, row);
            }
            matrix_state[col][row]= col_result;
        }

        // Drive the row pin low
        nrf_gpio_pin_clear(row_pins[row]);

        // Pause before next scanning next row
        km_pause(KM_SCAN_PAUSE);  
    }
#else
    // Scan with col pins, and read with row pins
    for (uint32_t col = 0; col < KM_COL_COUNT; col++){
        km_init_scan_pin(col_pins[col])
    }
    for (uint32_t row = 0; row < KM_ROW_COUNT; row++){
        km_init_read_pin(row_pins[row])
    }

    for (uint32_t col = 0; col < KM_COL_COUNT; col++){
        // Drive the col pin high
        nrf_gpio_pin_set(col_pins[col]);

        // Read each row pin
        for (uint32_t row = 0; row < KM_ROW_COUNT; row++){
            bool row_result = (nrf_gpio_pin_read(row_pins[row])==1); 
            if (row_result) {
                PRINTF("col=%i row=%i pressed\r\n", col, row);
            }
            matrix_state[col][row]= col_result;
        }

        // Drive the col pin low
        nrf_gpio_pin_clear(col_pins[col]);  

        // Pause before next scanning next col
        km_pause(KM_SCAN_PAUSE);  
    }
#endif // KM_SCAN_DIR
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
    uint32_t pressed_keys[2]; = {0xFFFF};
    
    for (col = 0 to KM_COL_COUNT){
        for (row = 0 to KM_ROW_COUNT){
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
    
    for (unint32_t combo = 0; combo < key_combo_count; combo++ )
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

/** Pause for wait_ms  */
void km_pause(uint32_t wait_ms) {
    // [SC] Need to be written
}

#else // ENABLE_KEY_MATRIX

// Dummy implementation
int scan_key_matrix_for_key_combos() {
    return -1;
}

#endif // ENABLE_KEY_MATRIX