/*
 * File Name: xconf.c
 * Author: Seree Rakwong
 * Date: 21-NOV-17
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tui_xcnf.h"

/*
 * Create a configuration tree
 */
struct xcnf_s
{
  SPLAY_ENTRY( xcnf_s ) node;
  tui_char*    key;
  tui_char*    value;
};

static 
int
xcnf_compare(
  struct xcnf_s* x,
  struct xcnf_s* y
)
{
  return strcmp( x->key, y->key );
}

static SPLAY_HEAD( xcnf_tree, xcnf_s ) xcnf_root;
SPLAY_PROTOTYPE( xcnf_tree, xcnf_s, node, xcnf_compare )
SPLAY_GENERATE( xcnf_tree, xcnf_s, node, xcnf_compare )

struct _TUIXCONFIG_IMPL_STRUCT
{
  struct _TUIXCONFIGSTRUCT vtab;
  struct xcnf_tree*  root;
};
typedef struct _TUIXCONFIG_IMPL_STRUCT xcnf_impl_t;

tui_int
xcnf_add_key_value(
  xcnf_t*  xcnf,
  tui_char*   key,
  tui_char*   value
)
{
  xcnf_impl_t* impl = (xcnf_impl_t*)xcnf;
  struct xcnf_tree* root = NULL;
  struct xcnf_s* res  = NULL;
  struct xcnf_s  tmp;

  if ( !xcnf || !key || !value )
  {
    return XCNF_ERROR;
  }
  root = (struct xcnf_tree*)impl->root;

  tmp.key = key;
  res = SPLAY_FIND( xcnf_tree, root, &tmp );
  if ( NULL == res )
  {
    res = ( struct xcnf_s* )calloc( 1, sizeof( struct xcnf_s ) );
    if ( NULL == res )
    {
      return XCNF_INSUFFICIENT_MEM;
    }
    res->key   = ( tui_char* )calloc( 1, strlen( key )   + sizeof( tui_char ) );
    if ( NULL == res->key )
    {
      return XCNF_INSUFFICIENT_MEM;
    }
    res->value = ( tui_char* )calloc( 1, strlen( value ) + sizeof( tui_char ) );
    if ( NULL == res->value )
    {
      return XCNF_INSUFFICIENT_MEM;
    }
    strcpy( res->key,   key );
    strcpy( res->value, value );

    res = SPLAY_INSERT( xcnf_tree, root, res );
  }
  return ( NULL == res ? XCNF_ERROR : XCNF_OK );
}

tui_int
xcnf_get_value(
  xcnf_t* xcnf,
  tui_char*   key,
  tui_char*   value
)
{
  xcnf_impl_t* impl = (xcnf_impl_t*)xcnf;
  struct xcnf_tree* root = NULL;
  struct xcnf_s* res  = NULL;
  struct xcnf_s  tmp;

  if ( !xcnf || !key )
  {
    return XCNF_ERROR;
  }
  root = (struct xcnf_tree*)impl->root;

  tmp.key = key;
  res = SPLAY_FIND( xcnf_tree, root, &tmp );
  if ( NULL != res )
  {
    if ( value )
    {
      strcpy( value, res->value );
      return XCNF_OK;
    }
    else
    {
      return strlen( res->value );
    }
  }

  return XCNF_ERROR;
}

tui_int
xcnf_parse_line(
  xcnf_t*  xcnf,
  tui_char*   line_buffer
)
{
  tui_char* tui_charp = NULL;
  tui_char* key   = NULL;
  tui_char* value = NULL;
  tui_char  seps[2];

  /* empty line or comment line is not allowed to be kept */
  if ( ( line_buffer == NULL )                  || 
       ( XCNF_LINE_COMMENT  == line_buffer[0] ) ||
       ( strlen( line_buffer ) == 0 )
     )
  {
    return XCNF_SKIP_PARSING;
  }

  /* find separator */
  tui_charp = strchr( line_buffer, XCNF_KEY_VALUE_SEP );

  /* if there is no separator, skip the line */
  if ( NULL == tui_charp )
  {
    return XCNF_SKIP_PARSING;
  }

  seps[0] = XCNF_KEY_VALUE_SEP;
  seps[1] = '\0';
  key     = strtok( line_buffer, seps );
  value   = strtok( NULL, seps );     
  /* remove newline */
  value[ strlen( value )-1 ] = '\0';
  
  return  xcnf_add_key_value( xcnf, key, value );
}
/*----------------------*/

/*
 * load a configuration from file
 */
tui_i32 xcnf_Load(
  xcnf_t* xcnf,
  FILE*   fp
);

/*
 * save the configuration to file
 */
tui_i32 xcnf_Save(
  xcnf_t* xcnf,
  FILE*   fp
);

/*
 * xcnf_get_int() return the integer of value
 */
