/*
 * $QNXLicenseC:
 * Copyright 2016, QNX Software Systems.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You
 * may not reproduce, modify or distribute this software except in
 * compliance with the License. You may obtain a copy of the License
 * at: http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTIES OF ANY KIND, either express or implied.
 *
 * This file may contain contributions from others, either as
 * contributors under the License or as licensors under other terms.
 * Please review this entire file for other proprietary rights or license
 * notices, as well as the QNX Development Suite License Guide at
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */



/*
 *
 *  keycodes.h   QNX keycodes
 *

 *
 */

#ifndef __KEYCODES_H_INCLUDED
#define __KEYCODES_H_INCLUDED

#ifndef UNICODE_BASIC_LATIN
#define UNICODE_BASIC_LATIN
#endif

#ifndef UNICODE_LATIN_1_SUPPLEMENT
#define UNICODE_LATIN_1_SUPPLEMENT
#endif

#ifndef UNICODE_COMBINING_DIACRITICAL_MARKS
#define UNICODE_COMBINING_DIACRITICAL_MARKS
#endif

#ifndef UNICODE_PRIVATE_USE_AREA
#define UNICODE_PRIVATE_USE_AREA
#endif

#ifndef _UNICODE_H_INCLUDED
#include <unicode.h>
#endif

/*
 * Keyboard modifiers
 */
#define KEYMODBIT_SHIFT                                         0
#define KEYMODBIT_CTRL                                          1
#define KEYMODBIT_ALT                                           2
#define KEYMODBIT_ALTGR                                         3
#define KEYMODBIT_SHL3                                          4
#define KEYMODBIT_MOD6                                          5
#define KEYMODBIT_MOD7                                          6
#define KEYMODBIT_MOD8                                          7

#define KEYMODBIT_SHIFT_LOCK                                    8
#define KEYMODBIT_CTRL_LOCK                                     9
#define KEYMODBIT_ALT_LOCK                                      10
#define KEYMODBIT_ALTGR_LOCK                                    11
#define KEYMODBIT_SHL3_LOCK                                     12
#define KEYMODBIT_MOD6_LOCK                                     13
#define KEYMODBIT_MOD7_LOCK                                     14
#define KEYMODBIT_MOD8_LOCK                                     15

#define KEYMODBIT_CAPS_LOCK                                     16
#define KEYMODBIT_NUM_LOCK                                      17
#define KEYMODBIT_SCROLL_LOCK                                   18

#define KEYMOD_SHIFT                                            (1 << KEYMODBIT_SHIFT)
#define KEYMOD_CTRL                                             (1 << KEYMODBIT_CTRL)
#define KEYMOD_ALT                                              (1 << KEYMODBIT_ALT)
#define KEYMOD_ALTGR                                            (1 << KEYMODBIT_ALTGR)
#define KEYMOD_SHL3                                             (1 << KEYMODBIT_SHL3)
#define KEYMOD_MOD6                                             (1 << KEYMODBIT_MOD6)
#define KEYMOD_MOD7                                             (1 << KEYMODBIT_MOD7)
#define KEYMOD_MOD8                                             (1 << KEYMODBIT_MOD8)

#define KEYMOD_SHIFT_LOCK                                       (1 << KEYMODBIT_SHIFT_LOCK)
#define KEYMOD_CTRL_LOCK                                        (1 << KEYMODBIT_CTRL_LOCK)
#define KEYMOD_ALT_LOCK                                         (1 << KEYMODBIT_ALT_LOCK)
#define KEYMOD_ALTGR_LOCK                                       (1 << KEYMODBIT_ALTGR_LOCK)
#define KEYMOD_SHL3_LOCK                                        (1 << KEYMODBIT_SHL3_LOCK)
#define KEYMOD_MOD6_LOCK                                        (1 << KEYMODBIT_MOD6_LOCK)
#define KEYMOD_MOD7_LOCK                                        (1 << KEYMODBIT_MOD7_LOCK)
#define KEYMOD_MOD8_LOCK                                        (1 << KEYMODBIT_MOD8_LOCK)

#define KEYMOD_CAPS_LOCK                                        (1 << KEYMODBIT_CAPS_LOCK)
#define KEYMOD_NUM_LOCK                                         (1 << KEYMODBIT_NUM_LOCK)
#define KEYMOD_SCROLL_LOCK                                      (1 << KEYMODBIT_SCROLL_LOCK)

/*
 * Keyboard flags
 */
#define KEY_DOWN                                                0x00000001      /* Key was pressed down */
#define KEY_REPEAT                                              0x00000002      /* Key was repeated */
#define KEY_SCAN_VALID                                          0x00000020      /* Scancode is valid */
#define KEY_SYM_VALID                                           0x00000040      /* Key symbol is valid */
#define KEY_CAP_VALID                                           0x00000080      /* Key cap is valid */
#define	KEY_SYM_VALID_EX										0x00000100		/* Key symbol is valid extended */
#define KEY_MAPPING_CHANGED										0x20000000
#define KEY_DEAD                                                0x40000000      /* Key symbol is a DEAD key */
#define KEY_OEM_CAP                                             0x80000000      /* Key cap is an OEM scan code from keyboard */

/*
 * Keyboard Indicators
 */
#define KEYIND_SCROLL_LOCK                                      0x01
#define KEYIND_NUM_LOCK                                         0x02
#define KEYIND_CAPS_LOCK                                        0x04


/*
 * Keyboard codes for Key caps and Key symbols
 */
#define KEYCODE_PC_KEYS                                         UNICODE_PRIVATE_USE_AREA_FIRST + 0x1000

#define KEYCODE_PAUSE                                           (KEYCODE_PC_KEYS + 0x13)
#define KEYCODE_SCROLL_LOCK                                     (KEYCODE_PC_KEYS + 0x14)
#define KEYCODE_PRINT                                           (KEYCODE_PC_KEYS + 0x61)
#define KEYCODE_SYSREQ                                          (KEYCODE_PC_KEYS + 0x6A)
#define KEYCODE_BREAK                                           (KEYCODE_PC_KEYS + 0x6B)

#define KEYCODE_ESCAPE                                          (KEYCODE_PC_KEYS + 0x1B)
#define KEYCODE_BACKSPACE                                       (KEYCODE_PC_KEYS + 0x08)
#define KEYCODE_TAB                                             (KEYCODE_PC_KEYS + 0x09)
#define KEYCODE_BACK_TAB                                        (KEYCODE_PC_KEYS + 0x89)
#define KEYCODE_RETURN                                          (KEYCODE_PC_KEYS + 0x0D)
#define KEYCODE_CAPS_LOCK                                       (KEYCODE_PC_KEYS + 0xE5)
#define KEYCODE_LEFT_SHIFT                                      (KEYCODE_PC_KEYS + 0xE1)
#define KEYCODE_RIGHT_SHIFT                                     (KEYCODE_PC_KEYS + 0xE2)
#define KEYCODE_LEFT_CTRL                                       (KEYCODE_PC_KEYS + 0xE3)
#define KEYCODE_RIGHT_CTRL                                      (KEYCODE_PC_KEYS + 0xE4)
#define KEYCODE_LEFT_ALT                                        (KEYCODE_PC_KEYS + 0xE9)
#define KEYCODE_RIGHT_ALT                                       (KEYCODE_PC_KEYS + 0xEA)
#define KEYCODE_MENU                                            (KEYCODE_PC_KEYS + 0x67)
#define KEYCODE_LEFT_HYPER                                      (KEYCODE_PC_KEYS + 0xED)
#define KEYCODE_RIGHT_HYPER                                     (KEYCODE_PC_KEYS + 0xEE)

#define KEYCODE_INSERT                                          (KEYCODE_PC_KEYS + 0x63)
#define KEYCODE_HOME                                            (KEYCODE_PC_KEYS + 0x50)
#define KEYCODE_PG_UP                                           (KEYCODE_PC_KEYS + 0x55)
#define KEYCODE_DELETE                                          (KEYCODE_PC_KEYS + 0xFF)
#define KEYCODE_END                                             (KEYCODE_PC_KEYS + 0x57)
#define KEYCODE_PG_DOWN                                         (KEYCODE_PC_KEYS + 0x56)
#define KEYCODE_LEFT                                            (KEYCODE_PC_KEYS + 0x51)
#define KEYCODE_RIGHT                                           (KEYCODE_PC_KEYS + 0x53)
#define KEYCODE_UP                                              (KEYCODE_PC_KEYS + 0x52)
#define KEYCODE_DOWN                                            (KEYCODE_PC_KEYS + 0x54)

