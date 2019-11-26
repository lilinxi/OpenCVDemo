cd $(dirname $0) || exit
rm -rf ./build
mkdir build
cd build || exit
cmake ..
make
../run.sh