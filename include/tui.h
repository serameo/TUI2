/*-------------------------------------------------------------------
 * File name: tui.h
 * Author: Seree Rakwong
 * Email: meo.rakwong@gmail.com
 * Date: 28-SEP-18
 *-----------------------------------------------------------------*/
#ifndef __TEXTUSERINTERFACE_H__
#define __TEXTUSERINTERFACE_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

#include "tuidefs.h"
#include "tuitypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * TuiShowMsgBox()
 *    Show message box
 */
TVOID TuiShowMsgBox(
  TWND      wnd,
  TUINT     id,               /* user defined TFM_USER + #no to handle this value in TWM_NOTIFY */
  TLPCSTR   caption,
  TLPCSTR   text,
  TUINT     flags,            /* combination from MB_XXX  */
  TINT      show);            /* TW_SHOW or TW_HIDE       */

/*
 * TuiShowInputBox()
 *    Show dynamically input box
 */
TVOID TuiShowInputBox(
  TWND      wnd,
  TUINT     id,
  TLPCSTR   caption,
  TLPCSTR   text,
  TUINT     flags,
  TINT      limit,            /* limit input    */
  TDWORD    edtstyle,         /* TES_XXX        */
  TLPCSTR   deftext,          /* default input  */
  TINT      show);

/*
 * TuiShowLineInputBox()
 *    Show dynamically input box but one line 1 character input
 */
TVOID TuiShowLineInputBox(
  TWND      wnd,
  TUINT     id,
  TINT      y,                /* y-position */
  TINT      x,                /* x-position */
  TLPCSTR   text,
  TLPCSTR   deftext,
  TLPCSTR   validch,          /* valid characters */
  TINT      align,            /* DT_CENTER or 0   */
  TINT      show);

TVOID TuiShowPage(
  TWND      wnd,
  TINT      npage,
  TINT      show
);

TVOID TuiSetCurPage(
  TWND      wnd,
  TINT      npage
);

TINT TuiGetCurPage(
  TWND      wnd
);

/*-------------------------------------------------------------------
 * window functions
 *-----------------------------------------------------------------*/
/*
 * TuiStartup()
 *   Start TUI environment
 */
TLONG TuiStartup();
/*
 * TuiShutdown()
 *   End TUI environment
 */
TVOID TuiShutdown();
/*
 *
 */
const TWND TuiGetDummyWnd();
/*
 * TuiGetEnv()
 *   Get TUI environment
 */
TENV TuiGetEnv();
/*
 * TuiSetNextMove()
 *   Set next key to move to the next control
 *   Default TVK_ENTER (ENTER)
 */
TLONG TuiSetNextMove(TLONG nextmove);
/*
 * TuiSetPrevMove()
 *   Set previous key to move to the previous control
 *   Default KEY_BTAB (Shift + TAB)
 */
TLONG TuiSetPrevMove(TLONG prevmove);
/*
 * TuiLoadAccel()
 *   Load accelerator table into the TUI environment
 */
TUI_LONG TuiLoadAccel(TUI_ACCEL* accel);
/*
 * TuiGetSysColor()
 *   Get system color
 *   see also, COLOR_XXX
 */
TDWORD TuiGetSysColor(TINT clridx);
/*
 * TuiGetReverseSysColor()
 *   Get system color and reverse it
 *   see also, COLOR_XXX
 */
TDWORD TuiGetReverseSysColor(TINT clridx);
/*
 * TuiGetColor()
 *   Directly get color from index
 *   see also, BLACK_XXX, RED_XXX, and so on.
 */
TDWORD TuiGetColor(TINT clridx);
/*
 * TuiReverseColor()
 *   Directly reverse color and reverse it
 *   see also, COLOR_XXX
 */
TDWORD TuiReverseColor(TDWORD clr);
/*
 * TuiUnderlineText()
 *   Make underline attrinute
 */
TDWORD TuiUnderlineText(TDWORD clr);
/*
 * TuiGetSysColorTheme()
 *   Get system color from theme
 *   see also, COLOR_XXX for clridx
 *             THEME_XXX for themeidx
 */
