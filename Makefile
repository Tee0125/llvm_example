all: global_variable function

global_variable: global_variable.cc
	g++ -o $@ `llvm-config --cxxflags --ldflags --libs` $^

function: function.cc
	g++ -o $@ `llvm-config --cxxflags --ldflags --libs` $^
