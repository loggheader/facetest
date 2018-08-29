#!/bin/bash
sudo mkdir -p  /usr/local/include/opencv2/face/
sudo install face.hpp /usr/local/include/opencv2/
cd headers
sudo install *.hpp /usr/local/include/opencv2/face/
cd ../lib
sudo install opencv_face.so /usr/local/lib/
sudo install opencv_face.so.3.4 /usr/local/lib/
sudo install opencv_face.so.3.4.1 /usr/local/lib/
cd ..

 
