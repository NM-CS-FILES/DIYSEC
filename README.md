helk — 1:01 PM

cd ~ && git clone https://github.com/crowcpp/crow.git cd && crow  cmake .. -DCROW_BUILD_EXAMPLES=OFF && sudo make install


cd ~ && git clone https://github.com/machinezone/IXWebSocket.git && cd IXWebSocket && mkdir build && cd build && cmake .. && sudo make install


cd ~ && git clone https://github.com/tplgy/cppcodec && cd cppcodec && mkdir build && cd build && cmake .. -DBUILD_TESTING=OFF
 && sudo make install


sudo apt install catch2
ls /usr/include/ | grep catch


cd ~ && rm -rfv cppcodec && git clone https://github.com/tplgy/cppcodec && cd cppcodec && mkdir build && cd build && cmake -DBUILD_TESTING=OFF .. && sudo make install
