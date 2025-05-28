/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2025 John Donovan (geospark.co.uk)
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

#ifndef USB_DESCRIPTORS_H_
#define USB_DESCRIPTORS_H_

#include "tusb.h"

enum
{
  REPORT_ID_KEYBOARD = 1,
  REPORT_ID_TABLET,
  REPORT_ID_RAT,
  REPORT_ID_COMMAND,
  REPORT_ID_COUNT
};


/// HID Usage Table: Digitizer Page (0x0D)
enum {
  HID_USAGE_DIGITIZER_UNDEFINED                           = 0x00,
  HID_USAGE_DIGITIZER_DIGITIZER                           = 0x01, // CA
  HID_USAGE_DIGITIZER_PEN                                 = 0x02, // CA
  HID_USAGE_DIGITIZER_LIGHT_PEN                           = 0x03, // CA
  HID_USAGE_DIGITIZER_TOUCH_SCREEN                        = 0x04, // CA
  HID_USAGE_DIGITIZER_TOUCH_PAD                           = 0x05, // CA
  HID_USAGE_DIGITIZER_WHITEBOARD                          = 0x06, // CA
  HID_USAGE_DIGITIZER_COORDINATE_MEASURING_MACHINE        = 0x07, // CA
  HID_USAGE_DIGITIZER_3D_DIGITIZER                        = 0x08, // CA
  HID_USAGE_DIGITIZER_STEREO_PLOTTER                      = 0x09, // CA
  HID_USAGE_DIGITIZER_ARTICULATED_ARM                     = 0x0A, // CA
  HID_USAGE_DIGITIZER_ARMATURE                            = 0x0B, // CA
  HID_USAGE_DIGITIZER_MULTIPLE_POINT_DIGITIZER            = 0x0C, // CA
  HID_USAGE_DIGITIZER_FREE_SPACE_WAND                     = 0x0D, // CA
  HID_USAGE_DIGITIZER_DEVICE_CONFIGURATION                = 0x0E, // CA
  HID_USAGE_DIGITIZER_CAPACITIVE_HEAT_MAP_DIGITIZER       = 0x0F, // CA
  // Reserved (0x10 - 0x1F)
  HID_USAGE_DIGITIZER_STYLUS                              = 0x20, // CA/CL
  HID_USAGE_DIGITIZER_PUCK                                = 0x21, // CL
  HID_USAGE_DIGITIZER_FINGER                              = 0x22, // CL
  HID_USAGE_DIGITIZER_DEVICE_SETTINGS                     = 0x23, // CL
  HID_USAGE_DIGITIZER_CHARACTER_GESTURE                   = 0x24, // CL
  // Reserved (0x25 - 0x2F)
  HID_USAGE_DIGITIZER_TIP_PRESSURE                        = 0x30, // DV
  HID_USAGE_DIGITIZER_BARREL_PRESSURE                     = 0x31, // DV
  HID_USAGE_DIGITIZER_IN_RANGE                            = 0x32, // MC
  HID_USAGE_DIGITIZER_TOUCH                               = 0x33, // MC
  HID_USAGE_DIGITIZER_UNTOUCH                             = 0x34, // OSC
  HID_USAGE_DIGITIZER_TAP                                 = 0x35, // OSC
  HID_USAGE_DIGITIZER_QUALITY                             = 0x36, // DV
  HID_USAGE_DIGITIZER_DATA_VALID                          = 0x37, // MC
  HID_USAGE_DIGITIZER_TRANSDUCER_INDEX                    = 0x38, // DV
  HID_USAGE_DIGITIZER_TABLET_FUNCTION_KEYS                = 0x39, // CL
  HID_USAGE_DIGITIZER_PROGRAM_CHANGE_KEYS                 = 0x3A, // CL
  HID_USAGE_DIGITIZER_BATTERY_STRENGTH                    = 0x3B, // DV
  HID_USAGE_DIGITIZER_INVERT                              = 0x3C, // MC
  HID_USAGE_DIGITIZER_X_TILT                              = 0x3D, // DV
  HID_USAGE_DIGITIZER_Y_TILT                              = 0x3E, // DV
  HID_USAGE_DIGITIZER_AZIMUTH                             = 0x3F, // DV
  HID_USAGE_DIGITIZER_ALTITUDE                            = 0x40, // DV
  HID_USAGE_DIGITIZER_TWIST                               = 0x41, // DV
  HID_USAGE_DIGITIZER_TIP_SWITCH                          = 0x42, // MC
  HID_USAGE_DIGITIZER_SECONDARY_TIP_SWITCH                = 0x43, // MC
  HID_USAGE_DIGITIZER_BARREL_SWITCH                       = 0x44, // MC
  HID_USAGE_DIGITIZER_ERASER                              = 0x45, // MC
  HID_USAGE_DIGITIZER_TABLET_PICK                         = 0x46, // MC
  HID_USAGE_DIGITIZER_TOUCH_VALID                         = 0x47, // MC
  HID_USAGE_DIGITIZER_WIDTH                               = 0x48, // DV
  HID_USAGE_DIGITIZER_HEIGHT                              = 0x49, // DV
  // Reserved (0x4A - 0x50)
  HID_USAGE_DIGITIZER_CONTACT_IDENTIFIER                  = 0x51, // DV
  HID_USAGE_DIGITIZER_DEVICE_MODE                         = 0x52, // DV
  HID_USAGE_DIGITIZER_DEVICE_IDENTIFIER                   = 0x53, // DV/SV
  HID_USAGE_DIGITIZER_CONTACT_COUNT                       = 0x54, // DV
  HID_USAGE_DIGITIZER_CONTACT_COUNT_MAXIMUM               = 0x55, // SV
  HID_USAGE_DIGITIZER_SCAN_TIME                           = 0x56, // DV
  HID_USAGE_DIGITIZER_SURFACE_SWITCH                      = 0x57, // DF
  HID_USAGE_DIGITIZER_BUTTON_SWITCH                       = 0x58, // DF
  HID_USAGE_DIGITIZER_PAD_TYPE                            = 0x59, // SF
  HID_USAGE_DIGITIZER_TRANSDUCER_SERIAL_NUMBER            = 0x5B, // SV
  HID_USAGE_DIGITIZER_PREFERRED_COLOR                     = 0x5C, // DV
  HID_USAGE_DIGITIZER_PREFERRED_COLOR_LOCKED              = 0x5D, // MC
  HID_USAGE_DIGITIZER_PREFERRED_LINE_WIDTH                = 0x5E, // DV
  HID_USAGE_DIGITIZER_PREFERRED_LINE_WIDTH_LOCKED         = 0x5F, // MC
  HID_USAGE_DIGITIZER_LATENCY_MODE                        = 0x60, // DF
  HID_USAGE_DIGITIZER_GESTURE_CHARACTER_QUALITY           = 0x61, // DV
  HID_USAGE_DIGITIZER_CHARACTER_GESTURE_DATA_LENGTH       = 0x62, // DV
  HID_USAGE_DIGITIZER_CHARACTER_GESTURE_DATA              = 0x63, // DV
  HID_USAGE_DIGITIZER_GESTURE_CHARACTER_ENCODING          = 0x64, // NAry
  HID_USAGE_DIGITIZER_UTF8_CHARACTER_GESTURE_ENCODING     = 0x65, // Sel
  HID_USAGE_DIGITIZER_UTF16_LE_CHARACTER_GESTURE_ENCODING = 0x66, // Sel
  HID_USAGE_DIGITIZER_UTF16_BE_CHARACTER_GESTURE_ENCODING = 0x67, // Sel
  HID_USAGE_DIGITIZER_UTF32_LE_CHARACTER_GESTURE_ENCODING = 0x68, // Sel
  HID_USAGE_DIGITIZER_UTF32_BE_CHARACTER_GESTURE_ENCODING = 0x69, // Sel
  HID_USAGE_DIGITIZER_CAPACITIVE_HEAT_MAP_VENDOR_ID       = 0x6A, // SV
  HID_USAGE_DIGITIZER_CAPACITIVE_HEAT_MAP_VERSION         = 0x6B, // SV
  HID_USAGE_DIGITIZER_CAPACITIVE_HEAT_MAP_FRAME_DATA      = 0x6C, // DV
  HID_USAGE_DIGITIZER_GESTURE_CHARACTER_ENABLE            = 0x6D, // DF
  HID_USAGE_DIGITIZER_TRANSDUCER_SERIAL_NUMBER_PART2      = 0x6E, // SV
  HID_USAGE_DIGITIZER_NO_PREFERRED_COLOR                  = 0x6F, // DF
  HID_USAGE_DIGITIZER_PREFERRED_LINE_STYLE                = 0x70, // NAry
  HID_USAGE_DIGITIZER_PREFERRED_LINE_STYLE_LOCKED         = 0x71, // MC
  HID_USAGE_DIGITIZER_INK                                 = 0x72, // Sel
  HID_USAGE_DIGITIZER_PENCIL                              = 0x73, // Sel
  HID_USAGE_DIGITIZER_HIGHLIGHTER                         = 0x74, // Sel
  HID_USAGE_DIGITIZER_CHISEL_MARKER                       = 0x75, // Sel
  HID_USAGE_DIGITIZER_BRUSH                               = 0x76, // Sel
  HID_USAGE_DIGITIZER_NO_PREFERENCE                       = 0x77, // Sel
  // Reserved (0x78 - 0x7F)
  HID_USAGE_DIGITIZER_DIGITIZER_DIAGNOSTIC                = 0x80, // CL
  HID_USAGE_DIGITIZER_DIGITIZER_ERROR                     = 0x81, // NAry
  HID_USAGE_DIGITIZER_ERR_NORMAL_STATUS                   = 0x82, // Sel
  HID_USAGE_DIGITIZER_ERR_TRANSDUCERS_EXCEEDED            = 0x83, // Sel
  HID_USAGE_DIGITIZER_ERR_FULL_TRANS_FEATURES_UNAVAILABLE = 0x84, // Sel
  HID_USAGE_DIGITIZER_ERR_CHARGE_LOW                      = 0x85, // Sel
  // Reserved (0x86 - 0x8F)
  HID_USAGE_DIGITIZER_TRANSDUCER_SOFTWARE_INFO            = 0x90, // CL
  HID_USAGE_DIGITIZER_TRANSDUCER_VENDOR_ID                = 0x91, // SV
  HID_USAGE_DIGITIZER_TRANSDUCER_PRODUCT_ID               = 0x92, // SV
  HID_USAGE_DIGITIZER_DEVICE_SUPPORTED_PROTOCOLS          = 0x93, // NAry/CL
  HID_USAGE_DIGITIZER_TRANSDUCER_SUPPORTED_PROTOCOLS      = 0x94, // NAry/CL
  HID_USAGE_DIGITIZER_NO_PROTOCOL                         = 0x95, // Sel
  HID_USAGE_DIGITIZER_WACOM_AES_PROTOCOL                  = 0x96, // Sel
  HID_USAGE_DIGITIZER_USI_PROTOCOL                        = 0x97, // Sel
  HID_USAGE_DIGITIZER_MICROSOFT_PEN_PROTOCOL              = 0x98, // Sel
  // Reserved (0x99 - 0x9F)
  HID_USAGE_DIGITIZER_SUPPORTED_REPORT_RATES              = 0xA0, // SV/CL
  HID_USAGE_DIGITIZER_REPORT_RATE                         = 0xA1, // DV
  HID_USAGE_DIGITIZER_TRANSDUCER_CONNECTED                = 0xA2, // SF
  HID_USAGE_DIGITIZER_SWITCH_DISABLED                     = 0xA3, // Sel
  HID_USAGE_DIGITIZER_SWITCH_UNIMPLEMENTED                = 0xA4, // Sel
  HID_USAGE_DIGITIZER_TRANSDUCER_SWITCHES                 = 0xA5, // CL
  HID_USAGE_DIGITIZER_TRANSDUCER_INDEX_SELECTOR           = 0xA6, // DV
  // Reserved (0xA7 - 0xAF)
  HID_USAGE_DIGITIZER_BUTTON_PRESS_THRESHOLD              = 0xB0, // DV

