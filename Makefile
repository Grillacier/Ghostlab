CC = gcc
CCFLAGS = -Wall
JC = javac

all:
	$(JC) -d . Client/src/Requests.java Client/src/Client.java
	$(CC) $(CCFLAGS) -pthread Serveur/serveur.c -o serveur

clean:
	rm serveur *.class