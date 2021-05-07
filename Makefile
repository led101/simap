all: simap

simap: simap.cpp simap.h
	g++ -g -Wall --std=c++11 simap.cpp EasyBMP/EasyBMP.cpp -o simap

clean:
