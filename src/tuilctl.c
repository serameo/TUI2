/*-------------------------------------------------------------------
 * File name: tuilctl.c
 * Author: Seree Rakwong
 * Date: 17-SEP-18
 *-----------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "tui.h"

/*-------------------------------------------------------------------
 * LISTCTRL functions
 *-----------------------------------------------------------------*/
struct _TLISTCELLSTRUCT
{
  TINT         y;
  TINT         x;
  TINT         lines;
  TINT         cols;
  TUI_CHAR     caption[TUI_MAX_WNDTEXT+1];
  TDWORD       attrs;
  TUI_LPARAM   data;
  TDWORD       editstyle;
  
  struct _TLISTCELLSTRUCT *prev;
  struct _TLISTCELLSTRUCT *next;
};
typedef struct _TLISTCELLSTRUCT tlistcell_t;

struct _THEADERSTRUCT
{
  TINT              id;
  TUI_CHAR          caption[TUI_MAX_WNDTEXT+1];
  TINT              cols;      /* width */  
  TINT              align;     /* left is a default */
  TDWORD            attrs;
  TDWORD            editstyle;
  TINT              decwidth;
  
  tlistcell_t*      firstcell;
  tlistcell_t*      lastcell;

  struct _THEADERSTRUCT *prev;
  struct _THEADERSTRUCT *next;
};
typedef struct _THEADERSTRUCT theader_t;


struct _TLISTCTRLSTRUCT
{
  theader_t*      firsthdr;
  theader_t*      lasthdr;
  theader_t*      firstvisiblehdr;
  theader_t*      lastvisiblehdr;

  TINT            nheaders;
  TINT            nitems;
  TINT            hdrids;      /* header id */
  TINT            hdrallwidths;
  /* item control */
  TINT            curselrow;
  TINT            curselcol;
  TINT            firstvisiblerow;

  TWND            editbox;
  TINT            editingstate;
  TINT            movingstate;
  TINT            insertingstate;
  tlistcell_t*    editingcell;

  TUI_LPARAM      exparam;
  
  TLONG           editkey;
  TLONG           insertkey;
  TLONG           delkey;
  TLONG           canceleditkey;
  
  TINT*           editcols;
  TINT            nedtcols;
  TINT            curedtcol;
  
  tlistcell_t*    firsteditcell;
  tlistcell_t*    lasteditcell;
};
typedef struct _TLISTCTRLSTRUCT _TLISTCTRL;
typedef struct _TLISTCTRLSTRUCT *PTLISTCTRL;

theader_t*    _TLC_FindHeaderByIndex(PTLISTCTRL lctl, TINT col);
tlistcell_t*  _TLC_FindCellByIndex(PTLISTCTRL lctl, TINT col, TINT idx);
tlistcell_t*  _TLC_FindCellByHeader(PTLISTCTRL lctl, theader_t* header, TINT idx);
TLONG         _TLC_GetCellRect(tlistcell_t* cell, TRECT* rect);
TINT          _TLC_FindHeaderIndex(PTLISTCTRL lctl, theader_t* header);
TINT          _TLC_GetFirstEditableCol(PTLISTCTRL lctl);
TINT          _TLC_GetNextEditableCol(PTLISTCTRL lctl, TINT prevcol);
TINT          _TLC_GetPrevEditableCol(PTLISTCTRL lctl, TINT prevcol);
TINT          _TLC_GetLastEditableCol(PTLISTCTRL lctl);
TINT          _TLC_InsertEmptyItem(TWND wnd);

TVOID   _TLC_DrawItem(
  TDC dc, TRECT* rccell, TLPCSTR caption, TDWORD attrs, TINT align, TINT isheader);

TLONG   LISTCTRLPROC(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam);
TVOID   _TLC_OnKeyDown(TWND wnd, TLONG ch);
TVOID   _TLC_OnChar(TWND wnd, TLONG ch);
TVOID   _TLC_OnPaint(TWND wnd, TDC dc);
TLONG   _TLC_OnAddItem(TWND wnd, TLPSTR text, TINT nitems);
TVOID   _TLC_OnDeleteAllItems(TWND wnd);
TVOID   _TLC_OnDeleteColumn(TWND wnd, TINT col);
TLONG   _TLC_OnAddColumn(TWND wnd, THEADERITEM* hdritem);
TVOID   _TLC_OnDestroy(TWND wnd);
TLONG   _TLC_OnCreate(TWND wnd);
TLONG   _TLC_OnGetItem(TWND wnd, TUINT flags, TSUBITEM* subitem);
TLONG   _TLC_OnSetItem(TWND wnd, TUINT flags, TSUBITEM* subitem);
TVOID   _TLC_OnSetFocus(TWND wnd);
TLONG   _TLC_OnKillFocus(TWND wnd);
TVOID   _TLC_OnInvalidateItem(TWND wnd, TUINT col, TUINT idx);
TVOID   _TLC_OnSelChanged(TWND wnd);
TVOID   _TLC_OnBeginMoving(TWND wnd);
TVOID   _TLC_OnMovingCursor(TWND wnd, TLONG ch);
TVOID   _TLC_OnEndMoving(TWND wnd);
TDWORD  _TLC_OnGetEditStyle(TWND wnd, TINT col);
TVOID   _TLC_OnSetEditStyle(TWND wnd, TINT col, TDWORD editstyle);
TINT    _TLC_OnGetCurRow(TWND wnd);
TVOID   _TLC_OnSetCurRow(TWND wnd, TINT idx);
TVOID   _TLC_OnSetColWidth(TWND wnd, TINT col, TINT width);
TWND    _TLC_OnGetEditBox(TWND wnd);
TVOID   _TLC_OnSetCurPage(TWND wnd, TINT npage);
TINT    _TLC_OnGetCurPage(TWND wnd);
TINT    _TLC_OnGetItemsPerPage(TWND wnd);
TVOID   _TLC_OnSetEditableCols(TWND wnd, TINT ncols, TINT* edtcols);
TVOID   _TLC_OnEndEditRow(TWND wnd, TINT row, TINT ok);
TVOID   _TLC_OnBeginEditRow(TWND wnd, TINT row);
TVOID   _TLC_OnBeginInsertRow(TWND wnd, TINT row);
TVOID   _TLC_OnBeginInsertCell(TWND wnd, TINT row);
TVOID   _TLC_OnBeginEdit(TWND wnd);
TVOID   _TLC_OnEndEdit(TWND wnd, TINT ok);
TVOID   _TLC_OnDeleteItem(TWND wnd, TINT idx);

TINT  _TLC_FindHeaderIndex(PTLISTCTRL lctl, theader_t* header)
{
  TINT col = -1;
  theader_t* ctlhdr = lctl->firsthdr;
  
  if (header && ctlhdr)
  {
    while (ctlhdr)
    {
      ++col;
      if (header == ctlhdr)
      {
        break;
      }
      ctlhdr = ctlhdr->next;
    }
  }
  return col;
}
theader_t* _TLC_FindHeaderByIndex(PTLISTCTRL lctl, TINT col)
{
  theader_t* header = 0;
  TINT i = 0;
  
  if (col < 0 || col >= lctl->nheaders)
  {
    return 0; /* no header deleted */
  }
  
  header = lctl->firsthdr;
  while (header)
  {
    if (i == col)
    {
      break;
    }
    header = header->next;
    ++i;
  }
  return header;
}

tlistcell_t* _TLC_FindCellByIndex(PTLISTCTRL lctl, TINT col, TINT idx)
{
  tlistcell_t* cell = 0;
  theader_t* header = 0;
  TINT i = 0;
  
  if (idx < 0 || idx >= lctl->nitems)
  {
    return 0;
  }
  header = _TLC_FindHeaderByIndex(lctl, col);
  if (header)
  {
    cell = header->firstcell;
    while (cell)
    {
      if (i == idx)
      {
        break;
      }
      cell = cell->next;
      ++i;
    }
  }
  return cell;
}

tlistcell_t* _TLC_FindCellByHeader(PTLISTCTRL lctl, theader_t* header, TINT idx)
{
  tlistcell_t* cell = 0;
  TINT i = 0;
  
  if (idx < 0 || idx >= lctl->nitems)
  {
    return 0;
  }

  if (header)
  {
    cell = header->firstcell;
    while (cell)
    {
      if (i == idx)
      {
        break;
      }
      cell = cell->next;
      ++i;
    }
  }
  return cell;
}
TLONG _TLC_GetCellRect(tlistcell_t* cell, TRECT* rect)
{
  rect->y = cell->y;
  rect->x = cell->x;
  rect->lines = cell->lines;
  rect->cols  = cell->cols;
  return TUI_OK;
}