  // Reserved (0xB1 - 0xFFFF)
};

// Values are derived empirically.
// min_x: -1752, max_x: 6782, min_y: -1100, max_y: 5851, min_pressure: 0, max_pressure: 127
#define QUANTEL_TABLET_MIN_X (0xf928)
#define QUANTEL_TABLET_MIN_Y (0xfbb4)
#define QUANTEL_TABLET_MAX_X (0x1a7e)
#define QUANTEL_TABLET_MAX_Y (0x16db)

#define TUD_HID_REPORT_DESC_QUANTEL_TABLET(...)                      \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DIGITIZER )                      , \
  HID_USAGE      ( HID_USAGE_DIGITIZER_PEN )                       , \
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                    , \
    __VA_ARGS__                                                      \
    HID_USAGE    ( HID_USAGE_DIGITIZER_STYLUS )                    , \
    HID_COLLECTION ( HID_COLLECTION_PHYSICAL )                     , \
      HID_USAGE        ( HID_USAGE_DIGITIZER_TIP_SWITCH )          , \
      HID_USAGE        ( HID_USAGE_DIGITIZER_IN_RANGE )            , \
      HID_USAGE        ( HID_USAGE_DIGITIZER_BARREL_SWITCH )       , /* Not used but needed for libinput */ \
      HID_USAGE        ( HID_USAGE_DIGITIZER_ERASER )              , /* Not used but needed for libinput */ \
      HID_LOGICAL_MIN  ( 0                                        ), \
      HID_LOGICAL_MAX  ( 1                                        ), \
      HID_REPORT_SIZE  ( 1                                        ), \
      HID_REPORT_COUNT ( 4                                        ), \
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE   ), \
      HID_REPORT_SIZE  ( 1                                        ), \
      HID_REPORT_COUNT ( 4                                        ), \
      HID_INPUT       ( HID_CONSTANT | HID_VARIABLE | HID_ABSOLUTE), \
    HID_USAGE_PAGE     ( HID_USAGE_PAGE_DESKTOP                   ), \
      HID_LOGICAL_MIN_N( QUANTEL_TABLET_MIN_X, 2                  ), \
      HID_LOGICAL_MAX_N( QUANTEL_TABLET_MAX_X, 2                  ), \
      HID_PHYSICAL_MIN_N ( 0, 2                                   ), /* Fairly arbitrary, but needed for libinput */ \
      HID_PHYSICAL_MAX_N ( 100, 2                                 ), /* Fairly arbitrary, but needed for libinput */ \
      HID_UNIT         ( 0x11                                     ), /* Fairly arbitrary, but needed for libinput */ \
      HID_UNIT_EXPONENT( -2                                       ), /* Fairly arbitrary, but needed for libinput */ \
      HID_REPORT_SIZE  ( 16                                       ), \
      HID_REPORT_COUNT ( 1                                        ), \
      HID_USAGE        ( HID_USAGE_DESKTOP_X                      ), \
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE   ), \
      HID_LOGICAL_MIN_N( QUANTEL_TABLET_MIN_Y, 2                  ), \
      HID_LOGICAL_MAX_N( QUANTEL_TABLET_MAX_Y, 2                  ), \
      HID_PHYSICAL_MIN_N ( 0, 2                                   ), /* Fairly arbitrary, but needed for libinput */ \
      HID_PHYSICAL_MAX_N ( 100, 2                                 ), /* Fairly arbitrary, but needed for libinput */ \
      HID_UNIT         ( 0x11                                     ), /* Fairly arbitrary, but needed for libinput */ \
      HID_UNIT_EXPONENT( -2                                       ), /* Fairly arbitrary, but needed for libinput */ \
      HID_REPORT_SIZE  ( 16                                       ), \
      HID_REPORT_COUNT ( 1                                        ), \
      HID_USAGE        ( HID_USAGE_DESKTOP_Y                      ), \
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE   ), \
    HID_USAGE_PAGE ( HID_USAGE_PAGE_DIGITIZER )                    , \
      HID_USAGE        ( HID_USAGE_DIGITIZER_TIP_PRESSURE         ), \
      HID_LOGICAL_MIN_N  ( 0, 2                                   ), \
      HID_LOGICAL_MAX_N  ( 0x7f, 2                                ), \
      HID_REPORT_SIZE  ( 16                                       ), /* Only 8 bits are used, but Wireshark fails to parse an unsigned 8-bit value and treats it as -1 */ \
      HID_REPORT_COUNT ( 1                                        ), \
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE   ), \
    HID_COLLECTION_END                                             , \
  HID_COLLECTION_END                                                 \