TDWORD TuiGetSysColorTheme(TINT themeidx, TINT clridx);
/*
 * TuiGetReverseSysColorTheme()
 *   Get reversed system color from theme
 *   see also, COLOR_XXX for clridx
 *             THEME_XXX for themeidx
 */
TDWORD TuiGetReverseSysColorTheme(TINT themeidx, TINT clridx);
/*
 * TuiGetTheme()
 *   Get current theme index, default is THEME_STANDARD
 */
TINT   TuiGetTheme();
/*
 * TuiSetTheme()
 *   Set theme index, return previous theme
 */
TINT   TuiSetTheme(TINT themeidx);

/* window message functions */
/*
 * TuiGetChar()
 *   Synchronously get character input from screen
 */
TLONG  TuiGetChar();
/*
 * TuiGetWndFrame()
 *   find the frame window
 */
TWND   TuiGetWndFrame(TWND wnd);
/*
 * TuiDefWndProc()
 *   All windows MUST be called at its window procedure.
 *   wnd - window handle
 *   msg - window message
 *   TWPARAM - first parameter
 *   TLPARAM - second parameter
 */
TLONG TuiDefWndProc(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam);
/*
 * TuiRegisterCls()
 *   All window class MUST be registered before creating its window instance
 *   clsname - a unique name in an application
 *   wndproc - window procedure
 */
TLONG TuiRegisterCls(TLPCSTR clsname, TWNDPROC wndproc);
/*
 * TuiGetMsg()
 *   Synchronously get message input from screen
 *   msg - output from user input
 */
TLONG TuiGetMsg(TMSG* msg);
/*
 * TuiDispatchMsg()
 *   Dispatch message from application and user input
 *   msg - input/output from user input
 */
TLONG TuiDispatchMsg(TMSG* msg);
/*
 * TuiTranslateMsg()
 *   Translate message from the application and user input
 *   msg - input/output from user input
 */
TLONG TuiTranslateMsg(TMSG* msg);
/*
 * TuiPostQuitMsg()
 *   Post message to quit an application
 */
TLONG TuiPostQuitMsg(TLONG exitcode);
/*
 * TuiSendMsg()
 *   Synchronously send message to window handle
 */
TLONG TuiSendMsg(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam);
/*
 * TuiPostMsg()
 *   Asynchronously send message to window handle
 * The message will be dispatched once the application call TuiDispatchMsg()
 *
 * This function useful when the application does not need to wait response immediately
 */
TLONG TuiPostMsg(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam);


/*
 * TuiDefFrameWndProc()
 *   This inherits from TuiDefWndProc() but it is used by main window
 *   wnd - window handle
 *   msg - window message
 *   TWPARAM - first parameter
 *   TLPARAM - second parameter
 */
TLONG TuiDefFrameWndProc(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam);

/* window functions */
/*
 * TuiCreateWnd()
 *   Create a window object
 */
TWND TuiCreateWnd(
  TLPCSTR   clsname,       /* class name must be registered before calling this function */
  TLPCSTR   wndname,       /* window name */
  TDWORD    style,         /* window style, see TWS_XXX */
  TINT      y,             /* y-position       */
  TINT      x,             /* x-position       */
  TINT      lines,         /* window lines     */
  TINT      cols,          /* window columns   */
  TWND      parent,        /* parent of window */
  TINT      id,            /* window id        */
  TLPVOID   param          /* user parameter defined */
);
/*
 * TuiCreateWnd()
 *   Create a window object
 */
TWND TuiCreateWndEx(
  TLPCSTR    clsname,       /* class name must be registered before calling this function */
  TLPCSTR    wndname,       /* window name */
  TDWORD    style,          /* window style, see TWS_XXX */
  TDWORD    exstyle,        /* window style, see TWS_EXxxx */
  TINT      y,              /* y-position       */
  TINT      x,              /* x-position       */
  TINT      lines,          /* window lines     */
  TINT      cols,           /* window columns   */
  TWND      parent,         /* parent of window */
  TINT      id,             /* window id        */
  TLPCSTR    infotext,      /* window info */
  TLPVOID    param          /* user parameter defined */
);


/*
 * TuiCreateWndTempl()
 *   Create a window object from template
 * NB, the first object created must be a window frame
 *     the last object MUST be all nil values
 */
