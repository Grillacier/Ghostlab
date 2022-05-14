import java.io.BufferedReader;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.util.Scanner;

public class Requests {
    private String id; //str de 8 char
    private String port; //port UDP du client

    public String getId() {
        return id;
    }

    public String getPort() {
        return port;
    }

    public void setId(String id) {
        this.id = id;
    }

    public void setPort(String port) {
        this.port = port;
    }

    //fonctions appelant les autres fonctions
    //fonctions avant le début de la partie
    public void beforeGame(BufferedReader br, PrintWriter pw) throws Exception {
        receiveGames(br);
        boolean start = false; //le joueur n'est pas encore dans une partie
        while (!start) {
            System.out.println("Que voulez-vous faire ?");
            System.out.println("1. Créer une partie");
            System.out.println("2. Rejoindre une partie");
            System.out.println("3. Demander la liste des parties non commencées");
            System.out.println("4. Se désinscrire de la partie");
            System.out.println("5. Demander la taille du labyrinthe");
            System.out.println("6. Demander la liste des joueurs");
            System.out.println("7. Commencer à jouer");

            Scanner sc = new Scanner(System.in);
            int choice = sc.nextInt();
            switch (choice) {
                case 1:
                    newGame(pw);
                    receiveRegok(br);
                    receiveRegno(br);
                    break;
                case 2:
                    joinGame(pw);
                    receiveRegok(br);
                    receiveRegno(br);
                    break;
                case 3:
                    listGames(pw);
                    receiveGames(br);
                    break;
                case 4:
                    unregister(pw);
                    receiveUnrok(br);
                    receiveDunno(br);
                    break;
                case 5:
                    askSize(pw);
                    receiveSize(br);
                    receiveDunno(br);
                    break;
                case 6:
                    listPlayers(pw);
                    receiveList(br);
                    receiveDunno(br);
                    break;
                case 7:
                    startGame(pw);
                    start = true;
                    break;
                default:
                    System.out.println("Veuillez entrer un nombre entre 1 et 7");
                    break;
            }
        }
    }


    //TCP
    //messages reçus du serveur
    //recevoir le nombre de parties pas commencées
    //[GAMES_n***]
    public void receiveGames(BufferedReader br) throws Exception {
        char[] buffer = new char[10]; //pas de caractère de fin de ligne donc br.readline() ne fonctionne pas
        br.read(buffer, 0, 10); //écrit le contenu de br dans buffer
        String message = new String(buffer); //crée un String à partir du buffer
        int nbGames = buffer[6]; //récupère le 6e caractère du buffer (le nombre de parties)
        System.out.println(message.substring(0, 6) + nbGames + message.substring(7)); //affiche le message
        System.out.println("Il y a " + nbGames + " parties pas commencées");
        if (nbGames > 0)
            receiveOgame(nbGames, br); //affiche toutes les parties
    }

    //recevoir les parties disponibles
    //[OGAME␣m␣s***]
    public void receiveOgame(int nbGames, BufferedReader br) throws Exception {
        char[] buffer = new char[12];
        for (int i = 0; i < nbGames; i++) {
            br.read(buffer, 0, 12);
            String message = new String(buffer);
            int m = buffer[6];
            int nbPlayers = buffer[8];
            System.out.println(message.substring(0, 6) + m + message.charAt(7) + nbPlayers + message.substring(9));
            System.out.println("Partie " + m + " : " + nbPlayers + " joueurs");
        }
    }

    //recevoir message de confirmation d'inscription
    //[REGOK␣m***]
    public void receiveRegok(BufferedReader br) throws Exception {
        char[] buffer = new char[10];
        br.read(buffer, 0, 10);
        String message = new String(buffer);
        int game = buffer[6];
        System.out.println(message.substring(0, 6) + game + message.substring(7));
        System.out.println("Vous êtes inscrit à la partie " + game);
    }

    //recevoir message d'échec d'inscription
    //[REGNO***]
    public void receiveRegno(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
        System.out.println("Vous n'êtes pas inscrit à la partie");
    }

