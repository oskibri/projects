cc=clang
mdbconf=$(shell mariadb-config --cflags --libs)

all: mdb

%: %.c
	$(cc) -o $@ $^ $(shell mariadb-config --cflags --libs)
