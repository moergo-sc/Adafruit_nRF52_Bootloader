/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Ha Thach for Adafruit Industries
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
#define LED_PRIMARY_PIN       _PINNUM(1, 10)
#define LED_STATE_ON          1

/*------------------------------------------------------------------*/
/* BUTTON
 *------------------------------------------------------------------*/
#define BUTTONS_NUMBER        2
#define BUTTON_1              _PINNUM(1, 11) // SW3 CFG_FIRMWARE_UNLOCKED
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
#define KM_SCAN_DIR            0  // 1 = Scan with col pins, and read with row pins. 0 = Scan with row pins, and read with col pins
/**
  &kscan0 {
	row-gpios
		= <&gpio0 26 GPIO_OPEN_SOURCE> // LH ROW1
		, <&gpio0 5 GPIO_OPEN_SOURCE> // LH ROW2
		, <&gpio0 7 GPIO_OPEN_SOURCE> // LH ROW3
		, <&gpio1 8 GPIO_OPEN_SOURCE> // LH ROW4
		, <&gpio0 11 GPIO_OPEN_SOURCE> // LH ROW5
		, <&gpio0 12 GPIO_OPEN_SOURCE> // LH ROW6
		;
	col-gpios
		= <&gpio1 1 (GPIO_ACTIVE_HIGH | GPIO_PULL_DOWN)> // LH COL6
		, <&gpio1 3 (GPIO_ACTIVE_HIGH | GPIO_PULL_DOWN)> // LH COL5
		, <&gpio1 5 (GPIO_ACTIVE_HIGH | GPIO_PULL_DOWN)> // LH COL4
		, <&gpio1 7 (GPIO_ACTIVE_HIGH | GPIO_PULL_DOWN)> // LH COL3
		, <&gpio1 6 (GPIO_ACTIVE_HIGH | GPIO_PULL_DOWN)> // LH COL2
		, <&gpio1 4 (GPIO_ACTIVE_HIGH | GPIO_PULL_DOWN)> // LH COL1
		, <&gpio0 2 (GPIO_ACTIVE_HIGH | GPIO_PULL_DOWN)> // LH Thumb
		;
};
*/
#define KM_COL_COUNT           7  
#define KM_COL_PINS            {_PINNUM(1, 1),_PINNUM(1, 3),_PINNUM(1, 5),_PINNUM(1, 7),_PINNUM(1, 6),_PINNUM(1, 4),_PINNUM(0, 2)}
#define KM_ROW_COUNT           6
#define KM_ROW_PINS            {_PINNUM(0, 26),_PINNUM(0, 5),_PINNUM(0, 7),_PINNUM(1, 8),_PINNUM(0, 11),_PINNUM(0, 12)}
#define _KEYID(col_num_minus_1, row_num_minus_1)    (col_num_minus_1*KM_ROW_COUNT + row_num_minus_1)
#define KM_COMBO_MSC           {_KEYID(6-1, 6-1), _KEYID(3-1, 3-1)} // C6R6 + C3R3
#define KM_COMBO_WIPE_CONFIG   {_KEYID(6-1, 6-1), _KEYID(3-1, 2-1)} // C6R6 + C3R2
#define KM_COMBO_COUNT         2
#define KM_COMBOS              {KM_COMBO_MSC, KM_COMBO_WIPE_CONFIG} 
#define KM_SCAN_PAUSE_MS       1


//------------- UF2 -------------//
#define UF2_PRODUCT_NAME      "Glove80 v1 LH"
#define UF2_VOLUME_LABEL      "FTHR840BOOT"
#define UF2_BOARD_ID          "nRF52840-Glove80-LH-revA"
#define UF2_INDEX_URL         "https://www.moergo.com"

#endif // _GLOVE80_V1_LH_H
