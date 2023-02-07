# Projet Programmation Réseaux - GhostLab

**Compilation et exécution :**
Depuis un premier terminal, en étant dans le dossier du projet, il faut exécuter la commande : make

Cela permettra de compiler le client qui a été codé en Java et de compiler le serveur qui a été codé en C

Ensuite pour l'exécution du serveur et du client, il faut ouvrir deux terminaux, un servira au client et l'autre au serveur.

Dans le premier terminal (coté serveur), il suffit de lancer la commande :
./serveur *portTCP*

exemple : ./serveur 5551

Dans un second terminal (coté client), il suffit de lancer la commande :
java Client <\host> <\portUDPClient> <\portTCP> <\p/r>

exemple : java Client localhost 3333 5551 p

Une fois ces commandes entrées dans les terminaux, vous pouvez commencer à jouer ! Vous rencontrerez le tableau de bord avec les différents choix proposés.

### Les différents fichiers composant le rendu sont :
**Client.java** : Programme principal du client

**Request.java** : Programme gérant les requêtes à envoyer au serveur

**joueur.c** : Programme permettant d'initialiser un joueur.

**labyrinthe.c** : Programme créant le labyrinthe, les fantômes, puis place le joueur et les fantômes dans le labyrinthe de manière totalement aléatoire.

**sendCode.c** : Programme affichant si les informations sont bien envoyées.

**serveur.c** : Programme principal du serveur

Extensions :

Téléportation : Cette extension a été créée mais pas implémentée (elle ne fonctionne pas). Le but initial de cette extention est de téléporter le joueur aléatoirement quelque part dans le labyrinthe.

Merci de votre attention, nous vous souhaitons une agréable partie sur GhostLab !

Alaia, Ibrahima et Davy.
