#ifndef __TUI_XCNF_H__
#define __TUI_XCNF_H__
/*
 * File Name: tui_xcnf.h
 * Author: Seree Rakwong
 * Date: 29-MAR-19
 */
#include "tuitypes.h"
#include "tui_rbtree.h"

struct _TUIXCONFIGSTRUCT;
typedef struct _TUIXCONFIGSTRUCT xcnf_t;

enum xcnf_constants
{
  /* parsing constants */
  XCNF_MAX_CHAR_PER_LINE    = 256,
  XCNF_KEY_VALUE_SEP        = '=',
  XCNF_LINE_COMMENT         = '#',
  XCNF_SKIP_PARSING         = 1,
  XCNF_NOT_IMPLEMENTED      = -2,

  /* error codes */
  XCNF_INSUFFICIENT_MEM     = -100,
  XCNF_OPEN_FILE_FAILED     = -101,
  XCNF_ERROR                = -1,
  XCNF_OK                   = 0
};

/*
 * init xcnf_t
 */
xcnf_t*
XConfig_Init(tui_i32);

/*
 * release 
 */
tui_void
XConfig_Release(
  xcnf_t* xcnf
);

/*
 * load a configuration from file
 */
typedef tui_i32 (*fn_xcnf_Load)(
  xcnf_t*     xcnf,
  FILE*       fp
);

/*
 * save the configuration to file
 */
typedef tui_i32 (*fn_xcnf_Save)(
  xcnf_t*     xcnf,
  FILE*       fp
);

/*
 * xcnf_get_int() return the tui_integer of value
 */
typedef tui_i32 (*fn_xcnf_GetInt)(
  xcnf_t*     xcnf,
  tui_char*   key,    /* key to get value                       */
  tui_long    def     /* default value if there is no key       */
);

/*
 * xcnf_get_float() return the tui_double of value
 */
typedef tui_double (*fn_xcnf_GetFloat)(
  xcnf_t*     xcnf,
  tui_char*   key,    /* key to get value                       */
  tui_double  def     /* default value if there is no key       */
);

/*
 * xcnf_get_string() return the length of value
 */
typedef tui_i32 (*fn_xcnf_GetString)(
  xcnf_t*     xcnf,
  tui_char*   key,    /* key to get value                       */
  tui_char*   def,    /* default value if there is no key       */
  tui_char*   value,  /* output will be copied                  */
  tui_int     len     /* if len = -1, this function will return */
                  /* the length of value                    */
);

struct _TUIXCONFIGSTRUCT
{
    fn_xcnf_Load               Load;
    fn_xcnf_Save               Save;
    fn_xcnf_GetInt             GetInt;
    fn_xcnf_GetFloat           GetFloat;
    fn_xcnf_GetString          GetString;
};

#endif /* __TUI_XCNF_H__ */

