default: build
build: 
	g++ -O2 -o Draughts Position.cpp Player.cpp HumanPlayer.cpp RandomAIPlayer.cpp AlphaBetaAIPlayer.cpp Board.cpp Movement.cpp Match.cpp Main.cpp
clean: 
	rm Draughts
