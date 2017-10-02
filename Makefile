CXX = g++
CXXFLAGS = -std=c++11 -O3
CXXFLAGSDEBUG = -std=c++11 -O0 -g3
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

compressor: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o compressor

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $^ -c -o $@

debug:
	$(CXX) $(CXXFLAGSDEBUG) *.cpp -o compressor

clean:
	rm -f *.o compressor