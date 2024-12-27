cc=clang

all: main

%: %.c
	$(cc) --static -g -o $@ $^ -lc

leafgrep: main.c
	$(cc) --static -Ofast -o $@ $^ -lc
