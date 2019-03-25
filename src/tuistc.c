/*-------------------------------------------------------------------
 * File name: tuistc.c
 * Author: Seree Rakwong
 * Date: 17-SEP-18
 *-----------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __USE_CURSES__
#include <curses.h>
#endif

#include "tui.h"

/*-------------------------------------------------------------------
 * STATIC functions
 *-----------------------------------------------------------------*/
TVOID _TSTC_OnPaint(TWND wnd, TDC dc);
TLONG _TSTC_OnCreate(TWND wnd);
TLONG STATICPROC(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam);

TLONG _TSTC_OnCreate(TWND wnd)
{
  TuiEnableWnd(wnd, TW_DISABLE);
  return TUI_CONTINUE;
}

TVOID _TSTC_OnPaint(TWND wnd, TDC dc)
{
  TUI_CHAR buf[TUI_MAX_WNDTEXT+1];
  TUI_CHAR text[TUI_MAX_WNDTEXT+1];
  TRECT rc;
  TDWORD attrs;

  if (TuiIsWndVisible(wnd))
  {
    TuiGetWndRect(wnd, &rc);
    
    TuiGetWndText(wnd, text, TUI_MAX_WNDTEXT);
    TuiPrintTextAlignment(buf, text, rc.cols, TuiGetWndStyle(wnd));
    
    attrs = TuiGetWndTextAttrs(wnd);
    if (attrs)
    {
        TuiDrawText(dc, rc.y, rc.x, buf, attrs);
    }
    else
    {
        TuiDrawText(dc, rc.y, rc.x, buf, TuiGetSysColor(COLOR_WNDTEXT));
    }
  }
}

TLONG STATICPROC(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam)
{
  switch (msg)
  {
    case TWM_PAINT:
    {
      _TSTC_OnPaint(wnd, TuiGetDC(wnd));
      return 0;
    }
    case TWM_CREATE:
    {
      return _TSTC_OnCreate(wnd);
    }
  }
  return TuiDefWndProc(wnd, msg, wparam, lparam);
}

