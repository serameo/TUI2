/*-------------------------------------------------------------------
 * File name: tuitypes.h
 * Author: Seree Rakwong
 * Date: 28-MAR-19
 *-----------------------------------------------------------------*/
#ifndef __TUI_TYPES_H__
#define __TUI_TYPES_H__

#include <curses.h>
#include "tuidefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------------
 * types
 *-----------------------------------------------------------------*/
 
typedef long                TWPARAM;
typedef long                TLPARAM;
typedef long                TLONG;
typedef int                 TINT;
typedef void                TVOID;
typedef void*               TLPVOID;
typedef const char*         TLPCSTR;
typedef char*               TLPSTR;
typedef char                TTCHAR;
typedef unsigned char       TBYTE;
typedef double              TDOUBLE;
typedef unsigned long       TDWORD;
typedef unsigned int        TUINT;
typedef char                TINT8;
typedef unsigned char       TUINT8;
typedef short               TINT16;
typedef unsigned short      TUINT16;
typedef int                 TINT32;
typedef unsigned int        TUINT32;
typedef long long           TINT64;
typedef unsigned long long  TUINT64;
typedef TINT32              TBOOL;
/* new defines */
typedef TWPARAM             TUI_WPARAM;
typedef TLPARAM             TUI_LPARAM;
typedef TLONG               TUI_LONG;
typedef TINT                TUI_INT;
typedef TVOID               TUI_VOID;
typedef TLPVOID             TUI_LPVOID;
typedef TLPCSTR             TUI_LPCSTR;
typedef TLPSTR              TUI_LPSTR;
typedef TTCHAR              TUI_CHAR;
typedef TBYTE               TUI_BYTE;
typedef TDOUBLE             TUI_DOUBLE;
typedef TDWORD              TUI_DWORD;
typedef TUINT               TUI_UINT;
typedef TINT8               TUI_INT8;
typedef TUINT8              TUI_UINT8;
typedef TINT16              TUI_INT16;
typedef TUINT16             TUI_UINT16;
typedef TINT32              TUI_INT32;
typedef TUINT32             TUI_UINT32;
typedef TINT64              TUI_INT64;
typedef TUINT64             TUI_UINT64;
typedef TUI_INT32           TUI_BOOL;
typedef TINT8               TUI_I8;
typedef TUINT8              TUI_UI8;
typedef TINT16              TUI_I16;
typedef TUINT16             TUI_UI16;
typedef TINT32              TUI_I32;
typedef TUINT32             TUI_UI32;
typedef TINT64              TUI_I64;
typedef TUINT64             TUI_UI64;
/* type definitions for tui data structure */
typedef TUI_VOID            tui_void;
typedef TUI_CHAR            tui_char;
typedef TUI_BYTE            tui_byte;
typedef TUI_CHAR            tui_i8;
typedef TUI_BYTE            tui_ui8;
typedef TUI_INT8            tui_i16;
typedef TUI_UINT8           tui_ui16;
typedef TUI_INT32           tui_i32;
typedef TUI_UINT32          tui_ui32;
typedef TUI_INT64           tui_i64;
typedef TUI_UINT64          tui_ui64;
typedef float               tui_f32;
typedef double              tui_f64;
typedef char*               tui_psz;
typedef float               tui_float;
typedef double              tui_double;
typedef long int            tui_int;
typedef short int           tui_short;
typedef long long           tui_long;


/* device context */
struct _TUIDEVICECONTEXSTRUCT;
typedef struct _TUIDEVICECONTEXSTRUCT _TDC;
typedef struct _TUIDEVICECONTEXSTRUCT *TDC;

/* window handle */
struct _TUIWINDOWSTRUCT;
typedef struct _TUIWINDOWSTRUCT _TWND;
typedef struct _TUIWINDOWSTRUCT *TWND;

/* window procedure */
typedef TLONG (*TWNDPROC)(TWND, TUINT, TWPARAM, TLPARAM);
/* procedure type */
typedef TLONG (*VALIDATEPROC)(TWND, TLPCSTR);

/* environment */
struct _TUIENVSTRUCT;
typedef struct _TUIENVSTRUCT _TENV;
typedef struct _TUIENVSTRUCT *TENV;

/* accelerator */
struct _TUIACCELSTRUCT
{
  TUI_INT     vkey;
  TUI_UINT    cmd;
};
typedef struct _TUIACCELSTRUCT _TUI_ACCEL;
typedef struct _TUIACCELSTRUCT TUI_ACCEL;

/* message structure */
struct _TMSGSTRUCT
{
  TWND        wnd;         /* window handle  */
  TUINT       msg;         /* window message */
  TWPARAM     wparam;      /* parameter      */
  TLPARAM     lparam;      /* parameter      */
};
typedef struct _TMSGSTRUCT TMSG;

/* notify message structure */
struct _NMHDRSTRUCT
{
  TUINT       id;            /* control id     */
  TUINT       code;          /* notify code    */
  TWND        ctl;           /* control handle */
};
typedef struct _NMHDRSTRUCT TNMHDR;

/* window rectangle */
struct _TRECTSTRUCT
{
  TINT        y;
  TINT        x;
  TINT        lines;
  TINT        cols;
};
typedef struct _TRECTSTRUCT TRECT;

/* y,x position */
struct _POSSTRUCT
{
  TINT    y;
  TINT    x;
};
typedef struct _POSSTRUCT TPOS;

struct _DRAWITEMSTRUCT
{
  TINT  idx;
  TRECT rcitem;
};
typedef struct _DRAWITEMSTRUCT TDRAWITEM;

typedef TUI_VOID (*TUI_TIMERPROC)(TWND, TUI_UINT32, TUI_VOID*);


