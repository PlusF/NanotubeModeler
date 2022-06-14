CC = c++
CFLAGS = -std=c++14 -Wall -O2 -o create
# CC = g++
# CFLAGS = -O2 -o create
create: create.cpp Atom.cpp Bond.cpp NanoTube.cpp vectools.cpp
	$(CC) $(CFLAGS) create.cpp Atom.cpp Bond.cpp NanoTube.cpp vectools.cpp
