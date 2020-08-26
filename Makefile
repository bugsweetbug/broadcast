src = $(wildcard *.c)
tar = $(patsubst %.c, %, $(src))
ALL:$(tar)

$(tar):%:%.c
	gcc -o $@ $< comm.o -Wall

clean:
	rm -rf $(tar)

.PHONY:clean ALL


