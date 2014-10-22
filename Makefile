testFiles=src/*.spec.cpp
appFiles=$(shell find src ! -name "*.spec.cpp" -name "*.cpp")

buildAll:
	mpiCC -Wall $(appFiles) -o build/app.o

clean:
	rm -rf build/*

test: clean buildTests executeTests

runApp:
	./build/app.o

run: buildAll runApp

buildTests:
	g++ test_module.spec.cpp $(testFiles) -o build/unit_tests.o

executeTests:
	./build/unit_tests.o