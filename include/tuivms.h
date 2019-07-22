/*-------------------------------------------------------------------
 * File name: tuivms.h
 * Author: Seree Rakwong
 * Date: 19-JUN-19
 *-----------------------------------------------------------------*/
#ifndef __TUIVMS_H__
#define __TUIVMS_H__

#include <stdlib.h>
#include <stdio.h>

#include "tuidefs.h"
#include "tuitypes.h"

#ifdef __VMS__
#include <ssdef.h>
#include <starlet.h>
#include <stddef.h>
#include <iodef.h>
#include <descrip.h>
#include <stsdef.h>
#include <lib$routines.h>
#include <smgdef.h>
#include <smg$routines.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VMS_ROWS                25
#define VMS_COLUMNS             80

long vms_get_sysio(unsigned long*  iochan, char* sysio);
int vms_getint (unsigned long* kbid);
int vms_getch  (unsigned long* kbid);
unsigned long vms_writeio(unsigned long  wchannel, iosb_t* iosb, char* text, unsigned long len);

#ifdef __cplusplus
}
#endif

#endif /* __VMS__ */

#endif /* __TUIVMS_H__ */