TLONG _TLC_OnCreate(TWND wnd)
{
  PTLISTCTRL lctl = (PTLISTCTRL)malloc(sizeof(_TLISTCTRL));
  TUI_UINT8 editable = 0;
  if (!lctl)
  {
    return TUI_MEM;
  }
  memset(lctl, 0, sizeof(_TLISTCTRL));
  lctl->hdrids    = 1;
  lctl->editbox = TuiCreateWnd(TEDITBOX,
                    "",
                    TWS_CHILD|TES_AUTOHSCROLL,
                    0,    /* y */
                    0,    /* x */
                    1,    /* lines  */
                    1,    /* cols   */
                    wnd,  /* parent */
                    lctl->hdrids,    /* id */
                    0);   /* no parameter */
  if (!lctl->editbox)
  {
    free(lctl);
    return TUI_MEM;
  }
  lctl->curselrow = -1;
  lctl->curselcol = -1;
  lctl->firstvisiblerow = -1;
  
  lctl->editkey         = TVK_ENTER;
  lctl->insertkey       = TVK_INSERT;
  lctl->delkey          = TVK_DELETE;
  lctl->canceleditkey   = TVK_ESCAPE;
  
  lctl->curedtcol = -1;
  lctl->nedtcols  = 256;
  lctl->editcols  = (TINT*)malloc(lctl->nedtcols * sizeof(TINT));
  if (TLCS_EDITABLE & TuiGetWndStyle(wnd))
  {
    editable = 1;
  }
  memset(lctl->editcols, editable, lctl->nedtcols * sizeof(TINT));
  lctl->firsteditcell = 0;
  lctl->lasteditcell  = 0;
  /* increment child ids */
  ++lctl->hdrids;
  
  /* save memory */
  TuiSetWndParam(wnd, (TLPVOID)lctl);
  return TUI_CONTINUE;
}

TVOID _TLC_OnSelChanged(TWND wnd)
{
  TNMHDR nmhdr;
  /* send notification */
  nmhdr.id   = TuiGetWndID(wnd);
  nmhdr.ctl  = wnd;
  nmhdr.code = TLCN_SELCHANGED;

  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdr);
}

TVOID _TLC_OnSetFocus(TWND wnd)
{
  TNMHDR nmhdr;
  /* send notification */
  nmhdr.id   = TuiGetWndID(wnd);
  nmhdr.ctl  = wnd;
  nmhdr.code = TLCN_SETFOCUS;
  
  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdr);
}

TLONG _TLC_OnKillFocus(TWND wnd)
{
  TNMHDR nmhdr;
  PTLISTCTRL lctl = 0;
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (lctl->movingstate == TLCT_MOVINGCURSOR)
  {
    _TLC_OnEndMoving(wnd);
    lctl->movingstate = TLCT_VIEW;
  }
  else if (lctl->editingstate == TLCT_EDITING)
  {
    _TLC_OnEndEdit(wnd, TLC_ENDEDITCANCEL);
    lctl->editingstate = TLCT_VIEW;
  }
  /* send notification */
  nmhdr.id   = TuiGetWndID(wnd);
  nmhdr.ctl  = wnd;
  nmhdr.code = TLCN_KILLFOCUS;
  
  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdr);

  return TUI_CONTINUE;
}

TVOID _TLC_OnDestroy(TWND wnd)
{
  PTLISTCTRL lctl = 0;
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  
  TLC_DeleteAllColumns(wnd);
  free(lctl);
}

TVOID  _TLC_OnSetEditableCols(TWND wnd, TINT ncols, TINT* edtcols)
{
  PTLISTCTRL lctl = 0;
  TINT i = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (0 == edtcols)
  {
    /* this means re*/
    return;
  }
  if (ncols > lctl->nheaders)
  {
    ncols = lctl->nheaders;
  }
  for (i = 0; i < ncols; ++i)
  {
    lctl->editcols[i] = edtcols[i];
  }
}

TLONG _TLC_OnAddColumn(TWND wnd, THEADERITEM* hdritem)
{
  PTLISTCTRL lctl = 0;
  theader_t* header = 0;
  TRECT rc;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  
  if (lctl->nitems > 0)
  {
    /* not allowed to add header after there are any items */
    return TUI_ERROR;
  }

  header = (theader_t*)malloc(sizeof(theader_t));
  if (!header)
  {
    return TUI_MEM;
  }
  memset(header, 0, sizeof(theader_t));
  
  TuiGetWndRect(TuiGetParent(wnd), &rc);
  strncpy(header->caption,
    hdritem->caption,
    TUI_MIN(TUI_MAX_WNDTEXT, strlen(hdritem->caption)));
  header->cols      = hdritem->cols;
  header->align     = hdritem->align;
  header->attrs     = hdritem->attrs;
  header->editstyle = hdritem->editstyle;
  header->decwidth  = hdritem->decwidth;
  header->id        = lctl->hdrids;
 
  /* make link */
  if (lctl->firsthdr)
  {
    header->prev = lctl->lasthdr;
    lctl->lasthdr->next = header;
    lctl->lasthdr = header;
  }
  else
  {
    lctl->firsthdr = lctl->lasthdr = header;
    lctl->firstvisiblehdr = header;
  }
  /* increment child ids */
  ++lctl->hdrids;
  ++lctl->nheaders;
  lctl->hdrallwidths += header->cols;
  
  return 0;
}

TVOID _TLC_OnDeleteColumn(TWND wnd, TINT col)
{
  PTLISTCTRL lctl = 0;
  theader_t* next = 0;
  tlistcell_t* cell = 0;
  tlistcell_t* nextcell = 0;
  theader_t* header = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  header = _TLC_FindHeaderByIndex(lctl, col);
  if (!header)
  {
    return;
  }

  /* re-link */
  next = header->next;
  if (next)
  {
    next->prev = header->prev;
  }
  if (header->prev)
  {
    header->prev->next = next;
  }
  
  if (header == lctl->firsthdr)
  {
    lctl->firsthdr = next;
  }
  else if (header == lctl->lasthdr)
  {
    lctl->lasthdr = header->prev;
  }
  /* delete */
  header->next = header->prev = 0;

  cell = header->firstcell;
  while (cell)
  {
    nextcell = cell->next;
    /*free(cell->caption);*/
    cell->next = cell->prev = 0;
    free(cell);
    cell = nextcell;
  }

  free(header);

  /* done */
  --lctl->nheaders;
}

TVOID _TLC_OnDeleteAllItems(TWND wnd)
{
  TINT nitems = 0;
  TINT i = 0;
  PTLISTCTRL lctl = 0;

  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  nitems = lctl->nheaders;
  for (i = 0; i < nitems; ++i)
  {
    TuiSendMsg(wnd, TLCM_DELETEITEM, 0, 0);
  }
}

TVOID _TLC_OnDeleteItem(TWND wnd, TINT idx)
{
  PTLISTCTRL lctl = 0;
  tlistcell_t* cell = 0;
  tlistcell_t* nextcell = 0;
  theader_t* header = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (lctl->nitems <= 0 || idx < 0 || idx >= lctl->nitems)
  {
    return;
  }
  
  header = lctl->firsthdr;
  while (header)
  {
    cell = _TLC_FindCellByHeader(lctl, header, idx);
    nextcell = cell->next;
    if (nextcell)
    {
      nextcell->prev = cell->prev;
    }
    if (cell->prev)
    {
      cell->prev->next = nextcell;
    }
    if (header->firstcell == cell)
    {
      header->firstcell = cell->next;
    }
    else if (header->lastcell == cell)
    {
      header->lastcell = cell->prev;
    }
    
    cell->next = cell->prev = 0;
    free(cell);
    /* next header */
    header = header->next;
  }
  --lctl->nitems;
}

TLONG _TLC_OnAddItem(TWND wnd, TLPSTR text, TINT nitems)
{
  PTLISTCTRL lctl = 0;
  TINT i = 0;
  TUI_CHAR* tok;
  theader_t* header = 0;
  TUI_CHAR buf[TUI_MAX_WNDTEXT+1];
  tlistcell_t* newcell = 0;

  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (lctl->nheaders > 0)
  {
    /* insert into all listboxes */
    header = lctl->firsthdr;
    
    strcpy(buf, text);
    tok = strtok(buf, "\t");
    while (/*tok &&*/ i < nitems && i < lctl->nheaders)
    {
      newcell = (tlistcell_t*)malloc(sizeof(tlistcell_t));
      if (!newcell)
      {
        break;
      }
      memset(newcell, 0, sizeof(tlistcell_t));
      if (tok)
      {
        strncpy(newcell->caption, tok, TUI_MIN(TUI_MAX_WNDTEXT, strlen(tok)));
      }
      else
      {
        strcpy(newcell->caption, "");
      }
      
      /* add the new item */
      if (header->firstcell)
      {
        newcell->prev  = header->lastcell;
        header->lastcell->next = newcell;
        header->lastcell = newcell;
      }
      else
      {
        header->firstcell = header->lastcell = newcell;

        lctl->firstvisiblerow   = 0;
      }
      /* insert next */
      header = header->next;
      tok = strtok(0, "\t");
      ++i;
    }
    /* all items count */
    ++lctl->nitems;

  } /* have header */
  return lctl->nitems;
}

TVOID _TLC_DrawItem(
  TDC dc, TRECT* rccell, TLPCSTR caption, TDWORD attrs, TINT align, TINT isheader)
{
  TLONG len = 0;
  TUI_CHAR buf[TUI_MAX_WNDTEXT+1];
  len = TuiPrintTextAlignment(buf, 
          caption,
          rccell->cols,
          align);
  /* is is a header */
  if (isheader)
  {
    buf[0] = '[';
    buf[len - 1] = ']';
  }

  if (0 == attrs)
  {
      TuiDrawText(dc,
          rccell->y,
          rccell->x,
          buf,
          TuiGetSysColor(COLOR_WNDTEXT));
  }
  else
  {
      TuiDrawText(dc,
          rccell->y,
          rccell->x,
          buf,
          attrs);
  }
}

TVOID _TLC_OnPaint(TWND wnd, TDC dc)
{
  PTLISTCTRL lctl = 0;
  theader_t* header = 0;
  TINT width = 0;
  TRECT rcitem, rcwnd, rccell;
  TDWORD attrs = 0;
  TDWORD hdrattrs = 0;
  tlistcell_t* visiblecell = 0;
  TINT i = 0;
  TINT forcewidth = 0;
  TDWORD style = TuiGetWndStyle(wnd);
  TDWORD highlight = TuiGetSysColor(COLOR_HIGHLIGHTED);

  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  
  /* if no headers or control is hiding */
  if (lctl->nheaders <= 0 || !TuiIsWndVisible(wnd))
  {
    return;
  }

  /* draw headers */
  TuiGetWndRect(wnd, &rcwnd);
  rcitem = rcwnd; /* copy some values */
  rcitem.lines = (style & TLCS_NOHEADER ? 0 : 1);
  
  header = lctl->firstvisiblehdr;
  width  = header->cols;
  
  /* first column width must not be over window columns */
  if (width > rcwnd.cols)
  {
    width = rcwnd.cols - 1;
    forcewidth = 1;
  }
  
  while (header && width < rcwnd.cols)
  {    
    rcitem.x    = rcwnd.x + width - header->cols;
    rcitem.cols = header->cols;
    if (rcitem.x < 0)
    {
      rcitem.x = rcwnd.x;
      if (forcewidth == 1)
      {
        rcitem.cols = width;
      }
      else
      {
        --rcitem.cols;
      }
    }

    hdrattrs = header->attrs;
    attrs = header->attrs;/*TuiReverseColor(header->attrs);*/

    if (!(style & TLCS_NOHEADER))
    {
        if (style & TLCS_NOBORDER)
        {
            _TLC_DrawItem(dc, &rcitem,
                header->caption, attrs, header->align, 0); /* 0=no border */
        }
        else
        {
            _TLC_DrawItem(dc, &rcitem,
                header->caption, attrs, TALIGN_CENTER, 1); /* 1=header */
        }
    }

    /* draw cells */
    rccell = rcitem;
    rccell.y += (style & TLCS_NOHEADER ? 0 : 1);
    rccell.lines = 1;
    visiblecell = header->firstcell;
    for (i = 0; i < lctl->nitems && visiblecell;
        ++i, visiblecell = visiblecell->next)
    {
      if (i < lctl->firstvisiblerow)
      {
        /* do nothing */
        continue;
      }
      else if (i - lctl->firstvisiblerow <= rcwnd.lines - 2)
      {

        attrs = visiblecell->attrs;
        if (!(TLCS_NOSELECTION & style) && i == lctl->curselrow)
        {
#if defined __USE_CURSES__ || defined __USE_WIN32__
          attrs = TuiReverseColor(attrs);
#else
          attrs = highlight;
#endif
        }
        /* draw th item that it can be seen */
        _TLC_DrawItem(dc, &rccell, 
          visiblecell->caption, attrs, header->align, 0);

        /* update cell rect */
        visiblecell->y = rccell.y;
        visiblecell->x = rccell.x;
        visiblecell->lines = rccell.lines;
        visiblecell->cols  = rccell.cols;
        /* next cell line */
        ++rccell.y;
      }
      else
      {
        /* no need to draw more items than client lines */
        break;
      }
    } /* for each drawing cell */
    
    /* draw next header */
    header = header->next;
    if (header)
    {
      width += header->cols;
      if (width > rcwnd.cols)
      {
        break;
      }
    }
  } /* while header */
  
  /* print arrow controls */
  attrs = TuiReverseColor(hdrattrs);
  if (lctl->firsthdr != lctl->firstvisiblehdr)
  {
    if (!(style & TLCS_NOHEADER))
    {
      TuiPutChar(dc, rcwnd.y, rcwnd.x + 1, '<', attrs);
    }
  }
  /* save the last visible */
  if (header)
  {
    lctl->lastvisiblehdr = header->prev;
    if (!(style & TLCS_NOHEADER))
    {
      TuiPutChar(dc, rcwnd.y, 
        rcwnd.x + width - header->cols - 2, '>', attrs);
    }
  }
  else
  {
    lctl->lastvisiblehdr = lctl->lasthdr;
  }

  TuiMoveYX(dc, rcitem.y,
      rcitem.x);
}

TVOID _TLC_OnBeginMoving(TWND wnd)
{
  TNMHDR nmhdr;
  PTLISTCTRL lctl = 0;
  TRECT rccell;
  tlistcell_t* cell = 0;
  theader_t* header = 0;
  TINT curselcol = -1;
    
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (lctl->movingstate == TLCT_MOVINGCURSOR)
  {
    _TLC_OnEndMoving(wnd);
    lctl->movingstate = TLCT_VIEW;
    return;
  }
  
  lctl->movingstate = TLCT_MOVINGCURSOR;
  /* move cursor to the current row */
  curselcol = _TLC_FindHeaderIndex(lctl, lctl->firstvisiblehdr);
  /*lctl->curedtcol = _TLC_FindHeaderIndex(lctl, lctl->firstvisiblehdr);*/
  if (curselcol < 0)
  {
    lctl->curselrow = 0;
    TuiInvalidateWnd(wnd);
  }
  
  /* draw moving cursor */
  if (0 > lctl->curselcol)
  {
    lctl->curselcol = curselcol;
  }
  if (0 > lctl->curselrow)
  {
    lctl->curselrow = 0;
  }
  header = _TLC_FindHeaderByIndex(lctl, lctl->curselcol);
  /*header = _TLC_FindHeaderByIndex(lctl, lctl->curedtcol);*/
  cell   = _TLC_FindCellByHeader(lctl, header, lctl->curselrow);
  _TLC_GetCellRect(cell, &rccell);
  
  _TLC_DrawItem(TuiGetDC(wnd), &rccell, 
          cell->caption,
          TuiUnderlineText(cell->attrs),
          header->align, 0);

  /* move cursor */
  TuiMoveYX(TuiGetDC(wnd), rccell.y, rccell.x);
  
  /* save the editing cell */
  lctl->editingcell = cell;
  /* send notification */
  nmhdr.id   = TuiGetWndID(wnd);
  nmhdr.ctl  = wnd;
  nmhdr.code = TLCN_BEGINMOVING;

  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdr);
}