#define KEYCODE_NUM_LOCK                                        (KEYCODE_PC_KEYS + 0x7F)
#define KEYCODE_KP_PLUS                                         (KEYCODE_PC_KEYS + 0xAB)
#define KEYCODE_KP_MINUS                                        (KEYCODE_PC_KEYS + 0xAD)
#define KEYCODE_KP_MULTIPLY                                     (KEYCODE_PC_KEYS + 0xAA)
#define KEYCODE_KP_DIVIDE                                       (KEYCODE_PC_KEYS + 0xAF)
#define KEYCODE_KP_ENTER                                        (KEYCODE_PC_KEYS + 0x8D)
#define KEYCODE_KP_HOME                                         (KEYCODE_PC_KEYS + 0xB7)
#define KEYCODE_KP_UP                                           (KEYCODE_PC_KEYS + 0xB8)
#define KEYCODE_KP_PG_UP                                        (KEYCODE_PC_KEYS + 0xB9)
#define KEYCODE_KP_LEFT                                         (KEYCODE_PC_KEYS + 0xB4)
#define KEYCODE_KP_FIVE                                         (KEYCODE_PC_KEYS + 0xB5)
#define KEYCODE_KP_RIGHT                                        (KEYCODE_PC_KEYS + 0xB6)
#define KEYCODE_KP_END                                          (KEYCODE_PC_KEYS + 0xB1)
#define KEYCODE_KP_DOWN                                         (KEYCODE_PC_KEYS + 0xB2)
#define KEYCODE_KP_PG_DOWN                                      (KEYCODE_PC_KEYS + 0xB3)
#define KEYCODE_KP_INSERT                                       (KEYCODE_PC_KEYS + 0xB0)
#define KEYCODE_KP_DELETE                                       (KEYCODE_PC_KEYS + 0xAE)

#define KEYCODE_F1                                              (KEYCODE_PC_KEYS + 0xBE)
#define KEYCODE_F2                                              (KEYCODE_PC_KEYS + 0xBF)
#define KEYCODE_F3                                              (KEYCODE_PC_KEYS + 0xC0)
#define KEYCODE_F4                                              (KEYCODE_PC_KEYS + 0xC1)
#define KEYCODE_F5                                              (KEYCODE_PC_KEYS + 0xC2)
#define KEYCODE_F6                                              (KEYCODE_PC_KEYS + 0xC3)
#define KEYCODE_F7                                              (KEYCODE_PC_KEYS + 0xC4)
#define KEYCODE_F8                                              (KEYCODE_PC_KEYS + 0xC5)
#define KEYCODE_F9                                              (KEYCODE_PC_KEYS + 0xC6)
#define KEYCODE_F10                                             (KEYCODE_PC_KEYS + 0xC7)
#define KEYCODE_F11                                             (KEYCODE_PC_KEYS + 0xC8)
#define KEYCODE_F12                                             (KEYCODE_PC_KEYS + 0xC9)

#define KEYCODE_CONSUMER_KEYS                                   (KEYCODE_PC_KEYS + 0x200)

#define KEYCODE_POWER                                           (KEYCODE_CONSUMER_KEYS + 0x00)
#define KEYCODE_RESET                                           (KEYCODE_CONSUMER_KEYS + 0x01)
#define KEYCODE_SLEEP                                           (KEYCODE_CONSUMER_KEYS + 0x02)
#define KEYCODE_SLEEP_AFTER                                     (KEYCODE_CONSUMER_KEYS + 0x03)
#define KEYCODE_SLEEP_MODE                                      (KEYCODE_CONSUMER_KEYS + 0x04)
#define KEYCODE_ILLUMINATION                                    (KEYCODE_CONSUMER_KEYS + 0x05)
//#define KEYCODE_MENU                                          (KEYCODE_CONSUMER_KEYS + 0x06)
#define KEYCODE_MENU_PICK                                       (KEYCODE_CONSUMER_KEYS + 0x07)
#define KEYCODE_MENU_UP                                         (KEYCODE_CONSUMER_KEYS + 0x08)
#define KEYCODE_MENU_DOWN                                       (KEYCODE_CONSUMER_KEYS + 0x09)
#define KEYCODE_MENU_LEFT                                       (KEYCODE_CONSUMER_KEYS + 0x0A)
#define KEYCODE_MENU_RIGHT                                      (KEYCODE_CONSUMER_KEYS + 0x0B)
#define KEYCODE_MENU_ESCAPE                                     (KEYCODE_CONSUMER_KEYS + 0x0C)
#define KEYCODE_MENU_VALUE_INCREASE                             (KEYCODE_CONSUMER_KEYS + 0x0D)
#define KEYCODE_MENU_VALUE_DECREASE                             (KEYCODE_CONSUMER_KEYS + 0x0E)
#define KEYCODE_SNAPSHOT                                        (KEYCODE_CONSUMER_KEYS + 0x0F)
#define KEYCODE_PLAY                                            (KEYCODE_CONSUMER_KEYS + 0x10)
//#define KEYCODE_PAUSE                                         (KEYCODE_CONSUMER_KEYS + 0x11)
#define KEYCODE_RECORD                                          (KEYCODE_CONSUMER_KEYS + 0x12)
#define KEYCODE_FAST_FORWARD                                    (KEYCODE_CONSUMER_KEYS + 0x13)
#define KEYCODE_REWIND                                          (KEYCODE_CONSUMER_KEYS + 0x14)
#define KEYCODE_SCAN_NEXT                                       (KEYCODE_CONSUMER_KEYS + 0x15)
#define KEYCODE_SCAN_PREVIOUS                                   (KEYCODE_CONSUMER_KEYS + 0x16)
#define KEYCODE_STOP                                            (KEYCODE_CONSUMER_KEYS + 0x17)
#define KEYCODE_EJECT                                           (KEYCODE_CONSUMER_KEYS + 0x18)
#define KEYCODE_STOP_EJECT                                      (KEYCODE_CONSUMER_KEYS + 0x19)
#define KEYCODE_PLAY_PAUSE                                      (KEYCODE_CONSUMER_KEYS + 0x1A)
#define KEYCODE_PLAY_SKIP                                       (KEYCODE_CONSUMER_KEYS + 0x1B)
#define KEYCODE_MUTE                                            (KEYCODE_CONSUMER_KEYS + 0x1C)
#define KEYCODE_VOLUME_UP                                       (KEYCODE_CONSUMER_KEYS + 0x1D)
#define KEYCODE_VOLUME_DOWN                                     (KEYCODE_CONSUMER_KEYS + 0x1E)
#define KEYCODE_WAKE_UP                                         (KEYCODE_CONSUMER_KEYS + 0x1F)

