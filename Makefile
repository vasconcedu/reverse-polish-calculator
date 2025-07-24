ritchie-4-3: ritchie-4-3.c calcstk.o 
	cc ritchie-4-3.c calcstk.o -o ritchie-4-3 -lm

calcstk.o: calcstk.c
	cc -c calcstk.c -o calcstk.o

clean:
	rm calcstk.o ritchie-4-3
