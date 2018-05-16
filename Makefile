all: main.exe

main.exe: schedule.o main.o shift.o person.o
	g++ $^ -o main.exe

schedule.o: schedule.cpp
	g++ -c schedule.cpp

shift.o: shift.cpp
	g++ -c shift.cpp

person.o: person.cpp
	g++ -c person.cpp

clean:
	del main.exe schedule.o main.o

.PHONY: clean all