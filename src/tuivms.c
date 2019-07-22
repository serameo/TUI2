/*-------------------------------------------------------------------
 * File name: tuivms.c
 * Author: Seree Rakwong
 * Date: 19-JUN-19
 *-----------------------------------------------------------------*/
#ifdef __VMS__
#include "tuivms.h"

#ifdef __cplusplus
extern "C" {
#endif


int
vms_getint(unsigned long* kbid)
{
  unsigned short key;                        /* key var */

  smg$read_keystroke(kbid, &key);
  return(key);
}

int
vms_getch(unsigned long* kbid)
{
  int c;

  do
  {
    c = vms_getint(kbid);
  } while (c == SS$_NORMAL);

  return c;
}

unsigned long vms_writeio(unsigned long wchannel, iosb_t* iosb, char* text, unsigned long len)
{
  return (TUI_INT)sys$qiow(0,
                           wchannel,
                           (IO$_WRITEVBLK | IO$M_NOFORMAT),
                           iosb,
                           0, 0,
                           text, len,
                           0, 0, 0, 0);
}

long vms_get_sysio(unsigned long*  iochan, char* sysio)
{
    long status = SS$_NORMAL;
    
    struct dsc$descriptor_s sys_input;
    memset(&sys_input, 0, sizeof(sys_input));
    sys_input.dsc$a_pointer = sysio;
    sys_input.dsc$w_length  = strlen(sysio);
    
    status = sys$assign(&sys_input, iochan, 0, 0);
    return status;
}


#ifdef __cplusplus
}
#endif

#endif /* __VMS__ */

