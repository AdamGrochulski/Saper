all:
	cc board.c highscore.c levels.c sweeper.c main.c -o game
debug:
	cc -Wall -pedantic board.c highscore.c levels.c sweeper.c main.c -o game
clean:
	@[ -f ./game ] && rm game || true



