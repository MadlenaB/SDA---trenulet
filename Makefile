build:
	gcc -o tren main.c functii_tren.c
run:
	./tren
clean:
	rm tren
valgrind:
	valgrind --leak check=yes --track-origins=yes ./tren 