/* Generic App Control Consumer Keys */
#define KEYCODE_AC_NEW                                          (KEYCODE_CONSUMER_KEYS + 0x20)
#define KEYCODE_AC_OPEN                                         (KEYCODE_CONSUMER_KEYS + 0x21)
#define KEYCODE_AC_CLOSE                                        (KEYCODE_CONSUMER_KEYS + 0x22)
#define KEYCODE_AC_EXIT                                         (KEYCODE_CONSUMER_KEYS + 0x23)
#define KEYCODE_AC_MAXIMIZE                                     (KEYCODE_CONSUMER_KEYS + 0x24)
#define KEYCODE_AC_MINIMIZE                                     (KEYCODE_CONSUMER_KEYS + 0x25)
#define KEYCODE_AC_SAVE                                         (KEYCODE_CONSUMER_KEYS + 0x26)
#define KEYCODE_AC_PRINT                                        (KEYCODE_CONSUMER_KEYS + 0x27)
#define KEYCODE_AC_PROPERTIES                                   (KEYCODE_CONSUMER_KEYS + 0x28)
#define KEYCODE_AC_UNDO                                         (KEYCODE_CONSUMER_KEYS + 0x29)
#define KEYCODE_AC_COPY                                         (KEYCODE_CONSUMER_KEYS + 0x2A)
#define KEYCODE_AC_CUT                                          (KEYCODE_CONSUMER_KEYS + 0x2B)
#define KEYCODE_AC_PASTE                                        (KEYCODE_CONSUMER_KEYS + 0x2C)
#define KEYCODE_AC_SELECT_ALL                                   (KEYCODE_CONSUMER_KEYS + 0x2D)
#define KEYCODE_AC_FIND                                         (KEYCODE_CONSUMER_KEYS + 0x2E)
#define KEYCODE_AC_FIND_AND_REPLACE                             (KEYCODE_CONSUMER_KEYS + 0x2F)
#define KEYCODE_AC_GO_TO                                        (KEYCODE_CONSUMER_KEYS + 0x30)
#define KEYCODE_AC_HOME                                         (KEYCODE_CONSUMER_KEYS + 0x31)
#define KEYCODE_AC_BACK                                         (KEYCODE_CONSUMER_KEYS + 0x32)
#define KEYCODE_AC_FORWARD                                      (KEYCODE_CONSUMER_KEYS + 0x33)
#define KEYCODE_AC_STOP                                         (KEYCODE_CONSUMER_KEYS + 0x34)
#define KEYCODE_AC_REFRESH                                      (KEYCODE_CONSUMER_KEYS + 0x35)
#define KEYCODE_AC_PREVIOUS_LINK                                (KEYCODE_CONSUMER_KEYS + 0x36)
#define KEYCODE_AC_NEXT_LINK                                    (KEYCODE_CONSUMER_KEYS + 0x37)
#define KEYCODE_AC_BOOKMARKS                                    (KEYCODE_CONSUMER_KEYS + 0x38)
#define KEYCODE_AC_HISTORY                                      (KEYCODE_CONSUMER_KEYS + 0x39)
#define KEYCODE_AC_ZOOM_IN                                      (KEYCODE_CONSUMER_KEYS + 0x3A)
#define KEYCODE_AC_ZOOM_OUT                                     (KEYCODE_CONSUMER_KEYS + 0x3B)
#define KEYCODE_AC_ZOOM                                         (KEYCODE_CONSUMER_KEYS + 0x3C)
#define KEYCODE_AC_FULLSCREEN                                   (KEYCODE_CONSUMER_KEYS + 0x3D)
#define KEYCODE_AC_NORMAL_VIEW                                  (KEYCODE_CONSUMER_KEYS + 0x3E)
#define KEYCODE_AC_VIEW_TOGGLE                                  (KEYCODE_CONSUMER_KEYS + 0x3F)
#define KEYCODE_AC_SCROLL_UP                                    (KEYCODE_CONSUMER_KEYS + 0x40)
#define KEYCODE_AC_SCROLL_DOWN                                  (KEYCODE_CONSUMER_KEYS + 0x41)
#define KEYCODE_AC_SCROLL                                       (KEYCODE_CONSUMER_KEYS + 0x42)
#define KEYCODE_AC_PAN_LEFT                                     (KEYCODE_CONSUMER_KEYS + 0x43)
#define KEYCODE_AC_PAN_RIGHT                                    (KEYCODE_CONSUMER_KEYS + 0x44)
#define KEYCODE_AC_PAN                                          (KEYCODE_CONSUMER_KEYS + 0x45)
#define KEYCODE_AC_SEARCH                                       (KEYCODE_CONSUMER_KEYS + 0x46)
#define KEYCODE_AC_SUBSCRIPTIONS                                (KEYCODE_CONSUMER_KEYS + 0x47)
#define KEYCODE_AC_NEW_WINDOW                                   (KEYCODE_CONSUMER_KEYS + 0x48)
#define KEYCODE_AC_TILE_HORIZONTALLY                            (KEYCODE_CONSUMER_KEYS + 0x49)
#define KEYCODE_AC_TILE_VERTICALLY                              (KEYCODE_CONSUMER_KEYS + 0x4A)
#define KEYCODE_AC_FORMAT                                       (KEYCODE_CONSUMER_KEYS + 0x4B)
#define KEYCODE_AC_EDIT                                         (KEYCODE_CONSUMER_KEYS + 0x4C)
#define KEYCODE_AC_BOLD                                         (KEYCODE_CONSUMER_KEYS + 0x4D)
#define KEYCODE_AC_ITALICS                                      (KEYCODE_CONSUMER_KEYS + 0x4E)
#define KEYCODE_AC_UNDERLINE                                    (KEYCODE_CONSUMER_KEYS + 0x4F)
#define KEYCODE_AC_STRIKETHROUGH                                (KEYCODE_CONSUMER_KEYS + 0x50)
#define KEYCODE_AC_SUBSCRIPT                                    (KEYCODE_CONSUMER_KEYS + 0x51)
#define KEYCODE_AC_SUPERSCRIPT                                  (KEYCODE_CONSUMER_KEYS + 0x52)
#define KEYCODE_AC_ALL_CAPS                                     (KEYCODE_CONSUMER_KEYS + 0x53)
#define KEYCODE_AC_ROTATE                                       (KEYCODE_CONSUMER_KEYS + 0x54)
#define KEYCODE_AC_RESIZE                                       (KEYCODE_CONSUMER_KEYS + 0x55)
#define KEYCODE_AC_FLIP_HORIZONTAL                              (KEYCODE_CONSUMER_KEYS + 0x56)
#define KEYCODE_AC_FLIP_VERTICAL                                (KEYCODE_CONSUMER_KEYS + 0x57)
#define KEYCODE_AC_MIRROR_HORIZONTAL                            (KEYCODE_CONSUMER_KEYS + 0x58)
#define KEYCODE_AC_MIRROR_VERTICAL                              (KEYCODE_CONSUMER_KEYS + 0x59)
#define KEYCODE_AC_FONT_SELECT                                  (KEYCODE_CONSUMER_KEYS + 0x5A)
#define KEYCODE_AC_FONT_COLOR                                   (KEYCODE_CONSUMER_KEYS + 0x5B)
#define KEYCODE_AC_FONT_SIZE                                    (KEYCODE_CONSUMER_KEYS + 0x5C)
#define KEYCODE_AC_JUSTIFY_LEFT                                 (KEYCODE_CONSUMER_KEYS + 0x5D)
#define KEYCODE_AC_JUSTIFY_CENTER_H                             (KEYCODE_CONSUMER_KEYS + 0x5E)
#define KEYCODE_AC_JUSTIFY_RIGHT                                (KEYCODE_CONSUMER_KEYS + 0x5F)
#define KEYCODE_AC_JUSTIFY_BLOCK_H                              (KEYCODE_CONSUMER_KEYS + 0x60)
#define KEYCODE_AC_JUSTIFY_TOP                                  (KEYCODE_CONSUMER_KEYS + 0x61)
#define KEYCODE_AC_JUSTIFY_CENTER_V                             (KEYCODE_CONSUMER_KEYS + 0x62)
#define KEYCODE_AC_JUSTIFY_BOTTOM                               (KEYCODE_CONSUMER_KEYS + 0x63)
#define KEYCODE_AC_JUSTIFY_BLOCK_V                              (KEYCODE_CONSUMER_KEYS + 0x64)
#define KEYCODE_AC_INDENT_DECREASE                              (KEYCODE_CONSUMER_KEYS + 0x65)
#define KEYCODE_AC_INDENT_INCREASE                              (KEYCODE_CONSUMER_KEYS + 0x66)
#define KEYCODE_AC_NUMBERED_LIST                                (KEYCODE_CONSUMER_KEYS + 0x67)
#define KEYCODE_AC_RESTART_NUMBERING                            (KEYCODE_CONSUMER_KEYS + 0x68)
#define KEYCODE_AC_BULLETED_LIST                                (KEYCODE_CONSUMER_KEYS + 0x69)
#define KEYCODE_AC_PROMOTE                                      (KEYCODE_CONSUMER_KEYS + 0x6A)
#define KEYCODE_AC_DEMOTE                                       (KEYCODE_CONSUMER_KEYS + 0x6B)
#define KEYCODE_AC_YES                                          (KEYCODE_CONSUMER_KEYS + 0x6C)
#define KEYCODE_AC_NO                                           (KEYCODE_CONSUMER_KEYS + 0x6D)
#define KEYCODE_AC_CANCEL                                       (KEYCODE_CONSUMER_KEYS + 0x6E)
#define KEYCODE_AC_CATALOG                                      (KEYCODE_CONSUMER_KEYS + 0x6F)
#define KEYCODE_AC_BUY                                          (KEYCODE_CONSUMER_KEYS + 0x70)
#define KEYCODE_AC_ADD_TO_CART                                  (KEYCODE_CONSUMER_KEYS + 0x71)
#define KEYCODE_AC_EXPAND                                       (KEYCODE_CONSUMER_KEYS + 0x72)
#define KEYCODE_AC_EXPAND_ALL                                   (KEYCODE_CONSUMER_KEYS + 0x73)
#define KEYCODE_AC_COLLAPSE                                     (KEYCODE_CONSUMER_KEYS + 0x74)
#define KEYCODE_AC_COLLAPSE_ALL                                 (KEYCODE_CONSUMER_KEYS + 0x75)
#define KEYCODE_AC_PRINT_PREVIEW                                (KEYCODE_CONSUMER_KEYS + 0x76)
#define KEYCODE_AC_PASTE_SPECIAL                                (KEYCODE_CONSUMER_KEYS + 0x77)
#define KEYCODE_AC_INSERT_MODE                                  (KEYCODE_CONSUMER_KEYS + 0x78)
#define KEYCODE_AC_DELETE                                       (KEYCODE_CONSUMER_KEYS + 0x79)
#define KEYCODE_AC_LOCK                                         (KEYCODE_CONSUMER_KEYS + 0x7A)
#define KEYCODE_AC_UNLOCK                                       (KEYCODE_CONSUMER_KEYS + 0x7B)
#define KEYCODE_AC_PROTECT                                      (KEYCODE_CONSUMER_KEYS + 0x7C)
#define KEYCODE_AC_UNPROTECT                                    (KEYCODE_CONSUMER_KEYS + 0x7D)
#define KEYCODE_AC_ATTACH_COMMENT                               (KEYCODE_CONSUMER_KEYS + 0x7E)
#define KEYCODE_AC_DELETE_COMMENT                               (KEYCODE_CONSUMER_KEYS + 0x7F)
#define KEYCODE_AC_VIEW_COMMENT                                 (KEYCODE_CONSUMER_KEYS + 0x80)
#define KEYCODE_AC_SELECT_WORD                                  (KEYCODE_CONSUMER_KEYS + 0x81)
#define KEYCODE_AC_SELECT_SENTENCE                              (KEYCODE_CONSUMER_KEYS + 0x82)
#define KEYCODE_AC_SELECT_PARAGRAPH                             (KEYCODE_CONSUMER_KEYS + 0x83)
#define KEYCODE_AC_SELECT_COLUMN                                (KEYCODE_CONSUMER_KEYS + 0x84)
#define KEYCODE_AC_SELECT_ROW                                   (KEYCODE_CONSUMER_KEYS + 0x85)
#define KEYCODE_AC_SELECT_TABLE                                 (KEYCODE_CONSUMER_KEYS + 0x86)
#define KEYCODE_AC_SELECT_OBJECT                                (KEYCODE_CONSUMER_KEYS + 0x87)
#define KEYCODE_AC_REDO                                         (KEYCODE_CONSUMER_KEYS + 0x88)
#define KEYCODE_AC_SORT                                         (KEYCODE_CONSUMER_KEYS + 0x89)
#define KEYCODE_AC_SORT_ASCENDING                               (KEYCODE_CONSUMER_KEYS + 0x8A)
#define KEYCODE_AC_SORT_DESCENDING                              (KEYCODE_CONSUMER_KEYS + 0x8B)
#define KEYCODE_AC_FILTER                                       (KEYCODE_CONSUMER_KEYS + 0x8C)
#define KEYCODE_AC_SET_CLOCK                                    (KEYCODE_CONSUMER_KEYS + 0x8D)
#define KEYCODE_AC_VIEW_CLOCK                                   (KEYCODE_CONSUMER_KEYS + 0x8E)
#define KEYCODE_AC_SELECT_TIME_ZONE                             (KEYCODE_CONSUMER_KEYS + 0x8F)
#define KEYCODE_AC_EDIT_TIME_ZONES                              (KEYCODE_CONSUMER_KEYS + 0x90)
#define KEYCODE_AC_SET_ALARM                                    (KEYCODE_CONSUMER_KEYS + 0x91)
#define KEYCODE_AC_CLEAR_ALARM                                  (KEYCODE_CONSUMER_KEYS + 0x92)
#define KEYCODE_AC_SNOOZE_ALARM                                 (KEYCODE_CONSUMER_KEYS + 0x93)
#define KEYCODE_AC_RESET_ALARM                                  (KEYCODE_CONSUMER_KEYS + 0x94)
#define KEYCODE_AC_SYNCHRONIZE                                  (KEYCODE_CONSUMER_KEYS + 0x95)
#define KEYCODE_AC_SEND_RECEIVE                                 (KEYCODE_CONSUMER_KEYS + 0x96)
#define KEYCODE_AC_SEND_TO                                      (KEYCODE_CONSUMER_KEYS + 0x97)
#define KEYCODE_AC_REPLY                                        (KEYCODE_CONSUMER_KEYS + 0x98)
#define KEYCODE_AC_REPLY_ALL                                    (KEYCODE_CONSUMER_KEYS + 0x99)
#define KEYCODE_AC_FORWARD_MSG                                  (KEYCODE_CONSUMER_KEYS + 0x9A)
#define KEYCODE_AC_SEND                                         (KEYCODE_CONSUMER_KEYS + 0x9B)
#define KEYCODE_AC_ATTACH_FILE                                  (KEYCODE_CONSUMER_KEYS + 0x9C)
#define KEYCODE_AC_UPLOAD                                       (KEYCODE_CONSUMER_KEYS + 0x9D)
#define KEYCODE_AC_DOWNLOAD                                     (KEYCODE_CONSUMER_KEYS + 0x9E)
#define KEYCODE_AC_SET_BORDERS                                  (KEYCODE_CONSUMER_KEYS + 0x9F)
#define KEYCODE_AC_INSERT_ROW                                   (KEYCODE_CONSUMER_KEYS + 0xA0)
#define KEYCODE_AC_INSERT_COLUMN                                (KEYCODE_CONSUMER_KEYS + 0xA1)
#define KEYCODE_AC_INSERT_FILE                                  (KEYCODE_CONSUMER_KEYS + 0xA2)
#define KEYCODE_AC_INSERT_PICTURE                               (KEYCODE_CONSUMER_KEYS + 0xA3)
#define KEYCODE_AC_INSERT_OBJECT                                (KEYCODE_CONSUMER_KEYS + 0xA4)
#define KEYCODE_AC_INSERT_SYMBOL                                (KEYCODE_CONSUMER_KEYS + 0xA5)
#define KEYCODE_AC_SAVE_AND_CLOSE                               (KEYCODE_CONSUMER_KEYS + 0xA6)
#define KEYCODE_AC_RENAME                                       (KEYCODE_CONSUMER_KEYS + 0xA7)
#define KEYCODE_AC_MERGE                                        (KEYCODE_CONSUMER_KEYS + 0xA8)
#define KEYCODE_AC_SPLIT                                        (KEYCODE_CONSUMER_KEYS + 0xA9)
#define KEYCODE_AC_DISTRIBUTE_HORIZONTALLY                      (KEYCODE_CONSUMER_KEYS + 0xAA)
#define KEYCODE_AC_DISTRIBUTE_VERTICALLY                        (KEYCODE_CONSUMER_KEYS + 0xAB)

