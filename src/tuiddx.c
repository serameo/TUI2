/*
 * File name: tuiddx.c
 * Author: Seree Rakwong
 * Date: 27-MAR-2019
 *
 * NOTE:
 */

#include <stdlib.h>
#include <string.h>

#include "tui.h"
#include "tuiddx.h"
#include "tui_dic.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _TUIDDX_IMPL_STRUCT
{
  struct _TUIDDXSTRUCT  vtab;
  TWND                  frmwnd;
  TUI_LPARAM            lparam;
  ddxctx_t*             ctx;    /* dynamic data exchange context */
  tdic_t*               dic;
  TUI_VOID*             buffer; /* load and save */
  TUI_UINT32            size;
  TUI_LPARAM            tag;
};
typedef struct _TUIDDX_IMPL_STRUCT ddx_impl_t;



tui_void
_ddx_copy_data(
  TUI_VOID*           fldp,
  BOS_DICTIONARY*     fld_prop,
  const TUI_CHAR*     fld_val
)
{
  /*tui_void* fldp = (tui_void*)( (size_t)buffer + fld_prop->offset );*/
  switch ( fld_prop->type )
  {
    case DICT_HEX   : /*= 'X' */
    case DICT_BYTE  : /*= 'B',*/
    {
      tui_byte b = (tui_byte)atoi( fld_val );
      memcpy( fldp, &b, fld_prop->size );
      break;
    }
    case DICT_CHAR  : /*= 'C',*/
    {
      memcpy( fldp, fld_val, fld_prop->size );
      break;
    }
    case DICT_INT   : /*= 'I',*/
    {
      tui_int val = atoi( fld_val );
      memcpy( fldp, &val, fld_prop->size );
      break;
    }
    case DICT_LONG  : /*= 'L',*/
    {
      tui_long val = atol( fld_val );
      memcpy( fldp, &val, fld_prop->size );
      break;
    }
    case DICT_FLOAT : /*= 'F',*/
    {
      tui_float val = (tui_float)atof( fld_val );
      memcpy( fldp, &val, fld_prop->size );
      break;
    }    
    case DICT_DOUBLE: /*= 'D',*/
    {
      tui_double val = atof( fld_val );
      memcpy( fldp, &val, fld_prop->size );
      break;
    }
  }
}

tui_void
_ddx_get_field(
  tui_void*           recp,
  BOS_DICTIONARY* fld_prop,
  tui_char*           fldp
)
{
  switch ( fld_prop->type )
  {
    case DICT_HEX   : /*= 'X' */
    case DICT_BYTE  : /*= 'B',*/
    {
      unsigned char val = 0;
      memcpy( &val, recp, fld_prop->size );
      sprintf( fldp, "%d", val );
      break;
    }
    case DICT_CHAR  : /*= 'C',*/
    {
      memcpy( fldp, recp, fld_prop->size );
      break;
    }
    case DICT_INT   : /*= 'I',*/
    {
      int val = 0;
      memcpy( &val, recp, fld_prop->size );
      sprintf( fldp, "%d", val );
      break;
    }
    case DICT_LONG  : /*= 'L',*/
    {
      long val = 0;
      memcpy( &val, recp, fld_prop->size );
      sprintf( fldp, "%ld", val );
      break;
    }
    case DICT_FLOAT : /*= 'F',*/
    {
      float val = 0;
      memcpy( &val, recp, fld_prop->size );
      sprintf( fldp, "%f", val );
      break;
    }    
    case DICT_DOUBLE: /*= 'D',*/
    {
      double val = 0;
      memcpy( &val, recp, fld_prop->size );
      sprintf( fldp, "%f", val );
      break;
    }
  }
}


tui_int
_ddx_find_field(
  tdic_t*         dict,
  const TUI_CHAR*       field,
  BOS_DICTIONARY *fld_prop
)
{
  tui_int rc = DICT_OK;  
  tui_char key[TUI_MAX_DICT_NAME+1]   = "\0";
  
  sprintf( key, "%-*s", TUI_MAX_DICT_NAME, field );
  rc = dict->GetValue(
          dict,
          key,
          fld_prop
        );
  return rc;
}

