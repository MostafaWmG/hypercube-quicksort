testFiles=src/*.spec.cpp
appFiles=$(shell find src ! -name "*.spec.cpp" -name "*.cpp")

buildAll:
	mpiCC -Wall src/sequential.cpp -o build/sequential.o
	mpiCC -Wall src/parallel.cpp -o build/parallel.o

clean:
	rm -rf build/*

test: clean buildTests executeTests

buildTests:
	g++ test_module.spec.cpp $(testFiles) -o build/unit_tests.o

executeTests:
	./build/unit_tests.o