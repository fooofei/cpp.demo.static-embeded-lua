/*
  the file is for get config from lua file
  download from http://windrealm.org/tutorials/reading-a-lua-configuration-file-from-c.php
  and do some changes, make it to c++ 
*/
#ifndef WINDREALM_LUA_UTILS_H
#define WINDREALM_LUA_UTILS_H

#include "lua/lua.hpp"
#include <string>
#include <map>
#include <stdint.h>

/*
  all api return 0 for success
*/

/**
  Evaluates a Lua expression and fill in the string result.
*/

int 
lua_stringexpr(lua_State* L, const char* expr, std::string &);

/**
  Evaluates a Lua expression that results in a number.
  The number is stored in out.
*/
int 
lua_numberexpr( lua_State* L, const char* expr, double* out );

/**
  Evaluates a Lua expression that results in a number and cast to an int.
*/
int 
lua_intexpr( lua_State* L, const char* expr, int32_t * out );

/**
  Evaluates a Lua expression that results in a number.
*/
int 
lua_boolexpr( lua_State* L, const char* expr, bool * out);


// get args, push to table, have not clear the table, you can append to the table something 
// before call this
int
lua_stringtableexpr(lua_State *, const char * expr, std::map<std::string,std::string>& );


int
lua_booltableexpr(lua_State *, const char * expr, std::map<std::string, bool> &);

#endif

