
#include "luautils.hpp"
#include <sstream>
#include <algorithm>

int
lua_stringexpr(lua_State* L, const char* expr, std::string & out)
{
  int err;
  std::ostringstream oss;
  size_t l;
  const char * p;
  
  if (!L) {
    return -1;
  }
  if (!expr) {
    return -1;
  }

  oss << "evalExpr=";
  oss << expr;

  /* return  LUA_OK=0 for success */
  err = luaL_dostring(L, oss.str().c_str());
  if (err) {
    return err;
  }
  /* no check the return value */
  lua_getglobal(L, "evalExpr");
  err = -1;
  if (lua_isstring(L, -1))
  {
    l = 0;
    p = lua_tolstring(L, -1, &l);
    if ((p && l)) {
      out.clear();
      out.assign(p, l);
      err = 0;
    }
  }
  /* remove lua_getglobal value */
  lua_pop(L, 1);
  return err;
}

/**
Evaluates a Lua expression that results in a number.
The number is stored in out.
*/
int
lua_numberexpr(lua_State* L, const char* expr, double* out)
{
  int err;
  std::ostringstream oss;

  if (!L) {
    return -1;
  }
  if (!expr) {
    return -1;
  }
  if (!out) {
    return -1;
  }

  oss << "evalExpr=";
  oss << expr;

  /* return  LUA_OK=0 for success */
  err = luaL_dostring(L, oss.str().c_str());
  if (err) {
    return err;
  }
  /* no check the return value */
  lua_getglobal(L, "evalExpr");
  err = -1;
  if (lua_isnumber(L, -1))
  {
    *out = lua_tonumber(L, -1);
    err = 0;
  }
  /* remove lua_getglobal value */
  lua_pop(L, 1);
  return err;
}

/**
Evaluates a Lua expression that results in a number and cast to an int.
*/
int
lua_intexpr(lua_State* L, const char* expr, int32_t * out)
{
  double d;
  int err;
  
  err = lua_numberexpr(L, expr, &d);
  if (err) {
    return err;
    
  }
  *out = (int32_t)d;
  return 0;
}

/**
Evaluates a Lua expression that results in a number.
*/
int
lua_boolexpr(lua_State* L, const char* expr, bool * out)
{

  int err;
  std::ostringstream oss;

  if (!L) {
    return -1;
  }
  if (!expr) {
    return -1;
  }
  if (!out) {
    return -1;
  }

  oss << "evalExpr=";
  oss << expr;

  /* return  LUA_OK=0 for success */
  err = luaL_dostring(L, oss.str().c_str());
  if (err) {
    return err;
  }
  /* no check the return value */
  lua_getglobal(L, "evalExpr");
  err = -1;
  if (lua_isboolean(L, -1))
  {
    *out = (bool)lua_toboolean(L, -1);
    err = 0;
  }
  /* remove lua_getglobal value */
  lua_pop(L, 1);
  return err;
}


int
lua_stringtableexpr(lua_State * L, const char * expr, std::map<std::string, std::string>& out)
{
  int err;
  std::ostringstream oss;
  int32_t index;

  if (!L) {
    return -1;
  }
  if (!expr) {
    return -1;
  }


  oss << "evalExpr=";
  oss << expr;

  /* return  LUA_OK=0 for success */
  err = luaL_dostring(L, oss.str().c_str());
  if (err) {
    return err;
  }
  /* no check the return value */
  index = lua_getglobal(L, "evalExpr");
  err = -1;

  // https://stackoverflow.com/questions/6137684/iterate-through-lua-table
  if (lua_istable(L,-1))
  {
    // stack now contains: -1 => table

    lua_pushnil(L);
    // stack now contains: -1 => nil; -2 => table
    for (;lua_next(L, -2) !=0;)
    {
      // stack now contains: -1 => value; -2 => key; -3 => table
      // copy the key so that lua_tostring does not modify the original
      lua_pushvalue(L, -2);
      // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
      if (lua_isstring(L, -1) && lua_isstring(L, -2))
      {
        const char * p1;
        const char * p2;
        size_t l1=0;
        size_t l2=0;
        p1 = lua_tolstring(L, -1, &l1);
        p2 = lua_tolstring(L, -2, &l2);
        if (p1 && p2 && l1 && l2)
        {
          out.insert(std::make_pair(std::string(p1, l1), std::string(p2, l2)));
        }
      }
      // pop value + copy of key, leaving original key
      lua_pop(L, 2);
      // stack now contains: -1 => key; -2 => table
    }
    err = 0;
  }

 
  /* remove lua_getglobal value */
  lua_pop(L, 1);
  return err;
}


int
lua_booltableexpr(lua_State * L , const char * expr, std::map<std::string, bool> & out)
{
  int err;
  std::ostringstream oss;
  int32_t index;

  if (!L) {
    return -1;
  }
  if (!expr) {
    return -1;
  }


  oss << "evalExpr=";
  oss << expr;

  /* return  LUA_OK=0 for success */
  err = luaL_dostring(L, oss.str().c_str());
  if (err) {
    return err;
  }
  /* no check the return value */
  index = lua_getglobal(L, "evalExpr");
  err = -1;

  // https://stackoverflow.com/questions/6137684/iterate-through-lua-table
  if (lua_istable(L, -1))
  {
    // stack now contains: -1 => table

    lua_pushnil(L);
    // stack now contains: -1 => nil; -2 => table
    for (; lua_next(L, -2) != 0;)
    {
      // stack now contains: -1 => value; -2 => key; -3 => table
      // copy the key so that lua_tostring does not modify the original
      lua_pushvalue(L, -2);
      // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
      if (lua_isstring(L, -1) && lua_isboolean(L, -2))
      {
        const char * p1;
        size_t l1 = 0;
        bool b;
        p1 = lua_tolstring(L, -1, &l1);
        b = (bool)lua_toboolean(L, -2);
        if (p1 && l1)
        {
          out.insert(std::make_pair(std::string(p1, l1), b));
        }
      }
      // pop value + copy of key, leaving original key
      lua_pop(L, 2);
      // stack now contains: -1 => key; -2 => table
    }
    err = 0;
  }


  /* remove lua_getglobal value */
  lua_pop(L, 1);
  return err;
  return 0;
}