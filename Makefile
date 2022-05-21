CC = gcc
CCFLAGS = -Wall
JC = javac

all:
	$(JC) -d . Client/src/Requests.java Client/src/Client.java
	$(CC) $(CCFLAGS) -pthread Serveur/sendCode.c Serveur/messageUDP.c Serveur/labyrinthe.c Serveur/joueur.c Serveur/gameList.c Serveur/serveur.c -o serveur

clean:
	rm serveur *.class