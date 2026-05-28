NAME = fractal_tree

CC = gcc
CFLAGS = -g -Wall -Wextra -std=c99 -pedantic
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

$(NAME): main.c
	$(CC) main.c -o $(NAME) $(CFLAGS) $(LIBS)

clean:
	rm -f $(NAME)

.PHONY: clean