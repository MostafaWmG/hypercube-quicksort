buildAll:
	mpiCC -Wall src/sequential.cpp src/calculations.cpp -o build/sequential.o
	mpiCC -Wall src/parallel.cpp src/calculations.cpp -o build/parallel.o
	mpiCC -Wall src/parallel_master.cpp src/calculations.cpp -o build/parallel_master.o
	mpiCC -Wall src/parallel_slave.cpp src/calculations.cpp -o build/parallel_slave.o

generate:
	g++ src/sequential.cpp src/calculations.cpp -o build/sequential.o

clean:
	rm -rf build/*

test: clean buildTests executeTests

buildTests:
	g++ src/utils.cpp src/utils.spec.cpp -o build/unit.o

executeTests:
	./build/unit.o