TVOID _TLC_OnMovingCursor(TWND wnd, TLONG ch)
{
  PTLISTCTRL lctl = 0;
  TINT firstcol = -1, lastcol = -1;
  TINT newcol = -1;
  TINT newrow = -1;
  TRECT rccell;
  TRECT rcwnd;
  tlistcell_t* cell = 0;  
  theader_t* header = 0;
  TINT maxrows = 25;
  TDWORD style = TuiGetWndStyle(wnd);

  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (lctl->movingstate != TLCT_MOVINGCURSOR)
  {
    return;
  }
  
  TuiGetWndRect(wnd, &rcwnd);
  firstcol = _TLC_FindHeaderIndex(lctl, lctl->firstvisiblehdr);
  lastcol  = _TLC_FindHeaderIndex(lctl, lctl->lastvisiblehdr);
  newcol   = lctl->curselcol;
  newrow   = lctl->curselrow;
  
  maxrows  = lctl->firstvisiblerow + rcwnd.lines - 2;
  
  switch (ch)
  {
    case TVK_LEFT:
    {
      newcol = _TLC_GetPrevEditableCol(lctl, lctl->curedtcol);
      if (newcol < 0)
      {
        newcol = _TLC_GetFirstEditableCol(lctl);
      }
        /*--newcol;*/
      if (newcol < firstcol)
      {
        newcol = firstcol;
      }
      break;
    }
    
    case TVK_RIGHT:
    {
      newcol = _TLC_GetNextEditableCol(lctl, lctl->curedtcol);
      if (newcol < 0)
      {
        newcol = _TLC_GetLastEditableCol(lctl);
      }
      if (newcol < 0)
      {
        
      }
      /*++newcol;*/
      if (newcol > lastcol)
      {
        newcol = lastcol;
      }
      break;
    }
    
    case TVK_DOWN:
    {
      if (!(TLCS_LINEEDIT & style))
      {
        /* not fixed line edit style */
        ++newrow;
        if (newrow > maxrows)
        {
          newrow = maxrows;
        }
      }
      break;
    }
    
    case TVK_UP:
    {
      if (!(TLCS_LINEEDIT & style))
      {
        /* not fixed line edit style */
        --newrow;
        if (newrow < lctl->firstvisiblerow)
        {
          newrow = lctl->firstvisiblerow;
        }
      }
      break;
    }
  }
  
  if (newcol != lctl->curselcol || newrow != lctl->curselrow)
  {
    /* redraw the previous moving cursor */
    header = _TLC_FindHeaderByIndex(lctl, lctl->curselcol);
    cell   = _TLC_FindCellByHeader(lctl, header, lctl->curselrow);
    _TLC_GetCellRect(cell, &rccell);
    _TLC_DrawItem(
      TuiGetDC(wnd),
      &rccell,
      cell->caption,
      cell->attrs,
      header->align,
      0);

    /* draw moving cursor */
    header = _TLC_FindHeaderByIndex(lctl, newcol);
    cell   = _TLC_FindCellByHeader(lctl, header, newrow);
    _TLC_GetCellRect(cell, &rccell);
    _TLC_DrawItem(TuiGetDC(wnd),
      &rccell,
      cell->caption,
      TuiUnderlineText(cell->attrs),
      header->align,
      0);
    
    TuiMoveYX(TuiGetDC(wnd), rccell.y, rccell.x);

    /* save the last current selected column */
    lctl->curselcol = newcol;
    lctl->curselrow = newrow;
    /* save the editing cell */
    lctl->curedtcol = newcol;
    lctl->editingcell = cell;
    if (TLCT_EDITING == lctl->editingstate)
    {
    }
  }
}

TVOID _TLC_OnEndMoving(TWND wnd)
{
  TNMHDR nmhdr;
  PTLISTCTRL lctl = 0;
  tlistcell_t* cell = 0;
  theader_t* header = 0;
  TRECT rccell;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (lctl->movingstate != TLCT_MOVINGCURSOR)
  {
    return;
  }
  lctl->movingstate = TLCT_ENDMOVING;
  
  /* redraw the previous moving cursor */
  header = _TLC_FindHeaderByIndex(lctl, lctl->curselcol);
  /*header = _TLC_FindHeaderByIndex(lctl, lctl->curedtcol);*/
  cell   = _TLC_FindCellByHeader(lctl, header, lctl->curselrow);
  _TLC_GetCellRect(cell, &rccell);

  _TLC_DrawItem(
    TuiGetDC(wnd),
    &rccell, 
    cell->caption,
    TuiReverseColor(cell->attrs),
    header->align,
    0);

  /* update state */
  lctl->movingstate   = TLCT_VIEW;
  /*lctl->editingstate  = TLCT_VIEW;*/
  
  TuiInvalidateWnd(wnd);
  /* send notification */
  nmhdr.id   = TuiGetWndID(wnd);
  nmhdr.ctl  = wnd;
  nmhdr.code = TLCN_ENDMOVING;

  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdr);
}


TVOID  _TLC_OnBeginInsertRow(TWND wnd, TINT row)
{
  PTLISTCTRL lctl = 0;
  TNMHDRITEMSTRUCT nmhdri;

  if (row < 0)
  {
    row = 0;
  }
  /* save all cells on the row */
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  lctl->insertingstate = TLCT_INSERTING;
  
  /* send notification */
  nmhdri.hdr.id   = TuiGetWndID(wnd);
  nmhdri.hdr.ctl  = wnd;
  nmhdri.hdr.code = TLCN_BEGININSERTROW;  
  nmhdri.row      = lctl->curselrow;
  nmhdri.col      = lctl->curselcol;

  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdri);
}

TVOID  _TLC_OnEndInsertRow(TWND wnd, TINT row, TINT ok)
{
  TNMHDRITEMSTRUCT nmhdri;
  PTLISTCTRL lctl = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  lctl->insertingstate = TLCT_ENDINSERTING;
  
  if (TLC_ENDEDITCANCEL == ok)
  {
    /* rollback */
    _TLC_OnDeleteItem(wnd, row);
  }
   
  /* send notification */
  nmhdri.hdr.id   = TuiGetWndID(wnd);
  nmhdri.hdr.ctl  = wnd;
  nmhdri.hdr.code = (TLC_ENDEDITOK == ok ?
                      TLCN_ENDINSERTROWOK : TLCN_ENDINSERTROWCANCEL);
  nmhdri.row      = lctl->curselrow;
  nmhdri.col      = lctl->curselcol;

  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdri);
}

TVOID  _TLC_OnBeginEditRow(TWND wnd, TINT row)
{
  PTLISTCTRL lctl = 0;
  tlistcell_t* cell = 0;
  tlistcell_t* newcell = 0;
  TINT i = 0;
  TNMHDRITEMSTRUCT nmhdri;

  if (row < 0)
  {
    row = 0;
  }
  /* save all cells on the row */
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  
  lctl->firsteditcell = lctl->lasteditcell = 0;
  
  for (i=0; i<lctl->nheaders; ++i)
  {
    cell = _TLC_FindCellByIndex(lctl, i, row);
    newcell = (tlistcell_t*)malloc(sizeof(tlistcell_t));
    memcpy(newcell, cell, sizeof(tlistcell_t));
    newcell->next = newcell->prev = 0;
    
    if (0 == lctl->lasteditcell)
    {
      lctl->firsteditcell = lctl->lasteditcell = newcell;
    }
    else
    {
      newcell->prev = lctl->lasteditcell;
      lctl->lasteditcell->next = newcell;
      lctl->lasteditcell = newcell;
    }
  }
  /* send notification */
  nmhdri.hdr.id   = TuiGetWndID(wnd);
  nmhdri.hdr.ctl  = wnd;
  nmhdri.hdr.code = TLCN_BEGINEDITROW;  
  nmhdri.row      = lctl->curselrow;
  nmhdri.col      = lctl->curselcol;

  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdri);
}

TVOID  _TLC_OnEndEditRow(TWND wnd, TINT row, TINT ok)
{
  TNMHDRITEMSTRUCT nmhdri;
  PTLISTCTRL lctl = 0;
  tlistcell_t* cell = 0;
  tlistcell_t* nextcell = 0;
  TINT i = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (TLC_ENDEDITCANCEL == ok)
  {
    /* rollback */
    nextcell = lctl->firsteditcell;
    for (i=0; i<lctl->nheaders && nextcell != 0; ++i)
    {
      cell = _TLC_FindCellByIndex(lctl, i, row);
      strcpy(cell->caption, nextcell->caption);
      nextcell = nextcell->next;
    }
  }
  
  /* release backed-up cells */
  nextcell = lctl->firsteditcell;
  while (nextcell)
  {
    cell = nextcell;
    nextcell = nextcell->next;
    
    free(cell);
  }
  lctl->firsteditcell = lctl->lasteditcell = 0;
  
  /* send notification */
  nmhdri.hdr.id   = TuiGetWndID(wnd);
  nmhdri.hdr.ctl  = wnd;
  nmhdri.hdr.code = (TLC_ENDEDITOK == ok ?
                      TLCN_ENDEDITROWOK : TLCN_ENDEDITROWCANCEL);
  nmhdri.row      = lctl->curselrow;
  nmhdri.col      = lctl->curselcol;

  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdri);
}

