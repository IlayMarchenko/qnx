/*
 * $QNXLicenseC:
 * Copyright 2016, QNX Software Systems. All Rights Reserved.
 *
 * You must obtain a written license from and pay applicable license fees to QNX
 * Software Systems before you may reproduce, modify or distribute this software,
 * or any work that includes all or part of this software.   Free development
 * licenses are available for evaluation and non-commercial purposes.  For more
 * information visit http://licensing.qnx.com or email licensing@qnx.com.
 *
 * This file may contain contributions from others.  Please review this entire
 * file for other proprietary rights or license notices, as well as the QNX
 * Development Suite License Guide at http://licensing.qnx.com/license-guide/
 * for other information.
 * $
 */

#ifndef __HIDD_USAGE_TABLE_INCLUDED
#define __HIDD_USAGE_TABLE_INCLUDED

/*
	Report Types
*/
#define HID_INPUT_REPORT                             0x08
#define HID_OUTPUT_REPORT                            0x09
#define HID_FEATURE_REPORT                           0x0B

/*
	Device Report Protocol
*/
#define HID_PROTOCOL_BOOT                            0
#define HID_PROTOCOL_REPORT                          1

/*
	Collection Types
*/
#define HIDD_COLLECTION_TYPE_PHYSICAL                0x0000
#define HIDD_COLLECTION_TYPE_APPLICATION             0x0001
#define HIDD_COLLECTION_TYPE_LOGICAL                 0x0002
#define HIDD_COLLECTION_TYPE_RESERVED1               0x0003
#define HIDD_COLLECTION_TYPE_RESERVED2               0x007F
#define HIDD_COLLECTION_TYPE_VENDOR1                 0x0080
#define HIDD_COLLECTION_TYPE_VENDOR2                 0x00FF

/*
	Data properties
*/
#define HID_FIELD_DATA                               0x00010000
#define HID_FIELD_CONSTANT                           0x00010001
#define HID_FIELD_ARRAY                              0x00020000
#define HID_FIELD_VARIABLE                           0x00020002
#define HID_FIELD_ABSOLUTE                           0x00040000
#define HID_FIELD_RELATIVE                           0x00040004
#define HID_FIELD_NOWRAP                             0x00080000
#define HID_FIELD_WRAP                               0x00080008
#define HID_FIELD_LINEAR                             0x00100000
#define HID_FIELD_NONLINEAR                          0x00100010
#define HID_FIELD_PREFERED                           0x00200000
#define HID_FIELD_NONPREFERED                        0x00200020
#define HID_FIELD_NONULL                             0x00400000
#define HID_FIELD_NULL                               0x00400040
#define HID_FIELD_BITFIELD                           0x01000000
#define HID_FIELD_BUFFERED                           0x01000100

/*
	Usage Pages ( Page 14 ) of HID Usage Tables Ver 1.12rc1
*/
#define HIDD_PAGE_UNDEFINED                          0x0000
#define HIDD_PAGE_DESKTOP                            0x0001
#define HIDD_PAGE_SIMULATION                         0x0002
#define HIDD_PAGE_VR_CONTROL                         0x0003
#define HIDD_PAGE_SPORT_CONTROL                      0x0004
#define HIDD_PAGE_GAME_CONTROL                       0x0005
#define HIDD_PAGE_RESERVED1                          0x0006
#define HIDD_PAGE_KEYBOARD                           0x0007
#define HIDD_PAGE_LEDS                               0x0008
#define HIDD_PAGE_BUTTONS                            0x0009
#define HIDD_PAGE_ORDINAL                            0x000A
#define HIDD_PAGE_TELEPHONY                          0x000B
#define HIDD_PAGE_CONSUMER                           0x000C
#define HIDD_PAGE_DIGITIZER                          0x000D
#define HIDD_PAGE_RESERVED2                          0x000E
#define HIDD_PAGE_PID                                0x000F
#define HIDD_PAGE_UNICODE                            0x0010
#define HIDD_PAGE_RESERVED3                          0x0011 /* 0x0011--0x0013 */
#define HIDD_PAGE_ALPHANUMERIC_DISPLAY               0x0014
#define HIDD_PAGE_RESERVED4                          0x0015 /* 0x0015--0x003F */
#define HIDD_PAGE_MEDICAL                            0x0040
/* 0x0041--0x007F Reserved */
#define HIDD_PAGE_MONITOR_PAGES                      0x0080 /* 0x0080--0x0083 */
#define HIDD_PAGE_POWER_PAGES                        0x0084 /* 0x0084--0x0087 */
#define HIDD_PAGE_RESERVED5                          0x0088 /* 0x0088--0x008B */
#define HIDD_PAGE_BAR_CODE_SCANNER                   0x008C
#define HIDD_PAGE_SCALE                              0x008D
#define HIDD_PAGE_MAGNETIC_STRIPE_READING            0x008E
#define HIDD_PAGE_POINT_OF_SALE                      0x008F
#define HIDD_PAGE_CAMERA_CONTROL                     0x0090
#define HIDD_PAGE_ARCADE                             0x0091
/* 0x0092--0xFEFF Reserved */
/* 0xFF00--0xFFFF Vendor Defined */

