/*-------------------------------------------------------------------
 * File name: tuidefs.h
 * Author: Seree Rakwong
 * Date: 12-APR-19
 *-----------------------------------------------------------------*/
#ifndef __TUI_DEFINES_H__
#define __TUI_DEFINES_H__

#ifdef __USE_CURSES__
#include <curses.h>
#endif

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

/* tty colors */
#define TTY_COLOR_DEFAULT             "[39;49m"
#define TTY_COLOR_BLACK               "[30;40m"
#define TTY_COLOR_RED                 "[31;41m"
#define TTY_COLOR_GREEN               "[32;42m"
#define TTY_COLOR_YELLOW              "[33;43m"
#define TTY_COLOR_BLUE                "[34;44m"
#define TTY_COLOR_MAGENTA             "[35;45m"
#define TTY_COLOR_CYAN                "[36;46m"
#define TTY_COLOR_WHITE               "[37;47m"
#define TTY_COLOR_BRIGHT_BLACK        "[90;100m"
#define TTY_COLOR_BRIGHT_RED          "[91;101m"
#define TTY_COLOR_BRIGHT_GREEN        "[92;102m"
#define TTY_COLOR_BRIGHT_YELLOW       "[93;103m"
#define TTY_COLOR_BRIGHT_BLUE         "[94;104m"
#define TTY_COLOR_BRIGHT_MAGENTA      "[95;105m"
#define TTY_COLOR_BRIGHT_CYAN         "[96;106m"
#define TTY_COLOR_BRIGHT_WHITE        "[97;107m"
/* tty attributes */
#define TTY_ATTR_BOLD                 "[1m"
#define TTY_ATTR_REVERSE              "[1;7m"
#define TTY_ATTR_OFF                  "[0m"
/* tty cursor */
#define TTY_FMT_CURSOR_DD             "[%d;%dH"

#define TTY_GOTO_LINE24               "[0;1m[24;H[K"   /* Set position at line 24 */
#define TTY_SET_APPKEYS               "="                    /* Set keypad to application key*/
#define TTY_SET_NUMKEYS               ">"                    /* Set keypad to numeric key */
#define TTY_SET_NOSCROLL              "[?7l"                 /* Set no scrolling */
#define TTY_ON_LINE25                 "?2$~?1$}"                /* Set line 25 to use */
#define TTY_OFF_LINE25                "?0$}"                    /* Reset line 25 */
#define TTY_OFF_CURSOR                "[?25l"                /* Set cursor off */
#define TTY_ON_CURSOR                 "[?25h"                /* Set cursor on */



/* windows */
#define TALIGN_LEFT             0
#define TALIGN_CENTER           1
#define TALIGN_RIGHT            2

#define TW_HIDE                 0
#define TW_SHOW                 1

#define TW_DISABLE              0
#define TW_ENABLE               1

/* window styles */
#define TWS_WINDOW              0x00000001
#define TWS_CHILD               0x00000002
#define TWS_VISIBLE             0x00000004
#define TWS_DISABLED            0x00000008
#define TWS_BORDER              0x00000010
#define TWS_LEFT                0x00000000             /* shared controls style */
#define TWS_CENTER              0x00010000
#define TWS_RIGHT               0x00020000

