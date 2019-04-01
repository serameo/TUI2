/*
 * File Name: tui_dic.c
 * Author: Seree Rakwong
 * Date: 29-MAR-19
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tui_dic.h"

/*
 * Create a configuration tree
 */

struct dict_s
{
  SPLAY_ENTRY( dict_s ) node;
  tui_char*             key;
  BOS_DICTIONARY        value;
};

static 
tui_i32
dict_compare(
  struct dict_s* x,
  struct dict_s* y
)
{
  return strcmp( x->key, y->key );
}

static SPLAY_HEAD( tdic_tree, dict_s ) dict_root;
SPLAY_PROTOTYPE( tdic_tree, dict_s, node, dict_compare )
SPLAY_GENERATE( tdic_tree, dict_s, node, dict_compare )




struct _TUIDICTIONARY_IMPL_STRUCT
{
  struct _TUIDICTIONARYSTRUCT      vtab;
  struct tdic_tree                *root;
  std_tdic_t                      *stddict;
  tui_i32                          lparam;
};
typedef struct _TUIDICTIONARY_IMPL_STRUCT dict_impl_t;


tui_i32
dict_add_key_value(
  tdic_t*           dict,
  tui_char*         key,
  BOS_DICTIONARY*   value
)
{
  dict_impl_t* impl = (dict_impl_t*)dict;
  struct tdic_tree* root = 0;
  struct dict_s* res  = 0;
  struct dict_s  tmp;

  if ( !dict || !key || !value )
  {
    return DICT_ERROR;
  }
  root = ( struct tdic_tree* )impl->root;

  tmp.key = key;
  res = SPLAY_FIND( tdic_tree, root, &tmp );
  if ( 0 == res )
  {
    res = ( struct dict_s* )calloc( 1, sizeof( struct dict_s ) );
    if ( 0 == res )
    {
      return DICT_INSUFFICIENT_MEM;
    }
    res->key   = ( tui_char* )calloc( 1, strlen( key )   + sizeof( char ) );
    if ( 0 == res->key )
    {
      return DICT_INSUFFICIENT_MEM;
    }
    strcpy( res->key,   key );
    memcpy( &res->value, value, sizeof(BOS_DICTIONARY) );

    res = SPLAY_INSERT( tdic_tree, root, res );
  }
  return ( 0 == res ? DICT_ERROR : DICT_OK );
}

void
_Dictionary_DictFieldHandler(
  std_tdic_t* stddict,
  BOS_DICTIONARY* fld_prop
)
{
  dictlist_t* fld = 0;
  if ( 0 == stddict || 0 == fld_prop )
  {
    return;
  }
  
  fld = (dictlist_t*)malloc( sizeof ( dictlist_t ) );
  memset( fld, 0, sizeof( dictlist_t ) );
  memcpy( &fld->fld_prop, fld_prop, sizeof( BOS_DICTIONARY ) );
  
  if ( 0 == stddict->fld_last )
  {
    /* no field added */
    stddict->fld_first = stddict->fld_last = fld;
  }
  else
  {
    stddict->fld_last->next = fld;
    stddict->fld_last = fld;
  }
}

/*---------------------------------------------*/

tui_void
dict_ReleaseParam(
  tdic_t*     dict,
  std_tdic_t* stddict
);

/*
 * load a configuration from file
 */
tui_i32
dict_Load(
  tdic_t*     dict,
  FILE*       fp /* BOS dictionary file */
);

/*
 * load a configuration from file
 */

tui_i32
dict_LoadParam(
  tdic_t*             dict,
  FILE*               fp,
  fn_dict_handler     dict_handler
  /*,
  std_tdic_t*         stddict*/
);

/*
 * dict_GetChar() return the integer of value
 */
tui_char
dict_GetChar(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_char    def     /* default value if there is no key       */
);


/*
 * dict_GetLong() return the integer of value
 */
tui_i32
dict_GetInt(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_i32     def     /* default value if there is no key       */
);

/*
 * dict_get_float() return the double of value
 */
tui_float
dict_GetFloat(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_float   def     /* default value if there is no key       */
);

/*
 * dict_GetDouble() return the double of value
 */
tui_double
dict_GetDouble(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_double  def     /* default value if there is no key       */
);

/*
 * dict_get_string() return the length of value
 */
tui_i32
dict_GetString(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_char*   def,    /* default value if there is no key       */
  tui_char*   out,    /* output will be copied                  */
  tui_i32     len     /* if len = -1, this function will return */
                  /* the length of value                    */
);

