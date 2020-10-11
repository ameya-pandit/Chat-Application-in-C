#Team 04 makefile for ChessGame
#This file will make all of the object files and the executable


CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -g -c
LFLAGS = -ansi -std=c99 -Wall -lm
AR     = ar rc
RANLIB = ranlib

all: ChessGame


TestMv:

#Target to generate ChessGame.o
Main.o: Main.c ChessStruct.h Ai.h ChessStruct.h 
	$(CC) $(CFLAGS) Main.c -o Main.o

Moves.o: Moves.c Moves.h
	$(CC) $(CFLAGS) Moves.c -o Moves.o

ChessIO.o: ChessIO.c ChessIO.h ChessTree.h Ai.h
	$(CC) $(CFLAGS) ChessIO.c -o ChessIO.o

Moves_test.o: Moves_test.c
	$(CC) $(CFLAGS) Moves_test.c -o Moves_test.o

PlayersMove.o: playersmove2.c playersmove.h
	$(CC) $(CFLAGS) playersmove2.c -o PlayersMove.o

#Target to generate MovesList.o
MovesList.o: MovesList.c MovesList.h ChessStruct.h ChessTree.h
	$(CC) $(CFLAGS) MovesList.c -o MovesList.o

#Target to generate ChessTree.o
ChessTree.o: ChessTree.c ChessTree.h ChessStruct.h
	$(CC) $(CFLAGS) ChessTree.c -o ChessTree.o

#Target to generate Ai.o
Ai.o: Ai.c Ai.h ChessTree.h ChessStruct.h
	$(CC) $(CFLAGS) Ai.c -o Ai.o

#Target to generate GameLog.o
GameLog.o: GameLog.c GameLog.h
	$(CC) $(CFLAGS) GameLog.c -o GameLog.o

#Target to generate Board.o
Board.o: Board.c Board.h ChessStruct.h
	$(CC) $(CFLAGS) Board.c -o Board.o

#Target to generate checkmoves.0
CheckMoves.o: checkmove.c checkmove.h 
	$(CC) $(CFLAGS) checkmove.c -o CheckMoves.o

#Target to generate ChessGame executable
ChessGame: ChessIO.o ChessTree.o MovesList.o Ai.o Board.o Main.o GameLog.o Moves.o PlayersMove.o
	$(CC) $(LFLAGS) Main.o ChessTree.o Moves.o MovesList.o GameLog.o Ai.o Board.o ChessIO.o PlayersMove.o -o ../bin/ChessGame

TestMv: Moves.o ChessTree.o Board.o MovesList.o PlayersMove.o Moves_test.o ChessIO.o Ai.o
	$(CC) $(LFLAGS) Moves_test.o Ai.o Moves.o MovesList.o ChessTree.o Board.o ChessIO.o -o TestMv

Tar: 
	gtar cvzf ../Chess_V1.0_src.tar.gz ../bin ../doc ../src ../README.md ./Makefile ../Install.txt ../Copyright.txt

#Target to clean the directory
clean:
	
	rm -f *.o 
	rm -f ChessGame
	rm -f ../bin/LogTest.txt
	rm -f ../bin/ChessGame
	rm -f TestMv
	rm -f ../bin/ChessGame



