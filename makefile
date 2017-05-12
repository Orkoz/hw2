# This is a makefile for the airport project

CC = gcc
CFLAGS = -g -Wall
CCLINK = $(CC)
OBJS= main.o airport.o flight.o runway.o

airport: $(OBJS)
	$(CCLINK) -o airport $(OBJS) $(LIBS)

maim.o: main.c airport.h runway.h  flight.h ex2.h
airport.o: airport.c airport.h runway.h  flight.h ex2.h
runway.o:runway.c runway.h  flight.h ex2.h
flight.o:flight.c flight.h ex2.h