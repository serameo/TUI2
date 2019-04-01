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
typedef struct _QUEUE_STRUCT tqueue_t;

/* constructor and destructor functions */
tqueue_t*  Queue_Create(tui_i32 lparam);
void      Queue_Destroy(tqueue_t*);

/*
 * FIFO
 */
typedef tui_i32     (*fn_queue_enqueue)(tqueue_t*, const void*, tui_ui32);
typedef void        (*fn_queue_dequeue)(tqueue_t*);
typedef tui_ui32    (*fn_queue_first)(tqueue_t*, void*, tui_ui32);
typedef node_t      (*fn_queue_first_pointer)(tqueue_t*);
typedef tui_i32     (*fn_queue_is_empty)(tqueue_t*);
typedef tui_i32     (*fn_queue_count)(tqueue_t*);

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

