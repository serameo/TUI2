/*
 * File name: tui_queue.c
 * Author: Seree Rakwong
 * Date: 11-MAR-2019
 *
 */
#include "tui_queue.h"
#include "tui_list.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _QUEUE_IMPL_STRUCT
{
  struct _QUEUE_STRUCT vtab;
  /* members */
  tui_i32     items;
  tui_i32     lparam;
  list_t*     list;
};
typedef struct _QUEUE_IMPL_STRUCT queue_impl_t;

tui_i32     queue_enqueue(queue_t*, const void*, tui_ui32);
void        queue_dequeue(queue_t*);
tui_ui32    queue_first(queue_t*, void*, tui_ui32);
tui_i32     queue_is_empty(queue_t*);
node_t      queue_first_pointer(queue_t* queue);
tui_i32     queue_count(queue_t*);
/*-------------------------------------------------------*/

queue_t*
Queue_Create(tui_i32 lparam)
{
  queue_impl_t* queue = (queue_impl_t*)malloc(sizeof(queue_impl_t));
  if (queue)
  {
    memset(queue, 0, sizeof(queue_impl_t));

    queue->items  = 0;
    queue->lparam = lparam;
    queue->list   = List_Create(lparam);
    
    queue->vtab.Enqueue       = queue_enqueue;
    queue->vtab.Dequeue       = queue_dequeue;
    queue->vtab.First         = queue_first;
    queue->vtab.IsEmpty       = queue_is_empty;
    queue->vtab.FirstPointer  = queue_first_pointer;
    queue->vtab.Count         = queue_count;
  }
  return (queue_t*)queue;
}

void
Queue_Destroy(queue_t* queue)
{
  if (queue)
  {
    List_Destroy(((queue_impl_t*)queue)->list);
    free(queue);
  }
}


tui_i32
queue_enqueue(queue_t* queue, const void* vp, tui_ui32 size)
{
  list_t* list = ((queue_impl_t*)queue)->list;
  return list->InsertLast(list, vp, size);
}

void
queue_dequeue(queue_t* queue)
{
  list_t* list = ((queue_impl_t*)queue)->list;
  if (queue_is_empty(queue))
  {
    return;
  }
  list->RemoveFirst(list);
}

tui_ui32
queue_first(queue_t* queue, void* vp, tui_ui32 size)
{
  list_t* list = ((queue_impl_t*)queue)->list;
  list_iter_t first = list->Begin(list);
  if (queue_is_empty(queue))
  {
    return 0;
  }
  return list->GetItemData(first, vp, size);
}

tui_i32
queue_is_empty(queue_t* queue)
{
  list_t* list = ((queue_impl_t*)queue)->list;
  return (0 >= list->Count(list));
}

node_t
queue_first_pointer(queue_t* queue)
{
  list_t* list = ((queue_impl_t*)queue)->list;
  list_iter_t first = list->Begin(list);
  if (queue_is_empty(queue))
  {
    return 0;
  }
  return list->GetItemPointer(first);
}

tui_i32     queue_count(queue_t* queue)
{
  list_t* list = ((queue_impl_t*)queue)->list;
  return list->Count(list);
}

#ifdef __cplusplus
}
#endif
