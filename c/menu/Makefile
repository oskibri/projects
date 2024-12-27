menu: src/main.c lib/helper.c
	@clang -o $@ $^ -O3 -Iinclude -Wall -Wextra -pedantic -lncurses

term: term.c
	@clang -o $@ $^ -O3 -Iinclude -Wall -Wextra -pedantic -lncurses -lmenu
