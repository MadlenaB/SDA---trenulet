build:
	gcc -fsanitize=undefined -o tema1 main.c functii_tren.c
run:
	./tema1
clean:
	rm tema1
valgrind:
	valgrind --leak check=yes --track-origins=yes ./tema1
