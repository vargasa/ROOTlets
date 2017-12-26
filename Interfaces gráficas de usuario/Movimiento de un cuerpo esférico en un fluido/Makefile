CXX = g++
CFLAGS = `root-config --cflags`
LFLAGS = `root-config --glibs`

TARGET = NPM.exe

all: $(TARGET)

NPM.exe : NPM.o WMainNPM.o Dict.o
	$(CXX) -o $@ $^ $(LFLAGS) 

%.o: %.cxx
	$(CXX) $(CFLAGS) -c $<

Dict.cxx : WMainNPM.h
	@rootcint -f $@ -c $^

clean:
	@rm *.o *.pcm NPM.exe Dict.h Dict.cxx 