ddxctx_t*
_ddx_find_ctx(
  ddxctx_t* ctx,
  const TUI_CHAR* field
)
{
  /* lookup the specific field */
  TUI_INT i;
  for (i=0; ctx[i].id != 0; ++i)
  {
    if (0 == strcmp(ctx[i].name, field))
    {
      return &ctx[i];
    }
  }
  return 0;
}

/*------------------------------*/

TUI_INT32    ddx_load_to_buffer(tddx_t*, const TUI_VOID*, TUI_UINT32, TUI_LPARAM);
TUI_INT32    ddx_save_from_buffer(tddx_t*, TUI_VOID*, TUI_UINT32);
TUI_INT32    ddx_set_value(tddx_t*, const TUI_CHAR*, const TUI_CHAR*);
TUI_INT32    ddx_get_value(tddx_t*, const TUI_CHAR*, TUI_CHAR*);
TUI_INT32    ddx_validate(tddx_t*, const TUI_CHAR*);
TUI_INT32    ddx_validate_all(tddx_t*);
TUI_INT32    ddx_update_data(tddx_t*, TUI_BOOL);
TUI_VOID*    ddx_get_buffer(tddx_t*);
TUI_UINT32   ddx_get_buffer_size(tddx_t*);
TUI_UINT32   ddx_get_tag(tddx_t*);
TUI_INT32    ddx_dump(tddx_t* ddx, FILE* fp);
/*------------------------------*/

tddx_t*
DDX_Create(
  TWND        wnd,
  tdic_t*     dic,
  ddxctx_t*   ctx,
  TUI_LPARAM  lparam)
{
  ddx_impl_t* impl = (ddx_impl_t*)malloc(sizeof(ddx_impl_t));
  if (impl)
  {
    memset(impl, 0, sizeof(ddx_impl_t));
    impl->lparam      = lparam;
    impl->frmwnd      = wnd;
    impl->dic         = dic;
    impl->ctx         = ctx;
    
    impl->vtab.LoadToBuffer     = ddx_load_to_buffer;
    impl->vtab.SaveFromBuffer   = ddx_save_from_buffer;
    impl->vtab.SetValue         = ddx_set_value;
    impl->vtab.GetValue         = ddx_get_value;
    impl->vtab.Validate         = ddx_validate;
    impl->vtab.ValidateAll      = ddx_validate_all;
    impl->vtab.UpdateData       = ddx_update_data;
    impl->vtab.GetBuffer        = ddx_get_buffer;
    impl->vtab.GetBufferSize    = ddx_get_buffer_size;
    impl->vtab.GetTag           = ddx_get_tag;
    impl->vtab.Dump             = ddx_dump;
  }
  return (tddx_t*)impl;
}

TUI_VOID    DDX_Destroy(tddx_t* ddx)
{
  if (ddx)
  {
    ddx_impl_t* impl = (ddx_impl_t*)ddx;
    if (impl->buffer)
    {
      free(impl->buffer);
    }
    free(ddx);
  }
}


TUI_VOID*
ddx_get_buffer(tddx_t* ddx)
{
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  return (impl->buffer);
}

TUI_UINT32
ddx_get_buffer_size(tddx_t* ddx)
{
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  return (impl->size);
}

TUI_UINT32
ddx_get_tag(tddx_t* ddx)
{
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  return (impl->tag);
}