/* window messages */
#define TWM_FIRST               100
#define TWM_CREATE              (TWM_FIRST +    1)
#define TWM_DESTROY             (TWM_FIRST +    2)
#define TWM_INITDIALOG          (TWM_FIRST +    3) /* get when system initialized window frame */
#define TWM_PAINT               (TWM_FIRST +    4) /* paTINT window        */
#define TWM_SETFOCUS            (TWM_FIRST +    5) /* get focus           */
#define TWM_KILLFOCUS           (TWM_FIRST +    6) /* lost focus          */
#define TWM_KEYDOWN             (TWM_FIRST +    7) /* key down            */
#define TWM_KEYUP               (TWM_FIRST +    8) /* key up              */
#define TWM_CHAR                (TWM_FIRST +    9) /* character input     */
#define TWM_NOTIFY              (TWM_FIRST +   10) /* control sent notify to parent */
#define TWM_ERASEBK             (TWM_FIRST +   11) /* erase background    */
#define TWM_SETTEXT             (TWM_FIRST +   12) /* set window text     */
#define TWM_GETTEXT             (TWM_FIRST +   13) /* get window text     */
#define TWM_SETTEXTALIGN        (TWM_FIRST +   14) /* set text alignment  */
#define TWM_GETTEXTALIGN        (TWM_FIRST +   15) /* set text alignment  */
#define TWM_COMMAND             (TWM_FIRST +   16) /* control sent command to parent */
#define TWM_SETTEXTATTRS        (TWM_FIRST +   17) /* set text attributes */
#define TWM_GETTEXTATTRS        (TWM_FIRST +   18) /* set text attributes */
#define TWM_DRAWITEM            (TWM_FIRST +   19)
#define TWM_SETINFOTEXT         (TWM_FIRST +   20) /* set info text       */
#define TWM_GETINFOTEXT         (TWM_FIRST +   21) /* get info text       */
#define TWM_SHOW                (TWM_FIRST +   22) /* show window         */
#define TWM_ENABLE              (TWM_FIRST +   23) /* enable window       */
#define TWM_GETCURSOR           (TWM_FIRST +   24) /* get cursor          */
#define TWM_SETCURSOR           (TWM_FIRST +   25) /* set cursor          */
#define TWM_TIMER               (TWM_FIRST +   26) /* set timer           */
#define TWM_TIMER_SUSPEND       (TWM_FIRST +   27) /* timer suspend       */
#define TWM_TIMER_RESUME        (TWM_FIRST +   28) /* timer resume        */
#define TWM_SHOWMSGBOX          (TWM_FIRST +  100) /* TuiDefFrameWndProc  */
#define TWM_SHOWINPUTBOX        (TWM_FIRST +  101) /* TuiDefFrameWndProc  */
#define TWM_SHOWLINEINPUTBOX    (TWM_FIRST +  102) /* TuiDefFrameWndProc  */
#define TWM_INITPAGE            (TWM_FIRST +  103) /* TuiDefFrameWndProc  */
#define TWM_SETCURPAGE          (TWM_FIRST +  104) /* TuiDefFrameWndProc  */
#define TWM_GETCURPAGE          (TWM_FIRST +  105) /* TuiDefFrameWndProc  */
#define TWM_SHOWPAGE            (TWM_FIRST +  106) /* TuiDefFrameWndProc  */

/* application user messages */
#define TWM_USER                1000
#define TFM_USER                2000               /* use defined notification */

/* notification control message */
#define TCN_FIRST               (TWM_USER +   50)
#define TSN_FIRST               (TWM_USER +  100)
#define TEN_FIRST               (TWM_USER +  150)
#define TLBN_FIRST              (TWM_USER +  200)
#define TBN_FIRST               (TWM_USER +  250)
#define TLCN_FIRST              (TWM_USER +  300)
#define TTCN_FIRST              (TWM_USER +  350)

/* display info */
#define TCN_DISPLAYINFO         (TCN_FIRST +   1) /* see also DISPLAYINFO */

/*-------------------------------------------------------------------
 * frame window
 *-----------------------------------------------------------------*/

#define TUI_MAX_NMHDR        sizeof(RESPONSEMSGBOX)

#define TMB_YES               0x00000001
#define TMB_NO                0x00000002
#define TMB_CANCEL            0x00000004
#define TMB_YESNOCANCEL       (TMB_YES|TMB_NO|TMB_CANCEL)
#define TMB_YESNO             (TMB_YES|TMB_NO)

#define TMB_OK                0x00000008
#define TMB_OKCANCEL          (TMB_OK|TMB_CANCEL)

/* frame window */
#define TIDOK           10001
#define TIDYES          10002
#define TIDNO           10003
#define TIDCANCEL       10004
#define TIDINPUTBOX     10005


#define TFN_PAGECHANGING        (TFM_USER +    1)
#define TFN_PAGECHANGED         (TFM_USER +    2)


/*-------------------------------------------------------------------
 * static control
 *-----------------------------------------------------------------*/
#define TSTATIC                 "TSTATIC"
      
#define TSS_LEFT                TWS_LEFT
#define TSS_CENTER              TWS_CENTER
#define TSS_RIGHT               TWS_RIGHT
      
/*-------------------------------------------------------------------
 * edit control
 *-----------------------------------------------------------------*/
#define TEDITBOX                "TEDITBOX"

#define TES_LEFT                TWS_LEFT
#define TES_CENTER              TWS_CENTER
#define TES_RIGHT               TWS_RIGHT
#define TES_NUMBER              0x00040000
#define TES_UPPERCASE           0x00080000
#define TES_LOWERCASE           0x00100000
#define TES_PASSWORD            0x00200000
#define TES_APPENDMODE          0x00400000
#define TES_AUTOHSCROLL         0x00800000
#define TES_DECIMAL             0x01000000
#define TES_AUTODECIMALCOMMA    0x02000000
#define TES_UNDERLINE           0x04000000
#define TES_A2Z                 0x08000000
#define TES_AUTOSUFFIX          0x10000000
#define TES_NOTIFYKEYPRESSED    0x20000000

