facedemo:
	g++ -std=c++11 -o facedemo facedemo.cpp -lopencv_face -lopencv_highgui  -lopencv_imgcodecs   -lopencv_imgproc  -lopencv_core

clean:
	rm facedemo
