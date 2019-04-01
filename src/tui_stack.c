/*
 * File name: tui_stack.c
 * Author: Seree Rakwong
 * Date: 11-MAR-2019
 *
 */
#include "tui_stack.h"
#include "tui_list.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _STACK_IMPL_STRUCT
{
  struct _STACK_STRUCT vtab;
  /* members */
  tui_i32     items;
  tui_i32     lparam;
  tlist_t*     list;
};
typedef struct _STACK_IMPL_STRUCT stack_impl_t;

tui_i32     stack_push(tstack_t*, const void*, tui_ui32);
void        stack_pop(tstack_t*);
tui_ui32    stack_top(tstack_t*, void*, tui_ui32);
tui_i32     stack_is_empty(tstack_t*);
tui_i32     stack_is_full(tstack_t*);
node_t      stack_top_pointer(tstack_t*);
tui_i32     stack_count(tstack_t*);
tui_i32     stack_max_items(tstack_t*);

/*-------------------------------------------------------*/

tstack_t*
Stack_Create(tui_i32 items, tui_i32 lparam)
{
  stack_impl_t* stack = (stack_impl_t*)malloc(sizeof(stack_impl_t));
  if (stack)
  {
    memset(stack, 0, sizeof(stack_impl_t));
    if (items < 0)
    {
      items = 100;
    }
    stack->items  = items;
    stack->lparam = lparam;
    stack->list   = List_Create(lparam);
    /* functions */
    stack->vtab.Push        = stack_push;
    stack->vtab.Pop         = stack_pop;
    stack->vtab.Top         = stack_top;
    stack->vtab.IsEmpty     = stack_is_empty;
    stack->vtab.IsFull      = stack_is_full;
    stack->vtab.TopPointer  = stack_top_pointer;
    stack->vtab.Count       = stack_count;
    stack->vtab.GetMaxItems = stack_max_items;
  }
  return (tstack_t*)stack;
}

void
Stack_Destroy(tstack_t* stack)
{
  if (stack)
  {
    List_Destroy(((stack_impl_t*)stack)->list);
    free(stack);
  }
}


tui_i32
stack_push(tstack_t* stack, const void* vp, tui_ui32 size)
{
  tlist_t* list = ((stack_impl_t*)stack)->list;
  if (stack_is_full(stack))
  {
    return -1;
  }
  return (0 == list->InsertFirst(list, vp, size) ? -1 : 0);
}

void
stack_pop(tstack_t* stack)
{
  tlist_t* list = ((stack_impl_t*)stack)->list;
  if (stack_is_empty(stack))
  {
    return;
  }
  list->RemoveFirst(list);
}

tui_ui32
stack_top(tstack_t* stack, void* vp, tui_ui32 size)
{
  tlist_t* list = ((stack_impl_t*)stack)->list;
  list_iter_t top = list->Begin(list);
  if (stack_is_empty(stack))
  {
    return 0;
  }
  return list->GetItemData(top, vp, size);
}

tui_i32
stack_is_empty(tstack_t* stack)
{
  tlist_t* list = ((stack_impl_t*)stack)->list;
  return (0 >= list->Count(list));
}

tui_i32
stack_is_full(tstack_t* stack)
{
  tlist_t* list = ((stack_impl_t*)stack)->list;
  return (((stack_impl_t*)stack)->items <= list->Count(list));
}

node_t    stack_top_pointer(tstack_t* stack)
{
  tlist_t* list = ((stack_impl_t*)stack)->list;
  list_iter_t top = list->Begin(list);
  
  if (stack_is_empty(stack))
  {
    return 0;
  }
  return list->GetItemPointer(top);
}

tui_i32   stack_count(tstack_t* stack)
{
  tlist_t* list = ((stack_impl_t*)stack)->list;
  return list->Count(list);
}

tui_i32   stack_max_items(tstack_t* stack)
{
  return ((stack_impl_t*)stack)->items;
}

#ifdef __cplusplus
}
#endif