#define TEM_LIMITTEXT           (TWM_USER  +    1)
#define TEM_SETPASSWDCHAR       (TWM_USER  +    2)
#define TEM_SHOWPASSWDCHAR      (TWM_USER  +    3)
#define TEM_SETDECWIDTH         (TWM_USER  +    4)
#define TEM_SETVALIDSTRING      (TWM_USER  +    5)
#define TEM_SETVALIDMINMAX      (TWM_USER  +    6)

/* edit notified message */
#define TEN_CHANGED             (TEN_FIRST  +   0)
#define TEN_SETFOCUS            (TEN_FIRST  +   1)
#define TEN_KILLFOCUS           (TEN_FIRST  +   2)
#define TEN_KEYPRESSED          (TEN_FIRST  +   3)


/*-------------------------------------------------------------------
 * listbox control
 *-----------------------------------------------------------------*/
#define TLISTBOX                 "TLISTBOX"

#define TLB_OK                   TUI_OK
#define TLB_ERROR                TUI_ERROR
#define TLB_UNCHECKED            0
#define TLB_CHECKED              1

#define TLBS_LEFT               TWS_LEFT
#define TLBS_CENTER             TWS_CENTER
#define TLBS_RIGHT              TWS_RIGHT
#define TLBS_OWNERDRAW          0x00100000
#define TLBS_CHECKBOX           0x00200000
#define TLBS_RADIOBOX           0x00400000

#define TLBM_FIRST              (TWM_USER)
#define TLBM_ADDITEM            (TLBM_FIRST  +    1)
#define TLBM_DELETEITEM         (TLBM_FIRST  +    2)
#define TLBM_GETCURSEL          (TLBM_FIRST  +    3)
#define TLBM_SETCURSEL          (TLBM_FIRST  +    4)
#define TLBM_DELETEALLITEMS     (TLBM_FIRST  +    5)
#define TLBM_GETITEMCOUNT       (TLBM_FIRST  +    6)
#define TLBM_SETITEMDATA        (TLBM_FIRST  +    7)
#define TLBM_GETITEMDATA        (TLBM_FIRST  +    8)
#define TLBM_SETITEMTEXT        (TLBM_FIRST  +    9)
#define TLBM_GETITEMTEXT        (TLBM_FIRST  +   10)
#define TLBM_SETITEMCHECKED     (TLBM_FIRST  +   11)
#define TLBM_GETITEMCHECKED     (TLBM_FIRST  +   12)
#define TLBM_COUNTITEMCHECKED   (TLBM_FIRST  +   13)
#define TLBM_LAST               (TLBM_FIRST  +   50)

/* listbox notified message */
#define TLBN_SETFOCUS           (TLBN_FIRST  +    0)
#define TLBN_KILLFOCUS          (TLBN_FIRST  +    1)
#define TLBN_SELCHANGED         (TLBN_FIRST  +    2)
#define TLBN_ENTERITEM          (TLBN_FIRST  +    3)


/*-------------------------------------------------------------------
 * button control
 *-----------------------------------------------------------------*/
#define TBUTTON                 "TBUTTON"

#define TBS_RELEASED            0x0000
#define TBS_PRESSED             0x0001
#define TBS_FOCUSED             0x0002

#define TBM_PRESS               (TWM_USER  +    1)

#define TBN_SETFOCUS            (TBN_FIRST  +   0)
#define TBN_KILLFOCUS           (TBN_FIRST  +   1)

/*-------------------------------------------------------------------
 * listctrl control
 *-----------------------------------------------------------------*/
#define TLISTCTRL               "TLISTCTRL"

#define TLCS_NOHEADER           0x00010000
#define TLCS_EDITABLE           0x00020000
#define TLCS_LINEEDIT           0x00040000
#define TLCS_NOSELECTION        0x00080000
#define TLCS_NOBORDER           0x00100000

