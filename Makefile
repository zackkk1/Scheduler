all: main.exe

main.exe: schedule.o main.o shift.o person.o
	g++ -g $^ -o main.exe

main.o: main.cpp
	g++ -g -c main.cpp

schedule.o: schedule.cpp schedule.h
	g++ -g -c schedule.cpp

shift.o: shift.cpp shift.h
	g++ -g -c shift.cpp

person.o: person.cpp person.h
	g++ -g -c person.cpp

clean:
	rm -f main.exe schedule.o main.o shift.o person.o

.PHONY: clean all