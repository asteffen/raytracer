#LIB=-L/usr/informix/lib/c++
INC=-I.

default: main

main: as2.cpp
	g++ $(INC) -o raytracer as2.cpp -lpng

clean:
	rm -r as2.o raytracer
