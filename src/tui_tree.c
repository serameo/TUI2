/*
 * File name: tui_tree.c
 * Author: Seree Rakwong
 * Date: 17-SEP-2013
 *
 */

#include "tui_tree.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _TREE_ITER_STRUCT
{
    node_t          node;
    tui_ui32   node_size;
    tui_ui32   children;
    tui_ui32   level;
    tree_iter_t     parent;
    tree_iter_t     first_child;
    tree_iter_t     last_child;
    tree_iter_t     prev_sibling;
    tree_iter_t     next_sibling;
};

struct _IMPLTREE_STRUCT
{
    /*methods*/
    struct _TREE_STRUCT       vtab; /* always the first member */
    /* properties */
    tree_iter_t               root;
    tui_ui32                  items;
    tui_i32                   lparam;
};
typedef struct _IMPLTREE_STRUCT tree_impl_t;

tree_iter_t
_tree_iter_init(const void* vp, tui_ui32 size)
{
    tree_iter_t iter = (tree_iter_t)malloc(sizeof(struct _TREE_ITER_STRUCT));
    if (iter)
    {
        memset(iter, 0, sizeof(struct _TREE_ITER_STRUCT));
        if (vp != 0 && size > 0)
        {
            iter->node = Node_Init(vp, size);
            iter->node_size = size;
        }
    }
    return iter;
}

void
_tree_iter_release(tree_iter_t iter)
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

void
_tree_iter_delete_item(tree_iter_t item)
{
    tree_iter_t prev = 0;
    if (item && item->first_child == 0)
    {
        _tree_iter_release(item);
        return;
    }
    if (item == 0)
    {
        return;
    }
    if (item->last_child)
    {
        prev = item->last_child->prev_sibling;
    }
    _tree_iter_delete_item(item->last_child);
    _tree_iter_delete_item(prev);
}

tui_i32
_tree_populate_pre_order(
    ttree_t*      tree,
    tree_iter_t item,
    void* args,
    fn_tree_traverse_proc   traverse);
tui_i32
_tree_populate_in_order(
    ttree_t*      tree,
    tree_iter_t item,
    void* args,
    fn_tree_traverse_proc   traverse);
tui_i32
_tree_populate_post_order(
    ttree_t*      tree,
    tree_iter_t item,
    void* args,
    fn_tree_traverse_proc   traverse);

/*---------------------------------------------------------*/
tree_iter_t     tree_insert_item(
    ttree_t*          tree,
    tree_iter_t     parent,
    const void *    data,
    tui_ui32   size);
void            tree_delete_item(
    ttree_t*          tree,
    tree_iter_t     item);
tree_iter_t     tree_find_item(
    ttree_t*                  tree,
    const void *            vp,
    fn_tree_compare_proc    compare);
tree_iter_t     tree_find_next_item(
    ttree_t*      tree,
    tree_iter_t item,
    const void * vp,
    fn_tree_compare_proc compare);

tui_ui32        tree_count_item(ttree_t* tree);
tui_ui32        tree_count_child(tree_iter_t item);
tui_ui32        tree_get_level(tree_iter_t item);
tui_i32         tree_set_item_data(tree_iter_t, const void*, tui_ui32);
tui_ui32        tree_get_item_data(tree_iter_t, void*, tui_ui32);
tree_iter_t     tree_get_parent(tree_iter_t);
tree_iter_t     tree_get_first_child(tree_iter_t);
tree_iter_t     tree_get_last_child(tree_iter_t);
tree_iter_t     tree_get_prev_item(tree_iter_t);
tree_iter_t     tree_get_next_item(tree_iter_t);
tui_i32         tree_populate(
    ttree_t*     tree,
    tree_iter_t item,
    void*       args,
    fn_tree_traverse_proc   traverse,
    int         how_to_walk); /* < 0 := PRE-ORDER,
                                 = 0 := IN-ORDER,
                                 > 0 := POST-ORDER
                              */
tree_iter_t     tree_get_root_item(ttree_t*);
tui_i32         tree_get_param(ttree_t*);
node_t          tree_get_item_pointer(tree_iter_t);

/*---------------------------------------------------------*/

