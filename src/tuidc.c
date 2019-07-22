/*-------------------------------------------------------------------
 * File name: tuidc.c
 * Author: Seree Rakwong
 * Date: 17-SEP-18
 *-----------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __USE_CURSES__
#include <curses.h>
#elif defined __USE_WIN32__
#include <windows.h>
#elif defined __VMS__
#include "tuivms.h"
#endif

#include "tui.h"

/*-------------------------------------------------------------------
 * DC functions
 *-----------------------------------------------------------------*/
/*
 https://en.wikipedia.org/wiki/ANSI_escape_code
*/

TLONG TuiPutChar(
  TDC dc,
  TINT y,
  TINT x,
  TUI_CHAR   ch,
  TDWORD  attrs)
{
#if defined __USE_CURSES__
  /* set attributes on */
  attron(attrs);
  /* print now */
  if (y >= LINES)
  {
    y = LINES - 1;
  }
  if (x >= COLS)
  {
    x = COLS - 1;
  }
  mvwaddch(dc->win, y, x, ch);
  /* set attributes off */
  attroff(attrs);
#elif defined __USE_WIN32__
  DWORD dwWritten = 0;
  COORD coord;
  coord.X = x;
  coord.Y = y;
  FillConsoleOutputAttribute(dc->wout, attrs, 1, coord, &dwWritten);
  FillConsoleOutputCharacter(dc->wout, ch, 1, coord, &dwWritten);
#elif defined __USE_VMS__
  TUI_CHAR sz[TUI_MAX_WNDTEXT+1];
  TUI_CHAR pos[TUI_MAX_WNDTEXT+1];
  TUI_CHAR at[TUI_MAX_WNDTEXT+1] = "";

  if (attrs)
  {
    strcpy(at, TTY_ATTR_REVERSE);
  }
  if (y >= VMS_ROWS)
  {
    y = VMS_ROWS - 1;
  }
  if (x >= VMS_COLUMNS)
  {
    x = VMS_COLUMNS - 1;
  }
  sprintf(pos, TTY_FMT_CURSOR_DD, y, x);
  sprintf(sz, "\0x27[%d;%dH%c\0x27[0m", y, x, ch); 
  
  vms_writeio(dc->iochan, &dc->iosb, sz, strlen(sz));
  
  /*fprintf(dc->win, sz);*/
#endif
  return TUI_OK;
}

TLONG TuiDrawText(
  TDC dc,
  TINT y,
  TINT x,
  TLPCSTR text,
  TDWORD  attrs)
{
#if defined __USE_CURSES__
  if (y >= LINES)
  {
    y = LINES - 1;
  }
  if (x >= COLS)
  {
    x = COLS - 1;
  }
  /* set attributes on */
  attron(attrs);
  /* print now */
  mvwprintw(dc->win, y, x, text);
  /* set attributes off */
  attroff(attrs);
#elif defined __USE_WIN32__
  TDWORD dwWritten = 0;
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  TuiMoveYX(dc, y, x);
  GetConsoleScreenBufferInfo(dc->wout, &csbi);
  SetConsoleTextAttribute(dc->wout, attrs);
  WriteConsole(dc->wout, text, strlen(text), &dwWritten, 0);
  SetConsoleTextAttribute(dc->wout, csbi.wAttributes);
#elif defined __USE_VMS__
  TUI_CHAR sz[TUI_MAX_WNDTEXT+1];
  TUI_CHAR pos[TUI_MAX_WNDTEXT+1];
  TUI_CHAR at[TUI_MAX_WNDTEXT+1] = "";

  if (attrs)
  {
    strcpy(at, TTY_ATTR_REVERSE);
  }
  if (y >= VMS_ROWS)
  {
    y = VMS_ROWS - 1;
  }
  if (x >= VMS_COLUMNS)
  {
    x = VMS_COLUMNS - 1;
  }
  sprintf(pos, TTY_FMT_CURSOR_DD, y, x);
  sprintf(sz, "\0x27[%d;%dH%s\0x27[0m", y, x, text); 
  
  vms_writeio(dc->iochan, &dc->iosb, sz, strlen(sz));
  
  /*fprintf(dc->win, sz);*/
#endif
  return TUI_OK;
}

TLONG TuiMoveYX(TDC dc, TINT y, TINT x)
{
#if defined __USE_CURSES__
  wmove(dc->win, y, x);
#elif defined __USE_WIN32__
    DWORD dwWritten = 0;
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(dc->wout, coord);
#elif defined __USE_VMS__
  TUI_CHAR sz[TUI_MAX_WNDTEXT+1];
  TUI_CHAR pos[TUI_MAX_WNDTEXT+1];

  if (y >= VMS_ROWS)
  {
    y = VMS_ROWS - 1;
  }
  if (x >= VMS_COLUMNS)
  {
    x = VMS_COLUMNS - 1;
  }
  sprintf(pos, TTY_FMT_CURSOR_DD, y, x);
  sprintf(sz, "%s", pos);
  vms_writeio(dc->iochan, &dc->iosb, sz, strlen(sz));
#endif
  return TUI_OK;
}


TLONG TuiGetYX(TDC dc, TINT* y, TINT* x)
{
  int xx = 0, yy = 0;
#if defined __USE_CURSES__
  getyx(dc->win, yy, xx);
#elif defined __USE_WIN32__
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  GetConsoleScreenBufferInfo(dc->wout, &csbi);
  xx = csbi.dwCursorPosition.X;
  yy = csbi.dwCursorPosition.Y;
#elif defined __USE_VMS__
#endif
  *y = yy;
  *x = xx;
  return TUI_OK;
}