TWND TuiCreateWndTempl(
  WNDTEMPL* templs,
  TLPVOID    param
);

/*
 * TuiCreateFrameWnd()
 *   Create a window object from template
 * NB, as same as TuiCreateWndTempl(), but the first object must be
 *     its child.
 *     the last object MUST be all nil values
 */
TWND TuiCreateFrameWnd(
  TLPCSTR   clsname,
  TLPCSTR   wndname,
  TDWORD    style,
  TINT      y,
  TINT      x,
  TINT      lines,
  TINT      cols,
  WNDTEMPL* templs,
  TLPVOID    param
);

/*
 * TuiFrameWndCreatePage()
 *   Create page control object
 */
TLONG TuiFrameWndCreatePage(
  TWND      wnd,
  WNDTEMPL* templs,
  TLPVOID    param
);

/*
 * TuiCreateFrameWndEx()
 *   Create a window object from template
 * NB, as same as TuiCreateWndTempl(), but the first object must be
 *     its child.
 *     the last object MUST be all nil values
 */
TWND TuiCreateFrameWndEx(
  TLPCSTR   clsname,
  TLPCSTR   wndname,
  TDWORD    style,
  TDWORD    exstyle,
  TINT      y,
  TINT      x,
  TINT      lines,
  TINT      cols,
  FRMWNDTEMPL* templs,
  TLPVOID    param
);

/*
 * TuiFrameWndCreatePage()
 *   Create page control object
 */
TLONG TuiFrameWndCreatePageEx(
  TWND      wnd,
  FRMWNDTEMPL* templs,
  TLPVOID    param
);

/*
 * TuiDestroyWnd()
 *   Destroy window object
 * This function will destroy all children that
 * attached on wnd object, otherwise the application must be
 * destroy by self
 */
TVOID   TuiDestroyWnd(TWND wnd);
/*
 * TuiGetActiveChildWnd()
 *   Get the current active child of window
 */
TWND   TuiGetActiveChildWnd(TWND wnd);
/*
 * TuiGetFirstActiveChildWnd()
 *   Get the first child of window that could be got a focus
 */
TWND   TuiGetFirstActiveChildWnd(TWND wnd);
/*
 * TuiGetLastActiveChildWnd()
 *   Get the last child of window that could be got a focus
 */
TWND   TuiGetLastActiveChildWnd(TWND wnd);
/*
 * TuiGetNextActiveChildWnd()
 *   Get the next child of window that could be got a focus
 */
TWND   TuiGetNextActiveChildWnd(TWND wnd);
/*
 * TuiGetPrevActiveChildWnd()
 *   Get the previous child of window that could be got a focus
 */
TWND   TuiGetPrevActiveChildWnd(TWND wnd);
/*
 * TuiGetFirstChildWnd()
 *   Get the first child of window
 */
TWND   TuiGetFirstChildWnd(TWND wnd);
/*
 * TuiGetLastChildWnd()
 *   Get the last child of window
 */
TWND   TuiGetLastChildWnd(TWND wnd);
/*
 * TuiGetActiveWnd()
 *   System will return the active window frame
 */
TWND   TuiGetActiveWnd();
/*
 * TuiGetFirstWnd()
 *   System will return the first window frame
 */
TWND   TuiGetFirstWnd();
/*
 * TuiGetLastWnd()
 *   System will return the last window frame
 */
TWND   TuiGetLastWnd();
/*
 * TuiGetNextWnd()
 *   Return the next window from wnd object
 */
TWND   TuiGetNextWnd(TWND wnd);
/*
 * TuiGetPrevWnd()
 *   Return the previous window from wnd object
 */
TWND   TuiGetPrevWnd(TWND wnd);
/*
 * TuiInvalidateWnd()
 *   Call this to redraw the window object
 * NB. The application MUST NOT send TWM_PATINT directly to window object
 */
TLONG   TuiInvalidateWnd(TWND wnd);
/*
 * TuiInvalidateWndRect()
 *   Call this to redraw the window object
 * NB. The application MUST NOT send TWM_PATINT directly to window object
 */
