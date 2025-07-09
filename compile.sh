source /opt/rpi-4.0b/environment-setup-cortexa72-poky-linux 

#if debug
export LDFLAGS="-lpthread -g3 -O0 --sysroot=/opt/rpi-4.0b/sysroots/cortexa72-poky-linux"
export CXX=""
export CPPFLAGS=""
export CXXFLAGS=""
export CFLAGS=""
export TARGET="thread"
export SRC="*.c"
export CC="aarch64-poky-linux-gcc"

#if not debug
#export LDFLAGS="-lpthread"
#export CXX=""
#export CPPFLAGS=""
#export CXXFLAGS=""
#export CFLAGS=""
#export TARGET="thread"
#export SRC="*.c"

make -j

cp $TARGET ~/share