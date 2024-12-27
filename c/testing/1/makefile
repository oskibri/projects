CC=gcc
out=a.out

.SILENT:
a.out: test.c
	$(CC) -o $@ $<
	./$@ oskar 30

.PHONY:
clean: a.out
	rm -rf $(out)