TLONG   TuiInvalidateWndRect(TWND wnd, TRECT* rect);
/*
 * TuiShowWnd()
 *   Show window object
 *   show - TW_SHOW or TW_HIDE
 */
TLONG   TuiShowWnd(TWND wnd, TLONG show);
/*
 * TuiEnableWnd()
 *   Show window object
 *   show - TW_ENABLE or TW_DISABLE
 */
TLONG   TuiEnableWnd(TWND wnd, TLONG enable);
/*
 * TuiIsWndEnabled()
 *   Check if window object is enabled
 */
TLONG   TuiIsWndEnabled(TWND wnd);
/*
 * TuiIsWndVisible()
 *   Check if window object is visible
 */
TLONG   TuiIsWndVisible(TWND wnd);
/*
 * TuiGetWndItem()
 *   Get child control window
 */
TWND   TuiGetWndItem(TWND wnd, TINT ctlid);
/*
 * TuiGetWndText()
 *   Get window text
 *   outtext - output
 *   outlen  - maximum output
 * NB. Limitation of this library is the max window length is TUI_MAX_WNDTEXT
 */
TLONG   TuiGetWndText(TWND wnd, TLPSTR outtext, TLONG outlen);
/*
 * TuiSetWndText()
 *   Set window text
 * NB. Limitation of this library is the max window length is TUI_MAX_WNDTEXT
 */
TVOID   TuiSetWndText(TWND wnd, TLPCSTR text);
/*
 * TuiGetWndInfoText()
 *   Get window text
 *   outtext - output
 *   outlen  - maximum output
 * NB. Limitation of this library is the max window length is TUI_MAX_WNDTEXT
 */
TLONG   TuiGetWndInfoText(TWND wnd, TLPSTR outtext, TLONG outlen);
/*
 * TuiSetWndInfoText()
 *   Set window text
 * NB. Limitation of this library is the max window length is TUI_MAX_WNDTEXT
 */
TVOID   TuiSetWndInfoText(TWND wnd, TLPCSTR text);
/*
 * TuiGetParent()
 *   Get window parent
 */
TWND   TuiGetParent(TWND wnd);
/*
 * TuiSetFocus()
 *   Set window object to get focused
 */
TLONG   TuiSetFocus(TWND wnd);
/*
 * TuiGetFocus()
 *   Get the current active child window
 */
TWND   TuiGetFocus(TWND wnd);
/*
 *
 */
TUI_LONG TuiSetTimer(TWND wnd, TUI_UINT32 id, TUI_UINT32 timelapsed, TUI_TIMERPROC proc);
TUI_LONG TuiKillTimer(TWND wnd, TUI_UINT32 id);
TUI_LONG TuiSetTimerEvent(TWND wnd, TUI_UINT32 id, TUI_INT ev);
/*
 * TuiMoveWnd()
 *   Move window object
 */
TLONG   TuiMoveWnd(TWND wnd, TINT y, TINT x, TINT lines, TINT cols);

/*
 * TuiGetWndClsName()
 *   Get window class name
 */
TLONG   TuiGetWndClsName(TWND wnd, TLPSTR clsname, TLONG cb);
/*
 * TuiGetWndRect()
 *   Get window rectangle
 */
TLONG   TuiGetWndRect(TWND wnd, TRECT* rect);
/*
 * TuiGetCursorPos()
 *   Get cursor position
 */
TLONG   TuiGetCursorPos(TWND wnd, TPOS* pos);
/*
 * TuiSetCursorPos()
 *   Set cursor position
 */
TLONG   TuiSetCursorPos(TWND wnd, TPOS* pos);

/*
 * TuiGetWndStyle()
 *   Get window styles
 */
TDWORD  TuiGetWndStyle(TWND wnd);
/*
 * TuiSetWndStyle()
 *   Set window styles
 */
TDWORD  TuiSetWndStyle(TWND wnd, TDWORD styles);
/*
 * TuiGetWndStyleEx()
 *   Get window extended styles
 */
TDWORD  TuiGetWndStyleEx(TWND wnd);
/*
 * TuiSetWndStyleEx()
 *   Set window extended styles
 */
TDWORD  TuiSetWndStyleEx(TWND wnd, TDWORD exstyles);
/*
 * TuiGetWndTextAttrs()
 *   Get window text attributes
 */