TVOID _TLC_OnBeginEdit(TWND wnd)
{
  PTLISTCTRL lctl = 0;
  TRECT rccell;
  TUI_CHAR buf[TUI_MAX_WNDTEXT+1];
  TDWORD editstyle = 0;
  TNMHDRITEMSTRUCT nmhdri;
  
  if (!(TuiGetWndStyle(wnd) & TLCS_EDITABLE))
  {
    /* if it has no EDIT style */
    return;
  }
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);

  lctl->editingstate = TLCT_BEGINEDITING;
  /* show edit box at the current row and column */
  _TLC_GetCellRect(lctl->editingcell, &rccell);
  TuiMoveWnd(lctl->editbox, rccell.y, rccell.x, rccell.lines, rccell.cols);

  editstyle = TLC_GetEditStyle(wnd, lctl->curselcol);

  TuiSetWndStyle(lctl->editbox, editstyle);
  if (editstyle & TES_DECIMAL)
  {
    theader_t* header = _TLC_FindHeaderByIndex(lctl, lctl->curselcol);
    TEDT_SetDecimalWidth(lctl->editbox, header->decwidth);
  }
  
  /* update text before showing */
  strcpy(buf, lctl->editingcell->caption);
  TuiSetWndText(lctl->editbox, buf);
  TuiShowWnd(lctl->editbox, TW_SHOW);
  
  TuiSetFocus(lctl->editbox);
  
  /* update state */
  lctl->editingstate = TLCT_EDITING;
  
  /* send notification */
  nmhdri.hdr.id   = TuiGetWndID(wnd);
  nmhdri.hdr.ctl  = wnd;
  nmhdri.hdr.code = TLCN_BEGINEDIT;
  nmhdri.row      = lctl->curselrow;
  nmhdri.col      = lctl->curselcol;

  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdri);
  
  TuiInvalidateWnd(wnd);
}

TVOID _TLC_OnEndEdit(TWND wnd, TINT ok)
{
  TNMHDRITEMSTRUCT nmhdri;
  PTLISTCTRL lctl = 0;
  TUI_CHAR buf[TUI_MAX_WNDTEXT+1];
  TINT rc = TUI_CONTINUE;
  
  if (!(TuiGetWndStyle(wnd) & TLCS_EDITABLE))
  {
    /* if it has no EDIT style */
    return;
  }
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (lctl->editingstate != TLCT_EDITING)
  {
    return;
  }
  lctl->editingstate = TLCT_ENDEDITING;

  /* hide edit box */
  rc = TuiSendMsg(lctl->editbox, TWM_KILLFOCUS, 0, 0);
  TuiShowWnd(lctl->editbox, TW_HIDE);
  if (ok)
  {
    if (TUI_CONTINUE == rc)
    {
      /* update */
      TuiGetWndText(lctl->editbox, buf, TUI_MAX_WNDTEXT);
      strcpy(lctl->editingcell->caption, buf);
    }
  }
  
  /* send notification */
  nmhdri.hdr.id   = TuiGetWndID(wnd);
  nmhdri.hdr.ctl  = wnd;
  nmhdri.hdr.code = (TLC_ENDEDITOK == ok ?
                      TLCN_ENDEDITOK : TLCN_ENDEDITCANCEL);
  nmhdri.row      = lctl->curselrow;
  nmhdri.col      = lctl->curselcol;

  TuiPostMsg(TuiGetParent(wnd), TWM_NOTIFY, 0, (TLPARAM)&nmhdri);
  
  TuiInvalidateWnd(wnd);
}

TVOID _TLC_OnChar(TWND wnd, TLONG ch)
{
  PTLISTCTRL lctl = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (lctl->editingstate == TLCT_EDITING)
  {
    /* forward key entered to edit */
    TuiSendMsg(lctl->editbox, TWM_CHAR, (TWPARAM)ch, 0);
  }
}

TINT _TLC_GetFirstEditableCol(PTLISTCTRL lctl)
{
  return _TLC_GetNextEditableCol(lctl, -1);
}

TINT _TLC_GetNextEditableCol(PTLISTCTRL lctl, TINT prevcol)
{
  TINT col = -1;
  TINT i = 0;
  for (i = prevcol+1; i < lctl->nheaders; ++i)
  {
    if (TLCT_EDITING == lctl->editingstate)
    {
      if (lctl->editcols[i] != 0)
      {
        col = i;
        break;
      }
    }
    else
    {
      col = i;
      break;
    }
  }
  return col;
}

TINT _TLC_InsertEmptyItem(TWND wnd)
{
  TUI_CHAR sz[BUFSIZ];
  PTLISTCTRL lctl = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  memset(sz, '\t', lctl->nheaders);
  sz[lctl->nheaders] = 0;
  return _TLC_OnAddItem(wnd, sz, lctl->nheaders);
}

TINT _TLC_GetLastEditableCol(PTLISTCTRL lctl)
{
  return _TLC_GetPrevEditableCol(lctl, lctl->nheaders);
}

TINT _TLC_GetPrevEditableCol(PTLISTCTRL lctl, TINT prevcol)
{
  TINT col = -1;
  TINT i = 0;
  for (i = prevcol-1; i>=0; --i)
  {
    if (TLCT_EDITING == lctl->editingstate)
    {
      if (lctl->editcols[i] != 0)
      {
        col = i;
        break;
      }
    }
    else
    {
      col = i;
      break;
    }
  }
  return col;
}

TVOID _TLC_OnKeyDown(TWND wnd, TLONG ch)
{
  PTLISTCTRL lctl = 0;
  TINT repaint = 0;
  TRECT rc;
  TINT lines = 0;
  TDWORD style = TuiGetWndStyle(wnd);
  TINT row = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  TuiGetWndRect(wnd, &rc);
  
  if (lctl->nheaders <= 0)
  {
    return;
  }
  
  row = lctl->curselrow;
  if (row < 0)
  {
    row = 0;
  }
  if (ch == lctl->editkey && (style & TLCS_EDITABLE))
  {
    if (TLCT_EDITING == lctl->editingstate)
    {
      _TLC_OnEndEdit(wnd, TLC_ENDEDITOK); /* edit ok */
      _TLC_OnEndMoving(wnd);
      if (TLCT_INSERTING == lctl->insertingstate)
      {
        _TLC_OnEndInsertRow(wnd, row, TLC_ENDEDITOK);
      }
      else
      {
        _TLC_OnEndEditRow(wnd, row, TLC_ENDEDITOK);
      }
      return;
    }
    else
    {
      if (lctl->nitems <= 0)
      {
        return;
      }
      lctl->curedtcol = _TLC_GetFirstEditableCol(lctl);
      lctl->curselcol = lctl->curedtcol;
      _TLC_OnBeginMoving(wnd);
      _TLC_OnBeginEditRow(wnd, row);
      _TLC_OnBeginEdit(wnd); /* begin editing */      
    }
  }
  else if (ch == lctl->canceleditkey && (style & TLCS_EDITABLE))
  {
    if (TLCT_EDITING == lctl->editingstate)
    {
      _TLC_OnEndEdit(wnd, TLC_ENDEDITCANCEL); /* edit cancel */
      _TLC_OnEndMoving(wnd);
      if (TLCT_INSERTING == lctl->insertingstate)
      {
        _TLC_OnEndInsertRow(wnd, row, TLC_ENDEDITCANCEL);
      }
      else
      {
        _TLC_OnEndEditRow(wnd, row, TLC_ENDEDITCANCEL);
      }
      _TLC_OnSetCurRow(wnd, row-1);
    }
    return;
  }
  else if (ch == lctl->insertkey && (style & TLCS_EDITABLE))
  {
    if (TLCT_EDITING == lctl->editingstate)
    {
      _TLC_OnEndEdit(wnd, TLC_ENDEDITCANCEL); /* edit cancel */
      _TLC_OnEndMoving(wnd);
      if (TLCT_INSERTING == lctl->insertingstate)
      {
        _TLC_OnEndInsertRow(wnd, row, TLC_ENDEDITCANCEL);
      }
      else
      {
        _TLC_OnEndEditRow(wnd, row, TLC_ENDEDITCANCEL);
      }
      _TLC_OnSetCurRow(wnd, row-1);
    }
    else
    {
      row = _TLC_InsertEmptyItem(wnd);
      if (row <= 0)
      {
        return;
      }
      --row; /* move to the last inserted row */
      /* find the properly first visible row */
      if (row >= lctl->firstvisiblerow + rc.lines - 1)
      {
        lctl->firstvisiblerow += 1;
        if (lctl->firstvisiblerow - 1 > lctl->nitems - rc.lines)
        {
          lctl->firstvisiblerow = lctl->nitems - rc.lines;
        }
      }
      else if (lctl->firstvisiblerow > row)
      {
        lctl->firstvisiblerow += 1;
        if (lctl->firstvisiblerow < 0)
        {
          lctl->firstvisiblerow = 0;
        }
      }      
      _TLC_OnSetCurRow(wnd, row);
      
      lctl->curedtcol = _TLC_GetFirstEditableCol(lctl);
      lctl->curselcol = lctl->curedtcol;
      _TLC_OnBeginMoving(wnd);
      _TLC_OnBeginInsertRow(wnd, row);
      _TLC_OnBeginEdit(wnd); /* begin editing */      
    }
    return;
  }
  else if (ch == lctl->delkey)
  {
    if (TLCT_EDITING == lctl->editingstate)
    {
      _TLC_OnEndEdit(wnd, TLC_ENDEDITCANCEL); /* edit cancel */
      _TLC_OnEndEditRow(wnd, row, TLC_ENDEDITCANCEL);
      _TLC_OnEndMoving(wnd);
    }
    else if (TLCT_INSERTING == lctl->editingstate)
    {
      _TLC_OnEndEdit(wnd, TLC_ENDEDITCANCEL); /* edit cancel */
      _TLC_OnEndEditRow(wnd, row, TLC_ENDEDITCANCEL);
      _TLC_OnEndMoving(wnd);
    }
    _TLC_OnDeleteItem(wnd, row);
    if (row >= lctl->nitems)
    {
      --row;
    }
    if (row < 0)
    {
      TuiInvalidateWnd(wnd);
    }
    else
    {
      _TLC_OnSetCurRow(wnd, row);
    }
    return;
  }

  switch (ch)
  {
    case TVK_RIGHT:
    {
      if (lctl->editingstate == TLCT_EDITING)
      {
        _TLC_OnEndEdit(wnd, TLC_ENDEDITOK);
        _TLC_OnMovingCursor(wnd, ch);
        _TLC_OnBeginEdit(wnd);
      }
      else if (lctl->lastvisiblehdr != lctl->lasthdr)
      {
        lctl->firstvisiblehdr = lctl->firstvisiblehdr->next;
        ++repaint;
      }
      break;
    }

    case TVK_LEFT:
    {
      if (lctl->editingstate == TLCT_EDITING)
      {
        _TLC_OnEndEdit(wnd, TLC_ENDEDITOK);
        _TLC_OnMovingCursor(wnd, ch);
        _TLC_OnBeginEdit(wnd);
      }
      else if (lctl->firstvisiblehdr != lctl->firsthdr)
      {
        lctl->firstvisiblehdr = lctl->firstvisiblehdr->prev;
        ++repaint;
      }
      break;
    }

    case TVK_DOWN:
    {
      if (TLCT_EDITING == lctl->editingstate)
      {
        _TLC_OnEndEdit(wnd, TLC_ENDEDITCANCEL); /* edit cancel */
        /*_TLC_OnMovingCursor(wnd, ch);*/
        _TLC_OnEndMoving(wnd);
        if (TLCT_INSERTING == lctl->insertingstate)
        {
          _TLC_OnEndInsertRow(wnd, row, TLC_ENDEDITCANCEL);
        }
        else
        {
          _TLC_OnEndEditRow(wnd, row, TLC_ENDEDITCANCEL);
        }
      }
      else
      {
        ++lines;
        ++repaint;
      }
      break;
    }
  

    case TVK_UP:
    {
      if (TLCT_EDITING == lctl->editingstate)
      {
        _TLC_OnEndEdit(wnd, TLC_ENDEDITCANCEL); /* edit cancel */
        /*_TLC_OnMovingCursor(wnd, ch);*/
        _TLC_OnEndMoving(wnd);
        if (TLCT_INSERTING == lctl->insertingstate)
        {
          _TLC_OnEndInsertRow(wnd, row, TLC_ENDEDITCANCEL);
        }
        else
        {
          _TLC_OnEndEditRow(wnd, row, TLC_ENDEDITCANCEL);
        }
      }
      else
      {
        --lines;
        ++repaint;
      }
      break;
    }
      
    case TVK_PRIOR:
    {
      if (TLCT_EDITING == lctl->editingstate)
      {
        _TLC_OnEndEdit(wnd, TLC_ENDEDITCANCEL); /* edit cancel */
        /*_TLC_OnMovingCursor(wnd, ch);*/
        _TLC_OnEndMoving(wnd);
        if (TLCT_INSERTING == lctl->insertingstate)
        {
          _TLC_OnEndInsertRow(wnd, row, TLC_ENDEDITCANCEL);
        }
        else
        {
          _TLC_OnEndEditRow(wnd, row, TLC_ENDEDITCANCEL);
        }
      }
      else
      {
        lines -= rc.lines - 1;
        ++repaint;
      }
      break;
    }
    
    case TVK_NEXT:
    {
      if (TLCT_EDITING == lctl->editingstate)
      {
        _TLC_OnEndEdit(wnd, TLC_ENDEDITCANCEL); /* edit cancel */
        /*_TLC_OnMovingCursor(wnd, ch);*/
        _TLC_OnEndMoving(wnd);
        if (TLCT_INSERTING == lctl->insertingstate)
        {
          _TLC_OnEndInsertRow(wnd, row, TLC_ENDEDITCANCEL);
        }
        else
        {
          _TLC_OnEndEditRow(wnd, row, TLC_ENDEDITCANCEL);
        }
      }
      else
      {
        lines += rc.lines - 1;
        ++repaint;
      }
      break;
    }
    
    default:
    {
       break;
    }
  }
  if (repaint)
  {
    lctl->curselrow += lines;
    if (lctl->curselrow >= lctl->nitems)
    {
      lctl->curselrow = lctl->nitems - 1;
    }
    else if (lctl->curselrow < 0)
    {
      lctl->curselrow = 0;
    }
    
    if (lctl->curselrow >= lctl->firstvisiblerow + rc.lines - 1)
    {
      lctl->firstvisiblerow += lines;
      if (lctl->firstvisiblerow - 1 > lctl->nitems - rc.lines)
      {
        lctl->firstvisiblerow = lctl->nitems - rc.lines;
      }
    }
    else if (lctl->firstvisiblerow > lctl->curselrow)
    {
      lctl->firstvisiblerow += lines;
      if (lctl->firstvisiblerow < 0)
      {
        lctl->firstvisiblerow = 0;
      }
    }
    /* send notification */
    _TLC_OnSelChanged(wnd);
    
    TuiInvalidateWnd(wnd);
  }
}

TLONG _TLC_OnGetItemCount(TWND wnd)
{
  PTLISTCTRL lctl = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  return lctl->nitems;
}

TLONG _TLC_OnSetItem(TWND wnd, TUINT flags, TSUBITEM* subitem)
{
  PTLISTCTRL lctl = 0;
  tlistcell_t* cell = 0;
  TLONG rc = TUI_ERROR;

  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  cell = _TLC_FindCellByIndex(lctl, subitem->col, subitem->idx);
  if (cell)
  {
    if (flags & TLCFM_TEXT)  { strcpy(cell->caption, subitem->text);  }
    if (flags & TLCFM_DATA)  { cell->data  = subitem->data;  }
    if (flags & TLCFM_ATTRS) { cell->attrs = subitem->attrs; }
    rc = TUI_OK;
  }
  return rc;
}

TLONG _TLC_OnGetItem(TWND wnd, TUINT flags, TSUBITEM* subitem)
{
  PTLISTCTRL lctl = 0;
  tlistcell_t* cell = 0;
  TLONG rc = TUI_ERROR;

  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  cell = _TLC_FindCellByIndex(lctl, subitem->col, subitem->idx);
  if (cell)
  {
    if (flags & TLCFM_TEXT)  { subitem->text  = cell->caption;  }
    if (flags & TLCFM_DATA)  { subitem->data  = cell->data;  }
    if (flags & TLCFM_ATTRS) { subitem->attrs = cell->attrs; }
    rc = TUI_OK;
  }
  return rc;
}

TVOID _TLC_OnInvalidateItem(TWND wnd, TUINT col, TUINT idx)
{
  PTLISTCTRL lctl = 0;
  tlistcell_t* cell = 0;
  theader_t* header = 0;
  TRECT rcwnd;
  TRECT rccell;
  TDWORD attrs = 0;

  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  cell = _TLC_FindCellByIndex(lctl, col, idx);
  if (cell)
  {
    /* check if the cell is available on screen */
    TuiGetWndRect(wnd, &rcwnd);
    if (idx >= lctl->firstvisiblerow && 
        idx <  lctl->firstvisiblerow + rcwnd.lines)
    {
      if (col >= _TLC_FindHeaderIndex(lctl, lctl->firstvisiblehdr) &&
          col <  _TLC_FindHeaderIndex(lctl, lctl->lastvisiblehdr))
      {
        header = _TLC_FindHeaderByIndex(lctl, col);
        _TLC_GetCellRect(cell, &rccell);

        
        attrs = cell->attrs;
        if (idx == lctl->curselrow)
        {
          attrs = TuiReverseColor(CYAN_BLACK);
        }
        /* draw th item that it can be seen */
        _TLC_DrawItem(TuiGetDC(wnd), &rccell, 
          cell->caption, attrs, header->align, 0);
      }
    }
  }
}

