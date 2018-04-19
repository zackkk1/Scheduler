all: Schedule

Schedule: Schedule.cpp
	g++ Schedule.cpp -o Schedule

clean:
	del Schedule

.PHONY: clean all