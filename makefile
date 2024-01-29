# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CXX = g++
FLAGS = -g -std=c++11 -pthread


OBJECTS =	targets/obj/gcthreadfunction.o\
			targets/obj/gcuniquepointercore.o\
			targets/obj/gcuniquepointermethods.o\
			targets/obj/gcuniquepointerbase.o\
			targets/obj/gcweakpointercore.o\
			targets/obj/gcweakpointermethods.o\
			targets/obj/gcweakpointerbase.o\
			targets/obj/gcsharedpointercore.o\
			targets/obj/gcsharedpointermethods.o\
			targets/obj/gcsharedpointerbase.o\
			targets/obj/gccollector.o\
			targets/obj/gcmarkstate.o\
			targets/obj/gcsweepstate.o\
			targets/obj/gcobject.o\
			targets/obj/gcscope.o\
			targets/obj/gcscopestack.o\
			targets/obj/gcdebug.o

TESTS =		targets/obj/test0.o\
			targets/obj/test1.o\
			targets/obj/test2.o\
			targets/obj/test3.o\
			targets/obj/test4.o\
			targets/obj/test5.o\
			targets/obj/test6.o\
			targets/obj/test7.o\
			targets/obj/test8.o\
			targets/obj/test9.o\
			targets/obj/test10.o

LIBRARY = targets/lib/gc.a

TARGETS = targets/main targets/threads
TARGETS_OBJ = targets/obj/main.o targets/obj/threads.o

# ****************************************************
# targets

all: $(TARGETS)

targets/main: $(LIBRARY) $(TESTS) targets/obj/main.o
	$(CXX) -o targets/main targets/obj/main.o $(TESTS) $(LIBRARY)


targets/threads: $(LIBRARY) targets/obj/threads.o $(TESTS)
	$(CXX) -o targets/threads targets/obj/threads.o $(TESTS) $(LIBRARY)

# ****************************************************
# link library

$(LIBRARY): $(OBJECTS)
	ar crs $(LIBRARY) $(OBJECTS)

# ****************************************************
# compile

targets/obj/threads.o : src/tests/threads.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/main.o : src/tests/main.cpp
	$(CXX) $(FLAGS) -c $< -o $@


targets/obj/test10.o : src/tests/test10.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/test9.o : src/tests/test9.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/test8.o : src/tests/test8.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/test7.o : src/tests/test7.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/test6.o : src/tests/test6.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/test5.o : src/tests/test5.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/test4.o : src/tests/test4.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/test3.o : src/tests/test3.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/test2.o : src/tests/test2.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/test1.o : src/tests/test1.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/test0.o : src/tests/test0.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcthreadfunction.o : src/main/threads/gcthreadfunction.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcuniquepointercore.o : src/main/pointers/gcuniquepointercore.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcuniquepointermethods.o : src/main/pointers/gcuniquepointermethods.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcuniquepointerbase.o : src/main/pointers/gcuniquepointerbase.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcweakpointercore.o : src/main/pointers/gcweakpointercore.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcweakpointermethods.o : src/main/pointers/gcweakpointermethods.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcweakpointerbase.o : src/main/pointers/gcweakpointerbase.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcsharedpointercore.o : src/main/pointers/gcsharedpointercore.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcsharedpointermethods.o : src/main/pointers/gcsharedpointermethods.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcsharedpointerbase.o : src/main/pointers/gcsharedpointerbase.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gccollector.o : src/main/collector/gccollector.cpp
	$(CXX) $(FLAGS) -c $< -o $@


targets/obj/gcsweepstate.o : src/main/collector/gcsweepstate.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcmarkstate.o : src/main/collector/gcmarkstate.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcobject.o : src/main/objects/gcobject.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcscope.o : src/main/scope/gcscope.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcscopestack.o : src/main/scope/gcscopestack.cpp
	$(CXX) $(FLAGS) -c $< -o $@

targets/obj/gcdebug.o : src/main/collector/gcdebug.cpp
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(TARGETS) $(OBJECTS) $(TESTS) $(LIBRARY) 
