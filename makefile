CC=g++
CFLAGS=-O3
NAME=EarthQuake

all:
	$(CC) $(NAME).cpp -o $(NAME) $(CFLAGS)
	./$(NAME) > data.dat
	python2 plot.py
	rm *.dat
clear:
	rm *.dat