TUI_INT32
ddx_update_data(
  tddx_t*   ddx,
  TUI_BOOL  updscr)
{
  TUI_INT32 rc = TUI_OK;
  TWND ctl = 0;
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  TINT i;
  TUI_CHAR text[TUI_MAX_WNDTEXT+1];
  
  if (0 == impl->frmwnd)
  {
      return 0;
  }
  if (updscr)
  {
    /* update from buffer to screen */
    for (i=0; impl->ctx[i].id != 0; ++i)
    {
      ctl = TuiGetWndItem(impl->frmwnd, impl->ctx[i].id);
      ddx_get_value(ddx, impl->ctx[i].name, text);
      TuiSetWndText(ctl, text);
    }
  }
  else
  {
    /* update from screen to buffer */
    for (i=0; impl->ctx[i].id != 0; ++i)
    {
      ctl = TuiGetWndItem(impl->frmwnd, impl->ctx[i].id);
      TuiGetWndText(ctl, text, TUI_MAX_WNDTEXT);
      ddx_set_value(ddx, impl->ctx[i].name, text);
    }
  }
  return rc;
}

TUI_INT32
ddx_load_to_buffer(
  tddx_t*           ddx,
  const TUI_VOID*   data,
  TUI_UINT32        size,
  TUI_LPARAM        tag)
{
  TUI_INT32 rc = TUI_OK;
  TUI_VOID* buffer = 0;
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  /* check valid pointer */
  if (!data && 0 == size)
  {
    return TUI_ERROR;
  }
  /* allocate the new memory */
  buffer = (TUI_VOID*)malloc(size);
  if (!buffer)
  {
    return TUI_MEM;
  }
  memcpy(buffer, data, size);
  /* release the existing memory */
  if (impl->buffer)
  {
    free(impl->buffer);
    impl->buffer = 0;
  }
  impl->buffer  = buffer;
  impl->size    = size;
  impl->tag     = tag;
  
  return rc;
}

TUI_INT32    ddx_save_from_buffer(tddx_t* ddx, TUI_VOID* data, TUI_UINT32 size)
{
  TUI_INT32 rc = TUI_OK;
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  
  if (impl->buffer)
  {
    if (size > impl->size)
    {
      size = impl->size;
    }
    memcpy(data, impl->buffer, size);
  }
  return rc;
}

TUI_INT32    ddx_set_value(tddx_t* ddx, const TUI_CHAR* field, const TUI_CHAR* val)
{
  TUI_INT32 rc = TUI_OK;
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  BOS_DICTIONARY fld_prop;
  ddxctx_t* ctx = _ddx_find_ctx(impl->ctx, field);
  
  /* lookup the specific field */
  /*
  if (!ctx)
  {
    return TUI_ERROR;
  }
  */
  
  /* check if the field required to validate */
  rc = TUI_CONTINUE;
  if (impl->frmwnd && ctx && ctx->validateproc)
  {
    rc = ctx->validateproc(
            TuiGetWndItem(impl->frmwnd, ctx->id),
            val);
  }
  /* check if validate is successful */
  if (TUI_CONTINUE == rc)
  {
    tui_void* fldp = 0;
    tui_void* recp = impl->buffer;
    
    memset( &fld_prop, 0, sizeof ( BOS_DICTIONARY ) );
    if (DICT_OK == _ddx_find_field(impl->dic, field, &fld_prop))
    {
        fldp = (tui_void*)( (size_t)recp + fld_prop.offset );
        _ddx_copy_data(
            fldp,
            &fld_prop,
            val);
    }
  }
  
  return rc;
}


TUI_INT32    ddx_get_value(tddx_t* ddx, const TUI_CHAR* field, TUI_CHAR* val)
{
  TUI_INT32 rc = TUI_OK;
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  BOS_DICTIONARY fld_prop;
  ddxctx_t* ctx = _ddx_find_ctx(impl->ctx, field);
    
  /* lookup the specific field */
  /*
  if (!ctx)
  {
    return TUI_ERROR;
  }
  */
  memset( &fld_prop, 0, sizeof ( BOS_DICTIONARY ) );
  if (DICT_OK == _ddx_find_field(impl->dic, field, &fld_prop))
  {
    _ddx_get_field(
      impl->buffer,
      &fld_prop,
      val);
  }
  return rc;
}


