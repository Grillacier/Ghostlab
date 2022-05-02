CC = gcc
CCFLAGS = -Wall
JC = javac

all:
	$(JC) Client/src/Client.java
	$(CC) $(CCFLAGS) -pthread Serveur/serveur.c -o serveur
clean:
	rm Serveur/server Client/src/*.class
