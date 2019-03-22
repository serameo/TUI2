/*
 * File name: tui_tree.h
 * Author: Seree Rakwong
 * Date: 17-SEP-2013
 *
 */

#ifndef _TUI_TREE_H_
#define _TUI_TREE_H_

#include <stdlib.h>
#include <string.h>
#include "tui_node.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _TREE_STRUCT;
typedef struct _TREE_STRUCT tree_t;

struct _TREE_ITER_STRUCT;
typedef struct _TREE_ITER_STRUCT* tree_iter_t;

/* constructor and destructor functions */
tree_t* Tree_Create(tui_i32 lparam);
void    Tree_Destroy(tree_t*);

/* function interfaces */
typedef tui_i32         (*fn_tree_compare_proc)(const void*, const void*);
typedef tui_i32         (*fn_tree_traverse_proc)(void*, tree_iter_t, const void*, tui_ui32);
typedef tree_iter_t     (*fn_tree_insert_item)(tree_t*, tree_iter_t, const void *, tui_ui32);
typedef void            (*fn_tree_delete_item)(tree_t*, tree_iter_t);
typedef tree_iter_t     (*fn_tree_find_item)(tree_t*, const void *, fn_tree_compare_proc);
typedef tree_iter_t     (*fn_tree_find_next_item)(tree_t*, tree_iter_t, const void *, fn_tree_compare_proc);
typedef tui_ui32        (*fn_tree_count_item)(tree_t*);
typedef tui_ui32        (*fn_tree_count_child)(tree_iter_t);
typedef tui_i32         (*fn_tree_populate)(tree_t*, tree_iter_t, void*, fn_tree_traverse_proc, int);
typedef tui_ui32        (*fn_tree_get_level)(tree_iter_t);
typedef tui_i32         (*fn_tree_set_item_data)(tree_iter_t, const void*, tui_ui32);
typedef tui_ui32        (*fn_tree_get_item_data)(tree_iter_t, void*, tui_ui32);
typedef tree_iter_t     (*fn_tree_get_parent)(tree_iter_t);
typedef tree_iter_t     (*fn_tree_get_first_child)(tree_iter_t);
typedef tree_iter_t     (*fn_tree_get_last_child)(tree_iter_t);
typedef tree_iter_t     (*fn_tree_get_prev_item)(tree_iter_t);
typedef tree_iter_t     (*fn_tree_get_next_item)(tree_iter_t);
typedef tree_iter_t     (*fn_tree_get_root_item)(tree_t*);
typedef tui_i32         (*fn_tree_get_param)(tree_t*);
typedef node_t          (*fn_tree_get_item_pointer)(tree_iter_t);

enum
{
  TPO_PRE  = -1,  /* tree_populate_pre_order */
  TPO_IN   = 0,   /* tree_populate_in_order */
  TPO_POST = 1    /* tree_populate_post_order */
};


/*
tree_iter_t     tree_insert_item(
    tree_t*          tree,
    tree_iter_t     parent,
    const void *    data,
    tui_ui32   size);
void            tree_delete_item(
    tree_t*          tree,
    tree_iter_t     item);
tree_iter_t     tree_find_item(
    tree_t* tree,
    const void * vp,
    fn_tree_compare_proc compare);
tree_iter_t     tree_find_next_item(
    tree_t*      tree,
    tree_iter_t item,
    const void * vp,
    fn_tree_compare_proc compare);
tui_ui32   tree_count_item(tree_t* tree);
tui_ui32   tree_count_child(tree_iter_t item);

tui_i32         tree_populate(
    tree_t*      tree,
    tree_iter_t item,
    const void* args,
    fn_tree_traverse_proc   traverse,
    int         how_to_walk); // < 0 := PRE-ORDER,
                              // = 0 := IN-ORDER,
                              // > 0 := POST-ORDER


tui_ui32        tree_get_level(tree_iter_t item);
tui_i32         tree_set_item_data(tree_iter_t, const void*, tui_ui32);
tui_ui32        tree_get_item_data(tree_iter_t, void*, tui_ui32);
tree_iter_t     tree_get_parent(tree_iter_t);
tree_iter_t     tree_get_first_child(tree_iter_t);
tree_iter_t     tree_get_last_child(tree_iter_t);
tree_iter_t     tree_get_prev_item(tree_iter_t);
tree_iter_t     tree_get_next_item(tree_iter_t);
tree_iter_t     tree_get_root_item(tree_t*);
tui_i32         tree_get_param(tree_t*);
node_t          tree_get_item_pointer(tree_iter_t);
*/

struct _TREE_STRUCT
{
    /* methods */
    fn_tree_insert_item             InsertItem;
    fn_tree_delete_item             DeleteItem;
    fn_tree_find_item               FindItem;
    fn_tree_find_next_item          FindNextItem;
    fn_tree_count_item              CountItem;
    fn_tree_count_child             CountChild;
    fn_tree_populate                Populate;
    fn_tree_get_level               GetLevel;
    fn_tree_set_item_data           SetItemData;
    fn_tree_get_item_data           GetItemData;
    fn_tree_get_parent              GetParent;
    fn_tree_get_first_child         GetFirstChild;
    fn_tree_get_last_child          GetLastChild;
    fn_tree_get_prev_item           GetPrevItem;
    fn_tree_get_next_item           GetNextItem;
    fn_tree_get_root_item           GetRootItem;
    fn_tree_get_param               GetParam;
    fn_tree_get_item_pointer        GetItemPointer;
};


#ifdef __cplusplus
}
#endif

#endif /* _TUI_TREE_H_ */

