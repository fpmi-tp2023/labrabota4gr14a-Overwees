# Makefile fot lab 4, task 6

bin/program: obj/client.o obj/server.o
	gcc -o bin/program obj/client.o obj/server.o -l sqlite3

obj/client.o: src/client.c
	gcc -o obj/client.o -c src/client.c -l sqlite3

obj/server.o: src/server.c
	gcc -o obj/server.o -c src/server.c -l sqlite3

clean:
	rm -rf obj/*.o bin/program