#define TLCM_FIRST              (TWM_USER     +   0)
#define TLCM_ADDCOLUMN          (TLCM_FIRST   +   1)
#define TLCM_DELETECOLUMN       (TLCM_FIRST   +   2)
#define TLCM_DELETEALLCOLUMNS   (TLCM_FIRST   +   3)
#define TLCM_ADDITEM            (TLCM_FIRST   +   4)
#define TLCM_DELETEITEM         (TLCM_FIRST   +   5)
#define TLCM_DELETEALLITEMS     (TLCM_FIRST   +   6)
#define TLCM_SETITEM            (TLCM_FIRST   +   7)
#define TLCM_GETITEM            (TLCM_FIRST   +   8)
#define TLCM_GETITEMCOUNT       (TLCM_FIRST   +   9)
#define TLCM_INVALIDATEITEM     (TLCM_FIRST   +  10)
#define TLCM_SETEDITSTYLE       (TLCM_FIRST   +  11)
#define TLCM_GETEDITSTYLE       (TLCM_FIRST   +  12)
#define TLCM_GETCURROW          (TLCM_FIRST   +  13)
#define TLCM_SETCURROW          (TLCM_FIRST   +  14)
#define TLCM_SETCOLWIDTH        (TLCM_FIRST   +  15)
#define TLCM_GETEDITBOX         (TLCM_FIRST   +  16)
#define TLCM_SETCURPAGE         (TLCM_FIRST   +  17)
#define TLCM_GETCURPAGE         (TLCM_FIRST   +  18)
#define TLCM_GETITEMSPERPAGE    (TLCM_FIRST   +  19)
#define TLCM_SETEDITABLECOLS    (TLCM_FIRST   +  20)
#define TLCM_LAST               (TLCM_FIRST   +  50)
/*
#define TLCN_FIRST              (TWM_USER +  300)
*/
/* listctrl states */

#define TLCT_VIEW                   0x0000
#define TLCT_BEGINEDITING           0x0001
#define TLCT_EDITING                0x0002
#define TLCT_ENDEDITING             0x0000
#define TLCT_BEGININSERTING         0x0001
#define TLCT_INSERTING              0x0002
#define TLCT_ENDINSERTING           0x0000
#define TLCT_BEGINMOVING            0x0001
#define TLCT_MOVINGCURSOR           0x0002
#define TLCT_ENDMOVING              0x0000



#define TLCN_SETFOCUS             (TLCN_FIRST  +    0)
#define TLCN_KILLFOCUS            (TLCN_FIRST  +    1)
#define TLCN_SELCHANGED           (TLCN_FIRST  +    2)
#define TLCN_BEGINMOVING          (TLCN_FIRST  +    3)
#define TLCN_MOVINGCURSOR         (TLCN_FIRST  +    4)
#define TLCN_ENDMOVING            (TLCN_FIRST  +    5)
#define TLCN_BEGINEDITROW         (TLCN_FIRST  +    6)
#define TLCN_ENDEDITROWOK         (TLCN_FIRST  +    7)
#define TLCN_ENDEDITROWCANCEL     (TLCN_FIRST  +    8)
#define TLCN_BEGINEDIT            (TLCN_FIRST  +    9)
#define TLCN_ENDEDITOK            (TLCN_FIRST  +   10)
#define TLCN_ENDEDITCANCEL        (TLCN_FIRST  +   11)
#define TLCN_BEGININSERTROW       (TLCN_FIRST  +   12)
#define TLCN_ENDINSERTROWOK       (TLCN_FIRST  +   13)
#define TLCN_ENDINSERTROWCANCEL   (TLCN_FIRST  +   14)


#define TLC_ENDEDITOK              1
#define TLC_ENDEDITCANCEL          0

#define TLCFM_TEXT                0x0001
#define TLCFM_ATTRS               0x0002
#define TLCFM_DATA                0x0004


/*-------------------------------------------------------------------
 * list page control
 * This class inherited from listctrl
 * but support only 3 columns
 *   - HEADER_CAPTION   : caption field (text)
 *   - HEADER_VALUE     : editable field
 *   - HEADER_SUFFIX    : optional field (text)
 *-----------------------------------------------------------------*/
#define TLISTPAGECTRL               "TLISTPAGECTRL"

#define TLPCM_FIRST                 (TLCM_LAST)
#define TLPCM_ADDITEM               (TLCM_ADDITEM)
#define TLPCM_DELETEITEM            (TLCM_DELETEITEM)
#define TLPCM_DELETEALLITEMS        (TLCM_DELETEALLITEMS)
#define TLPCM_SETITEMTEXT           (TLCM_SETITEM)
#define TLPCM_GETITEMTEXT           (TLCM_GETITEM)
#define TLPCM_GETITEMCOUNT          (TLCM_GETITEMCOUNT)
#define TLPCM_GETCURROW             (TLCM_GETCURROW)
#define TLPCM_SETCURROW             (TLCM_SETCURROW)
#define TLPCM_SETEDITSTYLE          (TLCM_SETEDITSTYLE)
#define TLPCM_GETEDITSTYLE          (TLCM_GETEDITSTYLE)
#define TLPCM_SETCURPAGE            (TLCM_SETCURPAGE)
#define TLPCM_GETCURPAGE            (TLCM_GETCURPAGE)
#define TLPCM_GETITEMSPERPAGE       (TLCM_GETITEMSPERPAGE)
#define TLPCM_NEXTPAGE              (TLCM_NEXTPAGE)
#define TLPCM_ADDITEMEX             (TLPCM_FIRST    +     1)
#define TLPCM_LAST                  (TLPCM_FIRST    +    50)