/* Application Launch Buttons Consumer Keys */
#define KEYCODE_AL_CONFIG_TOOL                                  (KEYCODE_CONSUMER_KEYS + 0xAC)
#define KEYCODE_AL_PROG_BUTTON_CONFIG                           (KEYCODE_CONSUMER_KEYS + 0xAD)
#define KEYCODE_AL_CONSUMER_CTRL_CONFIG                         (KEYCODE_CONSUMER_KEYS + 0xAE)
#define KEYCODE_AL_WORD_PROCESSOR                               (KEYCODE_CONSUMER_KEYS + 0xAF)
#define KEYCODE_AL_TEXT_EDITOR                                  (KEYCODE_CONSUMER_KEYS + 0xB0)
#define KEYCODE_AL_SPREADSHEET                                  (KEYCODE_CONSUMER_KEYS + 0xB1)
#define KEYCODE_AL_GRAPHICS_EDITOR                              (KEYCODE_CONSUMER_KEYS + 0xB2)
#define KEYCODE_AL_PRESENTATION                                 (KEYCODE_CONSUMER_KEYS + 0xB3)
#define KEYCODE_AL_DATABASE                                     (KEYCODE_CONSUMER_KEYS + 0xB4)
#define KEYCODE_AL_EMAIL_READER                                 (KEYCODE_CONSUMER_KEYS + 0xB5)
#define KEYCODE_AL_NEWSREADER                                   (KEYCODE_CONSUMER_KEYS + 0xB6)
#define KEYCODE_AL_VOICEMAIL                                    (KEYCODE_CONSUMER_KEYS + 0xB7)
#define KEYCODE_AL_CONTACTS                                     (KEYCODE_CONSUMER_KEYS + 0xB8)
#define KEYCODE_AL_CALENDAR                                     (KEYCODE_CONSUMER_KEYS + 0xB9)
#define KEYCODE_AL_TASK                                         (KEYCODE_CONSUMER_KEYS + 0xBA)
#define KEYCODE_AL_LOG                                          (KEYCODE_CONSUMER_KEYS + 0xBB)
#define KEYCODE_AL_FINANCE                                      (KEYCODE_CONSUMER_KEYS + 0xBC)
#define KEYCODE_AL_CALCULATOR                                   (KEYCODE_CONSUMER_KEYS + 0xBD)
#define KEYCODE_AL_AV_CAPTURE_PLAYBACK                          (KEYCODE_CONSUMER_KEYS + 0xBE)
#define KEYCODE_AL_LOCAL_BROWSER                                (KEYCODE_CONSUMER_KEYS + 0xBF)
#define KEYCODE_AL_LAN_WAN_BROWSER                              (KEYCODE_CONSUMER_KEYS + 0xC0)
#define KEYCODE_AL_INTERNET_BROWSER                             (KEYCODE_CONSUMER_KEYS + 0xC1)
#define KEYCODE_AL_REMOTE_NETWORKING                            (KEYCODE_CONSUMER_KEYS + 0xC2)
#define KEYCODE_AL_NETWORK_CONFERENCE                           (KEYCODE_CONSUMER_KEYS + 0xC3)
#define KEYCODE_AL_NETWORK_CHAT                                 (KEYCODE_CONSUMER_KEYS + 0xC4)
#define KEYCODE_AL_TELEPHONY                                    (KEYCODE_CONSUMER_KEYS + 0xC5)
#define KEYCODE_AL_LOGON                                        (KEYCODE_CONSUMER_KEYS + 0xC6)
#define KEYCODE_AL_LOGOFF                                       (KEYCODE_CONSUMER_KEYS + 0xC7)
#define KEYCODE_AL_LOGON_LOGOFF                                 (KEYCODE_CONSUMER_KEYS + 0xC8)
#define KEYCODE_AL_TERMINAL_LOCK                                (KEYCODE_CONSUMER_KEYS + 0xC9)
#define KEYCODE_AL_CONTROL_PANEL                                (KEYCODE_CONSUMER_KEYS + 0xCA)
#define KEYCODE_AL_COMMAND_LINE                                 (KEYCODE_CONSUMER_KEYS + 0xCB)
#define KEYCODE_AL_PROCESS                                      (KEYCODE_CONSUMER_KEYS + 0xCC)
#define KEYCODE_AL_SELECT_TASK                                  (KEYCODE_CONSUMER_KEYS + 0xCD)
#define KEYCODE_AL_NEXT_TASK                                    (KEYCODE_CONSUMER_KEYS + 0xCE)
#define KEYCODE_AL_PREVIOUS_TASK                                (KEYCODE_CONSUMER_KEYS + 0xCF)
#define KEYCODE_AL_PREEMPTIVE_HALT_TASK                         (KEYCODE_CONSUMER_KEYS + 0xD0)
#define KEYCODE_AL_INTEGRATED_HELP_CENTER                       (KEYCODE_CONSUMER_KEYS + 0xD1)
#define KEYCODE_AL_DOCUMENTS                                    (KEYCODE_CONSUMER_KEYS + 0xD2)
#define KEYCODE_AL_THESAURUS                                    (KEYCODE_CONSUMER_KEYS + 0xD3)
#define KEYCODE_AL_DICTIONARY                                   (KEYCODE_CONSUMER_KEYS + 0xD4)
#define KEYCODE_AL_DESKTOP                                      (KEYCODE_CONSUMER_KEYS + 0xD5)
#define KEYCODE_AL_SPELL_CHECK                                  (KEYCODE_CONSUMER_KEYS + 0xD6)
#define KEYCODE_AL_GRAMMER_CHECK                                (KEYCODE_CONSUMER_KEYS + 0xD7)
#define KEYCODE_AL_WIRELESS_STATUS                              (KEYCODE_CONSUMER_KEYS + 0xD8)
#define KEYCODE_AL_KEYBOARD_LAYOUT                              (KEYCODE_CONSUMER_KEYS + 0xD9)
#define KEYCODE_AL_VIRUS_PROTECTION                             (KEYCODE_CONSUMER_KEYS + 0xDA)
#define KEYCODE_AL_ENCRYPTION                                   (KEYCODE_CONSUMER_KEYS + 0xDB)
#define KEYCODE_AL_SCREEN_SAVER                                 (KEYCODE_CONSUMER_KEYS + 0xDC)
#define KEYCODE_AL_ALARMS                                       (KEYCODE_CONSUMER_KEYS + 0xDD)
#define KEYCODE_AL_CLOCK                                        (KEYCODE_CONSUMER_KEYS + 0xDE)
#define KEYCODE_AL_FILE_BROWSER                                 (KEYCODE_CONSUMER_KEYS + 0xDF)
#define KEYCODE_AL_POWER_STATUS                                 (KEYCODE_CONSUMER_KEYS + 0xE0)
#define KEYCODE_AL_IMAGE_BROWSER                                (KEYCODE_CONSUMER_KEYS + 0xE1)
#define KEYCODE_AL_AUDIO_BROWSER                                (KEYCODE_CONSUMER_KEYS + 0xE2)
#define KEYCODE_AL_MOVIE_BROWSER                                (KEYCODE_CONSUMER_KEYS + 0xE3)
#define KEYCODE_AL_DIGITAL_RIGHTS_MANAGER                       (KEYCODE_CONSUMER_KEYS + 0xE4)
#define KEYCODE_AL_DIGITAL_WALLET                               (KEYCODE_CONSUMER_KEYS + 0xE5)
#define KEYCODE_AL_INSTANT_MESSAGING                            (KEYCODE_CONSUMER_KEYS + 0xE6)
#define KEYCODE_AL_OEM_FEATURES                                 (KEYCODE_CONSUMER_KEYS + 0xE7)
#define KEYCODE_AL_OEM_HELP                                     (KEYCODE_CONSUMER_KEYS + 0xE8)
#define KEYCODE_AL_ONLINE_COMMUNITY                             (KEYCODE_CONSUMER_KEYS + 0xE9)
#define KEYCODE_AL_ENTERTAINMENT_BROWSER                        (KEYCODE_CONSUMER_KEYS + 0xEA)
#define KEYCODE_AL_ONLINE_SHOPPING_BROWSER                      (KEYCODE_CONSUMER_KEYS + 0xEB)
#define KEYCODE_AL_SMARTCARD_INFORMATION                        (KEYCODE_CONSUMER_KEYS + 0xEC)
#define KEYCODE_AL_FINANCE_BROWSER                              (KEYCODE_CONSUMER_KEYS + 0xED)
#define KEYCODE_AL_NEWS_BROWSER                                 (KEYCODE_CONSUMER_KEYS + 0xEE)
#define KEYCODE_AL_ONLINE_ACTIVITY_BROWSER                      (KEYCODE_CONSUMER_KEYS + 0xEF)
#define KEYCODE_AL_SEARCH_BROWSER                               (KEYCODE_CONSUMER_KEYS + 0xF0)
#define KEYCODE_AL_AUDIO_PLAYER                                 (KEYCODE_CONSUMER_KEYS + 0xF1)

#define KEYCODE_SPACE                                           UCS_SPACE
#define KEYCODE_EXCLAM                                          UCS_EXCLAMATION_MARK
#define KEYCODE_QUOTE                                           UCS_QUOTATION_MARK
#define KEYCODE_NUMBER                                          UCS_NUMBER_SIGN
#define KEYCODE_DOLLAR                                          UCS_DOLLAR_SIGN
#define KEYCODE_PERCENT                                         UCS_PERCENT_SIGN
#define KEYCODE_AMPERSAND                                       UCS_AMPERSAND
#define KEYCODE_APOSTROPHE                                      UCS_APOSTROPHE
#define KEYCODE_LEFT_PAREN                                      UCS_LEFT_PARENTHESIS
#define KEYCODE_RIGHT_PAREN                                     UCS_RIGHT_PARENTHESIS
#define KEYCODE_ASTERISK                                        UCS_ASTERISK
#define KEYCODE_PLUS                                            UCS_PLUS_SIGN
#define KEYCODE_COMMA                                           UCS_COMMA
#define KEYCODE_MINUS                                           UCS_HYPHEN_MINUS
#define KEYCODE_PERIOD                                          UCS_FULL_STOP
#define KEYCODE_SLASH                                           UCS_SOLIDUS
#define KEYCODE_ZERO                                            UCS_DIGIT_ZERO
#define KEYCODE_ONE                                             UCS_DIGIT_ONE
#define KEYCODE_TWO                                             UCS_DIGIT_TWO
#define KEYCODE_THREE                                           UCS_DIGIT_THREE
#define KEYCODE_FOUR                                            UCS_DIGIT_FOUR
#define KEYCODE_FIVE                                            UCS_DIGIT_FIVE
#define KEYCODE_SIX                                             UCS_DIGIT_SIX
#define KEYCODE_SEVEN                                           UCS_DIGIT_SEVEN
#define KEYCODE_EIGHT                                           UCS_DIGIT_EIGHT
#define KEYCODE_NINE                                            UCS_DIGIT_NINE
#define KEYCODE_COLON                                           UCS_COLON
#define KEYCODE_SEMICOLON                                       UCS_SEMICOLON
#define KEYCODE_LESS_THAN                                       UCS_LESS_THAN_SIGN
#define KEYCODE_EQUAL                                           UCS_EQUALS_SIGN
#define KEYCODE_GREATER_THAN                                    UCS_GREATER_THAN_SIGN
#define KEYCODE_QUESTION                                        UCS_QUESTION_MARK
#define KEYCODE_AT                                              UCS_COMMERCIAL_AT
#define KEYCODE_CAPITAL_A                                       UCS_LATIN_CAPITAL_LETTER_A
#define KEYCODE_CAPITAL_B                                       UCS_LATIN_CAPITAL_LETTER_B
#define KEYCODE_CAPITAL_C                                       UCS_LATIN_CAPITAL_LETTER_C
#define KEYCODE_CAPITAL_D                                       UCS_LATIN_CAPITAL_LETTER_D
#define KEYCODE_CAPITAL_E                                       UCS_LATIN_CAPITAL_LETTER_E
#define KEYCODE_CAPITAL_F                                       UCS_LATIN_CAPITAL_LETTER_F
#define KEYCODE_CAPITAL_G                                       UCS_LATIN_CAPITAL_LETTER_G
#define KEYCODE_CAPITAL_H                                       UCS_LATIN_CAPITAL_LETTER_H
#define KEYCODE_CAPITAL_I                                       UCS_LATIN_CAPITAL_LETTER_I
#define KEYCODE_CAPITAL_J                                       UCS_LATIN_CAPITAL_LETTER_J
#define KEYCODE_CAPITAL_K                                       UCS_LATIN_CAPITAL_LETTER_K
#define KEYCODE_CAPITAL_L                                       UCS_LATIN_CAPITAL_LETTER_L
#define KEYCODE_CAPITAL_M                                       UCS_LATIN_CAPITAL_LETTER_M
#define KEYCODE_CAPITAL_N                                       UCS_LATIN_CAPITAL_LETTER_N
#define KEYCODE_CAPITAL_O                                       UCS_LATIN_CAPITAL_LETTER_O
#define KEYCODE_CAPITAL_P                                       UCS_LATIN_CAPITAL_LETTER_P
#define KEYCODE_CAPITAL_Q                                       UCS_LATIN_CAPITAL_LETTER_Q
#define KEYCODE_CAPITAL_R                                       UCS_LATIN_CAPITAL_LETTER_R
#define KEYCODE_CAPITAL_S                                       UCS_LATIN_CAPITAL_LETTER_S
#define KEYCODE_CAPITAL_T                                       UCS_LATIN_CAPITAL_LETTER_T
#define KEYCODE_CAPITAL_U                                       UCS_LATIN_CAPITAL_LETTER_U
#define KEYCODE_CAPITAL_V                                       UCS_LATIN_CAPITAL_LETTER_V
#define KEYCODE_CAPITAL_W                                       UCS_LATIN_CAPITAL_LETTER_W
#define KEYCODE_CAPITAL_X                                       UCS_LATIN_CAPITAL_LETTER_X
#define KEYCODE_CAPITAL_Y                                       UCS_LATIN_CAPITAL_LETTER_Y
#define KEYCODE_CAPITAL_Z                                       UCS_LATIN_CAPITAL_LETTER_Z
#define KEYCODE_LEFT_BRACKET                                    UCS_LEFT_SQUARE_BRACKET
#define KEYCODE_BACK_SLASH                                      UCS_REVERSE_SOLIDUS
#define KEYCODE_RIGHT_BRACKET                                   UCS_RIGHT_SQUARE_BRACKET
#define KEYCODE_CIRCUMFLEX                                      UCS_CIRCUMFLEX_ACCENT
#define KEYCODE_UNDERSCORE                                      UCS_LOW_LINE
#define KEYCODE_GRAVE                                           UCS_GRAVE_ACCENT
#define KEYCODE_A                                               UCS_LATIN_SMALL_LETTER_A
#define KEYCODE_B                                               UCS_LATIN_SMALL_LETTER_B
#define KEYCODE_C                                               UCS_LATIN_SMALL_LETTER_C
#define KEYCODE_D                                               UCS_LATIN_SMALL_LETTER_D
#define KEYCODE_E                                               UCS_LATIN_SMALL_LETTER_E
#define KEYCODE_F                                               UCS_LATIN_SMALL_LETTER_F
#define KEYCODE_G                                               UCS_LATIN_SMALL_LETTER_G
#define KEYCODE_H                                               UCS_LATIN_SMALL_LETTER_H
#define KEYCODE_I                                               UCS_LATIN_SMALL_LETTER_I
#define KEYCODE_J                                               UCS_LATIN_SMALL_LETTER_J
#define KEYCODE_K                                               UCS_LATIN_SMALL_LETTER_K
#define KEYCODE_L                                               UCS_LATIN_SMALL_LETTER_L
#define KEYCODE_M                                               UCS_LATIN_SMALL_LETTER_M
#define KEYCODE_N                                               UCS_LATIN_SMALL_LETTER_N
#define KEYCODE_O                                               UCS_LATIN_SMALL_LETTER_O
#define KEYCODE_P                                               UCS_LATIN_SMALL_LETTER_P
#define KEYCODE_Q                                               UCS_LATIN_SMALL_LETTER_Q
#define KEYCODE_R                                               UCS_LATIN_SMALL_LETTER_R
#define KEYCODE_S                                               UCS_LATIN_SMALL_LETTER_S
#define KEYCODE_T                                               UCS_LATIN_SMALL_LETTER_T
#define KEYCODE_U                                               UCS_LATIN_SMALL_LETTER_U
#define KEYCODE_V                                               UCS_LATIN_SMALL_LETTER_V
#define KEYCODE_W                                               UCS_LATIN_SMALL_LETTER_W
#define KEYCODE_X                                               UCS_LATIN_SMALL_LETTER_X
#define KEYCODE_Y                                               UCS_LATIN_SMALL_LETTER_Y
#define KEYCODE_Z                                               UCS_LATIN_SMALL_LETTER_Z
#define KEYCODE_LEFT_BRACE                                      UCS_LEFT_CURLY_BRACKET
#define KEYCODE_BAR                                             UCS_VERTICAL_LINE
#define KEYCODE_RIGHT_BRACE                                     UCS_RIGHT_CURLY_BRACKET
#define KEYCODE_TILDE                                           UCS_TILDE

#define KEYCODE_NO_BREAK_SPACE                                  UCS_NO_BREAK_SPACE
#define KEYCODE_INVERTED_EXCLAMATION_MARK                       UCS_INVERTED_EXCLAMATION_MARK
#define KEYCODE_CENT_SIGN                                       UCS_CENT_SIGN
#define KEYCODE_POUND_SIGN                                      UCS_POUND_SIGN
#define KEYCODE_CURRENCY_SIGN                                   UCS_CURRENCY_SIGN
#define KEYCODE_YEN_SIGN                                        UCS_YEN_SIGN
#define KEYCODE_BROKEN_BAR                                      UCS_BROKEN_BAR
#define KEYCODE_SECTION_SIGN                                    UCS_SECTION_SIGN
#define KEYCODE_DIAERESIS                                       UCS_DIAERESIS
#define KEYCODE_COPYRIGHT_SIGN                                  UCS_COPYRIGHT_SIGN
#define KEYCODE_FEMININE_ORDINAL_INDICATOR                      UCS_FEMININE_ORDINAL_INDICATOR
#define KEYCODE_LEFT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK       UCS_LEFT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK
#define KEYCODE_NOT_SIGN                                        UCS_NOT_SIGN
#define KEYCODE_SOFT_HYPHEN                                     UCS_SOFT_HYPHEN
#define KEYCODE_REGISTERED_SIGN                                 UCS_REGISTERED_SIGN
#define KEYCODE_MACRON                                          UCS_MACRON
#define KEYCODE_DEGREE_SIGN                                     UCS_DEGREE_SIGN
#define KEYCODE_PLUS_MINUS_SIGN                                 UCS_PLUS_MINUS_SIGN
#define KEYCODE_SUPERSCRIPT_TWO                                 UCS_SUPERSCRIPT_TWO
#define KEYCODE_SUPERSCRIPT_THREE                               UCS_SUPERSCRIPT_THREE
#define KEYCODE_ACUTE_ACCENT                                    UCS_ACUTE_ACCENT
#define KEYCODE_MICRO_SIGN                                      UCS_MICRO_SIGN
#define KEYCODE_PILCROW_SIGN                                    UCS_PILCROW_SIGN
#define KEYCODE_MIDDLE_DOT                                      UCS_MIDDLE_DOT
#define KEYCODE_CEDILLA                                         UCS_CEDILLA
#define KEYCODE_SUPERSCRIPT_ONE                                 UCS_SUPERSCRIPT_ONE
#define KEYCODE_MASCULINE_ORDINAL_INDICATOR                     UCS_MASCULINE_ORDINAL_INDICATOR
#define KEYCODE_RIGHT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK      UCS_RIGHT_POINTING_DOUBLE_ANGLE_QUOTATION_MARK
#define KEYCODE_VULGAR_FRACTION_ONE_QUARTER                     UCS_VULGAR_FRACTION_ONE_QUARTER
#define KEYCODE_VULGAR_FRACTION_ONE_HALF                        UCS_VULGAR_FRACTION_ONE_HALF
#define KEYCODE_VULGAR_FRACTION_THREE_QUARTERS                  UCS_VULGAR_FRACTION_THREE_QUARTERS
#define KEYCODE_INVERTED_QUESTION_MARK                          UCS_INVERTED_QUESTION_MARK
#define KEYCODE_LATIN_CAPITAL_LETTER_A_WITH_GRAVE               UCS_LATIN_CAPITAL_LETTER_A_WITH_GRAVE
#define KEYCODE_LATIN_CAPITAL_LETTER_A_WITH_ACUTE               UCS_LATIN_CAPITAL_LETTER_A_WITH_ACUTE
#define KEYCODE_LATIN_CAPITAL_LETTER_A_WITH_CIRCUMFLEX          UCS_LATIN_CAPITAL_LETTER_A_WITH_CIRCUMFLEX
#define KEYCODE_LATIN_CAPITAL_LETTER_A_WITH_TILDE               UCS_LATIN_CAPITAL_LETTER_A_WITH_TILDE
#define KEYCODE_LATIN_CAPITAL_LETTER_A_WITH_DIAERESIS           UCS_LATIN_CAPITAL_LETTER_A_WITH_DIAERESIS
#define KEYCODE_LATIN_CAPITAL_LETTER_A_WITH_RING_ABOVE          UCS_LATIN_CAPITAL_LETTER_A_WITH_RING_ABOVE
#define KEYCODE_LATIN_CAPITAL_LIGATURE_AE                       UCS_LATIN_CAPITAL_LIGATURE_AE
#define KEYCODE_LATIN_CAPITAL_LETTER_C_WITH_CEDILLA             UCS_LATIN_CAPITAL_LETTER_C_WITH_CEDILLA
#define KEYCODE_LATIN_CAPITAL_LETTER_E_WITH_GRAVE               UCS_LATIN_CAPITAL_LETTER_E_WITH_GRAVE
#define KEYCODE_LATIN_CAPITAL_LETTER_E_WITH_ACUTE               UCS_LATIN_CAPITAL_LETTER_E_WITH_ACUTE
#define KEYCODE_LATIN_CAPITAL_LETTER_E_WITH_CIRCUMFLEX          UCS_LATIN_CAPITAL_LETTER_E_WITH_CIRCUMFLEX
#define KEYCODE_LATIN_CAPITAL_LETTER_E_WITH_DIAERESIS           UCS_LATIN_CAPITAL_LETTER_E_WITH_DIAERESIS
#define KEYCODE_LATIN_CAPITAL_LETTER_I_WITH_GRAVE               UCS_LATIN_CAPITAL_LETTER_I_WITH_GRAVE
#define KEYCODE_LATIN_CAPITAL_LETTER_I_WITH_ACUTE               UCS_LATIN_CAPITAL_LETTER_I_WITH_ACUTE
#define KEYCODE_LATIN_CAPITAL_LETTER_I_WITH_CIRCUMFLEX          UCS_LATIN_CAPITAL_LETTER_I_WITH_CIRCUMFLEX
#define KEYCODE_LATIN_CAPITAL_LETTER_I_WITH_DIAERESIS           UCS_LATIN_CAPITAL_LETTER_I_WITH_DIAERESIS
#define KEYCODE_LATIN_CAPITAL_LETTER_ETH                        UCS_LATIN_CAPITAL_LETTER_ETH
#define KEYCODE_LATIN_CAPITAL_LETTER_N_WITH_TILDE               UCS_LATIN_CAPITAL_LETTER_N_WITH_TILDE
#define KEYCODE_LATIN_CAPITAL_LETTER_O_WITH_GRAVE               UCS_LATIN_CAPITAL_LETTER_O_WITH_GRAVE
#define KEYCODE_LATIN_CAPITAL_LETTER_O_WITH_ACUTE               UCS_LATIN_CAPITAL_LETTER_O_WITH_ACUTE
#define KEYCODE_LATIN_CAPITAL_LETTER_O_WITH_CIRCUMFLEX          UCS_LATIN_CAPITAL_LETTER_O_WITH_CIRCUMFLEX
#define KEYCODE_LATIN_CAPITAL_LETTER_O_WITH_TILDE               UCS_LATIN_CAPITAL_LETTER_O_WITH_TILDE
#define KEYCODE_LATIN_CAPITAL_LETTER_O_WITH_DIAERESIS           UCS_LATIN_CAPITAL_LETTER_O_WITH_DIAERESIS
#define KEYCODE_MULTIPLICATION_SIGN                             UCS_MULTIPLICATION_SIGN
#define KEYCODE_LATIN_CAPITAL_LETTER_O_WITH_STROKE              UCS_LATIN_CAPITAL_LETTER_O_WITH_STROKE
#define KEYCODE_LATIN_CAPITAL_LETTER_U_WITH_GRAVE               UCS_LATIN_CAPITAL_LETTER_U_WITH_GRAVE
#define KEYCODE_LATIN_CAPITAL_LETTER_U_WITH_ACUTE               UCS_LATIN_CAPITAL_LETTER_U_WITH_ACUTE
#define KEYCODE_LATIN_CAPITAL_LETTER_U_WITH_CIRCUMFLEX          UCS_LATIN_CAPITAL_LETTER_U_WITH_CIRCUMFLEX
#define KEYCODE_LATIN_CAPITAL_LETTER_U_WITH_DIAERESIS           UCS_LATIN_CAPITAL_LETTER_U_WITH_DIAERESIS
#define KEYCODE_LATIN_CAPITAL_LETTER_Y_WITH_ACUTE               UCS_LATIN_CAPITAL_LETTER_Y_WITH_ACUTE
#define KEYCODE_LATIN_CAPITAL_LETTER_THORN                      UCS_LATIN_CAPITAL_LETTER_THORN
#define KEYCODE_LATIN_SMALL_LETTER_SHARP_S                      UCS_LATIN_SMALL_LETTER_SHARP_S
#define KEYCODE_LATIN_SMALL_LETTER_A_WITH_GRAVE                 UCS_LATIN_SMALL_LETTER_A_WITH_GRAVE
#define KEYCODE_LATIN_SMALL_LETTER_A_WITH_ACUTE                 UCS_LATIN_SMALL_LETTER_A_WITH_ACUTE
#define KEYCODE_LATIN_SMALL_LETTER_A_WITH_CIRCUMFLEX            UCS_LATIN_SMALL_LETTER_A_WITH_CIRCUMFLEX
#define KEYCODE_LATIN_SMALL_LETTER_A_WITH_TILDE                 UCS_LATIN_SMALL_LETTER_A_WITH_TILDE
#define KEYCODE_LATIN_SMALL_LETTER_A_WITH_DIAERESIS             UCS_LATIN_SMALL_LETTER_A_WITH_DIAERESIS
#define KEYCODE_LATIN_SMALL_LETTER_A_WITH_RING_ABOVE            UCS_LATIN_SMALL_LETTER_A_WITH_RING_ABOVE
#define KEYCODE_LATIN_SMALL_LIGATURE_AE                         UCS_LATIN_SMALL_LIGATURE_AE
#define KEYCODE_LATIN_SMALL_LETTER_C_WITH_CEDILLA               UCS_LATIN_SMALL_LETTER_C_WITH_CEDILLA
#define KEYCODE_LATIN_SMALL_LETTER_E_WITH_GRAVE                 UCS_LATIN_SMALL_LETTER_E_WITH_GRAVE
#define KEYCODE_LATIN_SMALL_LETTER_E_WITH_ACUTE                 UCS_LATIN_SMALL_LETTER_E_WITH_ACUTE
#define KEYCODE_LATIN_SMALL_LETTER_E_WITH_CIRCUMFLEX            UCS_LATIN_SMALL_LETTER_E_WITH_CIRCUMFLEX
#define KEYCODE_LATIN_SMALL_LETTER_E_WITH_DIAERESIS             UCS_LATIN_SMALL_LETTER_E_WITH_DIAERESIS
#define KEYCODE_LATIN_SMALL_LETTER_I_WITH_GRAVE                 UCS_LATIN_SMALL_LETTER_I_WITH_GRAVE
#define KEYCODE_LATIN_SMALL_LETTER_I_WITH_ACUTE                 UCS_LATIN_SMALL_LETTER_I_WITH_ACUTE
#define KEYCODE_LATIN_SMALL_LETTER_I_WITH_CIRCUMFLEX            UCS_LATIN_SMALL_LETTER_I_WITH_CIRCUMFLEX
#define KEYCODE_LATIN_SMALL_LETTER_I_WITH_DIAERESIS             UCS_LATIN_SMALL_LETTER_I_WITH_DIAERESIS
#define KEYCODE_LATIN_SMALL_LETTER_ETH                          UCS_LATIN_SMALL_LETTER_ETH
#define KEYCODE_LATIN_SMALL_LETTER_N_WITH_TILDE                 UCS_LATIN_SMALL_LETTER_N_WITH_TILDE
#define KEYCODE_LATIN_SMALL_LETTER_O_WITH_GRAVE                 UCS_LATIN_SMALL_LETTER_O_WITH_GRAVE
#define KEYCODE_LATIN_SMALL_LETTER_O_WITH_ACUTE                 UCS_LATIN_SMALL_LETTER_O_WITH_ACUTE
#define KEYCODE_LATIN_SMALL_LETTER_O_WITH_CIRCUMFLEX            UCS_LATIN_SMALL_LETTER_O_WITH_CIRCUMFLEX
#define KEYCODE_LATIN_SMALL_LETTER_O_WITH_TILDE                 UCS_LATIN_SMALL_LETTER_O_WITH_TILDE
#define KEYCODE_LATIN_SMALL_LETTER_O_WITH_DIAERESIS             UCS_LATIN_SMALL_LETTER_O_WITH_DIAERESIS
#define KEYCODE_DIVISION_SIGN                                   UCS_DIVISION_SIGN
#define KEYCODE_LATIN_SMALL_LETTER_O_WITH_STROKE                UCS_LATIN_SMALL_LETTER_O_WITH_STROKE
#define KEYCODE_LATIN_SMALL_LETTER_U_WITH_GRAVE                 UCS_LATIN_SMALL_LETTER_U_WITH_GRAVE
#define KEYCODE_LATIN_SMALL_LETTER_U_WITH_ACUTE                 UCS_LATIN_SMALL_LETTER_U_WITH_ACUTE
#define KEYCODE_LATIN_SMALL_LETTER_U_WITH_CIRCUMFLEX            UCS_LATIN_SMALL_LETTER_U_WITH_CIRCUMFLEX
#define KEYCODE_LATIN_SMALL_LETTER_U_WITH_DIAERESIS             UCS_LATIN_SMALL_LETTER_U_WITH_DIAERESIS
#define KEYCODE_LATIN_SMALL_LETTER_Y_WITH_ACUTE                 UCS_LATIN_SMALL_LETTER_Y_WITH_ACUTE
#define KEYCODE_LATIN_SMALL_LETTER_THORN                        UCS_LATIN_SMALL_LETTER_THORN
#define KEYCODE_LATIN_SMALL_LETTER_Y_WITH_DIAERESIS             UCS_LATIN_SMALL_LETTER_Y_WITH_DIAERESIS

