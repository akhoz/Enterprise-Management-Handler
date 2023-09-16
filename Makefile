SOURCE = $(wildcard src/*.cpp)
OBJS = $(patsubst src/%.cpp,obj/%.o,$(SOURCE))
DEPS = $(patsubst src/%.cpp,obj/%.d,$(SOURCE))

CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -Iinclude -MD -MP
OUTPUT = bin/program


$(OUTPUT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

-include $(DEPS)

run: $(OUTPUT)
	./$(OUTPUT)
