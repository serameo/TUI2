/*-------------------------------------------------------------------
 * File name: tuidefs.h
 * Author: Seree Rakwong
 * Date: 12-APR-19
 *-----------------------------------------------------------------*/
#ifndef __TUI_DEFINES_H__
#define __TUI_DEFINES_H__

#include <curses.h>

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------
 * defines
 *-----------------------------------------------------------------*/

#define TUI_MAX_WNDTEXT    80
/*-------------------------------------------------------------------
 * types
 *-----------------------------------------------------------------*/
/*-------------------------------------------------------------------
 * defines
 *-----------------------------------------------------------------*/
#define TUI_CONTINUE        1
#define TUI_OK              0
#define TUI_ERROR          -1
#define TUI_MEM            -2

/* miscellaneous */

#define TVK_TAB            0x09
#define TVK_ENTER          0x0A

#define TVK_SPACE          0x20
#ifdef __USE_CURSES__
#define TVK_BTAB           KEY_BTAB
#define TVK_BACK           KEY_BACKSPACE
#define TVK_PRIOR          KEY_PPAGE
#define TVK_NEXT           KEY_NPAGE
#define TVK_END            KEY_END
#define TVK_HOME           KEY_HOME
#define TVK_LEFT           KEY_LEFT
#define TVK_UP             KEY_UP
#define TVK_RIGHT          KEY_RIGHT
#define TVK_DOWN           KEY_DOWN
#define TVK_INSERT         KEY_IC
#define TVK_DELETE         KEY_DC
#define TVK_HELP           KEY_HELP
#else /* __USE_CURSES__*/
#define TVK_BACK           0x08
#define TVK_PRIOR          0x21
#define TVK_NEXT           0x22
#define TVK_END            0x23
#define TVK_HOME           0x24
#define TVK_LEFT           0x25
#define TVK_UP             0x26
#define TVK_RIGHT          0x27
#define TVK_DOWN           0x28
#define TVK_INSERT         0x2D
#define TVK_DELETE         0x2E
#define TVK_HELP           0x2F
#endif /* __USE_CURSES__*/

#define TVK_ESCAPE         0x1B
#define TVK_NUMPAD0        0x60
#define TVK_NUMPAD1        0x61
#define TVK_NUMPAD2        0x62
#define TVK_NUMPAD3        0x63
#define TVK_NUMPAD4        0x64
#define TVK_NUMPAD5        0x65
#define TVK_NUMPAD6        0x66
#define TVK_NUMPAD7        0x67
#define TVK_NUMPAD8        0x68
#define TVK_NUMPAD9        0x69
#define TVK_MULTIPLY       0x6A
#define TVK_ADD            0x6B
#define TVK_SEPARATOR      0x6C
#define TVK_SUBTRACT       0x6D
#define TVK_DECIMAL        0x6E
#define TVK_DIVIDE         0x6F
#ifdef __USE_CURSES__
#define TVK_F1             KEY_F(1)
#define TVK_F2             KEY_F(2)
#define TVK_F3             KEY_F(3)
#define TVK_F4             KEY_F(4)
#define TVK_F5             KEY_F(5)
#define TVK_F6             KEY_F(6)
#define TVK_F7             KEY_F(7)
#define TVK_F8             KEY_F(8)
#define TVK_F9             KEY_F(9)
#define TVK_F10            KEY_F(10)
#define TVK_F11            KEY_F(11)
#define TVK_F12            KEY_F(12)
#define TVK_F13            KEY_F(13)
#define TVK_F14            KEY_F(14)
#define TVK_F15            KEY_F(15)
#define TVK_F16            KEY_F(16)
#define TVK_F17            KEY_F(17)
#define TVK_F18            KEY_F(18)
#define TVK_F19            KEY_F(19)
#define TVK_F20            KEY_F(20)
#define TVK_F21            KEY_F(21)
#define TVK_F22            KEY_F(22)
#define TVK_F23            KEY_F(23)
#define TVK_F24            KEY_F(24)
#else /* __USE_CURSES__ */
#define TVK_F1             0x70
#define TVK_F2             0x71
#define TVK_F3             0x72
#define TVK_F4             0x73
#define TVK_F5             0x74
#define TVK_F6             0x75
#define TVK_F7             0x76
#define TVK_F8             0x77
#define TVK_F9             0x78
#define TVK_F10            0x79
#define TVK_F11            0x7A
#define TVK_F12            0x7B
#define TVK_F13            0x7C
#define TVK_F14            0x7D
#define TVK_F15            0x7E
#define TVK_F16            0x7F
#define TVK_F17            0x80
#define TVK_F18            0x81
#define TVK_F19            0x82
#define TVK_F20            0x83
#define TVK_F21            0x84
#define TVK_F22            0x85
#define TVK_F23            0x86
#define TVK_F24            0x87
#endif /* __USE_CURSES__ */
/*
 * 0x88 - 0x8F : unassigned
 */

