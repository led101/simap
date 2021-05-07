all: sineosc

sineosc: Stk.cpp FileRead.cpp FileWrite.cpp FileWvIn.cpp FileLoop.cpp FileWvOut.cpp sineosc.cpp Stk.h FileRead.h FileWrite.h FileWvIn.h FileLoop.h FileWvOut.h WvIn.h WvOut.h
	g++ -Wall -D__LITTLE_ENDIAN__ -o sineosc Stk.cpp FileRead.cpp FileWrite.cpp FileWvIn.cpp FileLoop.cpp FileWvOut.cpp sineosc.cpp 

clean:


