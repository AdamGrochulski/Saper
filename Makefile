all:
	cc board.c highscore.c levels.c sweeper.c main.c -o game
	./game
	rm game
debug:
	cc -Wall -pedantic board.c highscore.c levels.c sweeper.c main.c -o debug_mode 
	./debug_mode
	rm debug_mode