ttree_t*
Tree_Create(tui_i32 lparam)
{
    tree_impl_t* tree = (tree_impl_t*)malloc(sizeof(tree_impl_t));

    if (tree != 0)
    {
        tree->root  = _tree_iter_init(0, 0);
        if (!tree->root)
        {
          free(tree);
          return 0;
        }
        tree->items                 = 0;
        tree->lparam                = lparam;
        /* init methods */
        tree->vtab.InsertItem       = tree_insert_item;
        tree->vtab.DeleteItem       = tree_delete_item;
        tree->vtab.FindItem         = tree_find_item;
        tree->vtab.FindNextItem     = tree_find_next_item;
        tree->vtab.CountItem        = tree_count_item;
        tree->vtab.CountChild       = tree_count_child;
        tree->vtab.Populate         = tree_populate;
        tree->vtab.SetItemData      = tree_set_item_data;
        tree->vtab.GetItemData      = tree_get_item_data;
        tree->vtab.GetParent        = tree_get_parent;
        tree->vtab.GetFirstChild    = tree_get_first_child;
        tree->vtab.GetLastChild     = tree_get_last_child;
        tree->vtab.GetPrevItem      = tree_get_prev_item;
        tree->vtab.GetNextItem      = tree_get_next_item;
        tree->vtab.GetLevel         = tree_get_level;
        tree->vtab.GetRootItem      = tree_get_root_item;
        tree->vtab.GetParam         = tree_get_param;
        tree->vtab.GetItemPointer   = tree_get_item_pointer;
    }
    return (ttree_t*)tree;
}

void
Tree_Destroy(ttree_t* tree)
{
    if (tree)
    {
        tree->DeleteItem(tree, ((tree_impl_t*)tree)->root);
        free(tree);
    }
}

tree_iter_t
tree_insert_item(
    ttree_t*         tree,
    tree_iter_t     parent,
    const void *    data,
    tui_ui32   size)
{
    tree_iter_t item = _tree_iter_init(data, size);

    /* cannot allocate memory */
    if (0 == item)
    {
        return item;
    }
    /* insert item at root */
    if (0 == parent)
    {
        parent = ((tree_impl_t*)tree)->root;
    }
    /* attach the new item to the tree */
    if (!parent->first_child)
    {
        /* it's the first child of the parent */
        parent->first_child = item;
    }
    else
    {
        /* attach to the last child */
        item->prev_sibling = parent->last_child;
        parent->last_child->next_sibling = item;
    }
    parent->last_child = item;
    item->parent = parent;
    /* set level */
    item->level = (1 + parent->level);
    /* increase children count */
    parent->children += 1;
    ((tree_impl_t*)tree)->items += 1;

    return item;
}

void
tree_delete_item(
    ttree_t*          tree,
    tree_iter_t     item)
{
    tree_iter_t parent  = 0;
    tree_iter_t next    = 0;
    tree_iter_t prev    = 0;

    if (0 == item)
    {
        return;
    }

    /* save the current information of its links */
    parent  = item->parent;
    next    = item->next_sibling;
    prev    = item->prev_sibling;

    if (parent && parent->first_child == item)
    {
        /* delete at the first child */
        parent->first_child = parent->first_child->next_sibling;
        if (parent->first_child)
        {
            parent->first_child->prev_sibling = 0;
        }
    }
    else if (parent && parent->last_child == item)
    {
        /* delete at the last child */
        parent->last_child = parent->last_child->prev_sibling;
        if (parent->last_child)
        {
            parent->last_child->next_sibling = 0;
        }
    }
    else
    {
        /* otherwise, delete any position of its child parent */
        if (next)
        {
            next->prev_sibling = prev;
        }
        if (prev)
        {
            prev->next_sibling = next;
        }
    }
    /* prompt to delete the item */
    _tree_iter_delete_item(item);
    /* decrease children count */
    --parent->children;
    ((tree_impl_t*)tree)->items -= 1;
}

tui_ui32
tree_count_item(ttree_t* tree)
{
    return ((tree_impl_t*)tree)->items;
}

tui_ui32
tree_count_child(tree_iter_t item)
{
    return item->children;
}

tree_iter_t
tree_find_item(
    ttree_t*                  tree,
    const void *            data,
    fn_tree_compare_proc    compare)
{
    tree_iter_t item = 0;
    if (data != 0 && compare != 0)
    {
        item = tree_find_next_item(
                    tree,
                    ((tree_impl_t*)tree)->root->first_child,
                    data,
                    compare);
    }
    return item;
}

