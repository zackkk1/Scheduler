all: main.exe

main.exe: schedule.o main.o
	g++ schedule.o main.o -o main.exe

schedule: schedule.cpp
	g++ -c schedule.cpp

clean:
	del main.exe schedule.o main.o

.PHONY: clean all