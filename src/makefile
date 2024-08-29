CXX=g++
CXXFLAGS=-std=c++11 -Wall -O 
GOAL=$(MAKECMDGOALS)
OBJECTS=$(GOAL).o


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GOAL): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(GOAL)
	rm $(OBJECTS) 

.PHONY: clean

clean:
	rm -v *.o