tree_iter_t
tree_find_next_item(
    ttree_t*                 tree,
    tree_iter_t             item,
    const void *            data,
    fn_tree_compare_proc    compare)
{
    tui_i32 rc = -1;
    tree_iter_t  found = 0;

    if (data != 0 && compare != 0)
    {
        rc = compare(data, (const void*)item->node);
        if (0 == rc)
        {
            return item;
        }
        found = tree_find_next_item(
                    tree,
                    item->first_child,
                    data,
                    compare);
        if (0 == found)
        {
            found = tree_find_next_item(
                        tree,
                        item->next_sibling,
                        data,
                        compare);
        }
    }
    return found;
}

tui_i32
tree_populate(
    ttree_t*      tree,
    tree_iter_t item,
    void* args,
    fn_tree_traverse_proc   traverse,
    int         how_to_walk)
{
  tui_i32 rc = 0;
  if (how_to_walk < 0)
  {
    rc = _tree_populate_pre_order(tree, item, args, traverse);
  }
  else if (how_to_walk > 0)
  {
    rc = _tree_populate_in_order(tree, item, args, traverse);
  }
  else
  {
    rc = _tree_populate_post_order(tree, item, args, traverse);
  }
  return rc;
}

tui_i32
_tree_populate_pre_order(
    ttree_t*      tree,
    tree_iter_t item,
    void* args,
    fn_tree_traverse_proc   traverse)
{
    tui_i32 rc = 0;
    if (traverse != 0 && item != 0)
    {
        rc = traverse(args, item, item->node, item->node_size);
        if (0 == rc)
        {
            rc = _tree_populate_pre_order(
                    tree,
                    item->first_child,
                    args,
                    traverse);
            if (0 == rc)
            {
                rc = _tree_populate_pre_order(
                        tree,
                        item->next_sibling,
                        args,
                        traverse);
            }
        }
    }
    return rc;
}

tui_i32
_tree_populate_in_order(
    ttree_t*      tree,
    tree_iter_t item,
    void* args,
    fn_tree_traverse_proc   traverse)
{
    tui_i32 rc = 0;
    if (traverse != 0 && item != 0)
    {
        rc = _tree_populate_in_order(
                tree,
                item->first_child,
                args,
                traverse);
        if (0 == rc)
        {
            rc = traverse(args, item, item->node, item->node_size);

            if (0 == rc)
            {
                rc = _tree_populate_in_order(
                        tree,
                        item->next_sibling,
                        args,
                        traverse);
            }
        }
    }
    return rc;
}

tui_i32
_tree_populate_post_order(
    ttree_t*      tree,
    tree_iter_t item,
    void* args,
    fn_tree_traverse_proc   traverse)
{
    tui_i32 rc = 0;
    if (traverse != 0 && item != 0)
    {
        rc = _tree_populate_post_order(
                tree,
                item->first_child,
                args,
                traverse);
        if (0 == rc)
        {
            rc = _tree_populate_post_order(
                    tree,
                    item->next_sibling,
                    args,
                    traverse);
            if (0 == rc)
            {
                rc = traverse(args, item, item->node, item->node_size);
            }
        }
    }
    return rc;
}

tui_ui32
tree_get_level(
    tree_iter_t item)
{
  return item->level;
}

tui_i32
tree_set_item_data(
  tree_iter_t iter,
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
tree_get_item_data(
  tree_iter_t iter,
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

tree_iter_t
tree_get_parent(tree_iter_t iter)
{
  return (iter ? iter->parent : 0);
}

tree_iter_t
tree_get_first_child(tree_iter_t iter)
{
  return (iter ? iter->first_child : 0);
}

tree_iter_t
tree_get_last_child(tree_iter_t iter)
{
  return (iter ? iter->last_child : 0);
}

tree_iter_t
tree_get_prev_item(tree_iter_t iter)
{
  return (iter ? iter->prev_sibling : 0);
}

tree_iter_t
tree_get_next_item(tree_iter_t iter)
{
  return (iter ? iter->next_sibling : 0);
}

tree_iter_t
tree_get_root_item(ttree_t* tree)
{
  return (((tree_impl_t*)tree)->root);
}

tui_i32
tree_get_param(ttree_t* tree)
{
  return (((tree_impl_t*)tree)->lparam);
}

node_t
tree_get_item_pointer(tree_iter_t iter)
{
  return (iter ? iter->node : 0);
}

#ifdef __cplusplus
}
#endif

