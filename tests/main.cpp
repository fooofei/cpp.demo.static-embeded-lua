#include "luautils.hpp"
#include <stdio.h>

#include <sstream>

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


  /* int values can be read as both string and int */
  print_settings_int(L, "settings.resolution.width");
  print_settings_string(L, "settings.resolution.width");
  print_settings_bool(L, "settings.resolution.width");


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
}

int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);

  if (luaL_dofile(L, "settings.lua") == 1) {
    printf("Error loading file \n");
    return 1;
  }

  print_settings(L);

  lua_close(L);
  return 0;
}

/*
read int settings.resolution.width=800
read string settings.resolution.width=800
read bool err?=-1 settings.resolution.width=false
read int settings.resolution.height=600
read bool err?=0 settings.resolution.fullscreen=true
read int #settings.images=3
read string settings.images[0]=error
read string settings.images[1]=C:\carrotxxx.bmp
read string settings.images[2]=C:\apple.bmp
read string settings.images[3]=C:\banana.bmp
read string settings.images[4]=error
*/