/*
	Generic Desktop (Page 0x01)
*/
#define HIDD_USAGE_UNDEFINED                         0x0000
#define HIDD_USAGE_POINTER                           0x0001
#define HIDD_USAGE_MOUSE                             0x0002
#define HIDD_USAGE_RESERVED1                         0x0003
#define HIDD_USAGE_JOYSTICK                          0x0004
#define HIDD_USAGE_GAMEPAD                           0x0005
#define HIDD_USAGE_KEYBOARD                          0x0006
#define HIDD_USAGE_KEYPAD                            0x0007
#define HIDD_USAGE_MULTI_ACCESS                      0x0008
#define HIDD_USAGE_TABLET                            0x0009
/* 0x000A--0x002F Reserved */
#define HIDD_USAGE_X                                 0x0030
#define HIDD_USAGE_Y                                 0x0031
#define HIDD_USAGE_Z                                 0x0032
#define HIDD_USAGE_RX                                0x0033
#define HIDD_USAGE_RY                                0x0034
#define HIDD_USAGE_RZ                                0x0035
#define HIDD_USAGE_SLIDER                            0x0036
#define HIDD_USAGE_DIAL                              0x0037
#define HIDD_USAGE_WHEEL                             0x0038
#define HIDD_USAGE_HAT_SWITCH                        0x0039
#define HIDD_USAGE_COUNTED_BUFFER                    0x003A
#define HIDD_USAGE_BYTE_COUNT                        0x003B
#define HIDD_USAGE_MOTION_WAKEUP                     0x003C
#define HIDD_USAGE_START                             0x003D
#define HIDD_USAGE_SELECT                            0x003E
#define HIDD_USAGE_RESERVED2                         0x003F
#define HIDD_USAGE_VX                                0x0040
#define HIDD_USAGE_VY                                0x0041
#define HIDD_USAGE_VZ                                0x0042
#define HIDD_USAGE_VBRX                              0x0043
#define HIDD_USAGE_VBRY                              0x0044
#define HIDD_USAGE_VBRZ                              0x0045
#define HIDD_USAGE_VNO                               0x0046
#define HIDD_USAGE_FEATURE_NOTIFICATION              0x0047
#define HIDD_USAGE_RESOLUTION_MULTIPLIER             0x0048
/* 0x49--0x7F Reserved */
#define HIDD_USAGE_SYSTEM_CONTROL                    0x0080
#define HIDD_USAGE_SYSTEM_POWER_DOWN                 0x0081
#define HIDD_USAGE_SYSTEM_SLEEP                      0x0082
#define HIDD_USAGE_SYSTEM_WAKE_UP                    0x0083
#define HIDD_USAGE_SYSTEM_CONTEXT_MENU               0x0084
#define HIDD_USAGE_SYSTEM_MAIN_MENU                  0x0085
#define HIDD_USAGE_SYSTEM_APP_MENU                   0x0086
#define HIDD_USAGE_SYSTEM_MENU_HELP                  0x0087
#define HIDD_USAGE_SYSTEM_MENU_EXIT                  0x0088
#define HIDD_USAGE_SYSTEM_MENU_SELECT                0x0089
#define HIDD_USAGE_SYSTEM_MENU_RIGHT                 0x008A
#define HIDD_USAGE_SYSTEM_MENU_LEFT                  0x008B
#define HIDD_USAGE_SYSTEM_MENU_UP                    0x008C
#define HIDD_USAGE_SYSTEM_MENU_DOWN                  0x008D
#define HIDD_USAGE_SYSTEM_COLD_RESTART               0x008E
#define HIDD_USAGE_SYSTEM_WARM_RESTART               0x008F
#define HIDD_USAGE_DPAD_UP                           0x0090
#define HIDD_USAGE_DPAD_DOWN                         0x0091
#define HIDD_USAGE_DPAD_RIGHT                        0x0092
#define HIDD_USAGE_DPAD_LEFT                         0x0093
/* 0x0094--0x009F Reserved */
#define HIDD_USAGE_SYSTEM_DOCK                       0x00A0
#define HIDD_USAGE_SYSTEM_UNDOCK                     0x00A1
#define HIDD_USAGE_SYSTEM_SETUP                      0x00A2
#define HIDD_USAGE_SYSTEM_BREAK                      0x00A3
#define HIDD_USAGE_SYSTEM_DEBUG_BREAK                0x00A4
#define HIDD_USAGE_APPLICATION_BREAK                 0x00A5
#define HIDD_USAGE_APPLICATION_DEBUG_BREAK           0x00A6
#define HIDD_USAGE_SYSTEM_SPEAKER_MUTE               0x00A7
#define HIDD_USAGE_SYSTEM_HIBERNATE                  0x00A8
/* 0x00A9--0x00AF Reserved */
#define HIDD_USAGE_SYSTEM_DISPLAY_INVERT             0x00B0
#define HIDD_USAGE_SYSTEM_DISPLAY_INTERNAL           0x00B1
#define HIDD_USAGE_SYSTEM_DISPLAY_EXTERNAL           0x00B2
#define HIDD_USAGE_SYSTEM_DISPLAY_BOTH               0x00B3
#define HIDD_USAGE_SYSTEM_DISPLAY_DUAL               0x00B4
#define HIDD_USAGE_SYSTEM_DISPLAY_TOGGLE             0x00B5
#define HIDD_USAGE_SYSTEM_DISPLAY_SWAP               0x00B6
#define HIDD_USAGE_SYSTEM_DISPLAY_AUTOSCALE          0x00B7
/* 0x00B8--0xFFFF Reserved */