TDWORD  TuiGetWndTextAttrs(TWND wnd);
/*
 * TuiSetWndTextAttrs()
 *   Set window text attributes
 */
TDWORD  TuiSetWndTextAttrs(TWND wnd, TDWORD attrs);
/*
 * TuiGetWndID()
 *   Get window id
 */
TUINT   TuiGetWndID(TWND wnd);
/*
 * TuiGetWndParam()
 *   Get window user defined object
 */
TLPVOID TuiGetWndParam(TWND wnd);
/*
 * TuiSetWndParam()
 *   Set window user defined object
 */
TLPVOID TuiSetWndParam(TWND wnd, TLPVOID);
/*
 * TuiIsWndValidate()
 *   Check if text is required validation
 * return TUI_CONTINUE if it is OK
 * otherwise return TUI_ERROR
 */
TLONG   TuiIsWndValidate(TWND wnd, TLPCSTR text);
/*
 * TuiSetWndValidateProc()
 *   Set window validate function
 */
VALIDATEPROC   TuiSetWndValidateProc(TWND wnd, VALIDATEPROC validateproc);
/*
 * TuiSetWndShowInfoProc()
 *   Set window validate function
 */
/* 
SHOWINFOPROC   TuiSetWndShowInfoProc(TWND wnd, SHOWINFOPROC showinfoproc);
*/

/*
 * TuiPrintTextAlignment()
 *   Helper function to prTINT text TINTo the box
 *   align - ALIGN_CENTER, ALIGN_LEFT(default), ALIGN_RIGHT
 */
TLONG TuiPrintTextAlignment(TLPSTR out, TLPCSTR in, TLONG limit, TINT align);
/*
 * TuiGetDC()
 *   Get window device context
 */
TDC  TuiGetDC(TWND wnd);
/*
 * TuiDrawText()
 *   Draw a string on screen
 */
TLONG TuiDrawText(TDC dc, TINT y, TINT x, TLPCSTR text, TDWORD attrs);
/*
 * TuiPutChar()
 *   Draw a character on screen
 */
TLONG TuiPutChar(TDC dc, TINT y, TINT x, TUI_CHAR ch, TDWORD attrs);
/*
 * TuiMoveYX()
 *   Move cursor to (y, x)
 */
TLONG TuiMoveYX(TDC dc, TINT, TINT);
/*
 * TuiGetYX()
 *   Get cursor position
 */
TLONG TuiGetYX(TDC dc, TINT*, TINT*);
/*
 * TuiDrawBorder()
 *   Draw border of rectangle with caption
 */
TLONG TuiDrawBorder(TDC dc, TRECT* rcwnd);
/*
 * TuiDrawBorderEx()
 *   Draw border of rectangle with caption
 */
TLONG TuiDrawBorderEx(TDC dc, TRECT* rcwnd, TDWORD attrs);
/*
 * TuiDrawFrame()
 *   Draw border of rectangle without caption
 */
TLONG TuiDrawFrame(TDC dc, TRECT* rcframe, TLPCSTR caption, TDWORD attrs);
/*
 * TuiDrawHLine()
 *   Draw border of rectangle without caption
 */
TLONG TuiDrawHLine(TDC dc, TINT y, TINT x, TINT nchars, TDWORD attrs);
/*
 * TuiDrawVLine()
 *   Draw border of rectangle without caption
 */
TLONG TuiDrawVLine(TDC dc, TINT y, TINT x, TINT nchars, TDWORD attrs);
/*
 * TuiDrawMultipleFrames()
 *   Draw multiple borders of rectangle without caption
 */
TLONG TuiDrawMultipleFrames(TDC dc, TRECT* rcframe, TLPCSTR caption, TDWORD attrs, TINT* widths);

TLONG TuiDrawVFrames(TDC dc, TRECT* rcframe, TINT* widths, TINT nframes, TDWORD attrs);
TLONG TuiDrawHFrames(TDC dc, TRECT* rcframe, TINT* heights, TINT nframes, TDWORD attrs);

#ifdef __cplusplus
}
#endif
#endif /*__TEXTUSERINTERFACE_H__*/