TVOID _TLC_OnSetEditStyle(TWND wnd, TINT col, TDWORD editstyle)
{
  PTLISTCTRL lctl = 0;
  theader_t* header = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  header = _TLC_FindHeaderByIndex(lctl, col);
  if (header)
  {
    header->editstyle = TWS_CHILD|editstyle;
  }
}

TDWORD _TLC_OnGetEditStyle(TWND wnd, TINT col)
{
  PTLISTCTRL lctl = 0;
  theader_t* header = 0;
  TDWORD editstyle = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  header = _TLC_FindHeaderByIndex(lctl, col);
  if (header)
  {
    editstyle = header->editstyle;
  }
  return editstyle;
}

TVOID _TLC_OnSetCurRow(TWND wnd, TINT idx)
{
  PTLISTCTRL lctl = 0;
  TRECT rcwnd;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (idx < 0 || idx >= lctl->nitems)
  {
    if (lctl->nitems <= 0)
    {
      lctl->curselrow = -1;
    }
    else
    {
      lctl->curselrow = lctl->nitems-1;
    }
    TuiInvalidateWnd(wnd);
    return;
  }
  
  /* find the new appropriate first visible item */
  TuiGetWndRect(wnd, &rcwnd);
  if (idx >= lctl->firstvisiblerow &&
      idx <  lctl->firstvisiblerow + rcwnd.lines)
  {
    /* no moved first visible item */
  }
  else
  {
    if (idx > lctl->nitems - rcwnd.lines)
    {
      lctl->firstvisiblerow = lctl->nitems - rcwnd.lines;
    }
    else
    {      
      lctl->firstvisiblerow = idx;
    }
  }
  /* set current selected row */
  lctl->curselrow = idx;
  
  /* re-fresh window */
  TuiInvalidateWnd(wnd);
}

TINT _TLC_OnGetCurRow(TWND wnd)
{
  PTLISTCTRL lctl = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  
  return lctl->curselrow;
}

TVOID _TLC_OnSetColWidth(TWND wnd, TINT col, TINT width)
{
  PTLISTCTRL lctl = 0;
  theader_t* header = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  header = _TLC_FindHeaderByIndex(lctl, col);
  if (header)
  {
    header->cols = width;
  }
}

TWND _TLC_OnGetEditBox(TWND wnd)
{
  PTLISTCTRL lctl = 0;
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  return lctl->editbox;
}

TVOID _TLC_OnSetCurPage(TWND wnd, TINT npage)
{
  TINT idx = 0;
  TINT nitemspp = _TLC_OnGetItemsPerPage(wnd);
  
  idx = (npage * nitemspp);
  TuiSendMsg(wnd, TLCM_SETCURROW, (TWPARAM)idx, 0);
}

TINT _TLC_OnGetCurPage(TWND wnd)
{
  TINT curselrow = _TLC_OnGetCurRow(wnd);
  TINT nitems = _TLC_OnGetItemCount(wnd);
  TINT nitemspp = _TLC_OnGetItemsPerPage(wnd);
  TINT npage = -1;
  
  /* items is greater than zero */
  if (nitems > 0 && nitemspp > 0)
  {
    /* has selected row yet? */
    if (curselrow < 0)
    {
      curselrow = 0;
    }
    /* find the current page */
    npage = (curselrow / nitemspp);
  }
  return npage;
}

TINT _TLC_OnGetItemsPerPage(TWND wnd)
{
  TRECT rcwnd;
  TuiGetWndRect(wnd, &rcwnd);
  return (rcwnd.lines > 1 ? rcwnd.lines - 1 : 0);
}

TLONG LISTCTRLPROC(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam)
{
  switch (msg)
  {
    case TWM_CREATE:
    {
      /* initial memory for static control */
      return _TLC_OnCreate(wnd);
    }
    case TWM_DESTROY:
    {
      /* release memory of static control */
      _TLC_OnDestroy(wnd);
      return 0;
    }

    case TWM_SETFOCUS:
    {
      _TLC_OnSetFocus(wnd);
      break;
    }
    case TWM_KILLFOCUS:
    {
      return _TLC_OnKillFocus(wnd);
    }

    case TWM_KEYDOWN:
    {
      _TLC_OnKeyDown(wnd, (TLONG)wparam);
      break;
    }
    
    case TWM_CHAR:
    {
      _TLC_OnChar(wnd, (TLONG)wparam);
      break;
    }

    case TWM_PAINT:
    {
      _TLC_OnPaint(wnd, TuiGetDC(wnd));
      return 0;
    }
    
    case TLCM_ADDCOLUMN:
    {
      return _TLC_OnAddColumn(wnd, (THEADERITEM*)lparam);
    }
    case TLCM_DELETECOLUMN:
    {
      _TLC_OnDeleteColumn(wnd, (TINT)wparam);
      return 0;
    }
    case TLCM_DELETEALLCOLUMNS:
    {
      _TLC_OnDeleteAllItems(wnd);
      return 0;
    }
    case TLCM_ADDITEM:
    {
      return _TLC_OnAddItem(wnd, (TLPSTR)lparam, (TINT)wparam);
    }
    case TLCM_DELETEITEM:
    {
      _TLC_OnDeleteItem(wnd, (TINT)lparam);
      return 0;
    }
    case TLCM_DELETEALLITEMS:
    {
      _TLC_OnDeleteAllItems(wnd);
      return 0;
    }
    case TLCM_SETITEM:
    {
      return _TLC_OnSetItem(wnd, (TUINT)wparam, (TSUBITEM*)lparam);
    }
    case TLCM_GETITEM:
    {
      return _TLC_OnGetItem(wnd, (TUINT)wparam, (TSUBITEM*)lparam);
    }
    case TLCM_GETITEMCOUNT:
    {
      return _TLC_OnGetItemCount(wnd);
    }
    case TLCM_INVALIDATEITEM:
    {
      _TLC_OnInvalidateItem(wnd, (TUINT)wparam, (TUINT)lparam);
      return 0;
    }
    case TLCM_SETEDITSTYLE:
    {
      _TLC_OnSetEditStyle(wnd, (TINT)wparam, (TDWORD)lparam);
      return 0;
    }
    case TLCM_GETEDITSTYLE:
    {
      return _TLC_OnGetEditStyle(wnd, (TINT)wparam);
    }
    case TLCM_GETCURROW:
    {
      return _TLC_OnGetCurRow(wnd);
    }
    case TLCM_SETCURROW:
    {
      _TLC_OnSetCurRow(wnd, (TINT)lparam);
      return 0;
    }
    case TLCM_SETCOLWIDTH:
    {
      _TLC_OnSetColWidth(wnd, (TINT)wparam, (TINT)lparam);
      return 0;
    }
    case TLCM_GETEDITBOX:
    {
      return (TLONG)_TLC_OnGetEditBox(wnd);
    }
    case TLCM_SETCURPAGE:
    {
      _TLC_OnSetCurPage(wnd, (TINT)wparam);
      return 0;
    }
    case TLCM_GETCURPAGE:
    {
      return _TLC_OnGetCurPage(wnd);
    }
    case TLCM_GETITEMSPERPAGE:
    {
      return _TLC_OnGetItemsPerPage(wnd);
    }
    case TLCM_SETEDITABLECOLS:
    {
      _TLC_OnSetEditableCols(wnd, (TINT)wparam, (TINT*)lparam);
      break;
    }
  }
  return TuiDefWndProc(wnd, msg, wparam, lparam);
}

/*-------------------------------------------------------------------
 * LISTPAGECTRL functions
 *-----------------------------------------------------------------*/
/* listctrl procedure is a based class of listpagectrl */
TVOID  _TLPC_OnKeyDown(TWND wnd, TLONG ch);
TDWORD _TLPC_OnSetEditStyle(TWND wnd, TINT idx, TDWORD style);
TDWORD _TLPC_OnGetEditStyle(TWND wnd, TINT idx);
TLONG  _TLPC_OnCreate(TWND wnd);
TVOID  _TLPC_OnPaint(TWND wnd, TDC dc);
TVOID  _TLPC_OnSetCurPage(TWND wnd, TINT npage);
TINT   _TLPC_OnGetCurPage(TWND wnd);
TVOID  _TLPC_OnGetItemsPerPage(TWND wnd, TINT nitems);
TVOID  _TLPC_OnSetCurRow(TWND wnd, TINT idx);
TVOID  _TLPC_OnSetFocus(TWND wnd);
TVOID  _TLPC_OpenEditBox(TWND wnd, TINT row);
TLONG  _TLPC_OnAddItem(TWND wnd, TLPSTR text);
TLONG  _TLPC_OnAddItemEx(TWND wnd, TLPSTR text, TDWORD editstyle);

TVOID  _TLPC_OpenEditBox(TWND wnd, TINT row)
{
  TDWORD editstyle = _TLPC_OnGetEditStyle(wnd, row);
/*  TWND edit = _TLC_OnGetEditBox(wnd);
  TuiSetWndStyle(edit, editstyle);
*/
  TLPC_SetEditStyle(wnd, row, editstyle);
  /* end editing from the previous */
  _TLC_OnEndEdit(wnd, TLC_ENDEDITOK);
  
  _TLPC_OnSetCurRow(wnd, row);
  
  /* re-fresh window to re-calculate position */
  TuiInvalidateWnd(wnd);
  
  /* move edit to the new position */
  _TLC_OnBeginMoving(wnd);
  _TLC_OnMovingCursor(wnd, TVK_RIGHT);

  /* open the current edit position */
  _TLC_OnBeginEdit(wnd);
}

TVOID _TLPC_OnKeyDown(TWND wnd, TLONG ch)
{
  PTLISTCTRL lctl = 0;
  TRECT rc;
  TINT currow = -1;
 
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  TuiGetWndRect(wnd, &rc);
  
  if (lctl->nheaders <= 0)
  {
    return;
  }

  switch (ch)
  {
    /* ignore some keys */
    case TVK_SPACE:
#if defined __USE_CURSES__
    /*case KEY_F(10):*/
    case KEY_F(6):
    case KEY_F(7):
    case KEY_RIGHT:
    case KEY_LEFT:
#elif defined __USE_WIN32__
    case TVK_F6:
    case TVK_F7:
    case TVK_RIGHT:
    case TVK_LEFT:
#endif
    {
      break;
    }

    /* enter is equal to key down arrow */
#if defined __USE_CURSES__
    case KEY_ENTER:
    case KEY_DOWN:
#elif defined __USE_WIN32__
    case TVK_ENTER:
#endif
    {
      currow = _TLC_OnGetCurRow(wnd);
      _TLPC_OpenEditBox(wnd, currow + 1);
      break;
    }
  
#if defined __USE_CURSES__
    case KEY_UP:
#elif defined __USE_WIN32__
    case TVK_UP:
#endif
    {
      currow = _TLC_OnGetCurRow(wnd);
      _TLPC_OpenEditBox(wnd, currow - 1);
      break;
    }
      
#ifdef __USE_CURSES__
    case KEY_PPAGE:
#elif defined __USE_WIN32__
    case TVK_PRIOR:
#endif
    {
      break;
    }
    
#ifdef __USE_CURSES__
    case KEY_NPAGE:
#elif defined __USE_WIN32__
    case TVK_NEXT:
#endif
    {
      break;
    }
/*
    case TVK_TAB:
    case KEY_BTAB:
    {
      currow = _TLC_OnGetCurRow(wnd);
      _TLPC_OpenEditBox(wnd, currow);
      
      TuiPostMsg(TuiGetParent(wnd), TWM_KEYDOWN, (TWPARAM)ch, 0);
      break;
    }
*/
    default:
    {
      LISTCTRLPROC(wnd, TWM_KEYDOWN, (TWPARAM)ch, (TLPARAM)0);
      return;
    }
  }
}

TDWORD _TLPC_OnSetEditStyle(TWND wnd, TINT idx, TDWORD style)
{
  PTLISTCTRL lctl = TuiGetWndParam(wnd);
  TDWORD oldstyle = 0;  
  tlistcell_t* cell = _TLC_FindCellByIndex(lctl, THEADER_VALUE, idx);
  if (cell)
  {
    oldstyle = cell->editstyle;
    cell->editstyle = style;
  }
  return oldstyle;
}

TDWORD _TLPC_OnGetEditStyle(TWND wnd, TINT idx)
{
  PTLISTCTRL lctl = TuiGetWndParam(wnd);
  TDWORD style = 0;  
  tlistcell_t* cell = 0;

  idx = lctl->curselrow;
  cell = _TLC_FindCellByIndex(lctl, THEADER_VALUE, idx);
  if (cell)
  {
    style = cell->editstyle;
  }
  return style;
}

TLONG _TLPC_OnCreate(TWND wnd)
{
  TDWORD style = TuiGetWndStyle(wnd);
  TLONG rc = _TLC_OnCreate(wnd);
  if (TUI_CONTINUE == rc)
  {
    style |= (TLCS_EDITABLE|TLCS_LINEEDIT|TLCS_NOHEADER|TLCS_NOSELECTION|TLCS_NOBORDER);
    TuiSetWndStyle(wnd, style);
    /* add 3 columns */
    TLC_AddColumnEx(wnd, "CAPTION", 40, TALIGN_LEFT, TuiGetColor(BLUE_YELLOW), 0, 0);
    TLC_AddColumnEx(wnd, "VALUE",   20, TALIGN_LEFT, TuiGetColor(BLUE_YELLOW), TES_AUTOHSCROLL, 0);
    TLC_AddColumnEx(wnd, "SUFFIX",  10, TALIGN_LEFT, TuiGetColor(BLUE_YELLOW), 0, 0);
  }
  return rc;
}

TVOID _TLPC_OnSetCurRow(TWND wnd, TINT idx)
{
  PTLISTCTRL lctl = 0;
  TINT nitemspp = _TLC_OnGetItemsPerPage(wnd);
  TINT npage = 0;
  TINT curpage = _TLC_OnGetCurPage(wnd);
  
  lctl = (PTLISTCTRL)TuiGetWndParam(wnd);
  if (idx < 0 || idx >= lctl->nitems)
  {
    return;
  }
  
  /* find the new appropriate first visible item */
  npage = (idx / nitemspp);
  if (npage != curpage)
  {
    /* first visible must be zero's index of each page */
    lctl->firstvisiblerow = (npage * nitemspp);
  }
  /* set current selected row */
  lctl->curselrow = idx;
}

TLONG _TLPC_OnAddItem(TWND wnd, TLPSTR text)
{
  TLONG nitems = _TLC_OnAddItem(wnd, text, 3);
  if (1 == nitems)
  {
    _TLPC_OpenEditBox(wnd, 0);
  }
  return nitems;
}

TLONG _TLPC_OnAddItemEx(TWND wnd, TLPSTR text, TDWORD editstyle)
{
  TLONG nitems = _TLPC_OnAddItem(wnd, text);
  if (nitems > 0)
  {
    _TLPC_OnSetEditStyle(wnd, nitems-1, editstyle);
  }
  return nitems;
}

TVOID _TLPC_OnSetFocus(TWND wnd)
{
  TINT currow = -1;
  currow = _TLC_OnGetCurRow(wnd);
  _TLPC_OnSetCurRow(wnd, currow);
}

TLONG LISTPAGECTRLPROC(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam)
{
  switch (msg)
  {
    case TWM_CREATE:
    {
      /* initial memory for static control */
      return _TLPC_OnCreate(wnd);
    }
    case TWM_KEYDOWN:
    {
      _TLPC_OnKeyDown(wnd, (TLONG)wparam);
      return 0;
    }
    case TLPCM_ADDITEMEX:
    {
      /* support 3 columns */
      return _TLPC_OnAddItemEx(wnd, (TLPSTR)lparam, (TDWORD)wparam);
    }
    case TLPCM_ADDITEM:
    {
      /* support 3 columns */
      return _TLPC_OnAddItem(wnd, (TLPSTR)lparam);
    }
    case TLPCM_SETCURROW:
    {
      _TLPC_OnSetCurRow(wnd, (TINT)wparam);
      return 0;
    }
    case TWM_SETFOCUS:
    {
      _TLPC_OnSetFocus(wnd);
      break;
    }
    case TLPCM_SETEDITSTYLE:
    {
      return _TLPC_OnSetEditStyle(wnd, (TINT)wparam, (TDWORD)lparam);
    }
    case TLPCM_GETEDITSTYLE:
    {
      return _TLPC_OnGetEditStyle(wnd, (TINT)wparam);
    }
  }
  return LISTCTRLPROC(wnd, msg, wparam, lparam);
}

