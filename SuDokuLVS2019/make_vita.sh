export VITASDK=/usr/local/vitasdk
cd "C:/SuDokuL/SuDokuLVS2019"
rm -r build_vita
mkdir build_vita
cd build_vita
cmake ../ -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake -DVITA=ON
make