tui_i32
dict_GetBinary(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_byte*   def,    /* default value if there is no key       */
  tui_byte*   out,    /* output will be copied                  */
  tui_i32     len     /* if len = -1, this function will return */
                  /* the length of value                    */
);

tui_i32
dict_GetValue(
  tdic_t*           dict,
  tui_char*         key,
  BOS_DICTIONARY*   value
);

/*---------------------------------------------*/
tui_i32
dict_get_value(
  tdic_t*           dict,
  tui_char*         key,
  BOS_DICTIONARY*   value
)
{
  dict_impl_t* impl = (dict_impl_t*)dict;
  struct tdic_tree* root = 0;
  struct dict_s* res  = 0;
  struct dict_s  tmp;

  if ( !dict || !key )
  {
    return DICT_ERROR;
  }
  root = ( struct tdic_tree* )impl->root;

  tmp.key = key;
  res = SPLAY_FIND( tdic_tree, root, &tmp );
  if ( 0 != res )
  {
    if ( value )
    {
      memcpy( value, &res->value, sizeof(BOS_DICTIONARY) );
      return DICT_OK;
    }
  }

  return DICT_ERROR;
}

tui_i32
dict_parse_line(
  tdic_t*     dict,
  tui_char*   line_buffer,
  tui_long    id,
  tui_i32     fldtype
)
{
  tui_char key[21]   = "\0";
  tui_char attrs[8]  = "\0";
  tui_char buffer[8] = "\0";
  BOS_DICTIONARY value;

  /* empty line or comment line is not allowed to be kept */
  if ( ( 0 == line_buffer )                  || 
       ( 0 == strlen( line_buffer ) )
     )
  {
    return DICT_SKIP_PARSING;
  }

  memcpy( &key[0], &line_buffer[0], 20 );     key[20]   = 0;
  memcpy( &attrs[0], &line_buffer[20], 7 );   attrs[7] = 0;
  
  value.id = id;
  strcpy(value.name, key);
  buffer[3] = 0;
  memcpy( buffer, attrs, 3 );
  value.offset  = atoi( buffer );
  memcpy( buffer, &attrs[3], 3 );
  value.size    = atoi( buffer );
  value.type    = attrs[6];
  value.fldtype = fldtype;
  
  return  dict_add_key_value( dict, key, &value );
}

tui_i32
dict_parse_line_param(
  tdic_t*           dict,
  tui_char*         line_buffer,
  tui_long          id,
  tui_i32           fldtype,
  fn_dict_handler   field_handler_proc,
  bos_tdic_t*       bosdict
)
{
  tui_char key[21]   = "\0";
  tui_char attrs[8]  = "\0";
  tui_char buffer[8] = "\0";
  BOS_DICTIONARY value;

  /* empty line or comment line is not allowed to be kept */
  if ( ( 0 == line_buffer )                  || 
       ( 0 == strlen( line_buffer ) )
     )
  {
    return DICT_SKIP_PARSING;
  }

  memcpy( &key[0],   &line_buffer[0],  20 );   key[20]  = 0;
  memcpy( &attrs[0], &line_buffer[20], 7  );   attrs[7] = 0;
  
  value.id = id;
  strcpy(value.name, key);
  buffer[3] = 0;
  memcpy( buffer, attrs, 3 );
  value.offset  = atoi( buffer );
  memcpy( buffer, &attrs[3], 3 );
  value.size    = atoi( buffer );
  value.type    = attrs[6];
  value.fldtype = fldtype;
  
  if ( field_handler_proc )
  {
    field_handler_proc( (std_tdic_t*)bosdict, &value );
  }
  
  return  dict_add_key_value( dict, key, &value );
}
tui_i32
dict_parse_line_std_param(
  tdic_t*           dict,
  tui_char*         line_buffer,
  tui_long          id,
  tui_i32           fldtype,
  fn_dict_handler   field_handler_proc,
  std_tdic_t*       stddict
)
{
  tui_char key[21]   = "\0";
  tui_char attrs[8]  = "\0";
  tui_char buffer[8] = "\0";
  BOS_DICTIONARY value;

  /* empty line or comment line is not allowed to be kept */
  if ( ( 0 == line_buffer )                  || 
       ( 0 == strlen( line_buffer ) )
     )
  {
    return DICT_SKIP_PARSING;
  }

  memcpy( &key[0],   &line_buffer[0],  20 );   key[20]  = 0;
  memcpy( &attrs[0], &line_buffer[20], 7  );   attrs[7] = 0;
  
  value.id = id;
  strcpy(value.name, key);
  buffer[3] = 0;
  memcpy( buffer, attrs, 3 );
  value.offset  = atoi( buffer );
  memcpy( buffer, &attrs[3], 3 );
  value.size    = atoi( buffer );
  value.type    = attrs[6];
  value.fldtype = fldtype;
  
  if ( field_handler_proc )
  {
    field_handler_proc( stddict, &value );
  }
  
  return  dict_add_key_value( dict, key, &value );
}
/*-----------------------------------*/
tui_i32
dict_GetValue(
  tdic_t*           dict,
  tui_char*         key,
  BOS_DICTIONARY*   value
)
{
  return dict_get_value( dict, key, value );
}

