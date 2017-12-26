CXX = g++
CFLAGS = `root-config --cflags`
LFLAGS = `root-config --glibs`

TARGET = CaidaLibre.exe

all: $(TARGET)

CaidaLibre.exe : CaidaLibreGui.o Aplicacion.o Dict.o
	$(CXX) -o $@ $^ $(LFLAGS) 

%.o: %.cxx
	$(CXX) $(CFLAGS) -c $<

Dict.cxx : CaidaLibreGui.h
	@rootcint -f $@ -c $^

clean:
	@rm *.o *.d CaidaLibre.exe Dict.h Dict.cxx