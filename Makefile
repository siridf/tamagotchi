all: bin/mainPersonnage bin/mainMemory bin/mainJeu bin/mainSdlJeu

CC = g++ -g -Wall `sdl2-config --cflags --libs`

bin/mainMemory: obj/mainMemory.o obj/Memory.o
	$(CC) obj/mainMemory.o obj/Memory.o -o bin/mainMemory

bin/mainJeu : obj/mainJeu.o obj/Jeu.o obj/Personnage.o obj/Memory.o
	$(CC) obj/mainJeu.o obj/Jeu.o obj/Personnage.o obj/Memory.o -o bin/mainJeu

bin/mainPersonnage: obj/mainPersonnage.o obj/Personnage.o
	$(CC) obj/mainPersonnage.o obj/Personnage.o -o bin/mainPersonnage


bin/mainSdlJeu : obj/mainSdlJeu.o obj/sdlJeu.o obj/Jeu.o obj/Personnage.o obj/Memory.o
	$(CC) obj/mainSdlJeu.o obj/sdlJeu.o obj/Jeu.o obj/Personnage.o obj/Memory.o -o bin/mainSdlJeu -lSDL2 -lSDL2_image -lSDL2_ttf


obj/mainMemory.o: src/mainMemory.cpp
	$(CC) -c src/mainMemory.cpp -o obj/mainMemory.o

obj/Memory.o: src/Memory.h src/Memory.cpp
	$(CC) -c src/Memory.cpp -o obj/Memory.o


obj/mainPersonnage.o: src/mainPersonnage.cpp
	$(CC) -c src/mainPersonnage.cpp -o obj/mainPersonnage.o

obj/Personnage.o: src/Personnage.h src/Personnage.cpp
	$(CC) -c src/Personnage.cpp -o obj/Personnage.o


obj/mainJeu.o: src/mainJeu.cpp src/Jeu.h src/Personnage.h src/Memory.h
	$(CC) -c src/mainJeu.cpp -o obj/mainJeu.o

obj/Jeu.o: src/Jeu.h src/Jeu.cpp src/Personnage.h src/Memory.h
	$(CC) -c src/Jeu.cpp -o obj/Jeu.o 


obj/sdlJeu.o: src/sdlJeu.h src/sdlJeu.cpp src/Jeu.h src/Personnage.h src/Memory.h
	$(CC) -c src/sdlJeu.cpp -o obj/sdlJeu.o -lSDL2 -lSDL2_image -lSDL2_ttf

obj/mainSdlJeu.o : src/mainSdlJeu.cpp src/sdlJeu.h src/Jeu.h src/Personnage.h src/Memory.h
	$(CC) -c src/mainSdlJeu.cpp -o obj/mainSdlJeu.o

clean:
	rm obj/*.o bin/mainPersonnage bin/mainMemory bin/mainJeu bin/mainSdlJeu 