tdic_t*
Dictionary_Create(tui_i32 lparam)
{
  dict_impl_t* impl = (dict_impl_t*)malloc(sizeof(dict_impl_t));
  if (impl)
  {    
    memset(impl, 0, sizeof(dict_impl_t));
    impl->root    = ( struct tdic_tree *)calloc( 1, sizeof( struct tdic_tree ) );
    impl->stddict = ( std_tdic_t *)calloc( 1, sizeof( std_tdic_t ) );
    impl->stddict = (tdic_t*)impl;
    impl->lparam  = lparam;
    /* functions */
    impl->vtab.LoadFromFile           = dict_LoadParam;
    impl->vtab.GetChar                = dict_GetChar;
    impl->vtab.GetInt                 = dict_GetInt;
    impl->vtab.GetFloat               = dict_GetFloat;
    impl->vtab.GetDouble              = dict_GetDouble;
    impl->vtab.GetString              = dict_GetString;
    impl->vtab.GetBinary              = dict_GetBinary;
    impl->vtab.GetValue               = dict_GetValue;
  }
  return ( tdic_t* )impl;
}

tui_void
Dictionary_Release(
  tdic_t* dict
)
{
  if (dict)
  {
    dict_impl_t* impl = (dict_impl_t*)dict;
    dict_ReleaseParam(dict, impl->stddict);
    free(impl->stddict);
    free(impl->root);
    free( dict );
  }
}

tui_void
dict_ReleaseParam(
  tdic_t*     dict,
  std_tdic_t* stddict
)
{
  dictlist_t* tmp = 0;
  dictlist_t* fld = stddict->fld_first;
  while ( fld )
  {
    tmp = fld;
    fld = fld->next;
    free( tmp );
  }
}

/*
 * load a configuration from file
 */
tui_i32
dict_LoadParam(
  tdic_t*           dict,
  FILE*             fp,
  fn_dict_handler   field_handler_proc
)
{
  tui_char* linep = 0;
  tui_char  line_buffer[ DICT_MAX_CHAR_PER_LINE + 1 ];
  tui_char  header[ DICT_MAX_CHAR_PER_LINE + 1 ];
  tui_long  id = 0;
  tui_char  buffer[8];
  tui_long  nflds = 0;
  tui_long  rec_bytes = 0;
  tui_long  nhdrs = 0;
  fn_dict_handler proc = (field_handler_proc ? field_handler_proc : _Dictionary_DictFieldHandler);
  dict_impl_t* impl = (dict_impl_t*)dict;

  if ( !fp || feof( fp ) )
  {
    return DICT_OPEN_FILE_FAILED;
  }
  
  /* read first line info */
  if ( !feof( fp ) )
  {
    linep = fgets( header, DICT_MAX_CHAR_PER_LINE, fp );
    memcpy( &buffer, &header[0], 6 ); buffer[6] = 0;
    nflds = atoi( buffer );
    memcpy( &buffer, &header[6], 3 ); buffer[3] = 0;
    rec_bytes = atoi( buffer );
    memcpy( &buffer, &header[9], 3 ); buffer[3] = 0;
    nhdrs = atoi( buffer );
    
    impl->stddict->nflds = nflds;
    impl->stddict->nhdrs = nhdrs;
    impl->stddict->rec_bytes = rec_bytes;
  }

  /* header */  
  while ( !feof( fp ) && id < nhdrs )
  {
    linep = fgets( line_buffer, DICT_MAX_CHAR_PER_LINE, fp );
    
    if ( linep != 0 )
    {
      ++id;
      dict_parse_line_std_param( dict,
        line_buffer, id, HEADER_FIELD,
        proc,
        impl->stddict );
    }
  }
  /* records */
  while ( !feof( fp ) )
  {
    linep = fgets( line_buffer, DICT_MAX_CHAR_PER_LINE, fp );
    
    if ( linep != 0 )
    {
      ++id;
      dict_parse_line_std_param( dict, 
        line_buffer, id, RECORD_FIELD,
        proc,
        impl->stddict );
    }
  }
  return DICT_OK;
}


