DIRS = src include
SEARCHCPP = $(addsuffix /*.cpp ,$(DIRS))
SRCS = $(wildcard $(SEARCHC))
vpath %.cpp $(DIRS)
vpath %.hpp $(DIRS)

reversi : main.o board.o tile.o render.o standardReferee.o fastPlayer.o
	g++ -o reversi *.o

main.o : main.cpp standardReferee.hpp fastPlayer.hpp board.hpp render.hpp
	g++ -c -O3 src/main.cpp

board.o : board.cpp board.hpp tile.hpp
	g++ -c -O3 src/board.cpp

tile.o : tile.cpp tile.hpp
	g++ -c -O3 src/tile.cpp

render.o : render.cpp render.hpp board.hpp tile.hpp
	g++ -c -O3 src/render.cpp

standardReferee.o : standardReferee.cpp standardReferee.hpp referee.hpp board.hpp tile.hpp
	g++ -c -O3 src/standardReferee.cpp

fastPlayer.o : fastPlayer.cpp fastPlayer.hpp player.hpp board.hpp tile.hpp referee.hpp render.hpp
	g++ -c -O3 src/fastPlayer.cpp

clean:
	rm -f *.o