TLONG TuiDrawFrame(TDC dc, TRECT* rcframe, TLPCSTR caption, TDWORD attrs)
{
  TUI_CHAR buf[TUI_MAX_WNDTEXT+1];
  
  TuiDrawBorder(dc, rcframe);
  if (caption)
  {
    TuiPrintTextAlignment(buf, caption, strlen(caption), TDT_CENTER);
    TuiDrawText(dc, rcframe->y,
      rcframe->x + (rcframe->cols - strlen(caption))/2, buf, attrs);
  }
  return TUI_OK;
}

TLONG TuiDrawMultipleFrames(TDC dc, TRECT* rcframe, TLPCSTR caption, TDWORD attrs, TINT* widths)
{
  return TUI_OK;
}

TLONG TuiDrawBorder(TDC dc, TRECT* rcwnd)
{
#if defined __USE_CURSES__
  /* left vertical line */
  mvwvline(dc->win, rcwnd->y, rcwnd->x, ACS_VLINE, rcwnd->lines);
  /* right vertical line */
  mvwvline(dc->win, rcwnd->y, rcwnd->x + rcwnd->cols, ACS_VLINE, rcwnd->lines);
  /* top horizontal line */
  mvwhline(dc->win, rcwnd->y, rcwnd->x, ACS_HLINE, rcwnd->cols);
  /* bottom horizontal line */
  mvwhline(dc->win, rcwnd->y + rcwnd->lines, rcwnd->x, ACS_HLINE, rcwnd->cols);
  /* upper left */
  mvwaddch(dc->win, rcwnd->y, rcwnd->x, ACS_ULCORNER);
  /* upper right */
  mvwaddch(dc->win, rcwnd->y, rcwnd->x + rcwnd->cols, ACS_URCORNER);
  /* lower left */
  mvwaddch(dc->win, rcwnd->y + rcwnd->lines, rcwnd->x, ACS_LLCORNER);
  /* lower right */
  mvwaddch(dc->win, rcwnd->y + rcwnd->lines, rcwnd->x + rcwnd->cols, ACS_LRCORNER);
#elif defined __USE_WIN32__
#elif defined __USE_VMS__
#endif
  return TUI_OK;
}

TLONG TuiDrawBorderEx(TDC dc, TRECT* rcwnd, TDWORD attrs)
{
#if defined __USE_CURSES__
  attron(attrs);
#elif defined __USE_WIN32__
#endif
  TuiDrawBorder(dc, rcwnd);
#if defined __USE_CURSES__
  attroff(attrs);
#elif defined __USE_WIN32__
#elif defined __USE_VMS__
#endif
  return TUI_OK;
}

TLONG TuiDrawHLine(TDC dc, TINT y, TINT x, TINT nchars, TDWORD attrs)
{
#if defined __USE_CURSES__
  attron(attrs);
  /* horizontal line */
  mvwhline(dc->win, y, x, ACS_HLINE, nchars);
  attroff(attrs);
#elif defined __USE_WIN32__
#elif defined __USE_VMS__
#endif
  return TUI_OK;
}

TLONG TuiDrawVLine(TDC dc, TINT y, TINT x, TINT nchars, TDWORD attrs)
{
#if defined __USE_CURSES__
  attron(attrs);
  /* vertical line */
  mvwvline(dc->win, y, x, ACS_VLINE, nchars);
  attroff(attrs);
#elif defined __USE_WIN32__
#elif defined __USE_VMS__
#endif
  return TUI_OK;
}

TLONG TuiDrawVFrames(TDC dc, TRECT* rcframe, TINT* widths, TINT nframes, TDWORD attrs)
{
  TINT i = 0;
#if defined __USE_CURSES__
  /* border */
  TuiDrawBorderEx(dc, rcframe, attrs);
  /* frames */
  while (i < nframes-1)
  {
    TuiPutChar(dc, rcframe->y, rcframe->x + widths[i], ACS_TTEE, attrs | A_ALTCHARSET);
    TuiDrawVLine(dc, rcframe->y+1, rcframe->x + widths[i], rcframe->lines-1, attrs);
    TuiPutChar(dc, rcframe->y+rcframe->lines, rcframe->x + widths[i], ACS_BTEE, attrs | A_ALTCHARSET);
    
    rcframe->x += widths[i];
    ++i;
  }  
#elif defined __USE_WIN32__
#elif defined __USE_VMS__
#endif
  return TUI_OK;
}

TLONG TuiDrawHFrames(TDC dc, TRECT* rcframe, TINT* heights, TINT nframes, TDWORD attrs)
{
  TINT i = 0;
#if defined __USE_CURSES__
  /* border */
  TuiDrawBorderEx(dc, rcframe, attrs);
  /* frames */
  while (i < nframes-1)
  {
    TuiPutChar(dc, rcframe->y+heights[i], rcframe->x, ACS_LTEE, attrs | A_ALTCHARSET);
    TuiDrawHLine(dc, rcframe->y+heights[i], rcframe->x + 1, rcframe->cols-1, attrs);
    TuiPutChar(dc, rcframe->y+heights[i], rcframe->x + rcframe->cols, ACS_RTEE, attrs | A_ALTCHARSET);
    
    rcframe->y += heights[i];
    ++i;
  }  
#elif defined __USE_WIN32__
#elif defined __USE_VMS__
#endif
  return TUI_OK;
}
