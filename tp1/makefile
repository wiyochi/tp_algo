OPT = -g -Wall -Wextra -Wunused-parameter
LOG = @echo "\#MAKE"

tp1: tp1.c LC.o
	gcc -o tp1 tp1.c LC.o $(OPT)
	$(LOG) "Executable généré"

LC.o: LC.h LC.c
	gcc -o LC.o -c LC.c $(OPT)
	$(LOG) "lib liste chainee généré"

clean:
	rm *.o
	rm tp1