typedef struct TU_ATTR_PACKED {
  uint8_t flags;
  int16_t x;
  int16_t y;
  uint16_t tip_pressure;
} hid_quantel_tablet_report_t;

#define TUD_HID_REPORT_DESC_QUANTEL_RAT(...)                         \
  HID_USAGE_PAGE ( HID_USAGE_PAGE_DESKTOP )                        , \
  HID_USAGE      ( HID_USAGE_DESKTOP_GAMEPAD )                     , \
  HID_COLLECTION ( HID_COLLECTION_APPLICATION )                    , \
    __VA_ARGS__                                                      \
    HID_USAGE_PAGE ( HID_USAGE_PAGE_BUTTON )                       , \
      HID_USAGE_MIN    ( 1                                        ), \
      HID_USAGE_MAX    ( 5                                        ), \
      HID_LOGICAL_MIN  ( 0                                        ), \
      HID_LOGICAL_MAX  ( 1                                        ), \
      HID_REPORT_SIZE  ( 1                                        ), \
      HID_REPORT_COUNT ( 5                                        ), \
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE   ), \
      HID_REPORT_SIZE  ( 3                                        ), \
      HID_REPORT_COUNT ( 1                                        ), \
      HID_INPUT        ( HID_CONSTANT | HID_ARRAY | HID_ABSOLUTE  ), \
      HID_USAGE_PAGE   ( HID_USAGE_PAGE_DESKTOP                   ), \
      HID_LOGICAL_MIN  ( 0xff                                     ), \
      HID_LOGICAL_MAX  ( 0x01                                     ), \
      HID_REPORT_SIZE  ( 8                                        ), \
      HID_REPORT_COUNT ( 1                                        ), \
      HID_USAGE        ( HID_USAGE_DESKTOP_X                      ), \
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE   ), \
      HID_LOGICAL_MIN  ( 0xff                                     ), \
      HID_LOGICAL_MAX  ( 0x01                                     ), \
      HID_REPORT_SIZE  ( 8                                        ), \
      HID_REPORT_COUNT ( 1                                        ), \
      HID_USAGE        ( HID_USAGE_DESKTOP_Y                      ), \
      HID_INPUT        ( HID_DATA | HID_VARIABLE | HID_ABSOLUTE   ), \
  HID_COLLECTION_END                                                 \

typedef struct TU_ATTR_PACKED {
  uint8_t button_1: 1;
  uint8_t button_2: 1;
  uint8_t button_3: 1;
  uint8_t button_4: 1;
  uint8_t button_5: 1;
  uint8_t padding: 3;
  int8_t x;
  int8_t y;
} hid_quantel_rat_report_t;

#endif /* USB_DESCRIPTORS_H_ */
