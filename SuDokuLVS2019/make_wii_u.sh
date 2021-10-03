export DEVKITPRO=/opt/devkitpro
cd "C:/SuDokuL/SuDokuLVS2019"
rm -r build_wii_u
mkdir build_wii_u
cd build_wii_u
cmake ../ -DCMAKE_TOOLCHAIN_FILE=$DEVKITPRO/wut/share/wut.toolchain.cmake -DWIIU=ON
make