CC = clang
CFLAGS = -Wall -Iinc -Ofast -static
SRCS = src/main.c src/file_utils.c src/traversal.c
OBJ_DIR = obj
OBJS = $(SRCS:src/%.c=obj/%.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) $(EXEC)
