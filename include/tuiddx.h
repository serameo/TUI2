/*
 * File name: tuiddx.h
 * Author: Seree Rakwong
 * Date: 27-MAR-2019
 *
 * NOTE:
 * DDX = Dynamic Data Exchange
 */
#ifndef __TUI_DDX_H__
#define __TUI_DDX_H__

#include "tuitypes.h"


#ifdef __cplusplus
extern "C" {
#endif

struct _TUIDDXSTRUCT;
typedef struct _TUIDDXSTRUCT        tddx_t;
typedef struct _TUIDDXSTRUCT        TUIDDXSTRUCT;


struct _TUIDICTIONARYSTRUCT;

/*typedef TLONG (*VALIDATEPROC)(TWND, TLPCSTR);*/
struct _TUIDDXCONTEXT
{
  TUI_UINT32                  id;   /* map to control */
  TUI_CHAR*                   name; /* map to dictionary file */
  VALIDATEPROC                validateproc;
};
typedef struct _TUIDDXCONTEXT ddxctx_t;
typedef struct _TUIDDXCONTEXT TUIDDXCONTEXT;

tddx_t*     DDX_Create(TWND, struct _TUIDICTIONARYSTRUCT*, ddxctx_t*, TUI_LPARAM);
TUI_VOID    DDX_Destroy(tddx_t*);

typedef TUI_INT32             (*fn_ddx_load_to_buffer)(tddx_t*, const TUI_VOID*, TUI_UINT32, TUI_LPARAM);
typedef TUI_INT32             (*fn_ddx_save_from_buffer)(tddx_t*, TUI_VOID*, TUI_UINT32);
typedef TUI_INT32             (*fn_ddx_set_value)(tddx_t*, const TUI_CHAR*, const TUI_CHAR*);
typedef TUI_INT32             (*fn_ddx_get_value)(tddx_t*, const TUI_CHAR*, TUI_CHAR*);
typedef TUI_INT32             (*fn_ddx_validate)(tddx_t*, const TUI_CHAR*);
typedef TUI_INT32             (*fn_ddx_validate_all)(tddx_t*);
typedef TUI_INT32             (*fn_ddx_update_data)(tddx_t*, TUI_BOOL);
typedef TUI_VOID*             (*fn_ddx_get_buffer)(tddx_t*);
typedef TUI_UINT32            (*fn_ddx_get_buffer_size)(tddx_t*);
typedef TUI_UINT32            (*fn_ddx_get_tag)(tddx_t*);

struct _TUIDDXSTRUCT
{
    fn_ddx_load_to_buffer     LoadToBuffer;   /* load data to buffer */
    fn_ddx_save_from_buffer   SaveFromBuffer; /* get buffer */
    fn_ddx_set_value          SetValue;
    fn_ddx_get_value          GetValue;
    fn_ddx_validate           Validate;
    fn_ddx_validate_all       ValidateAll;
    fn_ddx_update_data        UpdateData;
    fn_ddx_get_buffer         GetBuffer;
    fn_ddx_get_buffer_size    GetBufferSize;
    fn_ddx_get_tag            GetTag;
};

#ifdef __cplusplus
}
#endif

#endif /* __TUI_DDX_H__ */