tui_char
dict_GetChar(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_char    def     /* default value if there is no key       */
)
{
  tui_i32 rc = -1;
  BOS_DICTIONARY value;
  tui_char buffer[8];
  
  if ( !dict || !key )
  {
    return def;
  }

  rc = dict_get_value(
          dict,
          key,
          &value
        );
  if ( DICT_ERROR == rc )
  {
    return def;
  }

  memcpy( buffer, &text[value.offset], value.size );
  buffer[ value.size ] = 0;
  return ( DICT_CHAR == value.type ? buffer[0] : def );
}


tui_i32
dict_GetInt(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_i32     def     /* default value if there is no key       */
)
{
  tui_i32 rc = -1;
  BOS_DICTIONARY value;
  tui_char buffer[8];
  
  if ( !dict || !key )
  {
    return def;
  }

  rc = dict_get_value(
          dict,
          key,
          &value
        );
  if ( DICT_ERROR == rc )
  {
    return def;
  }

  memcpy( buffer, &text[value.offset], value.size );
  buffer[ value.size ] = 0;
  return ( DICT_LONG == value.type ? atol( buffer ) : def );
}


tui_float
dict_GetFloat(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_float   def     /* default value if there is no key       */
)
{
  tui_i32 rc = -1;
  BOS_DICTIONARY value;
  float out = def;
  
  if ( !dict || !key )
  {
    return def;
  }

  rc = dict_get_value(
          dict,
          key,
          &value
        );
  if ( DICT_ERROR == rc )
  {
    return def;
  }

  memcpy( &out, &text[value.offset], value.size );
  return ( DICT_FLOAT == value.type ? out : def );
}

tui_double
dict_GetDouble(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_double  def     /* default value if there is no key       */
)
{
  tui_i32 rc = -1;
  BOS_DICTIONARY value;
  tui_double out = def;
  
  if ( !dict || !key )
  {
    return def;
  }

  rc = dict_get_value(
          dict,
          key,
          &value
        );
  if ( DICT_ERROR == rc )
  {
    return def;
  }

  memcpy( &out, &text[value.offset], value.size );
  return ( DICT_DOUBLE == value.type ? out : def );
}
/*typedef tui_i32     (*fn_dict_get_string)(tdic_t*, tui_char*, tui_char*, tui_i32, tui_char*, tui_i32);*/
tui_i32
dict_GetString(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_char*   def,    /* default value if there is no key       */
  tui_char*   out,    /* output will be copied                  */
  tui_i32     len     /* if len = -1, this function will return */
                      /* the length of value                    */
)
{
  tui_i32 rc = -1;
  BOS_DICTIONARY value;
  
  if ( !dict || !key )
  {
    if ( def )
    {
      strncpy( out, def, len );
    }
    return -1;
  }

  rc = dict_get_value(
          dict,
          key,
          &value
        );
  if ( DICT_ERROR == rc || value.type != DICT_CHAR )
  {
    if ( def )
    {
      strncpy( out, def, len );
    }
  }
  else
  {
    if ( value.size < len )
    {
      len = value.size;
    }
    memcpy( out, &text[value.offset], len );
    out[ len ]  = 0;
  }
  return len;
}


tui_i32
dict_GetBinary(
  tdic_t*     dict,
  tui_char*   key,    /* key to get value                       */
  tui_char*   text,   /* sFull from BOS global                  */
  tui_byte*   def,    /* default value if there is no key       */
  tui_byte*   out,    /* output will be copied                  */
  tui_i32     len     /* if len = -1, this function will return */
                      /* the length of value                    */
)
{
  tui_i32 rc = -1;
  BOS_DICTIONARY value;
  
  if ( !dict || !key )
  {
    if ( def )
    {
      memcpy( out, def, len );
    }
    return -1;
  }

  rc = dict_get_value(
          dict,
          key,
          &value
        );
  if ( DICT_ERROR == rc || value.type != DICT_HEX )
  {
    if ( def )
    {
      memcpy( out, def, len );
    }
  }
  else
  {
    if ( value.size < len )
    {
      len = value.size;
    }
    memcpy( out, &text[value.offset], len );
    out[ len ]  = 0;
  }
  return len;
}

