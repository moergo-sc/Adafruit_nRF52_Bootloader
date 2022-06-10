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

#ifndef _GLOVE80_V1_LH_H
#define _GLOVE80_V1_LH_H

#define _PINNUM(port, pin)    ((port)*32 + (pin))

/*------------------------------------------------------------------*/
/* Power Management
 *------------------------------------------------------------------*/
// Enable DCDC for both REG0 and REG1 - see https://infocenter.nordicsemi.com/index.jsp?topic=%2Fps_nrf52840%2Fpower.html&resultof=%22%44%43%44%43%45%4e%30%22%20%22%64%63%64%63%65%6e%30%22%20&anchor=unique_1227442007
#define ENABLE_DCDC_0	      1
#define ENABLE_DCDC_1         1

// Set the RegOut0 voltage to be 2.4V
#define UICR_REGOUT0_VALUE UICR_REGOUT0_VOUT_2V4

/*------------------------------------------------------------------*/
/* LED
 *------------------------------------------------------------------*/
#define LEDS_NUMBER           1
#define LED_PRIMARY_PIN       _PINNUM(1, 15)
#define LED_STATE_ON          1

/*------------------------------------------------------------------*/
/* BUTTON
 *------------------------------------------------------------------*/
#define BUTTONS_NUMBER        2
#define BUTTON_1              _PINNUM(0, 9) // Not connected
#define BUTTON_2              _PINNUM(0, 10) // Not connected 
#define BUTTON_PULL           NRF_GPIO_PIN_PULLUP

//--------------------------------------------------------------------+
// BLE OTA
//--------------------------------------------------------------------+
#define BLEDIS_MANUFACTURER   "MoErgo"
#define BLEDIS_MODEL          "Glove80 LH"

//--------------------------------------------------------------------+
// USB
//--------------------------------------------------------------------+
#define USB_DESC_VID           0x239A
#define USB_DESC_UF2_PID       0x0029
#define USB_DESC_CDC_ONLY_PID  0x002A

//--------------------------------------------------------------------+
// KEY MATRIX
//--------------------------------------------------------------------+
#define ENABLE_KEY_MATRIX      1
#define KM_SCAN_DIR            1  // 1 = Scan with col pins, and read with row pins. 0 = Scan with row pins, and read with col pins
#define KM_COL_COUNT           7  
#define KM_COL_PINS            {_PINNUM(1, 1),_PINNUM(1, 3),_PINNUM(1, 5),_PINNUM(1, 7),_PINNUM(1, 6),_PINNUM(1, 4),_PINNUM(1, 8)}
#define KM_ROW_COUNT           6
#define KM_ROW_PINS            {_PINNUM(0, 26),_PINNUM(0, 5),_PINNUM(0, 6),_PINNUM(0, 8),_PINNUM(0, 7),_PINNUM(1, 9)}
#define _KEYID(col_id, row_id)    (col_id*KM_ROW_COUNT + row_id)
#define KM_COMBO_DFU           {_KEYID(6, 6-1), _KEYID(3, 3-1)} // C6R6 + C3R3
#define KM_COMBO_WIPE_CONFIG   {_KEYID(6, 6-1), _KEYID(3, 2-1)} // C6R6 + C3R2
#define KM_COMBO_COUNT         2
#define KM_COMBOS              {KM_COMBO_DFU, KM_COMBO_WIPE_CONFIG} 


//------------- UF2 -------------//
#define UF2_PRODUCT_NAME      "Glove80 v1 LH"
#define UF2_VOLUME_LABEL      "GLV80LHBOOT"
#define UF2_BOARD_ID          "Glove80-LH-revH"
#define UF2_INDEX_URL         "https://www.moergo.com"

#endif // _GLOVE80_V1_LH_H
