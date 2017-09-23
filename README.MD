
# cpp static embeded lua [![Build Status](https://travis-ci.org/fooofei/cpp_static_embeded_lua.svg?branch=master)](https://travis-ci.org/fooofei/cpp_static_embeded_lua)

A way to use config file in c++.

use lua to read the script config file.

not use executable lua, luac.

lua is static linked in c++ project.


## usage


1/3 sync the code, or up the latest version of lua

2/3 if update the lua source code, run `python make_incldues` to update include files.

3/3 include the cmake files.

how to include? 
see https://github.com/fooofei/cpp_notes/blob/master/CMakeListsDoc.txt
`## add other library for static link`