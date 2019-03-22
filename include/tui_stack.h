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
typedef struct _STACK_STRUCT stack_t;

/* constructor and destructor functions */
stack_t*  Stack_Create(tui_i32 items, tui_i32 lparam);
void      Stack_Destroy(stack_t*);

/*
 * LIFO
 */
typedef tui_i32       (*fn_stack_push)(stack_t*, const void*, tui_ui32);
typedef void          (*fn_stack_pop)(stack_t*);
typedef tui_ui32      (*fn_stack_top)(stack_t*, void*, tui_ui32);
typedef tui_i32       (*fn_stack_is_empty)(stack_t*);
typedef tui_i32       (*fn_stack_is_full)(stack_t*);
typedef node_t        (*fn_stack_top_pointer)(stack_t*);
typedef tui_i32       (*fn_stack_count)(stack_t*);
typedef tui_i32       (*fn_stack_max_items)(stack_t*);
/*
tui_i32   stack_push(stack_t*, const void*, tui_ui32);
void      stack_pop(stack_t*);
tui_ui32  stack_top(stack_t*, void*, tui_ui32);
tui_i32   stack_is_empty(stack_t*);
tui_i32   stack_is_full(stack_t*);
node_t    stack_top_pointer(stack_t*);
tui_i32   stack_count(stack_t*);
tui_i32   stack_max_items(stack_t*);
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

