/*
 * File name: tui_list.c
 * Author: Seree Rakwong
 * Date: 11-MAR-2019
 */
#include "tui_list.h"
#include "tui_node.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _LIST_ITER_STRUCT
{
    node_t        node;
    tui_ui32      node_size;
    list_iter_t   prev;
    list_iter_t   next;
};

struct _LIST_IMPL_STRUCT
{
    /*methods*/
    struct _LIST_STRUCT       vtab; /* always the first member */
    list_iter_t     head;
    list_iter_t     tail;
    tui_ui32        nodes;
    tui_i32         lparam;
};
typedef struct _LIST_IMPL_STRUCT list_impl_t;




list_iter_t
_list_iterator_init(const void* vp, tui_ui32 size)
{
    list_iter_t iter = (list_iter_t)malloc(sizeof(struct _LIST_ITER_STRUCT));
    if (iter != 0)
    {
        memset(iter, 0, sizeof(struct _LIST_ITER_STRUCT));
        if (vp && size > 0)
        {
            iter->node = Node_Init(vp, size);
            iter->node_size = size;
        }
    }
    return iter;
}

void
_list_iterator_release(list_iter_t iter)
{
    if (iter)
    {
        if (iter->node)
        {
            Node_Release(iter->node);
        }
        free(iter);
    }
}

/*------------------------------------------------------------*/
list_iter_t     list_insert_first(list_t*, const void*, tui_ui32);
list_iter_t     list_insert_last(list_t*, const void*, tui_ui32);
list_iter_t     list_insert_before(list_t*, list_iter_t, const void*, tui_ui32);
list_iter_t     list_insert_after(list_t*, list_iter_t, const void*, tui_ui32);
void            list_free(list_t*);
tui_i32         list_remove_at(list_t*, list_iter_t);
tui_i32         list_remove_all(list_t*);
tui_i32         list_remove_first(list_t*);
tui_i32         list_remove_last(list_t*);
tui_ui32        list_get_count(list_t*);
list_iter_t     list_begin(list_t*);
list_iter_t     list_end(list_t*);
tui_i32         list_set_item_data(list_iter_t, const void*, tui_ui32);
tui_ui32        list_get_item_data(list_iter_t, void*, tui_ui32);
list_iter_t     list_get_next(list_iter_t);
list_iter_t     list_get_prev(list_iter_t);
node_t          list_get_item_pointer(list_iter_t);
list_iter_t     list_get_last(list_t*);

/*------------------------------------------------------------*/
list_t*
List_Create(tui_i32 lparam)
{
    list_impl_t* list = (list_impl_t*)malloc(sizeof(list_impl_t));
    
    if (list != 0)
    {
        list->nodes   = 0;
        list->head    = list->tail  = _list_iterator_init(0, 0);
        list->lparam  = lparam;
        /* init methods */
        list->vtab.InsertFirst      = list_insert_first;
        list->vtab.InsertLast       = list_insert_last;
        list->vtab.InsertBefore     = list_insert_before;
        list->vtab.InsertAfter      = list_insert_after;
        list->vtab.RemoveAt         = list_remove_at;
        list->vtab.RemoveAll        = list_remove_all;
        list->vtab.RemoveFirst      = list_remove_first;
        list->vtab.RemoveLast       = list_remove_last;
        list->vtab.Count            = list_get_count;
        list->vtab.Begin            = list_begin;
        list->vtab.End              = list_end;
        list->vtab.SetItemData      = list_set_item_data;
        list->vtab.GetItemData      = list_get_item_data;
        list->vtab.GetNext          = list_get_next;
        list->vtab.GetPrev          = list_get_prev;
        list->vtab.GetItemPointer   = list_get_item_pointer;
        list->vtab.GetLast          = list_get_last;
    }
    return (list_t*)list;
}

void
List_Destroy(list_t* list)
{
    if (list)
    {
        list_remove_all(list);
        free(list);
    }
}

list_iter_t
list_get_head(list_t* list)
{
  return ((list_impl_t*)list)->head;
}

list_iter_t
list_get_tail(list_t* list)
{
  return ((list_impl_t*)list)->tail;
}

list_iter_t
list_get_next(list_iter_t iter)
{
  return (iter ? iter->next : 0);
}

list_iter_t
list_get_prev(list_iter_t iter)
{
  return (iter ? iter->prev : 0);
}

list_iter_t
list_insert_first(list_t* list, const void* vp, tui_ui32 size)
{
    list_iter_t iter = 0;
    list_impl_t* impl = (list_impl_t*)list;
    
    if (vp && size)
    {
        iter = _list_iterator_init(vp, size);
        if (iter != 0)
        {
            iter->next = impl->head;
            impl->head->prev = iter;
            impl->head = iter;

            impl->nodes += 1;
        }
    }
    return iter;
}

list_iter_t
list_insert_last(list_t* list, const void* vp, tui_ui32 size)
{
    list_iter_t iter = 0;
    list_impl_t* impl = (list_impl_t*)list;
    
    if (vp && size)
    {
        iter = _list_iterator_init(vp, size);
        if (iter != 0)
        {
            iter->next = impl->tail;
            iter->prev = impl->tail->prev;

            if (impl->tail->prev)
            {
                impl->tail->prev->next = iter;
            }
            impl->tail->prev = iter;

            if (impl->head == impl->tail)
            {
                impl->head = iter;
            }

            impl->nodes += 1;
        }
    }
    return iter;
}

