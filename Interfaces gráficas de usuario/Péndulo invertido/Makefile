CXX = g++
CFLAGS = `root-config --cflags`
LFLAGS = `root-config --glibs`

TARGET = IP.exe

all: $(TARGET)

IP.exe : WMainIP.o WGraphsIP.o IP.o Dict.o 
	$(CXX) -o $@ $^ $(LFLAGS) 

%.o: %.cxx
	$(CXX) $(CFLAGS) -c $<

Dict.cxx : WMainIP.h WGraphsIP.h
	@rootcint -f $@ -c $^

clean:
	@rm *.o IP.exe Dict.h Dict.cxx