struct _WNDTEMPLSTRUCT
{
  TLPCSTR  clsname;           /* window class   */
  TLPCSTR  text;              /* window text    */
  TINT     id;                /* window id      */
  TINT     y;                 /* y-position     */
  TINT     x;                 /* x-position     */
  TINT     lines;             /* window lines   */
  TINT     cols;              /* window columns */
  TDWORD   style;             /* window style   */
  VALIDATEPROC validateproc;  /* to validate value before exiting */
                              /* the edit box return TUI_CONTINUE */
                              /* if 2nd parameter is accepted     */
                              /* otherwise return TUI_ERROR       */
};
typedef struct _WNDTEMPLSTRUCT WNDTEMPL;

struct _FRMWNDTEMPLSTRUCT
{
  TLPCSTR  clsname;           /* window class   */
  TLPCSTR  text;              /* window text    */
  TINT     id;                /* window id      */
  TINT     y;                 /* y-position     */
  TINT     x;                 /* x-position     */
  TINT     lines;             /* window lines   */
  TINT     cols;              /* window columns */
  TDWORD   style;             /* window style   */
  TDWORD   exstyle;           /* window style   */
  VALIDATEPROC validateproc;  /* to validate value before exiting */
                              /* the edit box return TUI_CONTINUE */
                              /* if 2nd parameter is accepted     */
                              /* otherwise return TUI_ERROR       */
  TLPCSTR  infotext;          /* to display information in a      */
                              /* specific control                 */
};
typedef struct _FRMWNDTEMPLSTRUCT FRMWNDTEMPL;


/*-------------------------------------------------------------------
 * frame window
 *-----------------------------------------------------------------*/
struct _INITPAGESTRUCT
{
  TWND    firstchild;
  TWND    lastchild;
};
typedef struct _INITPAGESTRUCT _TINITPAGE;
typedef struct _INITPAGESTRUCT *TINITPAGE;

/* response from TWM_SHOWTMSGBOX, TWM_SHOWINPUTBOX, TWM_SHOWLINEINPUTBOX */
struct _RESPONSEMSGBOXSTRUCT
{
  TNMHDR      hdr;
  TUI_CHAR    text[TUI_MAX_WNDTEXT+1];
};
typedef struct _RESPONSEMSGBOXSTRUCT RESPONSEMSGBOX;
typedef struct _RESPONSEMSGBOXSTRUCT DISPLAYINFO;

struct _PAGECHANGESTRUCT
{
  TNMHDR   hdr;
  TINT     frompage;
  TINT     topage;
};

typedef struct _PAGECHANGESTRUCT PAGECHANGE;

struct _VALIDMINMAXSTRUCT
{
  TINT        min;
  TINT        max;
};
typedef struct _VALIDMINMAXSTRUCT VALIDMINMAX;

struct _NMHDRKEYPRESSEDSTRUCT
{
  TNMHDR      hdr;          /* notification header */
  TUI_LONG    vkey;
};
typedef struct _NMHDRKEYPRESSEDSTRUCT TNMHDRKEYPRESSEDSTRUCT;

struct _SUBITEMSTRUCT
{
  TINT          col;      /* column index, zero based */
  TINT          idx;      /* row index, zero based    */
  TUI_CHAR*     text;
  TDWORD        attrs;    /* text attributes          */
  TUI_LPARAM    data;     /* user data                */
};
typedef struct _SUBITEMSTRUCT TSUBITEM;

struct _NMHDRITEMSTRUCT
{
  TNMHDR      hdr;          /* notification header */
  TINT        row;
  TINT        col;
};
typedef struct _NMHDRITEMSTRUCT TNMHDRITEMSTRUCT;


struct _HEADERITEMSTRUCT
{
  TUI_CHAR*     caption;
  TINT          cols;
  TINT          align;      /* column alignment         */
  TDWORD        attrs;      /* header text attributes   */
  TDWORD        editstyle;  /* edit style, see TES_XXX  */
  TINT          decwidth;   /* TES_DECIMAL or TES_AUTODECIMALCOMMA, default 6 */
};
typedef struct _HEADERITEMSTRUCT THEADERITEM;

struct _TREE_ITER_STRUCT;
typedef struct _TREE_ITER_STRUCT TTREEITEM;

struct _TTREEITEMDATASTRUCT
{
  TUI_CHAR    itemtext[TUI_MAX_WNDTEXT+1];
  TLPARAM     lparam;
  TBOOL       expanded;
  TBOOL       selected;
  TLONG       children;
  TBOOL       populated;
};
typedef struct _TTREEITEMDATASTRUCT TTREEITEMDATA;

struct _NMHDRTREEITEMSTRUCT
{
  TNMHDR hdr;          /* notification header */
  TTREEITEM* item;
};
typedef struct _NMHDRTREEITEMSTRUCT TNMHDRTREEITEMCTRL;

/*typedef TLONG (*LPTREEFINDITEMPROC)(const TVOID*, const TVOID*);*/
typedef tui_i32  (*LPTREEFINDITEMPROC)(const void*, const void*);
typedef TLONG (*LPTREEEXPORTPROC)(FILE*, TTREEITEMDATA*);
typedef TLONG (*LPTREEIMPORTPROC)(TTREEITEMDATA*, TLPCSTR);

struct _TUIDEVICECONTEXSTRUCT
{
#ifdef __USE_CURSES__
  WINDOW*     win;
#elif defined __USE_WIN32__
  TVOID*      win;
  TVOID*      wout;
#endif
};

#ifdef __cplusplus
}
#endif
#endif /*__TUI_TYPES_H__*/

