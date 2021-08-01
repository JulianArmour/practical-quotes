CC = gcc
CFLAGS = \
	-std=c99 \
	-g \
	-ggdb \
	-Og \
	-Wall \
	-Wextra \
	-Wwrite-strings \
	-Werror
objects = main.o data.o

practical-quotes : $(objects)
	$(CC) -o $@ $^ -lcurl

main.o : data.h

.PHONY : clean
clean :
	rm practical-quotes
	rm *.o