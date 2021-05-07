all: audiosynth

audiosynth: Stk.cpp FileRead.cpp FileWrite.cpp FileWvIn.cpp FileLoop.cpp FileWvOut.cpp audiosynth.cpp Stk.h FileRead.h FileWrite.h FileWvIn.h FileLoop.h FileWvOut.h WvIn.h WvOut.h SineWave.h SineWave.cpp Generator.h Instrmnt.h
	g++ -Wall -D__LITTLE_ENDIAN__ -o audiosynth Stk.cpp FileRead.cpp FileWrite.cpp FileWvIn.cpp FileLoop.cpp FileWvOut.cpp SineWave.cpp audiosynth.cpp 

clean:


