# dns_forwarder
A minimal DNS forwarder 

# Release build dependencies
  # Build tool-chain
  apt-get update && apt-get install build-essential
  # CMake
  https://cmake.org/install/ - version 3.6 minimum

# Test build dependencies
  Release build dependencies
          +
  # gtest
  sudo apt-get install libgtest-dev    
  cd /usr/src/gtest  
  sudo cmake CMakeLists.txt  
sudo cp *.a /usr/lib  

# Release Build and Run
  cd dns_forwarder/cpp/  
  mkdir build/  
  cd build/  
  cmake ..  
  make -j\`nproc\`  
  cd output/  
  ./dns_forwarder <upstream_server_ip> <upstream_server_port>  

# Test Build and Run
  cd dns_forwarder/cpp/  
  mkdir build/  
  cd build/  
  cmake .. -DUNITTEST=1  
  make -j\`nproc\`  
  cd output/  
  ./dns_forwarder_test  

# ToDo
1. Scale for handling concurrent client requests  
2. Transaction record maintenence policy  
3. Dimention the buffer sizes to accomodate maximum request and response possible  
