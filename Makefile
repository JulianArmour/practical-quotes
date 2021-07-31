CC = gcc
CFLAGS = \
	-g \
	-ggdb \
	-Og \
	-Wall \
	-Wextra \
	-Wwrite-strings \
	-Wswitch-default \
	-Wswitch-enum \
	-Werror
objects = main.o

practical-quotes : $(objects)
	$(CC) -o $@ $< -lcurl

practical_quotes.o : practical_quotes.c
	gcc -c -o $@ $<

.PHONY : clean
clean :
	rm practical-quotes
	rm *.o