/*
 * File name: tui_list.h
 * Author: Seree Rakwong
 * Date: 11-MAR-2019
 *
 * A list is implemented by the range as [a, b) (including a, but b)
 */

#ifndef _TUI_LIST_H_
#define _TUI_LIST_H_


#include "tui_node.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _LIST_STRUCT;
typedef struct _LIST_STRUCT tlist_t;

struct _LIST_ITER_STRUCT;
typedef struct _LIST_ITER_STRUCT* list_iter_t;

/* constructor and destructor functions */
tlist_t* List_Create(tui_i32 lparam);
void    List_Destroy(tlist_t*);

/* function interfaces */
typedef list_iter_t   (*fn_list_insert_first)(tlist_t*, const void*, tui_ui32);
typedef list_iter_t   (*fn_list_insert_last)(tlist_t*, const void*, tui_ui32);
typedef list_iter_t   (*fn_list_insert_before)(tlist_t*, list_iter_t, const void*, tui_ui32);
typedef list_iter_t   (*fn_list_insert_after)(tlist_t*, list_iter_t, const void*, tui_ui32);
typedef tui_i32       (*fn_list_remove_at)(tlist_t*, list_iter_t);
typedef tui_i32       (*fn_list_remove_all)(tlist_t*);
typedef tui_i32       (*fn_list_remove_first)(tlist_t*);
typedef tui_i32       (*fn_list_remove_last)(tlist_t*);
typedef tui_ui32      (*fn_list_get_count)(tlist_t*);
typedef list_iter_t   (*fn_list_begin)(tlist_t*);
typedef list_iter_t   (*fn_list_end)(tlist_t*);
typedef tui_i32       (*fn_list_set_item_data)(list_iter_t, const void*, tui_ui32);
typedef tui_ui32      (*fn_list_get_item_data)(list_iter_t, void*, tui_ui32);
typedef list_iter_t   (*fn_list_next)(list_iter_t);
typedef list_iter_t   (*fn_list_prev)(list_iter_t);
typedef node_t        (*fn_list_get_item_pointer)(list_iter_t);
typedef list_iter_t   (*fn_list_get_last)(tlist_t*);

/*
list_iter_t     list_insert_first(tlist_t*, const void*, tui_ui32);
list_iter_t     list_insert_last(tlist_t*, const void*, tui_ui32);
list_iter_t     list_insert_before(tlist_t*, list_iter_t, const void*, tui_ui32);
list_iter_t     list_insert_after(tlist_t*, list_iter_t, const void*, tui_ui32);
tui_i32         list_remove_at(tlist_t*, list_iter_t);
tui_i32         list_remove_all(tlist_t*);
tui_i32         list_remove_first(tlist_t*);
tui_i32         list_remove_last(tlist_t*);
tui_ui32        list_get_count(tlist_t*);
list_iter_t     list_begin(tlist_t*);
list_iter_t     list_end(tlist_t*);
tui_i32         list_set_item_data(list_iter_t, const void*, tui_ui32);
tui_ui32        list_get_item_data(list_iter_t, void*, tui_ui32);
list_iter_t     list_get_next(list_iter_t);
list_iter_t     list_get_prev(list_iter_t);
node_t          list_get_item_pointer(list_iter_t);
list_iter_t     list_get_last(tlist_t*);
*/

struct _LIST_STRUCT
{
    /* methods */
    fn_list_insert_first        InsertFirst;
    fn_list_insert_last         InsertLast;
    fn_list_insert_before       InsertBefore;
    fn_list_insert_after        InsertAfter;
    fn_list_remove_at           RemoveAt;
    fn_list_remove_all          RemoveAll;
    fn_list_remove_first        RemoveFirst;
    fn_list_remove_last         RemoveLast;
    fn_list_get_count           Count;
    fn_list_begin               Begin;
    fn_list_end                 End;
    fn_list_set_item_data       SetItemData;
    fn_list_get_item_data       GetItemData;
    fn_list_next                GetNext;
    fn_list_prev                GetPrev;
    fn_list_get_item_pointer    GetItemPointer;
    fn_list_get_last            GetLast;
};


#ifdef __cplusplus
}
#endif

#endif /* _TUI_LIST_H_ */

