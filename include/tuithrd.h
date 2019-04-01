/*
 * File name: tuithrd.h
 * Author: Seree Rakwong
 * Date: 27-MAR-2019
 *
 * NOTE:
 */
#ifndef __TUI_THREAD_H__
#define __TUI_THREAD_H__

#include "tuitypes.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _TUITIMERSTRUCT;
typedef struct _TUITIMERSTRUCT        ttimer_t;

ttimer_t*   Timer_Create(TUI_LPARAM);
TUI_VOID    Timer_Destroy(ttimer_t*);

typedef TUI_INT (*fn_timer_set_timer)(ttimer_t*,  TWND, TUI_UINT32, TUI_UINT32, TUI_BOOL, TUI_TIMERPROC, TUI_VOID*);
typedef TUI_INT (*fn_timer_kill_timer)(ttimer_t*, TWND, TUI_UINT32);
typedef TUI_INT (*fn_timer_suspend)(ttimer_t*,    TWND, TUI_UINT32);
typedef TUI_INT (*fn_timer_resume)(ttimer_t*,     TWND, TUI_UINT32);

/*
TUI_INT 
timer_set_timer(
  ttimer_t*     timer,
  TWND          wnd,
  TUI_UINT32    id,
  TUI_UINT32    timelapse,
  TUI_BOOL      paused,
  TTIMERPROC    notifyfn,
  TUI_VOID*     args);

TUI_INT
timer_kill_timer(
  ttimer_t*      timer,
  TWND          wnd,
  TUI_UINT32    id);
  
TUI_INT
timer_suspend(
  ttimer_t*     timer,
  TWND          wnd,
  TUI_UINT32    id);
  
TUI_INT
timer_resume(
  ttimer_t*     timer,
  TWND          wnd,
  TUI_UINT32    id);
*/


struct _TUITIMERSTRUCT
{
    fn_timer_set_timer            SetTimer;
    fn_timer_kill_timer           KillTimer;
    fn_timer_suspend              Suspend;
    fn_timer_resume               Resume;
};

#ifdef __cplusplus
}
#endif

#endif /* __TUI_THREAD_H__ */
