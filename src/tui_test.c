/*-------------------------------------------------------------------
 * File name: tui_test.c
 * Author: Seree Rakwong
 * Date: 28-SEP-18
 *-----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined __USE_CURSES__
#include <curses.h>
#elif defined __USE_WIN32__
#include <windows.h>
#endif
#include "tui.h"

#define IDC_STATUSBAR    199
#define IDC_NAME         200
#define IDC_TLISTBOX1    204
#define IDC_PASSWORD     205
#define IDC_OK           206
#define IDC_CANCEL       207
#define IDC_TLISTBOX2    208
#define IDC_TLISTBOX3    209
#define IDC_CLOSE        210
#define IDC_SAVE         211
#define IDC_OPENDLG2     212
#define IDC_OPENDLG3     213
#define IDC_MSG          214
#define IDC_PRICE        215
#define IDC_EDITCELL     216
#define IDC_OPENDLG4     217
#define IDC_TREECTRL1    218
#define IDC_PRINT        219

FRMWNDTEMPL dlg3a[] =
{
  /* 1st object is always dialog */
  /*{ "mylistctlproc", "Dialog3", 2,  0,  0, 25, 80, TWS_WINDOW, 0 },*/
  /* 2nd and others are controls */
  { TLISTCTRL, "",    IDC_TLISTBOX1,  1,  1,  16,  79, 
    TWS_CHILD|TWS_VISIBLE|
      TLCS_EDITABLE|TLCS_LINEEDIT/*|TLCS_NOSELECTION|TLCS_NOHEADER*/, 0, 0, "List" },
  { TBUTTON, "Edit",    IDC_EDITCELL,  20,  1,  1,  14, TWS_CHILD|TWS_VISIBLE, 0, 0, "Edit" },
  { TBUTTON, "Message",    IDC_MSG,  20,  20,  1,  15, TWS_CHILD|TWS_VISIBLE, 0, 0, "Message" },
  { TBUTTON, "Close",    IDC_CLOSE,  20,  40,  1,  15, TWS_CHILD|TWS_VISIBLE, 0, 0, "Close" },
  /* the last is the end-of-controls */
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

WNDTEMPL dlg3[] =
{
  /* 1st object is always dialog */
  { "mytreectlproc", "Dialog3", 2,  0,  0, 25, 80, TWS_WINDOW, 0 },
  /* 2nd and others are controls */
  { TTREECTRL, "",    IDC_TREECTRL1,  0,  0,  16,  40, 
    TWS_CHILD|TWS_VISIBLE|TTCS_SHOWNODE|TTCS_FULLSECROW/*|TTCS_NOHIGHLIGHT*/, 0 },
  { TBUTTON, "Print",    IDC_PRINT,  20,  20,  1,  15, TWS_CHILD|TWS_VISIBLE, 0 },
  { TBUTTON, "Close",    IDC_CLOSE,  20,  40,  1,  15, TWS_CHILD|TWS_VISIBLE, 0 },
  /* the last is the end-of-controls */
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};


