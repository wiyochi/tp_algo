OPT = -g -Wall -Wextra
LOG = @echo "\#MAKE"

all: gestion-message

gestion-message: tp1.c LC.o
	gcc -o gestion-message tp1.c LC.o $(OPT)
	$(LOG) "Executable généré"

LC.o: LC.h LC.c
	gcc -o LC.o -c LC.c $(OPT)
	$(LOG) "lib liste chainee généré"

clean:
	rm *.o
	rm gestion-message