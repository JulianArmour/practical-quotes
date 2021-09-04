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

objects = main.o data.o parser.o

practical-quotes : $(objects)
	$(CC) -g -o $@ $^ -lcurl

main.o : data.h

parser.test : test_parser.o parser.o unity.o
	$(CC) -g -o $@ $^

test_parser.o : parser.h

.PHONY : clean
clean :
	$(RM) practical-quotes
	$(RM) *.test
	$(RM) *.o