#define THEADER_CAPTION  0
#define THEADER_VALUE    1
#define THEADER_SUFFIX   2


/*-------------------------------------------------------------------
 * tree ctrl
 *-----------------------------------------------------------------*/
#define TTREECTRL                   "TTREECTRL"

#define TTCS_NOHIGHLIGHT        0x00100000
#define TTCS_FULLSECROW         0x00200000
#define TTCS_SHOWNODE           0x00400000

#define TTCM_FIRST                  (TWM_USER   +     0)
#define TTCM_INSERTITEM             (TTCM_FIRST +     1)
#define TTCM_DELETEITEM             (TTCM_FIRST +     2)
#define TTCM_SETITEM                (TTCM_FIRST +     3)
#define TTCM_GETITEM                (TTCM_FIRST +     4)
#define TTCM_FINDITEM               (TTCM_FIRST +     5)
#define TTCM_FINDNEXTITEM           (TTCM_FIRST +     6)
#define TTCM_SETFINDITEMPROC        (TTCM_FIRST +     7)
#define TTCM_COLLAPSEITEM           (TTCM_FIRST +     8)
#define TTCM_EXPANDITEM             (TTCM_FIRST +     9)
#define TTCM_SETSELITEM             (TTCM_FIRST +    10)
#define TTCM_GETSELITEM             (TTCM_FIRST +    11)
#define TTCM_EXPORTTOFILE           (TTCM_FIRST +    12)
#define TTCM_IMPORTFROMFILE         (TTCM_FIRST +    13)
#define TTCM_COLLAPSEALLITEMS       (TTCM_FIRST +    14)
#define TTCM_EXPANDALLITEMS         (TTCM_FIRST +    15)
#define TTCM_SETINDENTTEXT          (TTCM_FIRST +    16)
#define TTCM_GETINDENTTEXT          (TTCM_FIRST +    17)
#define TTCM_SETSHIFTEDTEXT         (TTCM_FIRST +    18)
#define TTCM_GETSHIFTEDTEXT         (TTCM_FIRST +    19)

/* Tree control notification messages */
#define TTCN_ITEMCHANGING           (TTCN_FIRST +     0)
#define TTCN_ITEMCHANGED            (TTCN_FIRST +     1)
#define TTCN_ITEMEXPANDING          (TTCN_FIRST +     2)
#define TTCN_ITEMEXPANDED           (TTCN_FIRST +     3)
#define TTCN_ITEMCOLLAPSING         (TTCN_FIRST +     4)
#define TTCN_ITEMCOLLAPSED          (TTCN_FIRST +     5)
#define TTCN_KILLFOCUS              (TTCN_FIRST +     6)
#define TTCN_SETFOCUS               (TTCN_FIRST +     7)
#define TTCN_ENTERITEM              (TTCN_FIRST  +    8)


/* device context */
#define TDT_LEFT              0x0001
#define TDT_CENTER            0x0002
#define TDT_RIGHT             0x0003

/* timer */
#define TTIMER_SUSPEND        0
#define TTIMER_RESUME         1
#define TTIMER_MILLISEC       1000
#define TTIMER_NANOSEC        1000000


/*-------------------------------------------------------------------
 * edit control macros
 *-----------------------------------------------------------------*/

#define TEDT_LimitText(edt, lim)    \
  TuiSendMsg(edt, TEM_LIMITTEXT, (TWPARAM)lim, (TLPARAM)0)
#define TEDT_SetPasswdChar(edt, ch)    \
  TuiSendMsg(edt, TEM_SETPASSWDCHAR, (TWPARAM)ch, (TLPARAM)0)
#define TEDT_ShowPasswdChar(edt, show)    \
  TuiSendMsg(edt, TEM_SHOWPASSWDCHAR, (TWPARAM)show, (TLPARAM)0)
#define TEDT_SetDecimalWidth(edt, wid)    \
  TuiSendMsg(edt, TEM_SETDECWIDTH, (TWPARAM)wid, (TLPARAM)0)
#define TEDT_SetValidString(edt, val)    \
  TuiSendMsg(edt, TEM_SETVALIDSTRING, (TWPARAM)0, (TLPARAM)val)


#define TEDT_SetValidMinMax(edt, mn, mx, on)    \
do {\
  VALIDMINMAX val; \
  val.min = mn; \
  val.max = mx; \
  TuiSendMsg(edt, TEM_SETVALIDMINMAX, \
    (TWPARAM)(on == TW_ENABLE ? TW_ENABLE : TW_DISABLE), (TLPARAM)&val); \
} while (0)



