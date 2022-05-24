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

bool km_matrix_state[KM_COL_COUNT][KM_ROW_COUNT] = {0};

void scan_key_matrix(bool *matrix_state[][]) {
#if KM_SCAN_DIR==0
    // Scan with row pins, and read with col pins
    int row_pins[]=KM_ROW_PINS;
    int col_pins[]=KM_COL_PINS;

    for (row = 0 to KM_ROW_COUNT){
        // Drive the row pin

        // Read each col pin
        for (col = 0 to KM_COL_COUNT){
            bool col_result = read_pin(); 

            *matrix_state[col][row]= col_result;
        }

        // Undrive the row pim
          
    }
#else
    // Scan with col pins, and read with row pins
#endif // KM_SCAN_DIR
}

/** Given a key matrix state, determine which key combo has been pressed
 * Returns:
 *  -1 = no_valid_combo_found
 *  >=0 = id of combo found
 */
int parse_key_matrix(bool *matrix_state[][]. int key_combo_count, int *key_combos[][]) {
    // Check the number of pressed keys
    int pressed_key_count = 0;
    for (col = 0 to KM_COL_COUNT){
        for (row = 0 to KM_ROW_COUNT){
            if (*matrix_state[col][row]) {
                pressed_key_count
            }


};


#endif // ENABLE_KEY_MATRIX