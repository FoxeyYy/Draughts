default: build
build: 
	g++ -o Draughts Position.cpp Player.cpp Board.cpp Movement.cpp Match.cpp Main.cpp
clean: 
	rm Draughts