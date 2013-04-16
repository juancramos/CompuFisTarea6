a.out: tarea6.o
	@cc -lm tarea6.o 
	@./a.out
	@python dibujar.py
	@rm -f *.dat

main.o: tarea6.c
	@cc -c tarea6.c

all: a.out

clean: 
	@rm -f *.o
	@rm -f a.out
	@rm -f *.jpg

