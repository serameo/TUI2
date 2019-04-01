/*
 * File name: tui_node.h
 * Author: Seree Rakwong
 * Date: 15-AUG-2018
 *
 * NOTE:
 */
#ifndef __TUI_NODE_H__
#define __TUI_NODE_H__

#include <stdlib.h>
#include <string.h>

#include "tuitypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* type definitions */
/*
typedef char                    tui_i8;
typedef unsigned char           tui_ui8;
typedef short                   tui_i16;
typedef unsigned short          tui_ui6;
typedef long int                tui_i32;
typedef unsigned long int       tui_ui32;
typedef long long               tui_i64;
typedef unsigned long long      tui_ui64;
typedef float                   tui_f32;
typedef double                  tui_f64;
typedef char*                   tui_psz;
*/
/* simple object */
struct _OBJECT_STRUCT;
typedef struct _OBJECT_STRUCT*        object_t;

/* constructor and destructor functions */
object_t      Object_Init(const tui_void*, tui_ui32);
tui_void      Object_Release(object_t);

/* node */
typedef object_t    node_t;
/* constructor and destructor functions */
node_t          Node_Init(const tui_void*, tui_ui32);
tui_void        Node_Release(node_t node);

/* context */
typedef object_t    context_t;
/* constructor and destructor functions */
context_t       Context_Init(const tui_void*, tui_ui32);
tui_void        Context_Release(context_t ctx);

#ifdef __cplusplus
}
#endif

#endif /* __TUI_NODE_H__ */