/*
	Keyboard/Keypad (Page 0x07)
*/
/* 0x0000 Reserved (no event indicated) */
#define HIDD_USAGE_KEYBOARD_ERROR_ROLL_OVER          0x0001
#define HIDD_USAGE_KEYBOARD_PDST_FAIL                0x0002
#define HIDD_USAGE_KEYBOARD_ERROR_UNDEFINED          0x0003
#define HIDD_USAGE_KEYBOARD_A                        0x0004
#define HIDD_USAGE_KEYBOARD_A                        0x0004
#define HIDD_USAGE_KEYBOARD_B                        0x0005
#define HIDD_USAGE_KEYBOARD_C                        0x0006
#define HIDD_USAGE_KEYBOARD_D                        0x0007
#define HIDD_USAGE_KEYBOARD_E                        0x0008
#define HIDD_USAGE_KEYBOARD_F                        0x0009
#define HIDD_USAGE_KEYBOARD_G                        0x000A
#define HIDD_USAGE_KEYBOARD_H                        0x000B
#define HIDD_USAGE_KEYBOARD_I                        0x000C
#define HIDD_USAGE_KEYBOARD_J                        0x000D
#define HIDD_USAGE_KEYBOARD_K                        0x000E
#define HIDD_USAGE_KEYBOARD_L                        0x000F
#define HIDD_USAGE_KEYBOARD_M                        0x0010
#define HIDD_USAGE_KEYBOARD_N                        0x0011
#define HIDD_USAGE_KEYBOARD_O                        0x0012
#define HIDD_USAGE_KEYBOARD_P                        0x0013
#define HIDD_USAGE_KEYBOARD_Q                        0x0014
#define HIDD_USAGE_KEYBOARD_R                        0x0015
#define HIDD_USAGE_KEYBOARD_S                        0x0016
#define HIDD_USAGE_KEYBOARD_T                        0x0017
#define HIDD_USAGE_KEYBOARD_U                        0x0018
#define HIDD_USAGE_KEYBOARD_V                        0x0019
#define HIDD_USAGE_KEYBOARD_W                        0x001A
#define HIDD_USAGE_KEYBOARD_X                        0x001B
#define HIDD_USAGE_KEYBOARD_Y                        0x001C
#define HIDD_USAGE_KEYBOARD_Z                        0x001D
#define HIDD_USAGE_KEYBOARD_1                        0x001E /* HIDD_USAGE_KEYBOARD_EXCLAMATION */
#define HIDD_USAGE_KEYBOARD_2                        0x001F /* HIDD_USAGE_KEYBOARD_AT */
#define HIDD_USAGE_KEYBOARD_3                        0x0020 /* HIDD_USAGE_KEYBOARD_NUMBER_SIGN */
#define HIDD_USAGE_KEYBOARD_4                        0x0021 /* HIDD_USAGE_KEYBOARD_DOLLAR */
#define HIDD_USAGE_KEYBOARD_5                        0x0022 /* HIDD_USAGE_KEYBOARD_PERCENT */
#define HIDD_USAGE_KEYBOARD_6                        0x0023 /* HIDD_USAGE_KEYBOARD_ASCII_CIRCUM */
#define HIDD_USAGE_KEYBOARD_7                        0x0024 /* HIDD_USAGE_KEYBOARD_AMPERSAND */
#define HIDD_USAGE_KEYBOARD_8                        0x0025 /* HIDD_USAGE_KEYBOARD_ASTERISK */
#define HIDD_USAGE_KEYBOARD_9                        0x0026 /* HIDD_USAGE_KEYBOARD_PARENTHESIS_LEFT */
#define HIDD_USAGE_KEYBOARD_0                        0x0027 /* HIDD_USAGE_KEYBOARD_PARENTHESIS_RIGHT */
#define HIDD_USAGE_KEYBOARD_ENTER                    0x0028
#define HIDD_USAGE_KEYBOARD_ESCAPE                   0x0029
#define HIDD_USAGE_KEYBOARD_BACKSPACE                0x002A
#define HIDD_USAGE_KEYBOARD_TAB                      0x002B
#define HIDD_USAGE_KEYBOARD_SPACEBAR                 0x002C
#define HIDD_USAGE_KEYBOARD_MINUS                    0x002D /* HIDD_USAGE_KEYBOARD_UNDERSCORE */
#define HIDD_USAGE_KEYBOARD_EQUAL                    0x002E /* HIDD_USAGE_KEYBOARD_PLUS */
#define HIDD_USAGE_KEYBOARD_BRACKET_LEFT             0x002F /* HIDD_USAGE_KEYBOARD_BRACE_LEFT */
#define HIDD_USAGE_KEYBOARD_BRACKET_RIGHT            0x0030 /* HIDD_USAGE_KEYBOARD_BRACE_RIGHT */
#define HIDD_USAGE_KEYBOARD_BACKSLASH                0x0031 /* HIDD_USAGE_KEYBOARD_BAR */
#define HIDD_USAGE_KEYBOARD_NON_US_NUMSIGN           0x0032 /* HIDD_USAGE_KEYBOARD_ASCII_TILDE */
#define HIDD_USAGE_KEYBOARD_SEMICOLON                0x0033 /* HIDD_USAGE_KEYBOARD_COLON */
#define HIDD_USAGE_KEYBOARD_APOSTROPHE               0x0034 /* HIDD_USAGE_KEYBOARD_QUOTEDBL */
#define HIDD_USAGE_KEYBOARD_GRAVE                    0x0035 /* HIDD_USAGE_KEYBOARD_TILDE */
#define HIDD_USAGE_KEYBOARD_COMMA                    0x0036 /* HIDD_USAGE_KEYBOARD_LESS */
#define HIDD_USAGE_KEYBOARD_PERIOD                   0x0037 /* HIDD_USAGE_KEYBOARD_GREATER */
#define HIDD_USAGE_KEYBOARD_SLASH                    0x0038 /* HIDD_USAGE_KEYBOARD_QUESTION */
#define HIDD_USAGE_KEYBOARD_CAPS_LOCK                0x0039
#define HIDD_USAGE_KEYBOARD_F1                       0x003A
#define HIDD_USAGE_KEYBOARD_F2                       0x003B
#define HIDD_USAGE_KEYBOARD_F3                       0x003C
#define HIDD_USAGE_KEYBOARD_F4                       0x003D
#define HIDD_USAGE_KEYBOARD_F5                       0x003E
#define HIDD_USAGE_KEYBOARD_F6                       0x003F
#define HIDD_USAGE_KEYBOARD_F7                       0x0040
#define HIDD_USAGE_KEYBOARD_F8                       0x0041
#define HIDD_USAGE_KEYBOARD_F9                       0x0042
#define HIDD_USAGE_KEYBOARD_F10                      0x0043
#define HIDD_USAGE_KEYBOARD_F11                      0x0044
#define HIDD_USAGE_KEYBOARD_F12                      0x0045
#define HIDD_USAGE_KEYBOARD_PRINT_SCREEN             0x0046
#define HIDD_USAGE_KEYBOARD_SCROLL_LOCK              0x0047
#define HIDD_USAGE_KEYBOARD_PAUSE                    0x0048
#define HIDD_USAGE_KEYBOARD_INSERT                   0x0049
#define HIDD_USAGE_KEYBOARD_HOME                     0x004A
#define HIDD_USAGE_KEYBOARD_PAGE_UP                  0x004B
#define HIDD_USAGE_KEYBOARD_DELETE                   0x004C
#define HIDD_USAGE_KEYBOARD_END                      0x004D
#define HIDD_USAGE_KEYBOARD_PAGE_DOWN                0x004E
#define HIDD_USAGE_KEYBOARD_ARROW_RIGHT              0x004F
#define HIDD_USAGE_KEYBOARD_ARROW_LEFT               0x0050
#define HIDD_USAGE_KEYBOARD_ARROW_DOWN               0x0051
#define HIDD_USAGE_KEYBOARD_ARROW_UP                 0x0052
#define HIDD_USAGE_KEYBOARD_NUM_LOCK                 0x0053
#define HIDD_USAGE_KEYBOARD_KEYPAD_DIVIDE            0x0054
#define HIDD_USAGE_KEYBOARD_KEYPAD_MULTIPLY          0x0055
#define HIDD_USAGE_KEYBOARD_KEYPAD_SUBTRACT          0x0056
#define HIDD_USAGE_KEYBOARD_KEYPAD_ADD               0x0057
#define HIDD_USAGE_KEYBOARD_KEYPAD_ENTER             0x0058
#define HIDD_USAGE_KEYBOARD_KEYPAD_1                 0x0059 /* HIDD_USAGE_KEYBOARD_KEYPAD_END */
#define HIDD_USAGE_KEYBOARD_KEYPAD_2                 0x005A /* HIDD_USAGE_KEYBOARD_KEYPAD_ARROW_DOWN */
#define HIDD_USAGE_KEYBOARD_KEYPAD_3                 0x005B /* HIDD_USAGE_KEYBOARD_KEYPAD_PAGE_DOWN */
#define HIDD_USAGE_KEYBOARD_KEYPAD_4                 0x005C /* HIDD_USAGE_KEYBOARD_KEYPAD_ARROW_LEFT */
#define HIDD_USAGE_KEYBOARD_KEYPAD_5                 0x005D
#define HIDD_USAGE_KEYBOARD_KEYPAD_6                 0x005E /* HIDD_USAGE_KEYBOARD_KEYPAD_ARROW_RIGHT */
#define HIDD_USAGE_KEYBOARD_KEYPAD_7                 0x005F /* HIDD_USAGE_KEYBOARD_KEYPAD_HOME */
#define HIDD_USAGE_KEYBOARD_KEYPAD_8                 0x0060 /* HIDD_USAGE_KEYBOARD_KEYPAD_ARROW_UP */
#define HIDD_USAGE_KEYBOARD_KEYPAD_9                 0x0061 /* HIDD_USAGE_KEYBOARD_KEYPAD_PAGE_UP */
#define HIDD_USAGE_KEYBOARD_KEYPAD_0                 0x0062 /* HIDD_USAGE_KEYBOARD_KEYPAD_INSERT */
#define HIDD_USAGE_KEYBOARD_KEYPAD_PERIOD            0x0063 /* HIDD_USAGE_KEYBOARD_KEYPAD_DELETE */
#define HIDD_USAGE_KEYBOARD_NON_US_SLASH             0x0064 /* HIDD_USAGE_KEYBOARD_NON_US_BAR */
#define HIDD_USAGE_KEYBOARD_APPLICATION              0x0065
#define HIDD_USAGE_KEYBOARD_POWER                    0x0066
#define HIDD_USAGE_KEYBOARD_KEYPAD_EQUAL             0x0067
#define HIDD_USAGE_KEYBOARD_F13                      0x0068
#define HIDD_USAGE_KEYBOARD_F14                      0x0069
#define HIDD_USAGE_KEYBOARD_F15                      0x006A
#define HIDD_USAGE_KEYBOARD_F16                      0x006B
#define HIDD_USAGE_KEYBOARD_F17                      0x006C
#define HIDD_USAGE_KEYBOARD_F18                      0x006D
#define HIDD_USAGE_KEYBOARD_F19                      0x006E
#define HIDD_USAGE_KEYBOARD_F20                      0x006F
#define HIDD_USAGE_KEYBOARD_F21                      0x0070
#define HIDD_USAGE_KEYBOARD_F22                      0x0071
#define HIDD_USAGE_KEYBOARD_F23                      0x0072
#define HIDD_USAGE_KEYBOARD_F24                      0x0073
#define HIDD_USAGE_KEYBOARD_EXECUTE                  0x0074
#define HIDD_USAGE_KEYBOARD_HELP                     0x0075
#define HIDD_USAGE_KEYBOARD_MENU                     0x0076
#define HIDD_USAGE_KEYBOARD_SELECT                   0x0077
#define HIDD_USAGE_KEYBOARD_STOP                     0x0078
#define HIDD_USAGE_KEYBOARD_AGAIN                    0x0079
#define HIDD_USAGE_KEYBOARD_UNDO                     0x007A
#define HIDD_USAGE_KEYBOARD_CUT                      0x007B
#define HIDD_USAGE_KEYBOARD_COPY                     0x007C
#define HIDD_USAGE_KEYBOARD_PASTE                    0x007D
#define HIDD_USAGE_KEYBOARD_FIND                     0x007E
#define HIDD_USAGE_KEYBOARD_MUTE                     0x007F
#define HIDD_USAGE_KEYBOARD_VOLUME_UP                0x0080
#define HIDD_USAGE_KEYBOARD_VOLUME_DOWN              0x0081
#define HIDD_USAGE_KEYBOARD_LOCKING_CAPS_LOCK        0x0082
#define HIDD_USAGE_KEYBOARD_LOCKING_NUM_LOCK         0x0083
#define HIDD_USAGE_KEYBOARD_LOCKING_SCROLL_LOCK      0x0084
#define HIDD_USAGE_KEYBOARD_KEYPAD_COMMA             0x0085
#define HIDD_USAGE_KEYBOARD_KEYPAD_EQUAL_SIGN        0x0086
#define HIDD_USAGE_KEYBOARD_INTERNATIONAL1           0x0087
#define HIDD_USAGE_KEYBOARD_INTERNATIONAL2           0x0088
#define HIDD_USAGE_KEYBOARD_INTERNATIONAL3           0x0089
#define HIDD_USAGE_KEYBOARD_INTERNATIONAL4           0x008A
#define HIDD_USAGE_KEYBOARD_INTERNATIONAL5           0x008B
#define HIDD_USAGE_KEYBOARD_INTERNATIONAL6           0x008C
#define HIDD_USAGE_KEYBOARD_INTERNATIONAL7           0x008D
#define HIDD_USAGE_KEYBOARD_INTERNATIONAL8           0x008E
#define HIDD_USAGE_KEYBOARD_INTERNATIONAL9           0x008F
#define HIDD_USAGE_KEYBOARD_LANG1                    0x0090
#define HIDD_USAGE_KEYBOARD_LANG2                    0x0091
#define HIDD_USAGE_KEYBOARD_LANG3                    0x0092
#define HIDD_USAGE_KEYBOARD_LANG4                    0x0093
#define HIDD_USAGE_KEYBOARD_LANG5                    0x0094
#define HIDD_USAGE_KEYBOARD_LANG6                    0x0095
#define HIDD_USAGE_KEYBOARD_LANG7                    0x0096
#define HIDD_USAGE_KEYBOARD_LANG8                    0x0097
#define HIDD_USAGE_KEYBOARD_LANG9                    0x0098
#define HIDD_USAGE_KEYBOARD_ALT_ERASE                0x0099
#define HIDD_USAGE_KEYBOARD_SYSREQ                   0x009A
#define HIDD_USAGE_KEYBOARD_CANCEL                   0x009B
#define HIDD_USAGE_KEYBOARD_CLEAR                    0x009C
#define HIDD_USAGE_KEYBOARD_PRIOR                    0x009D
#define HIDD_USAGE_KEYBOARD_RETURN                   0x009E
#define HIDD_USAGE_KEYBOARD_SEPERATOR                0x009F
#define HIDD_USAGE_KEYBOARD_OUT                      0x00A0
#define HIDD_USAGE_KEYBOARD_OPER                     0x00A1
#define HIDD_USAGE_KEYBOARD_CLEAR_AGAIN              0x00A2
#define HIDD_USAGE_KEYBOARD_CLEARSEL_PROPS           0x00A3
#define HIDD_USAGE_KEYBOARD_EXSEL                    0x00A4
/* 0x00A5--0x00AF Reserved */
#define HIDD_USAGE_KEYBOARD_KEYPAD_00                0x00B0
#define HIDD_USAGE_KEYBOARD_KEYPAD_000               0x00B1
#define HIDD_USAGE_KEYBOARD_THOUSANDS_SEPERATOR      0x00B2
#define HIDD_USAGE_KEYBOARD_DECIMAL_SEPERATOR        0x00B3
#define HIDD_USAGE_KEYBOARD_CURRENCY_UNIT            0x00B4
#define HIDD_USAGE_KEYBOARD_CURRENCY_SUBUNIT         0x00B5
#define HIDD_USAGE_KEYBOARD_KEYPAD_PARENTHESIS_LEFT  0x00B6
#define HIDD_USAGE_KEYBOARD_KEYPAD_PARENTHESIS_RIGHT 0x00B7
#define HIDD_USAGE_KEYBOARD_KEYPAD_BRACE_LEFT        0x00B8
#define HIDD_USAGE_KEYBOARD_KEYPAD_BRACE_RIGHT       0x00B9
#define HIDD_USAGE_KEYBOARD_KEYPAD_TAB               0x00BA
#define HIDD_USAGE_KEYBOARD_KEYPAD_BACKSPACE         0x00BB
#define HIDD_USAGE_KEYBOARD_KEYPAD_A                 0x00BC
#define HIDD_USAGE_KEYBOARD_KEYPAD_B                 0x00BD
#define HIDD_USAGE_KEYBOARD_KEYPAD_C                 0x00BE
#define HIDD_USAGE_KEYBOARD_KEYPAD_D                 0x00BF
#define HIDD_USAGE_KEYBOARD_KEYPAD_E                 0x00C0
#define HIDD_USAGE_KEYBOARD_KEYPAD_F                 0x00C1
#define HIDD_USAGE_KEYBOARD_KEYPAD_XOR               0x00C2
#define HIDD_USAGE_KEYBOARD_KEYPAD_CIRCUMFLEX        0x00C3
#define HIDD_USAGE_KEYBOARD_KEYPAD_PERCENT           0x00C4
#define HIDD_USAGE_KEYBOARD_KEYPAD_LESS              0x00C5
#define HIDD_USAGE_KEYBOARD_KEYPAD_GREATER           0x00C6
#define HIDD_USAGE_KEYBOARD_KEYPAD_AMPERSAND         0x00C7
#define HIDD_USAGE_KEYBOARD_KEYPAD_AND               0x00C8
#define HIDD_USAGE_KEYBOARD_KEYPAD_BAR               0x00C9
#define HIDD_USAGE_KEYBOARD_KEYPAD_OR                0x00CA
#define HIDD_USAGE_KEYBOARD_KEYPAD_COLON             0x00CB
#define HIDD_USAGE_KEYBOARD_KEYPAD_NUMBER_SIGN       0x00CC
#define HIDD_USAGE_KEYBOARD_KEYPAD_SPACE             0x00CD
#define HIDD_USAGE_KEYBOARD_KEYPAD_AT                0x00CE
#define HIDD_USAGE_KEYBOARD_KEYPAD_EXCLAMATION       0x00CF
#define HIDD_USAGE_KEYBOARD_KEYPAD_MEMORY_STORE      0x00D0
#define HIDD_USAGE_KEYBOARD_KEYPAD_MEMORY_RECALL     0x00D1
#define HIDD_USAGE_KEYBOARD_KEYPAD_MEMORY_CLEAR      0x00D2
#define HIDD_USAGE_KEYBOARD_KEYPAD_MEMORY_ADD        0x00D3
#define HIDD_USAGE_KEYBOARD_KEYPAD_MEMORY_SUBTRACT   0x00D4
#define HIDD_USAGE_KEYBOARD_KEYPAD_MEMORY_MULTIPLY   0x00D5
#define HIDD_USAGE_KEYBOARD_KEYPAD_MEMORY_DIVIDE     0x00D6
#define HIDD_USAGE_KEYBOARD_KEYPAD_PLUS_MINUS        0x00D7
#define HIDD_USAGE_KEYBOARD_KEYPAD_CLEAR             0x00D8
#define HIDD_USAGE_KEYBOARD_KEYPAD_CLEAR_ENTRY       0x00D9
#define HIDD_USAGE_KEYBOARD_KEYPAD_BINARY            0x00DA
#define HIDD_USAGE_KEYBOARD_KEYPAD_OCTAL             0x00DB
#define HIDD_USAGE_KEYBOARD_KEYPAD_DECIMAL           0x00DC
#define HIDD_USAGE_KEYBOARD_KEYPAD_HEXADECIMAL       0x00DD
/* 0x00DE--0x00DF Reserved */
#define HIDD_USAGE_KEYBOARD_CONTROL_LEFT             0x00E0
#define HIDD_USAGE_KEYBOARD_SHIFT_LEFT               0x00E1
#define HIDD_USAGE_KEYBOARD_ALT_LEFT                 0x00E2
#define HIDD_USAGE_KEYBOARD_GUI_LEFT                 0x00E3
#define HIDD_USAGE_KEYBOARD_CONTROL_RIGHT            0x00E4
#define HIDD_USAGE_KEYBOARD_SHIFT_RIGHT              0x00E5
#define HIDD_USAGE_KEYBOARD_ALT_RIGHT                0x00E6
#define HIDD_USAGE_KEYBOARD_GUI_RIGHT                0x00E7
/* 0x00E8--0xFFFF Reserved */

