all: foursine

foursine: Stk.cpp FileRead.cpp FileWrite.cpp FileWvIn.cpp FileLoop.cpp FileWvOut.cpp foursine.cpp Stk.h FileRead.h FileWrite.h FileWvIn.h FileLoop.h FileWvOut.h WvIn.h WvOut.h SineWave.h SineWave.cpp Generator.h
	g++ -Wall -D__LITTLE_ENDIAN__ -o foursine Stk.cpp FileRead.cpp FileWrite.cpp FileWvIn.cpp FileLoop.cpp FileWvOut.cpp SineWave.cpp foursine.cpp 

clean:


