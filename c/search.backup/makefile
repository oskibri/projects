CC = clang
CFLAGS = -Wall -Iinc
SRCS = src/main.c src/file_utils.c src/traversal.c
OBJS = $(SRCS:.c=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(EXEC)