#define TVK_NUMLOCK        0x90
#define TVK_SCROLL         0x91

/*-------------------------------------------------------------------
 * types
 *-----------------------------------------------------------------*/

#define TUI_TRUE            (TBOOL)1
#define TUI_FALSE           (TBOOL)0

#define TUI_MIN(a, b)       ((a) < (b) ? (a) : (b))
#define TUI_MAX(a, b)       ((a) > (b) ? (a) : (b))

#define TUI_DEQUEUE_TIMEWAIT      (3000)

/* colors */
enum
{
  TUI_COLOR_BLACK,
  TUI_COLOR_RED,
  TUI_COLOR_GREEN,
  TUI_COLOR_BLUE,
  TUI_COLOR_MAGENTA,
  TUI_COLOR_CYAN,
  TUI_COLOR_YELLOW,
  TUI_COLOR_WHITE
};
enum
{
  BLACK_BLACK,
  BLACK_RED,
  BLACK_GREEN,
  BLACK_YELLOW,
  BLACK_BLUE,
  BLACK_MAGENTA,
  BLACK_CYAN,
  BLACK_WHITE,
  RED_BLACK,
  RED_RED,
  RED_GREEN,
  RED_YELLOW,
  RED_BLUE,
  RED_MAGENTA,
  RED_CYAN,
  RED_WHITE,
  GREEN_BLACK,
  GREEN_RED,
  GREEN_GREEN,
  GREEN_YELLOW,
  GREEN_BLUE,
  GREEN_MAGENTA,
  GREEN_CYAN,
  GREEN_WHITE,
  YELLOW_BLACK,
  YELLOW_RED,
  YELLOW_GREEN,
  YELLOW_YELLOW,
  YELLOW_BLUE,
  YELLOW_MAGENTA,
  YELLOW_CYAN,
  YELLOW_WHITE,
  BLUE_BLACK,
  BLUE_RED,
  BLUE_GREEN,
  BLUE_YELLOW,
  BLUE_BLUE,
  BLUE_MAGENTA,
  BLUE_CYAN,
  BLUE_WHITE,
  MAGENTA_BLACK,
  MAGENTA_RED,
  MAGENTA_GREEN,
  MAGENTA_YELLOW,
  MAGENTA_BLUE,
  MAGENTA_MAGENTA,
  MAGENTA_CYAN,
  MAGENTA_WHITE,
  CYAN_BLACK,
  CYAN_RED,
  CYAN_GREEN,
  CYAN_YELLOW,
  CYAN_BLUE,
  CYAN_MAGENTA,
  CYAN_CYAN,
  CYAN_WHITE,
  WHITE_BLACK,
  WHITE_RED,
  WHITE_GREEN,
  WHITE_YELLOW,
  WHITE_BLUE,
  WHITE_MAGENTA,
  WHITE_CYAN,
  WHITE_WHITE,
  /* no color */
  COLOR_MAX
};

enum
{
  THEME_STANDARD = 0,
  THEME_LHS,
  THEME_ASP,
  THEME_CNS,
  THEME_KTZ,
  THEME_YUANTA,
  THEME_KSS,
  THEME_PST,
  THEME_MBKET,
  THEME_AIRA,
  THEME_ASL,
  THEME_MERCHANT,
  /* standard */
  THEME_LAST
};

enum /*THEME_STANDARD*/
{
  /* simple theme */
  COLOR_WNDTEXT = 0,
  COLOR_BTNENABLED,
  COLOR_BTNDISABLED,
  COLOR_BTNFOCUSED,
  COLOR_HDRTEXT,
  COLOR_EDTTEXT,
  COLOR_LBXTEXT,
  COLOR_WNDTITLE,
  COLOR_HIGHLIGHTED,
  COLOR_DISABLED,
  /* last color */
  COLOR_LAST
};


#ifdef __cplusplus
}
#endif
#endif /*__TUI_DEFINES_H__*/

