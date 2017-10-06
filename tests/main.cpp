#include "luautils.hpp"
#include <stdio.h>

#include <sstream>

#ifdef WIN32
#ifdef _DEBUG
#include "../../cpp_common/detectmemleak.h"
struct _crt_dbg_leak_t g_leak(0);
#endif
#endif

static
void
print_settings_int(lua_State * L, const char * expr)
{
  int32_t  value;
  int err;

  value = 0;
  err = lua_intexpr(L, expr, &value);
  if (err) {
    value = -1;
  }
  fprintf(stdout, "read int %s=%d\n", expr, value);
}


static
void
print_settings_string(lua_State * L, const char * expr)
{
  std::string temp;
  int err;

  temp.clear();
  err = lua_stringexpr(L, expr, temp);
  if (err) {
    temp = "error";
  }
  fprintf(stdout, "read string %s=%s\n", expr, temp.c_str());
}

static
void
print_settings_bool(lua_State * L, const char * expr)
{
  bool value;
  int err;

  value = false;
  err = lua_boolexpr(L, expr, &value);
  fprintf(stdout, "read bool err?=%d %s=%s\n", err, expr, value ? "true" : "false");
}



void
print_settings(lua_State* L)
{

  /* if the string of file is utf-8, then read is utf-8 */

  /* int values can be read as both string and int */

  print_settings_string(L, "path_directory_current_script");
  print_settings_string(L, "path_directory_current_script_utf8");
  

  print_settings_int(L, "settings.resolution.width");
  print_settings_string(L, "settings.resolution.width");
  print_settings_bool(L, "settings.resolution.width");


  print_settings_string(L, "settings.resolution.comment");

  print_settings_int(L, "settings.resolution.height");
  print_settings_bool(L, "settings.resolution.fullscreen");

  print_settings_int(L, "#settings.images");

  /* the image's index is startswith 1, not 0 */
  for (uint32_t i = 0; i < 5; ++i)
  {
    std::ostringstream oss;
    oss << "settings.images[" << i << "]";
    print_settings_string(L, oss.str().c_str());
  }
  
  typedef std::map<std::string, std::string> string_table_t;
  typedef std::map<std::string, bool> bool_table_t;
  string_table_t table;

  const char * expr;
  expr = "settings.enum_configs.config_string";
  lua_stringtableexpr(L, expr, table);

  for (string_table_t::const_iterator it = table.begin(); it != table.end(); ++it)
  {
    fprintf(stdout, "read string_table %s key<%s>=value<%s>\n", expr, it->first.c_str(), it->second.c_str());
  }

  bool_table_t btable;
  expr = "settings.enum_configs.config_bool";
  lua_booltableexpr(L, expr, btable);
  for (bool_table_t::const_iterator it = btable.begin(); it != btable.end(); ++it)
  {
    fprintf(stdout, "read bool_table %s key<%s>=value<%s>\n", expr, it->first.c_str(), it->second ?"true":"false");
  }
}


int
get_lua_abs_path(std::string & s)
{
#ifdef WIN32
  // Windows ansi path encoding
  s.assign("f:\\temp\\\xC9\xE8\xD6\xC3\\settings.lua");
#else
  // posix utf8 path encoding
  s.assign("F:\\temp\xE8\xAE\xBE\xE7\xBD\xAE\\settings.lua");
#endif

  return 0;
}


int main() {
  int err;
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  std::string path_relative;
  
#ifdef WIN32
  path_relative.append("../");
#else
#endif

  path_relative.append("settings.lua");


  // use the abs path to test the path encoding
  //get_lua_abs_path(path_relative);

  err = luaL_dofile(L, path_relative.c_str());
  if (err) {
    printf("Error loading file \n");
  }

  if (err==0)
  {
    print_settings(L);
  }

  lua_close(L);
  return 0;
}

/*
read int settings.resolution.width=800
read string settings.resolution.width=800
read bool err?=-1 settings.resolution.width=false
read string settings.resolution.comment=error
read int settings.resolution.height=600
read bool err?=0 settings.resolution.fullscreen=true
read int #settings.images=3
read string settings.images[0]=error
read string settings.images[1]=C:\carrotxxx.bmp
read string settings.images[2]=C:\apple.bmp
read string settings.images[3]=C:\banana.bmp
read string settings.images[4]=error
read string_table settings.enum_configs.config_string key<config_string1>=value<config_string1_value>
read string_table settings.enum_configs.config_string key<config_string2>=value<config_string2_value>
read string_table settings.enum_configs.config_string key<config_string_common1>=value<common_value_append1>
read string_table settings.enum_configs.config_string key<config_string_common2>=value<common_value_append2>
read bool_table settings.enum_configs.config_bool key<config_bool1>=value<false>
read bool_table settings.enum_configs.config_bool key<config_bool2>=value<true>
*/