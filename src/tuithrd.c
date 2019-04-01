/*
 * File name: tuithrd.c
 * Author: Seree Rakwong
 * Date: 27-MAR-2019
 *
 * NOTE:
 */
#define _POSIX_C_SOURCE 199309L /* enable nanosleep() */

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include "tui.h"
#include "tuithrd.h"
#include "tui_list.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MILLI_SECS        1.0e6

struct _TIMER_IMPL_STRUCT
{
  struct _TUITIMERSTRUCT vtab;
  tlist_t*       timers;
  TUI_LPARAM    lparam;
};
typedef struct _TIMER_IMPL_STRUCT timer_impl_t;

struct _TIMER_ATTR_STRUCT
{
  TWND              wnd;
  TUI_UINT32        id;
  TUI_UINT32        timelapse;
  TUI_TIMERPROC     timerproc;
  TUI_VOID*         arg;
  pthread_t         thrid;
  pthread_mutex_t   state_locked;
  TUI_BOOL          paused;
  TUI_BOOL          exit;
  ttimer_t*         timer;
  list_iter_t       item;
};
typedef struct _TIMER_ATTR_STRUCT timer_attr_t;


/*------------------------------*/

TUI_INT 
timer_set_timer(
  ttimer_t*     timer,
  TWND          wnd,
  TUI_UINT32    id,
  TUI_UINT32    timelapse,
  TUI_BOOL      paused,
  TUI_TIMERPROC notifyfn,
  TUI_VOID*     args);