    //recevoir message de confirmation de désinscription
    //[UNROK␣m***]
    public void receiveUnrok(BufferedReader br) throws Exception {
        char[] buffer = new char[10];
        br.read(buffer, 0, 10);
        String message = new String(buffer);
        int game = buffer[6];
        System.out.println(message.substring(0, 6) + game + message.substring(7));
        System.out.println("Vous êtes désinscrit de la partie " + game);
    }

    //recevoir message d'erreur
    //[DUNNO***]
    public void receiveDunno(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
        System.out.println("Vous n'êtes inscrit à aucune partie");
    }

    //recevoir la taille du labyrinthe
    //[SIZE!␣m␣h␣w***]
    public void receiveSize(BufferedReader br) throws Exception {
        char[] buffer = new char[16];
        br.read(buffer, 0, 16);
        String message = new String(buffer);
        int game = buffer[6];
        short height = (short) (buffer[8] + buffer[9]);
        short width = (short) (buffer[11] + buffer[12]);
        System.out.println(message.substring(0, 6) + game + message.charAt(7) + height
                + message.charAt(10) + width + message.substring(13));
        System.out.println("La taille du labyrinthe est de " + height + "x" + width);
    }

    //recevoir la liste des joueurs d'une partie
    //[LIST!␣m␣s***]
    public void receiveList(BufferedReader br) throws Exception {
        char[] buffer = new char[12];
        br.read(buffer, 0, 12);
        String message = new String(buffer);
        int m = buffer[6];
        int s = buffer[8];
        System.out.println(message.substring(0, 6) + m + message.charAt(7) + s + message.substring(9));
        System.out.println("Partie " + m + " : " + s + " joueurs");
        receivePlayr(s, br);
    }

    //recevoir les joueurs d'une partie
    //[PLAYR␣id***]
    public void receivePlayr(int nbPlayers, BufferedReader br) throws Exception {
        char[] buffer = new char[17];
        for (int i = 0; i < nbPlayers; i++) {
            br.read(buffer, 0, 17);
            String message = new String(buffer);
            System.out.println(message);
            System.out.println("Joueur " + nbPlayers+1 + " : " + message.substring(7));
        }
    }

    //recevoir le message de début de partie
    //[WELCO␣m␣h␣w␣f␣ip␣port***]
    public void receiveWelco(BufferedReader br) throws Exception {
        char[] buffer = new char[39];
        br.read(buffer, 0, 39);
        String message = new String(buffer);
        int game = buffer[6];
        short height = (short) (buffer[8] + buffer[9]);
        short width = (short) (buffer[11] + buffer[12]);
        int ghosts = buffer[14];
        System.out.println(message.substring(0,6) + game + message.charAt(7) + height
                + message.charAt(10) + width + message.charAt(13) + ghosts + message.substring(15));
        System.out.println("Bienvenue.\n La partie " + game + " a commencé avec " + ghosts + " fantômes");
        System.out.println("La taille du labyrinthe est de " + height + "x" + width);
        System.out.println("Adresse de multi-diffusion de la partie : " + message.substring(16, 32));
        System.out.println("Port de multi-diffusion de la partie : " + message.substring(33, 37));
    }

    //recevoir position dans le labyrinthe
    //[POSIT␣id␣x␣y***]
    public void receivePosit(BufferedReader br) throws Exception {
        char[] buffer = new char[25];
        br.read(buffer, 0, 25);
        String message = new String(buffer);
        System.out.println(message);
        System.out.println("Joueur " + message.substring(6, 15) + " est à la position (" + message.substring(15, 18)
                        + "," + message.substring(19, 22) + ")");
    }

    //recevoir confirmation de déplacement si on n'a pas rencontré de fantômes
    //[MOVE!␣x␣y***]
    public void receiveMove(BufferedReader br) throws Exception {
        char[] buffer = new char[20];
        br.read(buffer, 0, 20);
        String message = new String(buffer);
        System.out.println(message);
        System.out.println("Vous êtes maintenant à la position (" + message.substring(6, 9) + ","
                + message.substring(10, 13) + ")");
    }