tui_i32 xcnf_GetInt(
  xcnf_t* xcnf,
  tui_char*   key,    /* key to get value                       */
  tui_long    def     /* default value if there is no key       */
);

/*
 * xcnf_get_float() return the double of value
 */
tui_double xcnf_GetFloat(
  xcnf_t*     xcnf,
  tui_char*   key,    /* key to get value                       */
  tui_double  def     /* default value if there is no key       */
);

/*
 * xcnf_get_string() return the length of value
 */
tui_i32 xcnf_GetString(
  xcnf_t*     xcnf,
  tui_char*   key,    /* key to get value                       */
  tui_char*   def,    /* default value if there is no key       */
  tui_char*   value,  /* output will be copied                  */
  tui_int     len     /* if len = -1, this function will return */
                      /* the length of value                    */
);

/*-------------------------*/

xcnf_t*
xcnf_Init()
{
    xcnf_impl_t* impl = (xcnf_impl_t*)malloc(sizeof(xcnf_impl_t));
    if (impl)
    {
      impl->root = ( struct xcnf_tree *)calloc( 1, sizeof( struct xcnf_tree ) );
      impl->vtab.Load          = xcnf_Load;
      impl->vtab.Save          = xcnf_Save;
      impl->vtab.GetInt        = xcnf_GetInt;
      impl->vtab.GetFloat      = xcnf_GetFloat;
      impl->vtab.GetString     = xcnf_GetString;
    }
  return (xcnf_t*)impl;
}

void
xcnf_Release(
  xcnf_t* xcnf
)
{
  if (xcnf)
  {
    xcnf_impl_t* impl = (xcnf_impl_t*)xcnf;
    free(impl->root);
    free( xcnf );
  }
}

tui_i32 xcnf_Load(
  xcnf_t* xcnf,
  FILE*   fp
)
{
  tui_char*  linep = NULL;
  tui_char  line_buffer[ XCNF_MAX_CHAR_PER_LINE + 1 ];

  if ( !fp || feof( fp ) )
  {
    return XCNF_OPEN_FILE_FAILED;
  }
  while ( !feof( fp ) )
  {
    linep = fgets( line_buffer, XCNF_MAX_CHAR_PER_LINE, fp );
    if ( linep != NULL )
    {
      xcnf_parse_line( xcnf, line_buffer );
    }
  }
  return XCNF_OK;
}

tui_i32 xcnf_Save(
  xcnf_t* xcnf,
  FILE*   fp
)
{
  struct xcnf_tree* root = ( struct xcnf_tree* )xcnf;
  struct xcnf_s *itemp = NULL;
  
  
  if ( !fp )
  {
    return XCNF_OPEN_FILE_FAILED;
  }

  SPLAY_FOREACH( itemp, xcnf_tree, root )
  {
    fprintf( fp, "%s=%s\n", itemp->key, itemp->value );
  }
  
  return XCNF_OK;
}

tui_i32 xcnf_GetInt(
  xcnf_t*     xcnf,
  tui_char*   key,    /* key to get value                       */
  tui_long    def     /* default value if there is no key       */
)
{
  tui_int len = -1;
  tui_char value[ XCNF_MAX_CHAR_PER_LINE + 1 ];
  if ( !xcnf || !key )
  {
    return def;
  }

  len = xcnf_get_value(
          xcnf,
          key,
          value
        );
  if ( len == XCNF_ERROR )
  {
    return def;
  }

  return atol( value );
}


tui_double xcnf_GetFloat(
  xcnf_t*     xcnf,
  tui_char*   key,    /* key to get value                       */
  tui_double  def     /* default value if there is no key       */
)
{
  tui_int len = -1;
  tui_char value[ XCNF_MAX_CHAR_PER_LINE + 1 ];
  if ( !xcnf || !key )
  {
    return def;
  }

  len = xcnf_get_value(
          xcnf,
          key,
          value
        );
  if ( len == XCNF_ERROR )
  {
    return def;
  }

  return atof( value );
}


tui_i32 xcnf_GetString(
  xcnf_t* xcnf,
  tui_char*   key,    /* key to get value                       */
  tui_char*   def,    /* default value if there is no key       */
  tui_char*   value,  /* output will be copied                  */
  tui_int     len     /* if len = -1, this function will return */
                  /* the length of value                    */
)
{
  tui_int rc = -1;
  tui_char val[ XCNF_MAX_CHAR_PER_LINE + 1 ];
  if ( !xcnf || !key || !value )
  {
    return -1;
  }

  rc = xcnf_get_value(
          xcnf,
          key,
          val
       );
  if ( rc == XCNF_ERROR )
  {
    if ( def )
    {
      strncpy( value, def, len );
    }
    else
    {
      value[0] = 0;
    }
  }
  else
  {
    strncpy( value, val, len );
  }
  return strlen( value );
}