TUI_INT
timer_kill_timer(
  ttimer_t*     timer,
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
/*------------------------------*/

list_iter_t
_Timer_FindEvent(
  timer_impl_t* timer,
  TWND          wnd,
  TUI_UINT32    id
);
static
TUI_VOID*
_Timer_TimerProc(TUI_VOID* arg);

TUI_INT
_Timer_SetEvent(
  ttimer_t*     timer,
  TWND          wnd,
  TUI_UINT32    id,
  TUI_BOOL      paused,
  TUI_BOOL      exit);




static
TUI_VOID*
_Timer_TimerProc(TUI_VOID* arg)
{
  timer_attr_t* attr = (timer_attr_t*)arg;
  timer_impl_t* impl = (timer_impl_t*)attr->timer;
  struct timespec req;
  struct timespec rem;
  tui_ui32 sec  = 0;
  tui_ui32 nsec = 0;
  TWND frame = 0;
  
  /* infinite */
  while (TUI_FALSE == attr->exit)
  {
    /* sleep in nano secs */
    sec  = attr->timelapse/1000;
    nsec = (attr->timelapse > sec*1000 ? 
              (attr->timelapse - sec*1000)/1000000 : 0);
    req.tv_sec  = sec;
    req.tv_nsec = nsec;
    memset(&rem, 0, sizeof(rem));
    nanosleep(&req, &rem);

    if (TUI_FALSE == attr->paused)
    {
      frame = TuiGetWndFrame(TuiGetActiveWnd());
      if (frame == attr->wnd)
      {
        if (attr->timerproc)
        {
            attr->timerproc(attr->wnd, attr->id, attr->arg);
        }
        else
        {
            TuiPostMsg(attr->wnd, TWM_TIMER, (TWPARAM)attr->id, (TLPARAM)attr->arg);
        }
      }
      else if (TuiGetDummyWnd() == attr->wnd)
      {
        if (attr->timerproc)
        {
            attr->timerproc(attr->wnd, attr->id, attr->arg);
        }
      }
    }
  }
  pthread_mutex_destroy(&attr->state_locked);
  impl->timers->RemoveAt(impl->timers, attr->item);
  return 0;
}

list_iter_t
_Timer_FindEvent(
  timer_impl_t* impl,
  TWND          wnd,
  TUI_UINT32    id
)
{
  timer_attr_t* attr = 0;
  list_iter_t iter = impl->timers->Begin(impl->timers);
  list_iter_t end  = impl->timers->End(impl->timers);
  while (iter != end)
  {
    attr = (timer_attr_t*)impl->timers->GetItemPointer(iter);
    if (attr->wnd == wnd && attr->id == id)
    {
      return iter;
    }
    iter = impl->timers->GetNext(iter);
  }
  return 0;
}

TUI_INT
_Timer_SetEvent(
  ttimer_t*     timer,
  TWND          wnd,
  TUI_UINT32    id,
  TUI_BOOL      paused,
  TUI_BOOL      exit)
{
  timer_impl_t* impl = (timer_impl_t*)timer;
  list_iter_t iter = _Timer_FindEvent(impl, wnd, id);
  timer_attr_t* attr = 0;
  if (0 == iter)
  {
    return TUI_ERROR;
  }
  
  attr = (timer_attr_t*)impl->timers->GetItemPointer(iter);
  attr->exit   = exit;
  attr->paused = paused;
  
  return TUI_OK;
}

/*------------------------------*/
ttimer_t*
Timer_Create(TUI_LPARAM lparam)
{
    timer_impl_t* timer = (timer_impl_t*)malloc(sizeof(timer_impl_t));
    
    if (timer != 0)
    {
        timer->lparam           = lparam;
        timer->timers           = List_Create(lparam);
        /* init methods */
        timer->vtab.SetTimer    = timer_set_timer;
        timer->vtab.KillTimer   = timer_kill_timer;
        timer->vtab.Suspend     = timer_suspend;
        timer->vtab.Resume      = timer_resume;
    }
    return (ttimer_t*)timer;
}

TUI_VOID
Timer_Destroy(ttimer_t* timer)
{
    timer_attr_t* attr = 0;
    list_iter_t iter = 0;
    list_iter_t end = 0;
    timer_impl_t* impl = 0;

    if (timer)
    {
        impl = (timer_impl_t*)timer;
        iter = impl->timers->Begin(impl->timers);
        end  = impl->timers->End(impl->timers);
        while (iter != end)
        {
          attr = (timer_attr_t*)impl->timers->GetItemPointer(iter);
          timer_kill_timer(timer, attr->wnd, attr->id);
          iter = impl->timers->GetNext(iter);
        }
        
        List_Destroy(impl->timers);
        free(timer);
    }
}


TUI_INT 
timer_set_timer(
  ttimer_t*     timer,
  TWND          wnd,
  TUI_UINT32    id,
  TUI_UINT32    timelapse,
  TUI_BOOL      paused,
  TUI_TIMERPROC    proc,
  TUI_VOID*     arg)
{
  pthread_attr_t thrdattr;
  TUI_INT rc;
  timer_attr_t  attr;
  node_t node = 0;
  list_iter_t item = 0;
  timer_impl_t* impl = (timer_impl_t*)timer;

  memset(&attr, 0, sizeof(attr));
  attr.wnd        = wnd;
  attr.id         = id;
  attr.timelapse  = timelapse;
  attr.timerproc  = proc;
  attr.arg        = arg;
  attr.timer      = timer;
  attr.paused     = paused;
  attr.exit       = TUI_FALSE;

  rc = pthread_mutex_init(&attr.state_locked, 0);
  if (rc != 0)
  {
    return TUI_ERROR;
  }
  rc = pthread_attr_init(&thrdattr);
  if (rc != 0)
  {
    return TUI_ERROR;
  }

  /* keep the attribute into the list */
  item = impl->timers->InsertLast(impl->timers, &attr, sizeof(attr));
  attr.item = item;
  
  if (0 == item)
  {
    return TUI_MEM;
  }
  
  node = impl->timers->GetItemPointer(item);
  rc = pthread_create(&attr.thrid, &thrdattr, _Timer_TimerProc, node);
  pthread_attr_destroy(&thrdattr);

  if (rc != 0)
  {
    impl->timers->RemoveLast(impl->timers);
    return TUI_ERROR;
  }
  
  return TUI_OK;
}

TUI_INT
timer_kill_timer(
  ttimer_t*     timer,
  TWND          wnd,
  TUI_UINT32    id)
{

  return _Timer_SetEvent(
            timer,
            wnd,
            id,
            TUI_TRUE,  /* paused */
            TUI_TRUE); /* exit   */
}

TUI_INT
timer_suspend(
  ttimer_t*     timer,
  TWND          wnd,
  TUI_UINT32    id)
{

  return _Timer_SetEvent(
            timer,
            wnd,
            id,
            TUI_TRUE,   /* paused */
            TUI_FALSE); /* exit   */
}

TUI_INT
timer_resume(
  ttimer_t*     timer,
  TWND          wnd,
  TUI_UINT32    id)
{

  return _Timer_SetEvent(
            timer,
            wnd,
            id,
            TUI_FALSE,  /* paused */
            TUI_FALSE); /* exit   */
}


#ifdef __cplusplus
}
#endif
