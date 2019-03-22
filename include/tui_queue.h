/*
 * File name: tui_queue.h
 * Author: Seree Rakwong
 * Date: 11-MAR-2019
 *
 */

#ifndef _TUI_QUEUE_H_
#define _TUI_QUEUE_H_

#include "tui_node.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _QUEUE_STRUCT;
typedef struct _QUEUE_STRUCT queue_t;

/* constructor and destructor functions */
queue_t*  Queue_Create(tui_i32 lparam);
void      Queue_Destroy(queue_t*);

/*
 * FIFO
 */
typedef tui_i32     (*fn_queue_enqueue)(queue_t*, const void*, tui_ui32);
typedef void        (*fn_queue_dequeue)(queue_t*);
typedef tui_ui32    (*fn_queue_first)(queue_t*, void*, tui_ui32);
typedef node_t      (*fn_queue_first_pointer)(queue_t*);
typedef tui_i32     (*fn_queue_is_empty)(queue_t*);
typedef tui_i32     (*fn_queue_count)(queue_t*);

struct _QUEUE_STRUCT
{
    /* methods */
    fn_queue_enqueue        Enqueue;
    fn_queue_dequeue        Dequeue;
    fn_queue_first          First;
    fn_queue_is_empty       IsEmpty;
    fn_queue_first_pointer  FirstPointer;
    fn_queue_count          Count;
};


#ifdef __cplusplus
}
#endif

#endif /* _TUI_QUEUE_H_ */