/*
	LED (Page 0x08)
*/
/* #define HIDD_USAGE_UNDEFINED                         0x0000 */
#define HIDD_USAGE_NUM_LOCK                          0x0001
#define HIDD_USAGE_CAPS_LOCK                         0x0002
#define HIDD_USAGE_SCROLL_LOCK                       0x0003
/* 0x004E--0xFFFF Reserved */


/*
	Consumer (Page 0x0C)
*/
/* #define HIDD_USAGE_UNDEFINED                         0x0000 */
#define HIDD_USAGE_CONSUMER_CONTROL                  0x0001
#define HIDD_USAGE_NUMERIC_KEYPAD                    0x0002
#define HIDD_USAGE_PROGRAMMABLE_BUTTONS              0x0003
#define HIDD_USAGE_MICROPHONE                        0x0004
#define HIDD_USAGE_HEADPHONE                         0x0005
#define HIDD_USAGE_GRAPHIC_EQUALIZER                 0x0006
/* 0x0007--0x001F Reserved */
#define HIDD_USAGE_PLUS_10                           0x0020
#define HIDD_USAGE_PLUS_100                          0x0021
#define HIDD_USAGE_AM_PM                             0x0022
/* 0x0023--0x002F Reserved */
#define HIDD_USAGE_POWER                             0x0030
#define HIDD_USAGE_RESET                             0x0031
#define HIDD_USAGE_SLEEP                             0x0032
#define HIDD_USAGE_SLEEP_AFTER                       0x0033
#define HIDD_USAGE_SLEEP_MODE                        0x0034
#define HIDD_USAGE_ILLUMINATION                      0x0035
#define HIDD_USAGE_FUNCTION_BUTTONS                  0x0036
/* 0x0037--0x003F Reserved */
#define HIDD_USAGE_MENU                              0x0040
#define HIDD_USAGE_MENU_PICK                         0x0041
#define HIDD_USAGE_MENU_UP                           0x0042
#define HIDD_USAGE_MENU_DOWN                         0x0043
#define HIDD_USAGE_MENU_LEFT                         0x0044
#define HIDD_USAGE_MENU_RIGHT                        0x0045
#define HIDD_USAGE_MENU_ESCAPE                       0x0046
#define HIDD_USAGE_MENU_VALUE_INCREASE               0x0047
#define HIDD_USAGE_MENU_VALUE_DECREASE               0x0048
/* 0x0049--0x005F Reserved */
#define HIDD_USAGE_DATA_ON_SCREEN                    0x0060
#define HIDD_USAGE_CLOSED_CAPTION                    0x0061
#define HIDD_USAGE_CLOSED_CAPTION_SELECT             0x0062
#define HIDD_USAGE_VCR_TV                            0x0063
#define HIDD_USAGE_BROADCAST_MODE                    0x0064
#define HIDD_USAGE_SNAPSHOT                          0x0065
#define HIDD_USAGE_STILL                             0x0066
/* 0x0067--0x007F Reserved */
#define HIDD_USAGE_SELECTION                         0x0080
#define HIDD_USAGE_ASSIGN_SELECTION                  0x0081
#define HIDD_USAGE_MODE_STEP                         0x0082
#define HIDD_USAGE_RECALL_LAST                       0x0082
#define HIDD_USAGE_ENTER_CHANNEL                     0x0084
#define HIDD_USAGE_ORDER_MOVIE                       0x0085
#define HIDD_USAGE_CHANNEL                           0x0086
#define HIDD_USAGE_MEDIA_SELECTION                   0x0087
#define HIDD_USAGE_MEDIA_SELECT_COMPUTER             0x0088
#define HIDD_USAGE_MEDIA_SELECT_TV                   0x0089
#define HIDD_USAGE_MEDIA_SELECT_WWW                  0x008A
#define HIDD_USAGE_MEDIA_SELECT_DVD                  0x008B
#define HIDD_USAGE_MEDIA_SELECT_TELEPHONE            0x008C
#define HIDD_USAGE_MEDIA_SELECT_PROGRAM_GUIDE        0x008D
#define HIDD_USAGE_MEDIA_SELECT_VIDEO_PHONE          0x008E
#define HIDD_USAGE_MEDIA_SELECT_GAMES                0x008F
#define HIDD_USAGE_MEDIA_SELECT_MESSAGES             0x0090
#define HIDD_USAGE_MEDIA_SELECT_CD                   0x0091
#define HIDD_USAGE_MEDIA_SELECT_VCR                  0x0092
#define HIDD_USAGE_MEDIA_SELECT_TUNER                0x0093
#define HIDD_USAGE_QUIT                              0x0094
#define HIDD_USAGE_HELP                              0x0095
#define HIDD_USAGE_MEDIA_SELECT_TAPE                 0x0096
#define HIDD_USAGE_MEDIA_SELECT_CABLE                0x0097
#define HIDD_USAGE_MEDIA_SELECT_SATELLITE            0x0098
#define HIDD_USAGE_MEDIA_SELECT_SECURITY             0x0099
#define HIDD_USAGE_MEDIA_SELECT_HOME                 0x009A
#define HIDD_USAGE_MEDIA_SELECT_CALL                 0x009B
#define HIDD_USAGE_CHANNEL_INCREMENT                 0x009C
#define HIDD_USAGE_CHANNEL_DECREMENT                 0x009D
#define HIDD_USAGE_MEDIA_SELECT_SAP                  0x009E
/* 0x009F Reserved */
#define HIDD_USAGE_VCR_PLUS                          0x00A0
#define HIDD_USAGE_ONCE                              0x00A1
#define HIDD_USAGE_DAILY                             0x00A2
#define HIDD_USAGE_WEEKLY                            0x00A3
#define HIDD_USAGE_MONTHLY                           0x00A4
/* 0x00A5--0x00AF Reserved */
#define HIDD_USAGE_PLAY                              0x00B0
#define HIDD_USAGE_PAUSE                             0x00B1
#define HIDD_USAGE_RECORD                            0x00B2
#define HIDD_USAGE_FAST_FORWARD                      0x00B3
#define HIDD_USAGE_REWIND                            0x00B4
#define HIDD_USAGE_SCAN_NEXT_TRACK                   0x00B5
#define HIDD_USAGE_SCAN_PREVIOUS_TRACK               0x00B6
#define HIDD_USAGE_STOP                              0x00B7
#define HIDD_USAGE_EJECT                             0x00B8
#define HIDD_USAGE_RANDOM_PLAY                       0x00B9
#define HIDD_USAGE_SELEC_DISC                        0x00BA
#define HIDD_USAGE_ENTER_DISC                        0x00BB
#define HIDD_USAGE_REPEAT                            0x00BC
#define HIDD_USAGE_TRACKING                          0x00BD
#define HIDD_USAGE_TRACK_NORMAL                      0x00BE
#define HIDD_USAGE_SLOW_TRACKING                     0x00BF
#define HIDD_USAGE_FRAME_FORWARD                     0x00C0
#define HIDD_USAGE_FRAME_BACKWARD                    0x00C1
#define HIDD_USAGE_MARK                              0x00C2
#define HIDD_USAGE_CLEAR_MARK                        0x00C3
#define HIDD_USAGE_REPEAT_FROM_MARK                  0x00C4
#define HIDD_USAGE_RETURN_TO_MARK                    0x00C5
#define HIDD_USAGE_SEARCH_MARK_FORWARD               0x00C6
#define HIDD_USAGE_SEARCH_MARK_BACKWARDS             0x00C7
#define HIDD_USAGE_COUNTER_RESET                     0x00C8
#define HIDD_USAGE_SHOW_COUNTER                      0x00C9
#define HIDD_USAGE_TRACKING_INCREMENT                0x00CA
#define HIDD_USAGE_TRACKING_DECREMENT                0x00CB
#define HIDD_USAGE_STOP_EJECT                        0x00CC
#define HIDD_USAGE_PLAY_PAUSE                        0x00CD
#define HIDD_USAGE_PLAY_SKIP                         0x00CE
/* 0x00CF--0x00DF Reserved */
#define HIDD_USAGE_VOLUME                            0x00E0
#define HIDD_USAGE_BALANCE                           0x00E1
#define HIDD_USAGE_MUTE                              0x00E2
#define HIDD_USAGE_BASS                              0x00E3
#define HIDD_USAGE_TREBLE                            0x00E4
#define HIDD_USAGE_BASS_BOOST                        0x00E5
#define HIDD_USAGE_SURROUND_MODE                     0x00E6
#define HIDD_USAGE_LOUDNESS                          0x00E7
#define HIDD_USAGE_MPX                               0x00E8
#define HIDD_USAGE_VOLUME_INCREMENT                  0x00E9
#define HIDD_USAGE_VOLUME_DECREMENT                  0x00EA
/* 0x00EB--0x00EF Reserved */
#define HIDD_USAGE_PLAYBACK_SPEED                    0x00F1
#define HIDD_USAGE_STANDARD_PLAY                     0x00F2
#define HIDD_USAGE_STANDARD_LONG_PLAY                0x00F3
#define HIDD_USAGE_STANDARD_EXTENDED_PLAY            0x00F4
#define HIDD_USAGE_STANDARD_SLOW                     0x00F5
/* 0x00F6--0x00FF Reserved */
#define HIDD_USAGE_FAN_ENABLE                        0x0100
#define HIDD_USAGE_FAN_SPEED                         0x0101
#define HIDD_USAGE_LIGHT_ENABLE                      0x0102
#define HIDD_USAGE_LIGHT_ILLUMINATION_LEVEL          0x0103
#define HIDD_USAGE_CLIMATE_CONTROL_ENABLE            0x0104
#define HIDD_USAGE_ROOM_TEMPERATURE                  0x0105
#define HIDD_USAGE_SECURITY_ENABLE                   0x0106
#define HIDD_USAGE_FIRE_ALARM                        0x0107
#define HIDD_USAGE_POLICE_ALARM                      0x0108
#define HIDD_USAGE_PROXIMITY                         0x0109
#define HIDD_USAGE_MOTION                            0x010A
#define HIDD_USAGE_DURESS_ALARM                      0x010B
#define HIDD_USAGE_HOLDUP_ALARM                      0x010C
#define HIDD_USAGE_MEDICAL_ALARM                     0x010D
/* 0x010E--0x014F Reserved */
#define HIDD_USAGE_BALANCE_RIGHT                     0x0150
#define HIDD_USAGE_BALANCE_LEFT                      0x0151
#define HIDD_USAGE_BASS_INCREMENT                    0x0152
#define HIDD_USAGE_BASS_DECREMENT                    0x0153
#define HIDD_USAGE_TREBLE_INCREMENT                  0x0154
#define HIDD_USAGE_TREBLE_DECREMENT                  0x0155
/* 0x0156--0x015F Reserved */
#define HIDD_USAGE_SPEAKER_SYSTEM                    0x0160
#define HIDD_USAGE_CHANNEL_LEFT                      0x0161
#define HIDD_USAGE_CHANNEL_RIGHT                     0x0162
#define HIDD_USAGE_CHANNEL_CENTRE                    0x0163
#define HIDD_USAGE_CHANNEL_FRONT                     0x0164
#define HIDD_USAGE_CHANNEL_CENTER_FRONT              0x0165
#define HIDD_USAGE_CHANNEL_SIDE                      0x0166
#define HIDD_USAGE_CHANNEL_SURROUND                  0x0167
#define HIDD_USAGE_CHANNEL_LOW_FREQ_ENHANCE          0x0168
#define HIDD_USAGE_CHANNEL_TOP                       0x0169
#define HIDD_USAGE_CHANNEL_UNKNOWN                   0x016A
/* 0x016B--0x016F Reserved */
#define HIDD_USAGE_SUB_CHANNEL                       0x0170
#define HIDD_USAGE_SUB_CHANNEL_INCREMENT             0x0171
#define HIDD_USAGE_SUB_CHANNEL_DECREMENT             0x0172
#define HIDD_USAGE_ALT_AUDIO_INCREMENT               0x0173
#define HIDD_USAGE_ALT_AUDIO_DECREMENT               0x0174
/* 0x0175--0x017F Reserved */
#define HIDD_USAGE_APP_LAUNCH_BUTTONS                0x0180
#define HIDD_USAGE_AL_CONFIG_TOOL                    0x0181
#define HIDD_USAGE_AL_PROG_BUTTON_CONFIG             0x0182
#define HIDD_USAGE_AL_CONSUMER_CTRL_CONFIG           0x0183
#define HIDD_USAGE_AL_WORD_PROCESSOR                 0x0184
#define HIDD_USAGE_AL_TEXT_EDITOR                    0x0185
#define HIDD_USAGE_AL_SPREADSHEET                    0x0186
#define HIDD_USAGE_AL_GRAPHICS_EDITOR                0x0187
#define HIDD_USAGE_AL_PRESENTATION                   0x0188
#define HIDD_USAGE_AL_DATABASE                       0x0189
#define HIDD_USAGE_AL_EMAIL_READER                   0x018A
#define HIDD_USAGE_AL_NEWSREADER                     0x018B
#define HIDD_USAGE_AL_VOICEMAIL                      0x018C
#define HIDD_USAGE_AL_CONTACTS                       0x018D
#define HIDD_USAGE_AL_CALENDAR                       0x018E
#define HIDD_USAGE_AL_TASK                           0x018F
#define HIDD_USAGE_AL_LOG                            0x0190
#define HIDD_USAGE_AL_FINANCE                        0x0191
#define HIDD_USAGE_AL_CALCULATOR                     0x0192
#define HIDD_USAGE_AL_AV_CAPTURE_PLAYBACK            0x0193
#define HIDD_USAGE_AL_LOCAL_BROWSER                  0x0194
#define HIDD_USAGE_AL_LAN_WAN_BROWSER                0x0195
#define HIDD_USAGE_AL_INTERNET_BROWSER               0x0196
#define HIDD_USAGE_AL_REMOTE_NETWORKING              0x0197
#define HIDD_USAGE_AL_NETWORK_CONFERENCE             0x0198
#define HIDD_USAGE_AL_NETWORK_CHAT                   0x0199
#define HIDD_USAGE_AL_TELEPHONY                      0x019A
#define HIDD_USAGE_AL_LOGON                          0x019B
#define HIDD_USAGE_AL_LOGOFF                         0x019C
#define HIDD_USAGE_AL_LOGON_LOGOFF                   0x019D
#define HIDD_USAGE_AL_TERMINAL_LOCK                  0x019E
#define HIDD_USAGE_AL_CONTROL_PANEL                  0x019F
#define HIDD_USAGE_AL_COMMAND_LINE                   0x01A0
#define HIDD_USAGE_AL_PROCESS                        0x01A1
#define HIDD_USAGE_AL_SELECT_TASK                    0x01A2
#define HIDD_USAGE_AL_NEXT_TASK                      0x01A3
#define HIDD_USAGE_AL_PREVIOUS_TASK                  0x01A4
#define HIDD_USAGE_AL_PREEMPTIVE_HALT_TASK           0x01A5
#define HIDD_USAGE_AL_INTEGRATED_HELP_CENTER         0x01A6
#define HIDD_USAGE_AL_DOCUMENTS                      0x01A7
#define HIDD_USAGE_AL_THESAURUS                      0x01A8
#define HIDD_USAGE_AL_DICTIONARY                     0x01A9
#define HIDD_USAGE_AL_DESKTOP                        0x01AA
#define HIDD_USAGE_AL_SPELL_CHECK                    0x01AB
#define HIDD_USAGE_AL_GRAMMER_CHECK                  0x01AC
#define HIDD_USAGE_AL_WIRELESS_STATUS                0x01AD
#define HIDD_USAGE_AL_KEYBOARD_LAYOUT                0x01AE
#define HIDD_USAGE_AL_VIRUS_PROTECTION               0x01AF
#define HIDD_USAGE_AL_ENCRYPTION                     0x01B0
#define HIDD_USAGE_AL_SCREEN_SAVER                   0x01B1
#define HIDD_USAGE_AL_ALARMS                         0x01B2
#define HIDD_USAGE_AL_CLOCK                          0x01B3
#define HIDD_USAGE_AL_FILE_BROWSER                   0x01B4
#define HIDD_USAGE_AL_POWER_STATUS                   0x01B5
#define HIDD_USAGE_AL_IMAGE_BROWSER                  0x01B6
#define HIDD_USAGE_AL_AUDIO_BROWSER                  0x01B7
#define HIDD_USAGE_AL_MOVIE_BROWSER                  0x01B8
#define HIDD_USAGE_AL_DIGITAL_RIGHTS_MANAGER         0x01B9
#define HIDD_USAGE_AL_DIGITAL_WALLET                 0x01BA
/* 0x01BB Reserved */
#define HIDD_USAGE_AL_INSTANT_MESSAGING              0x01BC
#define HIDD_USAGE_AL_OEM_FEATURES                   0x01BD
#define HIDD_USAGE_AL_OEM_HELP                       0x01BE
#define HIDD_USAGE_AL_ONLINE_COMMUNITY               0x01BF
#define HIDD_USAGE_AL_ENTERTAINMENT_BROWSER          0x01C0
#define HIDD_USAGE_AL_ONLINE_SHOPPING_BROWSER        0x01C1
#define HIDD_USAGE_AL_SMARTCARD_INFORMATION          0x01C2
#define HIDD_USAGE_AL_FINANCE_BROWSER                0x01C3
#define HIDD_USAGE_AL_NEWS_BROWSER                   0x01C4
#define HIDD_USAGE_AL_ONLINE_ACTIVITY_BROWSER        0x01C5
#define HIDD_USAGE_AL_SEARCH_BROWSER                 0x01C6
#define HIDD_USAGE_AL_AUDIO_PLAYER                   0x01C7
/* 0x01C8--0x01FF Reserved */
#define HIDD_USAGE_GENERIC_APP_CONTROLS              0x0200
#define HIDD_USAGE_AC_NEW                            0x0201
#define HIDD_USAGE_AC_OPEN                           0x0202
#define HIDD_USAGE_AC_CLOSE                          0x0203
#define HIDD_USAGE_AC_EXIT                           0x0204
#define HIDD_USAGE_AC_MAXIMIZE                       0x0205
#define HIDD_USAGE_AC_MINIMIZE                       0x0206
#define HIDD_USAGE_AC_SAVE                           0x0207
#define HIDD_USAGE_AC_PRINT                          0x0208
#define HIDD_USAGE_AC_PROPERTIES                     0x0209
/* 0x020A--0x0219 Undefined in HID specification */
#define HIDD_USAGE_AC_UNDO                           0x021A
#define HIDD_USAGE_AC_COPY                           0x021B
#define HIDD_USAGE_AC_CUT                            0x021C
#define HIDD_USAGE_AC_PASTE                          0x021D
#define HIDD_USAGE_AC_SELECT_ALL                     0x021E
#define HIDD_USAGE_AC_FIND                           0x021F
#define HIDD_USAGE_AC_FIND_AND_REPLACE               0x0220
#define HIDD_USAGE_AC_SEARCH                         0x0221
#define HIDD_USAGE_AC_GO_TO                          0x0222
#define HIDD_USAGE_AC_HOME                           0x0223
#define HIDD_USAGE_AC_BACK                           0x0224
#define HIDD_USAGE_AC_FORWARD                        0x0225
#define HIDD_USAGE_AC_STOP                           0x0226
#define HIDD_USAGE_AC_REFRESH                        0x0227
#define HIDD_USAGE_AC_PREVIOUS_LINK                  0x0228
#define HIDD_USAGE_AC_NEXT_LINK                      0x0229
#define HIDD_USAGE_AC_BOOKMARKS                      0x022A
#define HIDD_USAGE_AC_HISTORY                        0x022B
#define HIDD_USAGE_AC_SUBSCRIPTIONS                  0x022C
#define HIDD_USAGE_AC_ZOOM_IN                        0x022D
#define HIDD_USAGE_AC_ZOOM_OUT                       0x022E
#define HIDD_USAGE_AC_ZOOM                           0x022F
#define HIDD_USAGE_AC_FULL_SCREEN_VIEW               0x0230
#define HIDD_USAGE_AC_NORMAL_VIEW                    0x0231
#define HIDD_USAGE_AC_VIEW_TOGGLE                    0x0232
#define HIDD_USAGE_AC_SCROLL_UP                      0x0233
#define HIDD_USAGE_AC_SCROLL_DOWN                    0x0234
#define HIDD_USAGE_AC_SCROLL                         0x0235
#define HIDD_USAGE_AC_PAN_LEFT                       0x0236
#define HIDD_USAGE_AC_PAN_RIGHT                      0x0237
#define HIDD_USAGE_AC_PAN                            0x0238
#define HIDD_USAGE_AC_NEW_WINDOW                     0x0239
#define HIDD_USAGE_AC_TILE_HORIZONTALLY              0x023A
#define HIDD_USAGE_AC_TILE_VERTICALLY                0x023B
#define HIDD_USAGE_AC_FORMAT                         0x023C
#define HIDD_USAGE_AC_EDIT                           0x023D
#define HIDD_USAGE_AC_BOLD                           0x023E
#define HIDD_USAGE_AC_ITALICS                        0x023F
#define HIDD_USAGE_AC_UNDERLINE                      0x0240
#define HIDD_USAGE_AC_STRIKETHROUGH                  0x0241
#define HIDD_USAGE_AC_SUBSCRIPT                      0x0242
#define HIDD_USAGE_AC_SUPERSCRIPT                    0x0243
#define HIDD_USAGE_AC_ALL_CAPS                       0x0244
#define HIDD_USAGE_AC_ROTATE                         0x0245
#define HIDD_USAGE_AC_RESIZE                         0x0246
#define HIDD_USAGE_AC_FLIP_HORIZONTAL                0x0247
#define HIDD_USAGE_AC_FLIP_VERTICAL                  0x0248
#define HIDD_USAGE_AC_MIRROR_HORIZONTAL              0x0249
#define HIDD_USAGE_AC_MIRROR_VERTICAL                0x024A
#define HIDD_USAGE_AC_FONT_SELECT                    0x024B
#define HIDD_USAGE_AC_FONT_COLOR                     0x024C
#define HIDD_USAGE_AC_FONT_SIZE                      0x024D
#define HIDD_USAGE_AC_JUSTIFY_LEFT                   0x024E
#define HIDD_USAGE_AC_JUSTIFY_CENTER_H               0x024F
#define HIDD_USAGE_AC_JUSTIFY_RIGHT                  0x0250
#define HIDD_USAGE_AC_JUSTIFY_BLOCK_H                0x0251
#define HIDD_USAGE_AC_JUSTIFY_TOP                    0x0252
#define HIDD_USAGE_AC_JUSTIFY_CENTER_V               0x0253
#define HIDD_USAGE_AC_JUSTIFY_BOTTOM                 0x0254
#define HIDD_USAGE_AC_JUSTIFY_BLOCK_V                0x0255
#define HIDD_USAGE_AC_INDENT_DECREASE                0x0256
#define HIDD_USAGE_AC_INDENT_INCREASE                0x0257
#define HIDD_USAGE_AC_NUMBERED_LIST                  0x0258
#define HIDD_USAGE_AC_RESTART_NUMBERING              0x0259
#define HIDD_USAGE_AC_BULLETED_LIST                  0x025A
#define HIDD_USAGE_AC_PROMOTE                        0x025B
#define HIDD_USAGE_AC_DEMOTE                         0x025C
#define HIDD_USAGE_AC_YES                            0x025D
#define HIDD_USAGE_AC_NO                             0x025E
#define HIDD_USAGE_AC_CANCEL                         0x025F
#define HIDD_USAGE_AC_CATALOG                        0x0260
#define HIDD_USAGE_AC_BUY                            0x0261
#define HIDD_USAGE_AC_ADD_TO_CART                    0x0262
#define HIDD_USAGE_AC_EXPAND                         0x0263
#define HIDD_USAGE_AC_EXPAND_ALL                     0x0264
#define HIDD_USAGE_AC_COLLAPSE                       0x0265
#define HIDD_USAGE_AC_COLLAPSE_ALL                   0x0266
#define HIDD_USAGE_AC_PRINT_PREVIEW                  0x0267
#define HIDD_USAGE_AC_PASTE_SPECIAL                  0x0268
#define HIDD_USAGE_AC_INSERT_MODE                    0x0269
#define HIDD_USAGE_AC_DELETE                         0x026A
#define HIDD_USAGE_AC_LOCK                           0x026B
#define HIDD_USAGE_AC_UNLOCK                         0x026C
#define HIDD_USAGE_AC_PROTECT                        0x026D
#define HIDD_USAGE_AC_UNPROTECT                      0x026E
#define HIDD_USAGE_AC_ATTACH_COMMENT                 0x026F
#define HIDD_USAGE_AC_DELETE_COMMENT                 0x0270
#define HIDD_USAGE_AC_VIEW_COMMENT                   0x0271
#define HIDD_USAGE_AC_SELECT_WORD                    0x0272
#define HIDD_USAGE_AC_SELECT_SENTENCE                0x0273
#define HIDD_USAGE_AC_SELECT_PARAGRAPH               0x0274
#define HIDD_USAGE_AC_SELECT_COLUMN                  0x0275
#define HIDD_USAGE_AC_SELECT_ROW                     0x0276
#define HIDD_USAGE_AC_SELECT_TABLE                   0x0277
#define HIDD_USAGE_AC_SELECT_OBJECT                  0x0278
#define HIDD_USAGE_AC_REDO                           0x0279
#define HIDD_USAGE_AC_SORT                           0x027A
#define HIDD_USAGE_AC_SORT_ASCENDING                 0x027B
#define HIDD_USAGE_AC_SORT_DESCENDING                0x027C
#define HIDD_USAGE_AC_FILTER                         0x027D
#define HIDD_USAGE_AC_SET_CLOCK                      0x027E
#define HIDD_USAGE_AC_VIEW_CLOCK                     0x027F
#define HIDD_USAGE_AC_SELECT_TIME_ZONE               0x0280
#define HIDD_USAGE_AC_EDIT_TIME_ZONES                0x0281
#define HIDD_USAGE_AC_SET_ALARM                      0x0282
#define HIDD_USAGE_AC_CLEAR_ALARM                    0x0283
#define HIDD_USAGE_AC_SNOOZE_ALARM                   0x0284
#define HIDD_USAGE_AC_RESET_ALARM                    0x0285
#define HIDD_USAGE_AC_SYNCHRONIZE                    0x0286
#define HIDD_USAGE_AC_SEND_RECEIVE                   0x0287
#define HIDD_USAGE_AC_SEND_TO                        0x0288
#define HIDD_USAGE_AC_REPLY                          0x0289
#define HIDD_USAGE_AC_REPLY_ALL                      0x028A
#define HIDD_USAGE_AC_FORWARD_MSG                    0x028B
#define HIDD_USAGE_AC_SEND                           0x028C
#define HIDD_USAGE_AC_ATTACH_FILE                    0x028D
#define HIDD_USAGE_AC_UPLOAD                         0x028E
#define HIDD_USAGE_AC_DOWNLOAD                       0x028F
#define HIDD_USAGE_AC_SET_BORDERS                    0x0290
#define HIDD_USAGE_AC_INSERT_ROW                     0x0291
#define HIDD_USAGE_AC_INSERT_COLUMN                  0x0292
#define HIDD_USAGE_AC_INSERT_FILE                    0x0293
#define HIDD_USAGE_AC_INSERT_PICTURE                 0x0294
#define HIDD_USAGE_AC_INSERT_OBJECT                  0x0295
#define HIDD_USAGE_AC_INSERT_SYMBOL                  0x0296
#define HIDD_USAGE_AC_SAVE_AND_CLOSE                 0x0297
#define HIDD_USAGE_AC_RENAME                         0x0298
#define HIDD_USAGE_AC_MERGE                          0x0299
#define HIDD_USAGE_AC_SPLIT                          0x029A
#define HIDD_USAGE_AC_DISTRIBUTE_HORIZONTALLY        0x029B
#define HIDD_USAGE_AC_DISTRIBUTE_VERTICALLY          0x029C
/* 0x029D--0xFFFF Reserved */