FRMWNDTEMPL dlg4a[] =
{
  /* 1st object is always dialog */
  /*{ "mylistpagectlproc", "Dialog4", 2,  0,  0, 25, 80, TWS_WINDOW, 0 },*/
  /* 2nd and others are controls */
  { TLISTPAGECTRL, "",    IDC_TLISTBOX1,  1,  1,  11,  79, 
    TWS_CHILD|TWS_VISIBLE, 0, 0, "list page control" },
  { TBUTTON, "Close",    IDC_CLOSE,  20,  40,  1,  15, TWS_CHILD|TWS_VISIBLE, 0, 0, "Close" },
  { TSTATIC, "",    IDC_STATUSBAR,  24,  0,  1,  80, TWS_CHILD|TWS_VISIBLE, 0, 0, "" },
  /* the last is the end-of-controls */
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

FRMWNDTEMPL frame1[] =
{
  /* 1st object is always dialog */
/*
  { "mywndproc", "Dialog1", 1,  0,  0, 25, 80, TWS_WINDOW|TWS_BORDER, 0, 0, "frame" },
*/
  /* 2nd and others are controls */
  { TSTATIC, "Name:",    100,  1,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0, 0, "name" },
  { TEDITBOX,   "12345678901234567890",       IDC_NAME,  1, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_LEFT|TES_UPPERCASE|TES_AUTOHSCROLL, 0, 0, "Name" },
  { TSTATIC, "ID:",    101,  2,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0, 0, "" },
  { TEDITBOX,   "DT66234",     201,  2, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_CENTER|TES_AUTOHSCROLL, 0, 0, "ID" },
  { TSTATIC, "Tel:",    102,  3,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0, 0, "" },
  { TEDITBOX,   "1234",   202,  3, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_NUMBER|TES_RIGHT|TES_AUTOHSCROLL, 0, 0, "Telephone" },
  { TSTATIC, "Email:",    103,  4,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0, 0, "" },
  { TEDITBOX,   "abc@abc.com", 203,  4, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|TWS_DISABLED|
      TES_AUTOHSCROLL, 0, 0, "Email" },
  { TSTATIC, "Password:",    104,  5,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0, 0, "" },
  { TEDITBOX,   "welcome1!", IDC_PASSWORD,  5, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_LEFT|TES_PASSWORD|TES_AUTOHSCROLL, 0, 0, "Password" },
  { TSTATIC, "Price:",    105,  6,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0, 0, "" },
  { TEDITBOX,   "132,399M", IDC_PRICE,  6, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_RIGHT|TES_AUTODECIMALCOMMA|TES_AUTOHSCROLL|TES_AUTOSUFFIX, 0, 0, "Price" },
  { TLISTBOX,"",               IDC_TLISTBOX1,  8,  1,  5, 16, 
    TWS_CHILD|TWS_VISIBLE|TLBS_CENTER|TWS_BORDER, 0, 0, "List1" },
  { TLISTBOX,"",               IDC_TLISTBOX2,  8, 21,  5, 16, 
    TWS_CHILD|TWS_VISIBLE|TLBS_CHECKBOX|TWS_BORDER, 0, 0, "List 2 checkbox" },
  { TLISTBOX,"",               IDC_TLISTBOX3,  8, 41,  5, 16, 
    TWS_CHILD|TWS_VISIBLE|TLBS_RADIOBOX|TLBS_RIGHT|TWS_BORDER, 0, 0, "List 2 radio" },
  { TBUTTON, "Dlg2",    IDC_OPENDLG2,  14,  1,  1,   10, TWS_CHILD|TWS_VISIBLE, 0, 0, "dlg2" },
  { TBUTTON, "Dlg3",    IDC_OPENDLG3,  14,  11,  1,   10, TWS_CHILD|TWS_VISIBLE, 0, 0, "dlg3" },
  { TBUTTON, "Dlg4",    IDC_OPENDLG4,  14,  21,  1,   10, TWS_CHILD|TWS_VISIBLE, 0, 0, "dlg4" },
  { TBUTTON, "Close",    IDC_CLOSE,    14,  31,  1,  11, TWS_CHILD|TWS_VISIBLE, 0, 0, "Close" },
  { TSTATIC, "Esc to exit: ", IDC_STATUSBAR, 24,  1,  1, 79, TWS_CHILD|TWS_VISIBLE|TWS_DISABLED|TSS_LEFT, 0, 0, "" },
  /* the last is the end-of-controls */
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};

TVOID mywndproc_onselchanged(TWND wnd, TWND ctl)
{
  TWND statusbar = 0;
  TWND listbox = 0;
  TINT i = 0;
  TTCHAR buf[TUI_MAX_WNDTEXT+1];
  
  statusbar = TuiGetWndItem(wnd, IDC_STATUSBAR);
  listbox = ctl;
  i = TLB_GetCurSel(listbox);
  if (i >= 0)
  {
    TLB_GetItemText(listbox, i, buf);
    TuiSetWndText(statusbar, buf);
  }
}

TVOID mywndproc_onmsgboxcommand(TWND wnd, TUINT cmd, TUINT id)
{
  TWND statusbar = 0;
  TTCHAR buf[TUI_MAX_WNDTEXT+1];
  
  statusbar = TuiGetWndItem(wnd, IDC_STATUSBAR);
  sprintf(buf, "cmd = %d, id = %d", cmd, id);
  TuiSetWndText(statusbar, buf);
}
TVOID mywndproc_ondisplayinfo(TWND wnd, DISPLAYINFO* di)
{
  TWND statusbar = TuiGetWndItem(wnd, IDC_STATUSBAR);
  TuiSetWndText(statusbar, di->text);
}

TVOID OpenDlg3()
{
  TWND dlg = TuiCreateWndTempl(dlg3, 0);
  TuiShowWnd(dlg, 1);
}

TLONG mywndproc(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam)
{
  TTCHAR buf[TUI_MAX_WNDTEXT+1];
  TINT i;
  TWND statusbar = 0;
  TWND listbox = 0;
  TWND edit = 0;
  TNMHDR* nmhdr = 0;
  TLONG rc = TUI_CONTINUE;

  switch (msg)
  {
    case TWM_INITDIALOG:
    {
      rc = TuiDefFrameWndProc(wnd, msg, wparam, lparam);
      if (TUI_CONTINUE != rc)
      {
        return rc;
      }
      listbox = TuiGetWndItem(wnd, IDC_TLISTBOX1);
      for (i = 0; i < 20; ++i)
      {
        sprintf(buf, "Item %d", (i));
        TLB_AddItem(listbox, buf);
      }
      
      TLB_DeleteItem(listbox, 5);
      TLB_SetCurSel(listbox, 7);

      listbox = TuiGetWndItem(wnd, IDC_TLISTBOX2);
      for (i = 0; i < 10; ++i)
      {
        sprintf(buf, "Item %d", (i));
        TLB_AddItem(listbox, buf);
      }
      
      listbox = TuiGetWndItem(wnd, IDC_TLISTBOX3);
      for (i = 0; i < 10; ++i)
      {
        sprintf(buf, "Item %d", (i));
        TLB_AddItem(listbox, buf);
      }

      edit = TuiGetWndItem(wnd, IDC_PRICE);
      TuiSendMsg(edit, TEM_SETDECWIDTH, (TWPARAM)2, (TLPARAM)0);

      edit = TuiGetWndItem(wnd, IDC_NAME);
      TuiSendMsg(edit, TEM_LIMITTEXT, (TWPARAM)20, (TLPARAM)0);
      
      statusbar = TuiGetWndItem(wnd, IDC_STATUSBAR);/*
      TuiSendMsg(statusbar,
        TWM_SETTEXTATTRS, 
        (TWPARAM)TuiGetColor(BLACK_YELLOW),
        (TLPARAM)0);*/
     /* 
      edit = TuiGetWndItem(wnd, IDC_PASSWORD);
      TEDT_ShowPasswdChar(edit, TW_HIDE);*/
      TuiSetFocus(edit);
      return rc;
    }

    case TWM_NOTIFY:
    {
      nmhdr = (TNMHDR*)lparam;
      switch (nmhdr->code)
      {
        case TLBN_SELCHANGED:
        {
          mywndproc_onselchanged(wnd, nmhdr->ctl);
          break;
        }
        case (TWM_USER+1):
        {
          /*RESPONSEMSGBOX* res = (RESPONSEMSGBOX*)lparam;*/
          mywndproc_onmsgboxcommand(wnd, nmhdr->id, nmhdr->code);
          break;
        }
        case TCN_DISPLAYINFO:
        {
          DISPLAYINFO* di = (DISPLAYINFO*)nmhdr;
          mywndproc_ondisplayinfo(wnd, di);
          /*
          statusbar = TuiGetWndItem(wnd, IDC_STATUSBAR);
          TuiSetWndText(statusbar, di->text);
          */
          break;
        }
      }
      
      break;
    }
    /*
    case TWM_MBXCOMMAND:
    {
      RESPONSEMSGBOX* res = (RESPONSEMSGBOX*)lparam;
      mywndproc_onmsgboxcommand(wnd, res->cmd, res->id);
      break;
    }*/
    
    case TWM_COMMAND:
    {
      sprintf(buf, "Pressed: %s", (IDC_OK == wparam ? "OK" : "Cancel"));
      statusbar = TuiGetWndItem(wnd, IDC_STATUSBAR);
      TuiSetWndText(statusbar, buf);

      if (wparam == IDC_OPENDLG2)
      {
        TuiShowMsgBox(wnd,
          TWM_USER+1,
          "Hello World",
          "Welcome to the real world",
          TMB_YESNOCANCEL,
          TW_SHOW);
      }
      else if (wparam == IDC_OPENDLG3)
      {
        OpenDlg3();
      }
      else if (wparam == IDC_OPENDLG4)
      {/*{ "mylistpagectlproc", "Dialog4", 2,  0,  0, 25, 80, TWS_WINDOW, 0 },*/
        TWND dlg = TuiCreateFrameWndEx(
                      "mylistctlproc",
                      "Dialog4",
                      TWS_WINDOW|TWS_VISIBLE,
                      0,
                      0, 0, 25, 80,
                      dlg3a, 0);
        TuiShowWnd(dlg, TUI_TRUE);        
      }
      else if (wparam == IDC_CLOSE)
      {
        TuiPostQuitMsg(0);
      }
      
      break;
    }
  }
  return TuiDefFrameWndProc(wnd, msg, wparam, lparam);
}

TVOID mylistctlproc_onnotify(TWND wnd, RESPONSEMSGBOX* res)
{

}

TVOID mylistctlproc_onnotify2(TWND wnd, RESPONSEMSGBOX* res)
{

}

TLONG mylistpagectlproc(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam)
{
  TWND list = 0;
  TNMHDR* nmhdr = 0;

  switch (msg)
  {
    case TWM_INITDIALOG:
    {
      list = TuiGetWndItem(wnd, IDC_TLISTBOX1);
      
      TLPC_AddItemEx(list, "Item #10\t""\t \t\t",       TES_UPPERCASE);
      TLPC_AddItemEx(list, "Item #10\t""\t \tK Baht\t", TES_NUMBER);
      TLPC_AddItemEx(list, "Item #10\t""\t \t%%\t",     TES_AUTODECIMALCOMMA);
      TLPC_AddItemEx(list, "Item #10\t""\t \tMins\t",   TES_NUMBER);
      TLPC_AddItemEx(list, "Item #10\t""\t \t\t",       TES_UPPERCASE);
      TLPC_AddItemEx(list, "Item #10\t""\t \tK Baht\t", TES_NUMBER);
      TLPC_AddItemEx(list, "Item #10\t""\t \t%%\t",     TES_AUTODECIMALCOMMA);
      TLPC_AddItemEx(list, "Item #10\t""\t \tMins\t",   TES_NUMBER);
      TLPC_AddItemEx(list, "Item #10\t""\t \t\t",       TES_UPPERCASE);
      TLPC_AddItemEx(list, "Item #10\t""\t \tK Baht\t", TES_NUMBER);
      TLPC_AddItemEx(list, "Item #20\t""\t \t%%\t",     TES_AUTODECIMALCOMMA);
      TLPC_AddItemEx(list, "Item #20\t""\t \tMins\t",   TES_NUMBER);
      TLPC_AddItemEx(list, "Item #20\t""\t \t\t",       TES_UPPERCASE);
      TLPC_AddItemEx(list, "Item #20\t""\t \tK Baht\t", TES_NUMBER);
      TLPC_AddItemEx(list, "Item #20\t""\t \t%%\t",     TES_AUTODECIMALCOMMA);
      TLPC_AddItemEx(list, "Item #20\t""\t \tMins\t",   TES_NUMBER);
      TLPC_AddItemEx(list, "Item #20\t""\t \t\t",       TES_UPPERCASE);
      TLPC_AddItemEx(list, "Item #20\t""\t \tK Baht\t", TES_NUMBER);
      TLPC_AddItemEx(list, "Item #20\t""\t \t%%\t",     TES_AUTODECIMALCOMMA);
      TLPC_AddItemEx(list, "Item #20\t""\t \tMins\t",   TES_NUMBER);
      TLPC_AddItemEx(list, "Item #30\t""\t \t\t",       TES_UPPERCASE);
      TLPC_AddItemEx(list, "Item #30\t""\t \tK Baht\t", TES_NUMBER);
      TLPC_AddItemEx(list, "Item #30\t""\t \t%%\t",     TES_AUTODECIMALCOMMA);
      TLPC_AddItemEx(list, "Item #30\t""\t \tMins\t",   TES_NUMBER);
      TLPC_AddItemEx(list, "Item #30\t""\t \t\t",       TES_UPPERCASE);
      TLPC_AddItemEx(list, "Item #30\t""\t \tK Baht\t", TES_NUMBER);
      TLPC_AddItemEx(list, "Item #30\t""\t \t%%\t",     TES_AUTODECIMALCOMMA);
      TLPC_AddItemEx(list, "Item #30\t""\t \tMins\t",   TES_NUMBER);
      TLPC_AddItemEx(list, "Item #30\t""\t \t\t",       TES_UPPERCASE);
      TLPC_AddItemEx(list, "Item #30\t""\t \tK Baht\t", TES_NUMBER);
      TLPC_AddItemEx(list, "Item #40\t""\t \t%%\t",     TES_AUTODECIMALCOMMA);
      TLPC_AddItemEx(list, "Item #40\t""\t \tMins\t",   TES_NUMBER);
      TLPC_AddItemEx(list, "Item #40\t""\t \t\t",       TES_UPPERCASE);
      TLPC_AddItemEx(list, "Item #40\t""\t \tK Baht\t", TES_NUMBER);
      TLPC_AddItemEx(list, "Item #40\t""\t \t%%\t",     TES_AUTODECIMALCOMMA);
      TLPC_AddItemEx(list, "Item #40\t""\t \tMins\t",   TES_NUMBER);
      TLPC_AddItemEx(list, "Item #40\t""\t \t\t",       TES_UPPERCASE);
      TLPC_AddItemEx(list, "Item #40\t""\t \tK Baht\t", TES_NUMBER);
      TLPC_AddItemEx(list, "Item #40\t""\t \t%%\t",     TES_AUTODECIMALCOMMA);
      TLPC_AddItemEx(list, "Item #40\t""\t \tMins\t",   TES_NUMBER);
      
      return TuiDefFrameWndProc(wnd, msg, wparam, lparam);
    }

    case TWM_COMMAND:
    {
      if (wparam == IDC_CLOSE)
      {
        TuiDestroyWnd(wnd);
      }
      else if (wparam == IDC_MSG)
      {
        TuiShowInputBox(wnd,
          TWM_USER+2,
          "Input Price",
          "Enter Price:",
          TMB_OKCANCEL,
          20,
          TES_DECIMAL|TES_AUTOHSCROLL|TES_RIGHT,  
          "0.0",
          TW_SHOW);
      }
      else if (wparam == IDC_EDITCELL)
      {
        TuiShowLineInputBox(wnd,
          TWM_USER+3,
          18, 30,
          "Do you want to save? (Y/N)",
          "Y",
          "YN",
          0,
          TW_SHOW);
      }
      break;
    }
    case TWM_NOTIFY:
    {
      nmhdr = (TNMHDR*)lparam;
      switch (nmhdr->code)
      {
        case (TWM_USER+2):
        {
          RESPONSEMSGBOX* res = (RESPONSEMSGBOX*)lparam;
          mylistctlproc_onnotify(wnd, res);
          break;
        }
        case (TWM_USER+3):
        {
          RESPONSEMSGBOX* res = (RESPONSEMSGBOX*)lparam;
          mylistctlproc_onnotify2(wnd, res);
          break;
        }
        case TCN_DISPLAYINFO:
        {
          DISPLAYINFO* di = (DISPLAYINFO*)lparam;
          TWND status = TuiGetWndItem(wnd, IDC_STATUSBAR);
          TuiSetWndText(status, di->text);
          break;
        }
      }
      
      break;
    }

  }
  return TuiDefFrameWndProc(wnd, msg, wparam, lparam);
}

TLONG mytreectlproc_printproc(FILE* fp, TTREEITEMDATA* data)
{
  fprintf(fp, "%s\n", data->itemtext);
  return 0;
}

TVOID mytreectlproc_oncommand(TWND wnd, TUINT cmd)
{
  switch (cmd)
  {
    case IDC_CLOSE:
      TuiDestroyWnd(wnd);
      break;
      
    case IDC_PRINT:
    {
        TWND tctl = TuiGetWndItem(wnd, IDC_TREECTRL1);
        FILE* fp = fopen("mytree.txt", "w");
        if (fp)
        {
          TTC_ExportToFile(tctl, fp, mytreectlproc_printproc);
          /*TTC_ExportToFile(tctl, fp, 0);*/
          fflush(fp);
          fclose(fp);
        }
        TTC_CollapseAllItems(tctl);
    }
    break;
  }
  
}

TLONG mytreectlproc_onimport(TTREEITEMDATA* data, TLPCSTR psz)
{
  strcpy(data->itemtext, psz);
  data->expanded = TUI_TRUE;
  return 0;
}

TLONG mytreectlproc_oninit(TWND wnd)
{
  TWND tctl = 0;
  FILE* fp = fopen("imptree.txt", "r");
  if (!fp)
  {
    return TUI_CONTINUE;
  }
  
  tctl = TuiGetWndItem(wnd, IDC_TREECTRL1);
  TTC_ImportFromFile(tctl, fp, 0);/*mytreectlproc_onimport);*/
  
  fclose(fp);
  
  /*TTC_ExpandAllItems(tctl);*/
  
  return TUI_CONTINUE;
}
TLONG mytreectlproc_oninit2(TWND wnd)
{
  TWND tctl = 0;
  TTREEITEMDATA data;
  TTREEITEM* item;
  TTREEITEM* parent;
  TTREEITEM* root = 0;
  
  tctl = TuiGetWndItem(wnd, IDC_TREECTRL1);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 1");
  TTC_InsertItem(tctl, 0, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 2");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 3");
  data.expanded = TUI_TRUE;
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 3 - Child 1");
  item = TTC_InsertItem(tctl, parent, &data);
  
  memset(&data, 0, sizeof(data));
  data.expanded = TUI_TRUE;
  strcpy(data.itemtext, "Item 3 - Child 2");
  item = TTC_InsertItem(tctl, parent, &data);

  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 3 - Child 2 - Accessors 1");
  TTC_InsertItem(tctl, item, &data);

  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 3 - Child 2 - Accessors 2");
  TTC_InsertItem(tctl, item, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 4");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 5");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 6");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 7");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 8");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 9");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 10");
  parent = TTC_InsertItem(tctl, root, &data);  
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 11");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 12");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 13");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 14");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 15");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 16");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 17");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 18");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 19");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 20");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 21");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 22");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 23");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 24");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 25");
  parent = TTC_InsertItem(tctl, root, &data);
  
  memset(&data, 0, sizeof(data));
  strcpy(data.itemtext, "Item 26");
  parent = TTC_InsertItem(tctl, root, &data);
  /*
  
  TTC_ExpandItem(tctl, parent);*/
  return TUI_CONTINUE;
}

