RM = rm -f
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

test_parser : test_parser.o parser.c unity.o
	$(CC) -o $@ $^

test_parser.o : parser.h

.PHONY : clean
clean :
	$(RM) practical-quotes
	$(RM) test_parser
	$(RM) *.o