    //recevoir la position et le nouveau nombre de points
    //[MOVEF␣x␣y␣p***]
    public void receiveMovef(BufferedReader br) throws Exception {
        char[] buffer = new char[21];
        br.read(buffer, 0, 21);
        String message = new String(buffer);
        System.out.println(message);
        System.out.println("Vous êtes maintenant à la position (" + message.substring(6, 9) + ","
                + message.substring(10, 13) + ")");
        System.out.println("Vous avez " + message.substring(14, 18) + " points");
    }

    //recevoir message d'au revoir
    //[GOBYE***]
    public void receiveGobye(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
        System.out.println("Au revoir");
    }

    //recevoir le nombre de joueurs présents dans la partie
    //[GLIS!␣s***]
    public void receiveGlis(BufferedReader br) throws Exception {
        char[] buffer = new char[10];
        br.read(buffer, 0, 10);
        String message = new String(buffer);
        int s = buffer[6];
        System.out.println(message.substring(0, 6) + s + message.substring(7));
        System.out.println("Il y a actuellement " + s + " joueurs dans la partie");
        receiveGplyr(s, br);
    }

    //recevoir les informations des autres joueurs
    //[GPLYR␣id␣x␣y␣p***]
    public void receiveGplyr(int nbPlayers, BufferedReader br) throws Exception {
        char[] buffer = new char[30];
        for (int i = 0; i < nbPlayers; i++) {
            br.read(buffer, 0, 30);
            String message = new String(buffer);
            System.out.println(message);
            System.out.println("Joueur " + message.substring(6, 15) + " est à la position (" + message.substring(16, 19)
                    + "," + message.substring(20, 23) + ")");
            System.out.println("Il a " + message.substring(24, 28) + " points");
        }
    }

    //recevoir confirmation de multi-diffusion
    //[MALL!***]
    public void receiveMall(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
        System.out.println("Votre message a bien été multi-diffusé");
    }

    //recevoir confirmation d'envoi de message
    //[SEND!***]
    public void receiveSend(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
        System.out.println("Votre message a bien été envoyé");
    }

    //recevoir message de non envoi de message
    //[NSEND***]
    public void receiveNsend(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
        System.out.println("Votre message n'a pas pu être envoyé");
    }


    //messages envoyés au serveur
    //créer une partie
    public void newGame(PrintWriter pw) throws Exception {
        pw.print("NEWPL " + this.id + " " + this.port + "***");
        pw.flush();
    }

    //rejoindre une partie
    public void joinGame(PrintWriter pw) throws Exception {
        Scanner game = new Scanner(System.in);
        System.out.println("Enter the game you want to join: ");
        byte gameNumber = (byte) game.nextInt();
        pw.print("REGIS " + this.id + " " + this.port + " " + (char) gameNumber + "***");
        pw.flush();
    }

    //commencer une partie
    public void startGame(PrintWriter pw) throws Exception {
        pw.print("START***");
        pw.flush();
    }

    //se désinscrire d'une partie
    public void unregister(PrintWriter pw) throws Exception {
        pw.print("UNREG***");
        pw.flush();
    }

    //demander la taille du labyrinthe
    public void askSize(PrintWriter pw) throws Exception {
        Scanner game = new Scanner(System.in);
        System.out.println("Which game do you want to know the size of? ");
        byte gameNumber = (byte) game.nextInt();
        pw.print("SIZE? " + (char) gameNumber + "***");
        pw.flush();
    }

    //demander la liste des joueurs inscrits
    public void listPlayers(PrintWriter pw) throws Exception {
        Scanner game = new Scanner(System.in);
        System.out.println("Which game do you want to know the players of? ");
        byte gameNumber = (byte) game.nextInt();
        pw.print("LIST? " + (char) gameNumber + "***");
        pw.flush();
    }

    //demander la liste des parties pas commencées
    public void listGames(PrintWriter pw) throws Exception {
        pw.print("GAME?***");
        pw.flush();
    }

