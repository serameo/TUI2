/*
 * File name: tui_stack.h
 * Author: Seree Rakwong
 * Date: 11-MAR-2019
 *
 */

#ifndef _TUI_STACK_H_
#define _TUI_STACK_H_

#include "tui_node.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _STACK_STRUCT;
typedef struct _STACK_STRUCT tstack_t;

/* constructor and destructor functions */
tstack_t*  Stack_Create(tui_i32 items, tui_i32 lparam);
void      Stack_Destroy(tstack_t*);

/*
 * LIFO
 */
typedef tui_i32       (*fn_stack_push)(tstack_t*, const tui_void*, tui_ui32);
typedef tui_void      (*fn_stack_pop)(tstack_t*);
typedef tui_ui32      (*fn_stack_top)(tstack_t*, tui_void*, tui_ui32);
typedef tui_i32       (*fn_stack_is_empty)(tstack_t*);
typedef tui_i32       (*fn_stack_is_full)(tstack_t*);
typedef node_t        (*fn_stack_top_pointer)(tstack_t*);
typedef tui_i32       (*fn_stack_count)(tstack_t*);
typedef tui_i32       (*fn_stack_max_items)(tstack_t*);
/*
tui_i32   stack_push(tstack_t*, const void*, tui_ui32);
void      stack_pop(tstack_t*);
tui_ui32  tstack_top(tstack_t*, void*, tui_ui32);
tui_i32   stack_is_empty(tstack_t*);
tui_i32   stack_is_full(tstack_t*);
node_t    tstack_top_pointer(tstack_t*);
tui_i32   stack_count(tstack_t*);
tui_i32   stack_max_items(tstack_t*);
*/

struct _STACK_STRUCT
{
    /* methods */
    fn_stack_push         Push;
    fn_stack_pop          Pop;
    fn_stack_top          Top;
    fn_stack_is_empty     IsEmpty;
    fn_stack_is_full      IsFull;
    fn_stack_top_pointer  TopPointer;
    fn_stack_count        Count;
    fn_stack_max_items    GetMaxItems;
};


#ifdef __cplusplus
}
#endif

#endif /* _TUI_STACK_H_ */

