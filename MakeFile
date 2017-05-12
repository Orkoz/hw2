CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS= main.o airport.o flight.o runway.o

maim.o: main.c airport.c airport.h airport.c runway.c runway.h flight.c flight.h ex2.h
airport.o: airport.c airport.h airport.c runway.c runway.h flight.c flight.h ex2.h
runway.o:runway.c runway.h flight.c flight.h ex2.h
flight.o:flight.c flight.h ex2.hs