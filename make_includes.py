#encoding=utf-8


import os
import sys
import shutil


def entry():
  current_dir = os.path.dirname(os.path.realpath(__file__))

  path_files_includes=[
            'lua.h',
            'lua.hpp',
            'luaconf.h',
            'lualib.h',
            'lauxlib.h',
  ]

  f = lambda v: os.path.join(current_dir,'src',v)
  path_files_includes = list(map(f,path_files_includes))

  p = os.path.join(current_dir,'include','lua')
  if os.path.exists(p):
    shutil.rmtree(p)
  os.makedirs(p)
  for v in path_files_includes:
    shutil.copy(v,p)
    print('[+] copy {0} to {1}'.format(v,p))

  print('[+] all done')

if __name__ == '__main__':
    entry()