list_iter_t
list_insert_before(list_t* list, list_iter_t iter_after, const void* vp, tui_ui32 size)
{
    list_iter_t iter = 0;
    list_impl_t* impl = (list_impl_t*)list;
    
    if (vp && size > 0)
    {
        iter = _list_iterator_init(vp, size);
        if (iter != 0)
        {
            iter->next = iter_after;
            iter->prev = iter_after->prev;

            if (iter_after->prev)
            {
                iter_after->prev->next = iter;
            }
            iter_after->prev = iter;

            impl->nodes += 1;
        }
    }
    return iter;
}

list_iter_t
list_insert_after(list_t* list, list_iter_t iter_before, const void* vp, tui_ui32 size)
{
    list_iter_t iter = 0;
    list_impl_t* impl = (list_impl_t*)list;
    
    if (vp && size > 0)
    {
        iter = _list_iterator_init(vp, size);
        if (iter != 0)
        {
            iter->prev = iter_before;
            iter->next = iter_before->next;

            if (iter_before->next)
            {
                iter_before->next->prev = iter;
            }
            iter_before->next = iter;

            impl->nodes += 1;
        }
    }
    return iter;
}

tui_i32
list_remove_at(list_t* list, list_iter_t iter)
{
    tui_i32 rc = 0;
    list_impl_t* impl = (list_impl_t*)list;

    /* is it a head item? */
    if (iter == ((list_impl_t*)list)->head)
    {
        return list_remove_first(list);
    }

    /* is it a tail item? */
    if (iter == ((list_impl_t*)list)->tail)
    {
        return list_remove_last(list);
    }

    /* link them */
    if (iter->next)
    {
        iter->next->prev = iter->prev;
    }
    if (iter->prev)
    {
        iter->prev->next = iter->next;
    }

    /* remove it */
    _list_iterator_release(iter);

    if (impl->nodes > 0)
    {
        impl->nodes -= 1;
    }

    return rc;
}

tui_i32
list_remove_all(list_t* list)
{
    tui_i32 rc = 0;
    list_impl_t* impl = (list_impl_t*)list;
    list_iter_t iter = impl->head;

    while (iter != impl->tail)
    {
        list_remove_first(list);
        iter = impl->head;
    }
    /*
    * set the tail and head of the list
    */
    impl->tail->prev = 0;
    impl->head  = impl->tail;
    impl->nodes = 0;

    return rc;
}

tui_i32
list_remove_first(list_t* list)
{
    tui_i32 rc = 0;
    list_impl_t* impl = (list_impl_t*)list;
    list_iter_t iter = impl->head;

    if (iter == impl->tail)
    {
        /* no more item to remove */
        return 0;
    }

    impl->head = iter->next;
    impl->head->prev = 0;
    /* ok to free the memory */
    _list_iterator_release(iter);

    if (impl->nodes > 0)
    {
        impl->nodes -= 1;
    }

    return rc;
}

tui_i32
list_remove_last(list_t* list)
{
    tui_i32 rc = 0;
    list_impl_t* impl = (list_impl_t*)list;
    list_iter_t iter = impl->tail->prev;

    if (!iter)
    {
        /* no more item to remove */
        return 0;
    }

    impl->tail->prev = iter->prev;
    if (iter->prev)
    {
        iter->prev->next = impl->tail;
    }
    /* ok to free the memory */
    _list_iterator_release(iter);
    
    if (impl->nodes > 0)
    {
        impl->nodes -= 1;
    }
    return rc;
}

tui_ui32
list_get_count(list_t* list)
{
    return ((list_impl_t*)list)->nodes;
}

list_iter_t
list_begin(list_t* list)
{
    return ((list_impl_t*)list)->head;
}

list_iter_t list_end(list_t* list)
{
    return ((list_impl_t*)list)->tail;
}

list_iter_t
list_get_last(list_t* list)
{
  list_iter_t end = list_end(list);
  return list_get_prev(end);
}

tui_i32
list_set_item_data(
  list_iter_t iter,
  const void* vp,
  tui_ui32 size)
{
  node_t newnode = 0;
  
  if (iter && vp && size > 0)
  {
    if (!iter->node)
    {
      iter->node = Node_Init(vp, size);
    }
    else
    {
      if (size != iter->node_size)
      {
        newnode = Node_Init(vp, size);
        if (newnode)
        {
          Node_Release(iter->node);
          iter->node = newnode;
        }
        else
        {
          return -1;
        }
      }
      else
      {
        memcpy(iter->node, vp, size);
      }
    }
    iter->node_size = size;
  }
  return 0;
}

tui_ui32
list_get_item_data(
  list_iter_t iter,
  void* vp,
  tui_ui32 size)
{
  tui_ui32 node_size = 0;
  if (iter)
  {
    node_size = iter->node_size;
    if (vp && size >= iter->node_size)
    {
      memset(vp, 0, size);
      memcpy(vp, (const void*)iter->node, iter->node_size);
    }
  }
  return node_size;
}

node_t
list_get_item_pointer(list_iter_t iter)
{
  return (iter ? iter->node : 0);
}



#ifdef __cplusplus
}
#endif
