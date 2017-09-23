

rm -rf build_posix
mkdir build_posix
cd build_posix
cmake ..
make 
cd ..
./test_liblua