/*
	Digitizer (Page 0x0D)
*/
/* #define HIDD_USAGE_UNDEFINED                         0x0000 */
#define HIDD_USAGE_DIGITIZER                         0x0001
#define HIDD_USAGE_PEN                               0x0002
#define HIDD_USAGE_LIGHT_PEN                         0x0003
#define HIDD_USAGE_TOUCH_SCREEN                      0x0004
#define HIDD_USAGE_TOUCH_PAD                         0x0005
#define HIDD_USAGE_WHITE_BOARD                       0x0006
#define HIDD_USAGE_COORD_MEASURE                     0x0007
#define HIDD_USAGE_3D_DIGITIZER                      0x0008
#define HIDD_USAGE_STEREO_PLOTTER                    0x0009
#define HIDD_USAGE_ARTICULATED_ARM                   0x000A
#define HIDD_USAGE_ARMATURE                          0x000B
#define HIDD_USAGE_MULTIPOINT_DIGITIZER              0x000C
#define HIDD_USAGE_FREE_SPACE_WAND                   0x000D
/* 0x000E--0x001F Reserved */
#define HIDD_USAGE_STYLUS                            0x0020
#define HIDD_USAGE_PUCK                              0x0021
#define HIDD_USAGE_FINGER                            0x0022
/* 0x0023--0x002F Reserved */
#define HIDD_USAGE_TABLET_FUNC_KEYS                  0x0039
#define HIDD_USAGE_PROGRAM_CHANGE_KEYS               0x003A
#define HIDD_USAGE_TIP_SWITCH                        0x0042
/* 0x0047--0xFFFF Reserved */

#endif /* __HIDD_USAGE_TABLE_INCLUDED */

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/lib/hiddi/public/sys/hidut.h $ $Rev: 803445 $")
#endif