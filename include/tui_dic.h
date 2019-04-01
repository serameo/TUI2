#ifndef __TUI_DIC_H__
#define __TUI_DIC_H__
/*
 * File Name: tui_dic.h
 * Author: Seree Rakwong
 * Date: 29-MAR-19
 */
#include <stdio.h>
#include <stdlib.h>
#include "tuitypes.h"
#include "tui_rbtree.h"

/*bos_cust.dic*/
/*
000090464007                   <000090 = first 6 bytes are number of fields, 464 = next 3 bytes are total bytes per record, 007 = the last 3 bytes are number of header fields>
lEndOld             000004L    <lEndOld = first header field named 'lEndOld', 000 = first 3 bytes are offset, next 3 bytes are size of field, 'L' the last byte tells what the type of field>
lNxtRec             004004L    
lOldUsed            008004L    
lLastAFCOrdNo       012004L    
cLastAFCOrdFlag     016001B    
lLastDBOrdNo        020004L    
cLastDBOrdFlag      024001B    <cLastDBOrdFlag = last header field>
lTradUserRec        000004L    <lTradUserRec = first record field>
lPosiF              004004L    
lPosiB              008004L    
lAuditF             012004L    
lCommSVTRec         016004L    
dWithdrawable       024008D    
lBeginHighLmt       032004L    
lSubAccNxtLnk       036004L    
lMasterAccLnk       040004L    
lOrderF             044004L    
lOrderB             048004L    
lUserFwd            052004L    
lLstChgPwdDate      056004L    
cAccTyp             060001C    
cPC                 061001C    
cCrdTyp             062001C    
cStatus             063001C    
cVip                064001C    
cSId                065001B    
cMarginRate         066001B    
cCnfrm              067001C    
sTradUserNo         068004C    
sCustId             072016C    
cPctHoldingTax      088001C    
cAutoApprove        089001C    
cLevelFilterMsg     090001C    
bFlag1              091001B    
cDefaultTrustId     092001C    
sFill               093005C    
sName               098050C    
sThai               148050C    
lUnpaid             200004L    
cMutalFlag          204001C    
cCustFlag           205001C    
cNotOverAndShort    206001C    
cChange             207001C    
bFlag               208001B    
sGrade              209012C    
cCurLogin           221001B    
cLimitLogin         222001B    
cPassThrou          223001C    
cOrdChkPwd          224001C    
lMaxOrdVol          228004L    
lMaxOrdVal          232004L    
lLLogUserRec        236004L    
cGroup              240001C    
cCashFlag           241001C    
cChequeFlag         242001C    
lCommType           244004L    
dBuyLmt             248008D    
dSelLmt             256008D    
dHighLmt            264008D    
dOrgSelLmt          272008D    
lComm               280004L    
dBuyValue           288008D    
dSellValue          296008D    
dOrgBuyLmt          304008D    
dAllBuyValue        312008D    
sPass               320016X    
dPrevEE             336008D    
sMasterAcc          344016C    
cVcustMinCommPerOrde360001C    
cLoginFailCount     361001B    
sCashAmount         362020C    
cServiceType        382001C    
sPinCode            383016X    
cPinFailCount       399001B    
cOrdAmendOpt        400001C    
bFlag3              401001B    
sClearingMember     402004C    
cDGWGroup           406001C    
bTriggerFlag        407001L    
fCustBuyCommG       408004F    
fCustSellCommG      412004F    
sCustGrpId          416013C    
lFrstCustInGrpLnk   432004L    
lCustInGrpFwdLnk    436004L    
bFlag4              440001B    
lSecCustF           444004L    
lSecCustL           448004L    
cNumGoodtillOrd     452001B    
cNumAdvOrd          453001B    
sFill2              454010C    <sFill2 = last record field>
*/
enum
{
  HEADER_FIELD = 0,
  RECORD_FIELD = 1
};

#define TUI_MAX_DICT_NAME    20

struct _BOS_DICTIONARY
{
  tui_i32   id;
  tui_char  name[TUI_MAX_DICT_NAME+1];
  tui_i32   offset;
  tui_i32   size;
  tui_char  type;
  tui_i32   fldtype;
};
typedef struct _BOS_DICTIONARY BOS_DICTIONARY;