/*-------------------------------------------------------------------
 * listbox control macros
 *-----------------------------------------------------------------*/

#define TLB_AddItem(lbx, text)    \
  TuiSendMsg(lbx, TLBM_ADDITEM, (TWPARAM)0, (TLPARAM)text)
#define TLB_DeleteItem(lbx, idx)  \
  TuiSendMsg(lbx, TLBM_DELETEITEM, (TWPARAM)idx, (TLPARAM)0)
#define TLB_GetCurSel(lbx)        \
  TuiSendMsg(lbx, TLBM_GETCURSEL, (TWPARAM)0, (TLPARAM)0)
#define TLB_SetCurSel(lbx, idx)   \
  TuiSendMsg(lbx, TLBM_SETCURSEL, (TWPARAM)idx, (TLPARAM)0)
#define TLB_DeleteAllItems(lbx)   \
  TuiSendMsg(lbx, TLBM_DELETEALLITEMS, (TWPARAM)0, (TLPARAM)0)
#define TLB_GetItemCount(lbx)   \
  TuiSendMsg(lbx, TLBM_GETITEMCOUNT, (TWPARAM)0, (TLPARAM)0)
#define TLB_SetItemData(lbx, idx, data)   \
  TuiSendMsg(lbx, TLBM_SETITEMDATA, (TWPARAM)idx, (TLPARAM)data)
#define TLB_GetItemData(lbx, idx)   \
  (TLPARAM)TuiSendMsg(lbx, TLBM_GETITEMDATA, (TWPARAM)idx, (TLPARAM)0)
#define TLB_SetItemText(lbx, idx, text)   \
  TuiSendMsg(lbx, TLBM_SETITEMTEXT, (TWPARAM)idx, (TLPARAM)text)
#define TLB_GetItemText(lbx, idx, text)   \
  TuiSendMsg(lbx, TLBM_GETITEMTEXT, (TWPARAM)idx, (TLPARAM)text)
#define TLB_SetItemChecked(lbx, idx, check)   \
  TuiSendMsg(lbx, TLBM_SETITEMCHECKED, (TWPARAM)idx, (TLPARAM)check)
#define TLB_GetItemChecked(lbx, idx)   \
  TuiSendMsg(lbx, TLBM_GETITEMCHECKED, (TWPARAM)idx, (TLPARAM)0)
#define TLB_CountItemChecked(lbx)   \
  TuiSendMsg(lbx, TLBM_COUNTITEMCHECKED, (TWPARAM)0, (TLPARAM)0)


/*-------------------------------------------------------------------
 * listctrl control macros
 *-----------------------------------------------------------------*/

#define TLC_AddColumn(lc, text, width, al)    \
do {\
  THEADERITEM hdr; \
  hdr.caption = text; \
  hdr.cols    = width; \
  hdr.align   = al; \
  hdr.attrs   = TuiGetSysColor(COLOR_HDRTEXT); \
  hdr.editstyle = 0; \
  hdr.decwidth  = 2; \
  TuiSendMsg(lc, TLCM_ADDCOLUMN, (TWPARAM)0, (TLPARAM)&hdr); \
} while (0)

#define TLC_AddColumnEx(lc, text, width, al, at, es, dec)    \
do {\
  THEADERITEM hdr; \
  hdr.caption = text; \
  hdr.cols    = width; \
  hdr.align   = al; \
  hdr.attrs   = at; \
  hdr.editstyle = es; \
  hdr.decwidth  = dec; \
  TuiSendMsg(lc, TLCM_ADDCOLUMN, (TWPARAM)0, (TLPARAM)&hdr); \
} while (0)
  
#define TLC_DeleteColumn(lc, col)    \
  TuiSendMsg(lc, TLCM_DELETECOLUMN, (TWPARAM)col, (TLPARAM)0)
#define TLC_DeleteAllColumns(lc)    \
  TuiSendMsg(lc, TLCM_DELETEALLCOLUMNS, (TWPARAM)0, (TLPARAM)0)
#define TLC_AddItem(lc, text, nitems)    \
  TuiSendMsg(lc, TLCM_ADDITEM, (TWPARAM)nitems, (TLPARAM)text)
#define TLC_DeleteItem(lc, idx)    \
  TuiSendMsg(lc, TLCM_DELETEITEM, (TWPARAM)0, (TLPARAM)idx)
#define TLC_DeleteAllItems(lc)    \
  TuiSendMsg(lc, TLCM_DELETEALLITEMS, (TWPARAM)0, (TLPARAM)0)
