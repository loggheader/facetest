#!/bin/bash
sudo install face.hpp /usr/local/include/opencv2/
cd headers
sudo install *.hpp /usr/local/include/opencv2/face/
cd ../lib
sudo install *.so /usr/local/lib/
cd ..

 
