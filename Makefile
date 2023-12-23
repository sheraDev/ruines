CXX=g++
CXXFLAGS=-I headers
SRCDIR=sources
TESTDIR=tests
SOURCES=$(wildcard $(SRCDIR)/*.cpp) $(wildcard $(TESTDIR)/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=myTests

# Exclure tous les fichiers main.cpp sauf celui dans le répertoire tests
SOURCES := $(filter-out $(SRCDIR)/main.cpp, $(SOURCES))
OBJECTS := $(filter-out $(SRCDIR)/main.cpp, $(OBJECTS))
SOURCES := $(filter-out $(filter-out $(TESTDIR)/mainTest.cpp, $(wildcard $(TESTDIR)/*.cpp)), $(SOURCES))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE)
