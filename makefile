CC=g++
CFLAGS=-O3
NAME=Lotka_Volterra

all:
	$(CC) $(NAME).cpp -o $(NAME) $(CFLAGS)
	./$(NAME) > data.dat
	rm *.dat
clear:
	rm *.dat
