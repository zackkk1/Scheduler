all: main.exe

main.exe: schedule.o main.o shift.o person.o
	g++ $^ -o main.exe

main.o: main.cpp
	g++ -c main.cpp

schedule.o: schedule.cpp schedule.h
	g++ -c schedule.cpp

shift.o: shift.cpp shift.h
	g++ -c shift.cpp

person.o: person.cpp person.h
	g++ -c person.cpp

clean:
	del main.exe schedule.o main.o

.PHONY: clean all