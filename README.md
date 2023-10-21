# test_socket

## Build
## server
cd test_socket/server
mkdir build
cd build
cmake ..
make

## client 
cd test_socket/client
mkdir build
cd build
cmake ..
make

## Execute
### server
./test_server
### client
./test_client <server_ip> <client_ip>
