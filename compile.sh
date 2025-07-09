source /opt/rpi-4.0b/environment-setup-cortexa72-poky-linux 

export LDFLAGS="-lpthread -g"
export CXX=""
export CPPFLAGS=""
export CXXFLAGS=""
export TARGET="thread"
export SRC="*.c"

make -j

cp $TARGET ~/share