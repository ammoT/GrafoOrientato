GXX = g++
main.exe: main.o
	$(GXX) main.o -o main.exe
main.o: main.cpp grafo.h
	$(GXX) -c main.cpp -o main.o
.PHONY:
clean:
	rm -rf *.o *.exe