#define TLC_SetItem(lc, flags, item)    \
  TuiSendMsg(lc, TLCM_SETITEM, (TWPARAM)flags, (TLPARAM)item)
#define TLC_GetItem(lc, flags, item)    \
  TuiSendMsg(lc, TLCM_GETITEM, (TWPARAM)flags, (TLPARAM)item)
#define TLC_GetItemCount(lc)    \
  TuiSendMsg(lc, TLCM_GETITEMCOUNT, (TWPARAM)0, (TLPARAM)0)
#define TLC_SetEditStyle(lc, col, es)    \
  TuiSendMsg(lc, TLCM_SETEDITSTYLE, (TWPARAM)col, (TLPARAM)es)
#define TLC_GetEditStyle(lc, col)    \
  (TDWORD)TuiSendMsg(lc, TLCM_GETEDITSTYLE, (TWPARAM)col, (TLPARAM)0)
#define TLC_GetCurRow(lc)    \
  TuiSendMsg(lc, TLCM_GETCURROW, (TWPARAM)0, (TLPARAM)0)
#define TLC_SetCurRow(lc, idx)    \
  TuiSendMsg(lc, TLCM_SETCURROW, (TWPARAM)0, (TLPARAM)idx)
#define TLC_SetCurPage(lc, pg)    \
  TuiSendMsg(lc, TLCM_SETCURPAGE, (TWPARAM)pg, (TLPARAM)0)
#define TLC_GetCurPage(lc)    \
  TuiSendMsg(lc, TLCM_GETCURPAGE, (TWPARAM)0, (TLPARAM)0)
#define TLC_GetItemsPerPage(lc)    \
  TuiSendMsg(lc, TLCM_GETITEMSPERPAGE, (TWPARAM)0, (TLPARAM)0)
#define TLC_GetEditBox(lc)    \
  (TWND)TuiSendMsg(lc, TLCM_GETEDITBOX, (TWPARAM)0, (TLPARAM)0)
#define TLC_SetEditableCols(lc, ncols, edtcols)    \
  TuiSendMsg(lc, TLCM_SETEDITABLECOLS, (TWPARAM)ncols, (TLPARAM)edtcols)

/*-------------------------------------------------------------------
 * list page control
 * This class inherited from listctrl
 * but support only 3 columns
 *   - THEADER_CAPTION   : caption field (text)
 *   - THEADER_VALUE     : editable field
 *   - THEADER_SUFFIX    : optional field (text)
 *-----------------------------------------------------------------*/

#define TLPC_AddItem(lc, text)    \
  TuiSendMsg(lc, TLPCM_ADDITEM, (TWPARAM)0, (TLPARAM)text)
#define TLPC_AddItemEx(lc, text, style)    \
  TuiSendMsg(lc, TLPCM_ADDITEMEX, (TWPARAM)style, (TLPARAM)text)
#define TLPC_DeleteItem(lc, idx)    \
  TuiSendMsg(lc, TLPCM_DELETEITEM, (TWPARAM)idx, (TLPARAM))
#define TLPC_DeleteAllItems(lc)    \
  TuiSendMsg(lc, TLPCM_DELETEALLITEMS, (TWPARAM)0, (TLPARAM)0)
#define TLPC_SetItemText(lc, indx, id, txt)  \
do {\
  SUBITEM item; \
  item.col   = id; \
  item.idx   = indx; \
  item.text  = txt;  \
  TuiSendMsg(lc, TLPCM_SETITEMTEXT, (TWPARAM)TLCFM_TEXT, (TLPARAM)&item) \
} while (0)
  
#define TLPC_GetItemText(lc, indx, id, outtext)  \
do {\
  TSUBITEM item; \
  item.col   = id; \
  item.idx   = indx; \
  item.text  = outtext;  \
  TuiSendMsg(lc, TLPCM_GETITEMTEXT, (TWPARAM)TLCFM_TEXT, (TLPARAM)&item) \
} while (0)

#define TLPC_GetItemCount(lc)  \
  TuiSendMsg(lc, TLPCM_GETITEMCOUNT, (TWPARAM)0, (TLPARAM)0)
#define TLPC_SetEditStyle(lc, idx, es)  \
  TuiSendMsg(lc, TLPCM_SETEDITSTYLE, (TWPARAM)idx, (TLPARAM)es)
#define TLPC_GetEditStyle(lc, idx)  \
  TuiSendMsg(lc, TLPCM_GETEDITSTYLE, (TWPARAM)idx, (TLPARAM)0)
#define TLPC_SetCurRow(lc, idx)    \
  TuiSendMsg(lc, TLPCM_SETCURROW, (TWPARAM)idx, (TLPARAM)0)