struct _TUIDICTIONARYSTRUCT;
typedef struct _TUIDICTIONARYSTRUCT tdic_t;

struct _dict_field_t
{
  BOS_DICTIONARY        fld_prop;
  struct _dict_field_t* next;
};
typedef struct _dict_field_t dictlist_t;

struct _std_tdic_t
{
  tui_i32         nflds;         /* number of fields   */
  tui_i32         rec_bytes;     /* record bytes       */
  tui_i32         nhdrs;         /* number of headers  */
  tdic_t*         dict;
  tui_char*       dict_file;     /* dictionary file    */
  dictlist_t*     fld_first;
  dictlist_t*     fld_last;
};
typedef struct _std_tdic_t std_tdic_t;

struct _bos_tdic_t
{
  struct _std_tdic_t  dicheader;
  tui_void*           gblp;          /* global pointer     */
  tui_char*           gbl_name;      /* global name        */
  size_t              gbl_bytes;     /* global total bytes */
  size_t              gbl_recs;      /* global total records */
};
typedef struct _bos_tdic_t bos_tdic_t;

enum
{
  DICT_BYTE    = 'B',
  DICT_CHAR    = 'C',
  DICT_INT     = 'I',
  DICT_LONG    = 'L',
  DICT_FLOAT   = 'F',
  DICT_DOUBLE  = 'D',
  DICT_HEX     = 'X'
};

#define OFFSET_FIELD        0
#define OFFSET_OFFSET       20
#define OFFSET_SIZE         23
#define OFFSET_TYPE         26

#define BYTES_FIELD         20
#define BYTES_OFFSET        3
#define BYTES_SIZE          3
#define BYTES_TYPE          1

enum _dict_constants
{
  /* parsing constants */
  DICT_MAX_CHAR_PER_LINE    = 256,
  DICT_LINE_COMMENT         = '#',
  DICT_SKIP_PARSING         = 1,
  DICT_NOT_IMPLEMENTED      = -2,

  /* error codes */
  DICT_INSUFFICIENT_MEM     = -100,
  DICT_OPEN_FILE_FAILED     = -101,
  DICT_ERROR                = -1,
  DICT_OK                   = 0
};


tdic_t*  Dictionary_Create(tui_i32);
tui_void Dictionary_Release(tdic_t*);

typedef tui_void    (*fn_dict_handler)(std_tdic_t*, BOS_DICTIONARY*);

typedef tui_i32     (*fn_dict_load_from_file)(tdic_t*, FILE*, fn_dict_handler);
typedef tui_char    (*fn_dict_get_char)(tdic_t*, tui_char*, tui_char*, tui_char);
typedef tui_i32     (*fn_dict_get_int)(tdic_t*, tui_char*, tui_char*, tui_i32);
typedef tui_float   (*fn_dict_get_float)(tdic_t*, tui_char*, tui_char*, tui_float);
typedef tui_double  (*fn_dict_get_double)(tdic_t*, tui_char*, tui_char*, tui_double);
typedef tui_i32     (*fn_dict_get_string)(tdic_t*, tui_char*, tui_char*, tui_char*, tui_char*, tui_i32);
typedef tui_i32     (*fn_dict_get_binary)(tdic_t*, tui_char*, tui_char*, tui_byte*, tui_byte*, tui_i32);
typedef tui_i32     (*fn_dict_get_value)(tdic_t*, tui_char*, BOS_DICTIONARY*);

struct _TUIDICTIONARYSTRUCT
{
  fn_dict_load_from_file          LoadFromFile;
  /*fn_dict_load_from_file_param    LoadFromFileWithParam;*/
  fn_dict_get_char                GetChar;
  fn_dict_get_int                 GetInt;
  fn_dict_get_float               GetFloat;
  fn_dict_get_double              GetDouble;
  fn_dict_get_string              GetString;
  fn_dict_get_binary              GetBinary;
  fn_dict_get_value               GetValue;
};


#endif /* __TUI_DIC_H__ */