    //se déplacer dans le labyrinthe
    public void move(PrintWriter pw) throws Exception {
        String directionString = "";
        Scanner dir = new Scanner(System.in);

        while (directionString.equals("")) {
            System.out.println("Which direction do you want to go? ");
            System.out.println("1. Up");
            System.out.println("2. Down");
            System.out.println("3. Left");
            System.out.println("4. Right");
            int direction = dir.nextInt();

            switch (direction) {
                case 1:
                    directionString = "UPMOV ";
                    break;
                case 2:
                    directionString = "DOMOV ";
                    break;
                case 3:
                    directionString = "LEMOV ";
                    break;
                case 4:
                    directionString = "RIMOV ";
                    break;
                default:
                    System.out.println("Wrong direction");
                    break;
            }
        }

        String d = "";
        while (d.length() < 4) {
            System.out.println("How many steps do you want to go? ");
            d = dir.next();
            switch (d.length()) {
                case 1:
                    d = "00" + d;
                    break;
                case 2:
                    d = "0" + d;
                    break;
                case 3:
                    break;
                default:
                    System.out.println("Wrong number of steps");
                    break;
            }
        }

        pw.print(directionString + d + "***");
        pw.flush();
    }

    //abandonner partie
    public void iquit(PrintWriter pw) throws Exception {
        pw.print("IQUIT***");
        pw.flush();
    }

    //demander la liste des joueurs présents
    public void listPlayersOnline(PrintWriter pw) throws Exception {
        pw.print("GLIS?***");
        pw.flush();
    }

    //demander à envoyer un message de 200 caractères maximum à tous les joueurs
    public void sendMessage(PrintWriter pw) throws Exception {
        Scanner message = new Scanner(System.in);
        System.out.println("What message do you want to send? ");
        String mess = message.nextLine();
        if (mess.length() > 200)
            mess = mess.substring(0, 200);
        pw.print("MALL? " + mess + "***");
        pw.flush();
    }

    //demander à envoyer un message de 200 caractères maximum à un joueur
    public void sendMessageToPlayer(PrintWriter pw) throws Exception {
        Scanner message = new Scanner(System.in);
        System.out.println("What message do you want to send? ");
        String mess = message.nextLine();
        if (mess.length() > 200)
            mess = mess.substring(0, 200);
        System.out.println("Who do you want to send it to? ");
        String id = message.nextLine();
        pw.print("SEND? " + id + " " + mess + "***");
        pw.flush();
    }



    //UDP
    //recevoir la nouvelle position d'un fantôme qui s'est déplacé
    //[GHOST␣x␣y+++]
    public void ghost(DatagramSocket dso) throws Exception {
        byte[] data = new byte[16];
        DatagramPacket paquet = new DatagramPacket(data, data.length);
        dso.receive(paquet);
        String message = new String(paquet.getData(), 0, paquet.getLength());
        System.out.println(message);
    }

    //recevoir le nouveau score d'un joueur qui vient de capturer un fantôme
    //[SCORE␣id␣p␣x␣y+++]
    public void score(DatagramSocket dso) throws Exception {
        byte[] data = new byte[30];
        DatagramPacket paquet = new DatagramPacket(data, data.length);
        dso.receive(paquet);
        String message = new String(paquet.getData(), 0, paquet.getLength());
        System.out.println(message);
    }

    //recevoir un message multi-diffusé par un autre joueur
    //[MESSA␣id␣mess+++]
    public void messa(DatagramSocket dso) throws Exception {
        byte[] data = new byte[218];
        DatagramPacket paquet = new DatagramPacket(data, data.length);
        dso.receive(paquet);
        String message = new String(paquet.getData(), 0, paquet.getLength());
        System.out.println(message);
    }

    //recevoir message de fin de partie
    //[ENDGA␣id␣p+++]
    public void endga(DatagramSocket dso) throws Exception {
        byte[] data = new byte[22];
        DatagramPacket paquet = new DatagramPacket(data, data.length);
        dso.receive(paquet);
        String message = new String(paquet.getData(), 0, paquet.getLength());
        System.out.println(message);
    }

    //recevoir message privé
    //[MESSP␣id2␣mess+++]
    public void messp(DatagramSocket dso) throws Exception {
        byte[] data = new byte[218];
        DatagramPacket paquet = new DatagramPacket(data, data.length);
        dso.receive(paquet);
        InetSocketAddress id = (InetSocketAddress) paquet.getSocketAddress();
        String message = new String(paquet.getData(), 0, paquet.getLength());
        System.out.println(message.substring(0,6) + id.getHostName() + message.substring(14));
    }
}