#define TLPC_GetCurRow(lc)    \
  TuiSendMsg(lc, TLPCM_GETCURROW, (TWPARAM)0, (TLPARAM)0)
#define TLPC_SetCurPage(lc, pg)    \
  TuiSendMsg(lc, TLPCM_SETCURPAGE, (TWPARAM)pg, (TLPARAM)0)
#define TLPC_GetCurPage(lc)    \
  TuiSendMsg(lc, TLPCM_GETCURPAGE, (TWPARAM)0, (TLPARAM)0)
#define TLPC_GetItemsPerPage(lc)    \
  TuiSendMsg(lc, TLPCM_GETITEMSPERPAGE, (TWPARAM)0, (TLPARAM)0)


/*-------------------------------------------------------------------
 * tree ctrl macros
 *-----------------------------------------------------------------*/

#define TTC_InsertItem(tc, parentitem, insertitem)    \
  (TTREEITEM*)TuiSendMsg(tc, TTCM_INSERTITEM, \
    (TWPARAM)(TTREEITEM*)(parentitem), \
    (TLPARAM)(TTREEITEMDATA*)(insertitem))
#define TTC_DeleteItem(tc, treeitem)    \
  TuiSendMsg(tc, TTCM_DELETEITEM, (TWPARAM)0, (TLPARAM)(TTREEITEM*)(treeitem))
#define TTC_SetItem(tc, item, treeitem)    \
  TuiSendMsg(tc, TTCM_SETITEM, \
    (TWPARAM)(TTREEITEM*)(item),\
    (TLPARAM)(TTREEITEMDATA*)(treeitem))
#define TTC_GetItem(tc, item, treeitem)    \
  TuiSendMsg(tc, TTCM_GETITEM,\
    (TWPARAM)(TTREEITEM*)(item),\
    (TLPARAM)(TTREEITEMDATA*)(treeitem))
#define TTC_FindItem(tc, finditem)    \
  (TTREEITEM*)TuiSendMsg(tc, TTCM_FINDITEM, (TWPARAM)0, (TLPARAM)(TTREEITEMDATA*)(finditem))
#define TTC_FindNextItem(tc, previtem)    \
  (TTREEITEM*)TuiSendMsg(tc, TTCM_FINDNEXTITEM, \
    (TWPARAM)(TTREEITEM*)(previtem), \
    (TLPARAM)(TTREEITEMDATA*)(finditem))
#define TTC_SetFindItemProc(tc, finditemproc)    \
  (LPTREEFINDITEMPROC)TuiSendMsg(tc, TTCM_SETFINDITEMPROC, (TWPARAM)0, (TLPARAM)(LPFINDITEMPROC)(finditemproc))
#define TTC_ExpandItem(tc, treeitem)    \
  TuiSendMsg(tc, TTCM_EXPANDITEM, (TWPARAM)0, (TLPARAM)(TTREEITEM*)(&treeitem))
#define TTC_CollapseItem(tc, treeitem)    \
  TuiSendMsg(tc, TTCM_COLLAPSEITEM, (TWPARAM)0, (TLPARAM)(TTREEITEM*)(&treeitem))
#define TTC_SetSelItem(tc, setitem)    \
  TuiSendMsg(tc, TTCM_SETSELITEM, \
    (TWPARAM)0,\
    (TLPARAM)(TTREEITEM*)(setitem))
#define TTC_GetSelItem(tc, getitem)    \
  (TLONG)TuiSendMsg(tc, TTCM_GETSELITEM,\
    (TWPARAM)0,\
    (TLPARAM)0)
#define TTC_ExportToFile(tc, fp, proc)\
  (TLONG)TuiSendMsg(tc, TTCM_EXPORTTOFILE, \
    (TWPARAM)(FILE*)(fp),\
    (TLPARAM)(LPTREEEXPORTPROC)(proc))
#define TTC_ImportFromFile(tc, fp, proc)\
  (TLONG)TuiSendMsg(tc, TTCM_IMPORTFROMFILE, \
    (TWPARAM)(FILE*)(fp),\
    (TLPARAM)(LPTREEIMPORTPROC)proc)
#define TTC_ExpandAllItems(tc)    \
  TuiSendMsg(tc, TTCM_EXPANDALLITEMS, (TWPARAM)0, (TLPARAM)(0))
#define TTC_CollapseAllItems(tc)    \
  TuiSendMsg(tc, TTCM_COLLAPSEALLITEMS, (TWPARAM)0, (TLPARAM)(0))



#ifdef __cplusplus
}
#endif
#endif /*__TUI_DEFINES_H__*/

