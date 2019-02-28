CC = gcc
CFLAGS = -ansi -Wall -g -O0 -Wwrite-strings -Wshadow \
         -pedantic-errors -fstack-protector-all 
PROGS = student_tests

all: $(PROGS)



student_tests: student_tests.o calendar.o my_memory_checker_216.o
	$(CC) student_tests.o calendar.o my_memory_checker_216.o -o student_tests

my_memory_checker_216.o: my_memory_checker_216.h my_memory_checker_216.c
	$(CC) $(CFLAGS) -c my_memory_checker_216.c

calendar.o: calendar.h calendar.c event.h
	$(CC) $(CFLAGS) -c calendar.c


student_tests.o: student_tests.c calendar.h event.h my_memory_checker_216.h
	$(CC) $(CFLAGS) -c student_tests.c

clean:
	@echo "Cleaning my system"
	@rm -f *.o $(PROGS) a.out