TLONG mytreectlproc(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam)
{
  /*TNMHDR* nmhdr = 0;*/

  switch (msg)
  {
    case TWM_INITDIALOG:
    {
      mytreectlproc_oninit(wnd);
      return TuiDefFrameWndProc(wnd, msg, wparam, lparam);
    }

    case TWM_COMMAND:
    {
      mytreectlproc_oncommand(wnd, wparam);
      break;
    }

  }
  return TuiDefFrameWndProc(wnd, msg, wparam, lparam);
}


TLONG mylistctlproc(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam)
{
  TWND list = 0;
  /*MSGBOXPARAM param;*/
  TSUBITEM item;
  TNMHDR* nmhdr = 0;

  switch (msg)
  {
    case TWM_INITDIALOG:
    {
      list = TuiGetWndItem(wnd, IDC_TLISTBOX1);
      
      TLC_AddColumnEx(list, "STOCK", 20, TALIGN_LEFT,   TuiGetColor(BLUE_YELLOW), TES_UPPERCASE|TES_AUTOHSCROLL, 0);
      TLC_AddColumnEx(list, "DATE",  16, TALIGN_CENTER, TuiGetColor(BLUE_YELLOW), TES_UPPERCASE|TES_AUTOHSCROLL, 0);
      TLC_AddColumnEx(list, "OPEN",  16, TALIGN_RIGHT,  TuiGetColor(BLUE_YELLOW), TES_DECIMAL|TES_AUTOHSCROLL, 2);
      TLC_AddColumnEx(list, "HIGH",  16, TALIGN_RIGHT,  TuiGetColor(BLUE_YELLOW), TES_DECIMAL|TES_AUTOHSCROLL, 2);
      TLC_AddColumnEx(list, "LOW",   16, TALIGN_RIGHT,  TuiGetColor(BLUE_YELLOW), TES_DECIMAL|TES_AUTOHSCROLL, 2);
      TLC_AddColumnEx(list, "CLOSE", 16, TALIGN_RIGHT,  TuiGetColor(BLUE_YELLOW), TES_DECIMAL|TES_AUTOHSCROLL, 2);

      TLC_AddItem(list, "SCC\t01-01-2018\t560.00\t563.50\t560.00\t562.00\t", 6);
      TLC_AddItem(list, "PTTEP\t01-01-2018\t160.00\t163.50\t160.00\t162.00\t", 6);
      TLC_AddItem(list, "PTTGC\t01-01-2018\t70.00\t73.50\t70.00\t72.00\t", 6);
      TLC_AddItem(list, "PTT\t01-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);

      TLC_AddItem(list, "PTT\t05-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t06-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t07-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t08-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t09-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t10-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t11-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t12-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t13-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t14-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t15-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t16-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t17-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t18-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t19-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t20-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t21-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t22-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t23-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t24-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t25-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t26-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t27-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t28-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t29-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      TLC_AddItem(list, "PTT\t30-01-2018\t60.00\t63.50\t60.00\t62.00\t", 6);
      
      item.col   = 0;
      item.idx   = 0;
      item.attrs = TuiGetColor(GREEN_MAGENTA); 
      TLC_SetItem(list, TLCFM_ATTRS, &item);
      
      item.col   = 1;
      item.idx   = 1;
      item.attrs = TuiGetColor(YELLOW_BLUE); 
      TLC_SetItem(list, TLCFM_ATTRS, &item);
      
      item.col   = 2;
      item.idx   = 2;
      item.attrs = TuiGetColor(YELLOW_RED); 
      TLC_SetItem(list, TLCFM_ATTRS, &item);
      
      item.col   = 3;
      item.idx   = 3;
      item.attrs = TuiGetColor(GREEN_BLUE); 
      TLC_SetItem(list, TLCFM_ATTRS, &item);
      
      item.col   = 4;
      item.idx   = 4;
      item.attrs = TuiGetColor(CYAN_MAGENTA); 
      TLC_SetItem(list, TLCFM_ATTRS, &item);

      item.col   = 5;
      item.idx   = 14;
      item.attrs = TuiGetColor(CYAN_MAGENTA); 
      TLC_SetItem(list, TLCFM_ATTRS, &item);
      
      return TuiDefFrameWndProc(wnd, msg, wparam, lparam);
    }

    case TWM_COMMAND:
    {
      if (wparam == IDC_CLOSE)
      {
        TuiDestroyWnd(wnd);
      }
      else if (wparam == IDC_MSG)
      {
        TuiShowInputBox(wnd,
          TWM_USER+2,
          "Input Price",
          "Enter Price:",
          TMB_OKCANCEL,
          20,
          TES_DECIMAL|TES_AUTOHSCROLL|TES_RIGHT,  
          "0.0",
          TW_SHOW);
      }
      else if (wparam == IDC_EDITCELL)
      {
        TuiShowLineInputBox(wnd,
          TWM_USER+3,
          18, 30,
          "Do you want to save? (Y/N)",
          "Y",
          "YN",
          0,
          TW_SHOW);
      }
      break;
    }
    case TWM_NOTIFY:
    {
      nmhdr = (TNMHDR*)lparam;
      switch (nmhdr->code)
      {
        case (TWM_USER+2):
        {
          RESPONSEMSGBOX* res = (RESPONSEMSGBOX*)lparam;
          mylistctlproc_onnotify(wnd, res);
          break;
        }
        case (TWM_USER+3):
        {
          RESPONSEMSGBOX* res = (RESPONSEMSGBOX*)lparam;
          mylistctlproc_onnotify2(wnd, res);
          break;
        }
      }
      
      break;
    }

  }
  return TuiDefFrameWndProc(wnd, msg, wparam, lparam);
}

WNDTEMPL framepage[] =
{
  { TBUTTON, "Close",    IDC_CLOSE,    14,  41,  1,  11, TWS_CHILD|TWS_VISIBLE, 0 },
  { TSTATIC, "Esc to exit: ", IDC_STATUSBAR, 24,  1,  1, 79, TWS_CHILD|TWS_VISIBLE|TWS_DISABLED|TSS_LEFT, 0 },
  /* the last is the end-of-controls */
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};

#define IDC_PAGE1         10001
#define IDC_PAGE2         10021
#define IDC_PAGE3         10041

WNDTEMPL page1[] =
{
  /* 2nd and others are controls */
  { TSTATIC, "Name:",    IDC_PAGE1+1,  1,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0 },
  { TEDITBOX,   "12345678901234567890",       IDC_PAGE1+2,  1, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_LEFT|TES_UPPERCASE|TES_AUTOHSCROLL, 0 },
  { TSTATIC, "ID:",    IDC_PAGE1+3,  2,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0 },
  { TEDITBOX,   "DT66234",     IDC_PAGE1+4,  2, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_CENTER|TES_AUTOHSCROLL, 0 },
  { TSTATIC, "Tel:",    IDC_PAGE1+5,  3,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0 },
  { TEDITBOX,   "66892030023",   IDC_PAGE1+6,  3, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_NUMBER|TES_RIGHT|TES_AUTOHSCROLL, 0 },
  /* the last is the end-of-controls */
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};


WNDTEMPL page2[] =
{
  /* 2nd and others are controls */
  { TSTATIC, "Email:",    IDC_PAGE2+1,  4,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0 },
  { TEDITBOX,   "abc@abc.com", IDC_PAGE2+2,  4, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|TWS_DISABLED|
      TES_AUTOHSCROLL, 0 },
  { TSTATIC, "Password:",    IDC_PAGE2+3,  5,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0 },
  { TEDITBOX,   "welcome1!", IDC_PAGE2+4,  5, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_LEFT|TES_PASSWORD|TES_AUTOHSCROLL, 0 },
  { TSTATIC, "Price:",    IDC_PAGE2+5,  6,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0 },
  { TEDITBOX,   "132,399.50", IDC_PAGE2+6,  6, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_RIGHT|TES_AUTODECIMALCOMMA|TES_AUTOHSCROLL|TES_AUTOSUFFIX, 0 },
  /* the last is the end-of-controls */
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};


WNDTEMPL page3[] =
{
  /* 2nd and others are controls */
  { TSTATIC, "ID:",    IDC_PAGE3+1,  2,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0 },
  { TEDITBOX,   "DT66234",     IDC_PAGE3+2,  2, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_CENTER|TES_AUTOHSCROLL, 0 },
  { TSTATIC, "Email:",    IDC_PAGE3+3,  4,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0 },
  { TEDITBOX,   "abc@abc.com", IDC_PAGE3+4,  4, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|TWS_DISABLED|
      TES_AUTOHSCROLL, 0 },
  { TSTATIC, "Password:",    IDC_PAGE3+5,  5,  1,  1,  16, TWS_CHILD|TWS_VISIBLE|TSS_RIGHT, 0 },
  { TEDITBOX,   "welcome1!", IDC_PAGE3+6,  5, 18,  1, 16, 
    TWS_CHILD|TWS_VISIBLE|
      TES_LEFT|TES_PASSWORD|TES_AUTOHSCROLL, 0 },
  /* the last is the end-of-controls */
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};



TLONG myframepageproc(TWND wnd, TUINT msg, TWPARAM wparam, TLPARAM lparam)
{
  TLONG rc = TUI_CONTINUE;

  switch (msg)
  {
    case TWM_INITDIALOG:
    {
      rc = TuiDefFrameWndProc(wnd, msg, wparam, lparam);
      if (TUI_CONTINUE == rc)
      {
        rc = TuiFrameWndCreatePage(wnd, page1, 0);
      }
      if (TUI_CONTINUE == rc)
      {
        rc = TuiFrameWndCreatePage(wnd, page2, 0);
      }
      if (TUI_CONTINUE == rc)
      {
        rc = TuiFrameWndCreatePage(wnd, page3, 0);
      }
      return rc;
    }

    case TWM_COMMAND:
    {
      if (wparam == IDC_CLOSE)
      {
        TuiPostQuitMsg(0);
      }
      break;
    }
  }
  return TuiDefFrameWndProc(wnd, msg, wparam, lparam);
}

TUI_ACCEL accel[] =
{
#ifdef __USE_CURSES__
  { KEY_F(6), IDC_OPENDLG3 },
  { KEY_F(7), IDC_OPENDLG4 },
#elif __USE_WIN32__
  { TVK_F6, IDC_OPENDLG3 },
  { TVK_F7, IDC_OPENDLG4 },
#endif
  /* last */
  { 0, 0 }
};

int main(int argc, char* argv[])
{
  TMSG msg;
  TWND wnd;

  TuiStartup();

  TuiSetNextMove(TVK_TAB);
  TuiRegisterCls("mywndproc", mywndproc);
  TuiRegisterCls("mylistctlproc", mylistctlproc);
  TuiRegisterCls("myframepageproc", myframepageproc);
  TuiRegisterCls("mylistpagectlproc", mylistpagectlproc);
  TuiRegisterCls("mytreectlproc", mytreectlproc);
  
  TuiLoadAccel((TUI_ACCEL*)&accel);
  
  wnd = TuiCreateFrameWndEx(
          "mywndproc",
          "frame window",
          TWS_WINDOW|TWS_VISIBLE,
          0,
          0, 0, 25, 80,
          frame1, 0);
  if (!wnd)
  {
    TuiShutdown();
    return -1;
  }
  TuiShowWnd(wnd, TW_SHOW);
/*  TuiSetFocus(TuiGetWndItem(wnd, IDC_NAME));*/
/*
  TuiSendMsg(wnd, TWM_SETCURPAGE, 0, 0);

  TuiMoveYX(TuiGetDC(wnd), 0, 0);*/

  while (TuiGetMsg(&msg))
  {
    TuiDispatchMsg(&msg);
    TuiTranslateMsg(&msg);
  }
  TuiShutdown();
  return 0;
}