TUI_INT32    ddx_validate(tddx_t* ddx, const TUI_CHAR* field)
{
  TUI_INT32 rc = TUI_CONTINUE;
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  BOS_DICTIONARY fld_prop;
  ddxctx_t* ctx = _ddx_find_ctx(impl->ctx, field);
  TUI_CHAR buffer[BUFSIZ];
  
  /* lookup the specific field */
  if (!ctx)
  {
    return TUI_ERROR;
  }
  
  if (0 == impl->frmwnd)
  {
    return rc;
  }
  /* check if the field required to validate */
  if (ctx->validateproc)
  {
    memset( &fld_prop, 0, sizeof ( BOS_DICTIONARY ) );
    _ddx_find_field(impl->dic, field, &fld_prop);
    
    _ddx_get_field(
      impl->buffer,
      &fld_prop,
      buffer);
      
    rc = ctx->validateproc(
            TuiGetWndItem(impl->frmwnd, ctx->id),
            buffer);
  }
  if (rc != TUI_CONTINUE)
  {
    /* move cursor */
    TRECT rcwnd;
    TWND ctl = TuiGetWndItem(impl->frmwnd, ctx->id);
    TuiGetWndRect(ctl, &rcwnd);
    
    TuiPostMsg(ctl, TWM_SETFOCUS, 0, (TLPARAM)0);
    TuiMoveYX(TuiGetDC(ctl), rcwnd.y, rcwnd.x);
    return rc;
  }

  
  return rc;
}


TUI_INT32    ddx_validate_all(tddx_t* ddx)
{
  TUI_INT32 rc = TUI_CONTINUE;
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  dictlist_t* fld = 0;
  std_dic_t* dic = impl->dic->GetDict(impl->dic);
  tui_long  id_beg = ( 0 == impl->tag ? 0 : dic->nhdrs );
  tui_long  id_end = ( 0 == impl->tag ? dic->nhdrs : dic->nflds );
  tui_long  id = id_beg + 1;

  
  fld = dic->fld_first;
  while ( fld ) /* loop though the required field */
  {
    if ( fld->fld_prop.id == id )
    {
      break;
    }
    /* find the next field */
    fld = fld->next;
  }
  
  while ( fld && fld->fld_prop.id <= id_end )
  {
    rc = ddx_validate(ddx, fld->fld_prop.name);
    if (rc != TUI_CONTINUE)
    {
      break;
    }

    /* print next field */
    fld = fld->next;
  }
  return rc;
}

TUI_INT32 ddx_dump(tddx_t* ddx, FILE* fp)
{
  TUI_INT32 rc = TUI_CONTINUE;
  ddx_impl_t* impl = (ddx_impl_t*)ddx;
  dictlist_t* fld = 0;
  std_dic_t* dic = impl->dic->GetDict(impl->dic);
  tui_long  id_beg = ( 0 == impl->tag ? 0 : dic->nhdrs );
  tui_long  id_end = ( 0 == impl->tag ? dic->nhdrs : dic->nflds );
  tui_long  id = id_beg + 1;
  TUI_CHAR buffer[BUFSIZ];
  tui_void* recp = impl->buffer;
  tui_void* fldp = 0;

      
  fld = dic->fld_first;
  while ( fld ) /* loop though the required field */
  {
    if ( fld->fld_prop.id == id )
    {
      break;
    }
    /* find the next field */
    fld = fld->next;
  }
  
  while ( fld && fld->fld_prop.id <= id_end )
  {
    fldp = (tui_void*)( (size_t)recp + fld->fld_prop.offset );
    _ddx_get_field(
      fldp,
      &fld->fld_prop,
      buffer);
    fprintf(fp, "%s: [%.*s]\n",
      fld->fld_prop.name,
      fld->fld_prop.size,
      buffer);
    /* print next field */
    fld = fld->next;
  }
  return rc;
}


#ifdef __cplusplus
}
#endif
