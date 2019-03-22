/*
 * File name: tui_node.c
 * Author: Seree Rakwong
 * Date: 15-AUG-2018
 *
 * NOTE:
 */
#include "tui_node.h"
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* object */
object_t
Object_Init(const void* vp, tui_ui32 sz)
{    
    object_t obj = 0;

    if (0 == vp || 0 == sz)
    {
        return obj;
    }

    obj = (object_t)malloc(sz);
    if (obj != 0)
    {
        memcpy(obj, vp, sz);
    }
    return obj;
}

void
Object_Release(object_t obj)
{
    free(obj);
}

/* node */
node_t
Node_Init(const void* vp, tui_ui32 sz)
{ 
    return (node_t)Object_Init(vp, sz); 
}

void
Node_Release(node_t node)
{
    Object_Release((object_t)node);
}

/* context */
context_t
Context_Init(const void* vp, tui_ui32 sz)
{
    return (context_t) Object_Init(vp, sz);
}

void
Context_Release(context_t ctx)
{
    Object_Release((object_t)ctx);
}

#ifdef __cplusplus
}
#endif
