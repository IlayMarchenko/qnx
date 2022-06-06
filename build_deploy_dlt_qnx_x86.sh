source qnx700/qnxsdp-env.sh
cd dlt/
bash cb.sh
cd build/
cmake ../ -DCMAKE_TOOLCHAIN_FILE=../../qnx_toolchain.cmake -DBUILD_SHARED_LIBS=OFF -DWITH_DLT_SHM_ENEBLE=ON -DCMAKE_INSTALL_PREFIX=/home/Illia/local -DWITH_DLT_USE_IPv6=OFF
make
cp src/daemon/dlt-daemon ../../uploader/to_upload/
cp src/examples/dlt-example-user ../../uploader/to_upload/
cd ../../uploader/
bash deploy.sh