#define KEYCODE_COMBINING_GRAVE_ACCENT                          UCS_COMBINING_GRAVE_ACCENT
#define KEYCODE_COMBINING_ACUTE_ACCENT                          UCS_COMBINING_ACUTE_ACCENT
#define KEYCODE_COMBINING_CIRCUMFLEX_ACCENT                     UCS_COMBINING_CIRCUMFLEX_ACCENT
#define KEYCODE_COMBINING_TILDE                                 UCS_COMBINING_TILDE
#define KEYCODE_COMBINING_MACRON                                UCS_COMBINING_MACRON
#define KEYCODE_COMBINING_OVERLINE                              UCS_COMBINING_OVERLINE
#define KEYCODE_COMBINING_BREVE                                 UCS_COMBINING_BREVE
#define KEYCODE_COMBINING_DOT_ABOVE                             UCS_COMBINING_DOT_ABOVE
#define KEYCODE_COMBINING_DIAERESIS                             UCS_COMBINING_DIAERESIS
#define KEYCODE_COMBINING_HOOK_ABOVE                            UCS_COMBINING_HOOK_ABOVE
#define KEYCODE_COMBINING_RING_ABOVE                            UCS_COMBINING_RING_ABOVE
#define KEYCODE_COMBINING_DOUBLE_ACUTE_ACCENT                   UCS_COMBINING_DOUBLE_ACUTE_ACCENT
#define KEYCODE_COMBINING_CARON                                 UCS_COMBINING_CARON
#define KEYCODE_COMBINING_VERTICAL_LINE_ABOVE                   UCS_COMBINING_VERTICAL_LINE_ABOVE
#define KEYCODE_COMBINING_DOUBLE_VERTICAL_LINE_ABOVE            UCS_COMBINING_DOUBLE_VERTICAL_LINE_ABOVE
#define KEYCODE_COMBINING_DOUBLE_GRAVE_ACCENT                   UCS_COMBINING_DOUBLE_GRAVE_ACCENT
#define KEYCODE_COMBINING_CANDRABINDU                           UCS_COMBINING_CANDRABINDU
#define KEYCODE_COMBINING_INVERTED_BREVE                        UCS_COMBINING_INVERTED_BREVE
#define KEYCODE_COMBINING_TURNED_COMMA_ABOVE                    UCS_COMBINING_TURNED_COMMA_ABOVE
#define KEYCODE_COMBINING_COMMA_ABOVE                           UCS_COMBINING_COMMA_ABOVE
#define KEYCODE_COMBINING_REVERSED_COMMA_ABOVE                  UCS_COMBINING_REVERSED_COMMA_ABOVE
#define KEYCODE_COMBINING_COMMA_ABOVE_RIGHT                     UCS_COMBINING_COMMA_ABOVE_RIGHT
#define KEYCODE_COMBINING_GRAVE_ACCENT_BELOW                    UCS_COMBINING_GRAVE_ACCENT_BELOW
#define KEYCODE_COMBINING_ACUTE_ACCENT_BELOW                    UCS_COMBINING_ACUTE_ACCENT_BELOW
#define KEYCODE_COMBINING_LEFT_TACK_BELOW                       UCS_COMBINING_LEFT_TACK_BELOW
#define KEYCODE_COMBINING_RIGHT_TACK_BELOW                      UCS_COMBINING_RIGHT_TACK_BELOW
#define KEYCODE_COMBINING_LEFT_ANGLE_BELOW                      UCS_COMBINING_LEFT_ANGLE_BELOW
#define KEYCODE_COMBINING_HORN                                  UCS_COMBINING_HORN
#define KEYCODE_COMBINING_LEFT_HALF_RING_BELOW                  UCS_COMBINING_LEFT_HALF_RING_BELOW
#define KEYCODE_COMBINING_UP_TACK_BELOW                         UCS_COMBINING_UP_TACK_BELOW
#define KEYCODE_COMBINING_DOWN_TACK_BELOW                       UCS_COMBINING_DOWN_TACK_BELOW
#define KEYCODE_COMBINING_PLUS_SIGN_BELOW                       UCS_COMBINING_PLUS_SIGN_BELOW
#define KEYCODE_COMBINING_MINUS_SIGN_BELOW                      UCS_COMBINING_MINUS_SIGN_BELOW
#define KEYCODE_COMBINING_PALATALIZED_HOOK_BELOW                UCS_COMBINING_PALATALIZED_HOOK_BELOW
#define KEYCODE_COMBINING_RETROFLEX_HOOK_BELOW                  UCS_COMBINING_RETROFLEX_HOOK_BELOW
#define KEYCODE_COMBINING_DOT_BELOW                             UCS_COMBINING_DOT_BELOW
#define KEYCODE_COMBINING_DIAERESIS_BELOW                       UCS_COMBINING_DIAERESIS_BELOW
#define KEYCODE_COMBINING_RING_BELOW                            UCS_COMBINING_RING_BELOW
#define KEYCODE_COMBINING_COMMA_BELOW                           UCS_COMBINING_COMMA_BELOW
#define KEYCODE_COMBINING_CEDILLA                               UCS_COMBINING_CEDILLA
#define KEYCODE_COMBINING_OGONEK                                UCS_COMBINING_OGONEK
#define KEYCODE_COMBINING_VERTICAL_LINE_BELOW                   UCS_COMBINING_VERTICAL_LINE_BELOW
#define KEYCODE_COMBINING_BRIDGE_BELOW                          UCS_COMBINING_BRIDGE_BELOW
#define KEYCODE_COMBINING_INVERTED_DOUBLE_ARCH_BELOW            UCS_COMBINING_INVERTED_DOUBLE_ARCH_BELOW
#define KEYCODE_COMBINING_CARON_BELOW                           UCS_COMBINING_CARON_BELOW
#define KEYCODE_COMBINING_CIRCUMFLEX_ACCENT_BELOW               UCS_COMBINING_CIRCUMFLEX_ACCENT_BELOW
#define KEYCODE_COMBINING_BREVE_BELOW                           UCS_COMBINING_BREVE_BELOW
#define KEYCODE_COMBINING_INVERTED_BREVE_BELOW                  UCS_COMBINING_INVERTED_BREVE_BELOW
#define KEYCODE_COMBINING_TILDE_BELOW                           UCS_COMBINING_TILDE_BELOW
#define KEYCODE_COMBINING_MACRON_BELOW                          UCS_COMBINING_MACRON_BELOW
#define KEYCODE_COMBINING_LOW_LINE                              UCS_COMBINING_LOW_LINE
#define KEYCODE_COMBINING_DOUBLE_LOW_LINE                       UCS_COMBINING_DOUBLE_LOW_LINE
#define KEYCODE_COMBINING_TILDE_OVERLAY                         UCS_COMBINING_TILDE_OVERLAY
#define KEYCODE_COMBINING_SHORT_STROKE_OVERLAY                  UCS_COMBINING_SHORT_STROKE_OVERLAY
#define KEYCODE_COMBINING_LONG_STROKE_OVERLAY                   UCS_COMBINING_LONG_STROKE_OVERLAY
#define KEYCODE_COMBINING_SHORT_SOLIDUS_OVERLAY                 UCS_COMBINING_SHORT_SOLIDUS_OVERLAY
#define KEYCODE_COMBINING_LONG_SOLIDUS_OVERLAY                  UCS_COMBINING_LONG_SOLIDUS_OVERLAY
#define KEYCODE_COMBINING_RIGHT_HALF_RING_BELOW                 UCS_COMBINING_RIGHT_HALF_RING_BELOW
#define KEYCODE_COMBINING_INVERTED_BRIDGE_BELOW                 UCS_COMBINING_INVERTED_BRIDGE_BELOW
#define KEYCODE_COMBINING_SQUARE_BELOW                          UCS_COMBINING_SQUARE_BELOW
#define KEYCODE_COMBINING_SEAGULL_BELOW                         UCS_COMBINING_SEAGULL_BELOW
#define KEYCODE_COMBINING_X_ABOVE                               UCS_COMBINING_X_ABOVE
#define KEYCODE_COMBINING_VERTICAL_TILDE                        UCS_COMBINING_VERTICAL_TILDE
#define KEYCODE_COMBINING_DOUBLE_OVERLINE                       UCS_COMBINING_DOUBLE_OVERLINE
#define KEYCODE_COMBINING_GRAVE_TONE_MARK                       UCS_COMBINING_GRAVE_TONE_MARK
#define KEYCODE_COMBINING_ACUTE_TONE_MARK                       UCS_COMBINING_ACUTE_TONE_MARK
#define KEYCODE_COMBINING_GREEK_PEROSPOMENI                     UCS_COMBINING_GREEK_PEROSPOMENI
#define KEYCODE_COMBINING_GREEK_KORONIS                         UCS_COMBINING_GREEK_KORONIS
#define KEYCODE_COMBINING_GREEK_DIALYTIKA                       UCS_COMBINING_GREEK_DIALYTIKA
#define KEYCODE_COMBINING_GREEK_YPOGEGRAMMENI                   UCS_COMBINING_GREEK_YPOGEGRAMMENI
#define KEYCODE_COMBINING_DOUBLE_TILDE                          UCS_COMBINING_DOUBLE_TILDE
#define KEYCODE_COMBINING_DOUBLE_INVERTED_BREVE                 UCS_COMBINING_DOUBLE_INVERTED_BREVE

#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/branches/7.0.0/trunk/hardware/devi/public/sys/keycodes.h $ $Rev: 811496 $")
#endif
