import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    private String id;
    private String port;

    public Client(String id, String port) {
        this.id = id;
        this.port = port;
    }


    //messages reçus du serveur
    //recevoir un message sans paramètre
    ////[REGNO***] [DUNNO***] [GOBYE***] [MALL!***] [SEND!***] [NSEND!***]
    public void receiveMess(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
    }

    //recevoir le nombre de parties pas commencées
    //[GAMES_n***]
    public void receiveGames(BufferedReader br) throws Exception {
        char[] buffer = new char[10]; //pas de caractère de fin de ligne donc il br.readline() ne fonctionne pas
        br.read(buffer, 0, 10); //écrit le contenu de br dans buffer
        String message = new String(buffer); //crée un String à partir du buffer
        int nbGames = buffer[6]; //récupère le 6e caractère du buffer (le nombre de parties)
        System.out.println(message.substring(0, 6) + nbGames + message.substring(7)); //affiche le message
        receiveOgame(nbGames, br);
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
    }

    //recevoir message d'échec d'inscription
    //[REGNO***]
    /*
    public void receiveRegno(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
    }
    */

    //identique à receiveRegok()
    //recevoir message de confirmation de désinscription
    //[UNROK␣m***]
    public void receiveUnrok(BufferedReader br) throws Exception {
        char[] buffer = new char[10];
        br.read(buffer, 0, 10);
        String message = new String(buffer);
        int game = buffer[6];
        System.out.println(message.substring(0, 6) + game + message.substring(7));
    }

    //identique à receiveRegno()
    //recevoir message d'erreur
    //[DUNNO***]
    /*
    public void receiveDunno(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
    }
     */

    //recevoir la taille du labyrinthe
    //[SIZE!␣m␣h␣w***]
    public void receiveSize(BufferedReader br) throws Exception {
        char[] buffer = new char[16];
        br.read(buffer, 0, 16);
        String message = new String(buffer);
        int game = buffer[6];
        int height = buffer[8];
        int height2 = buffer[9];
        int width = buffer[11];
        int width2 = buffer[12];
        System.out.println(message.substring(0, 6) + game + message.charAt(7) + height + height2
                + message.charAt(10) + width + width2 + message.substring(13));
    }
    /*
    public void receiveSize(BufferedReader br) throws Exception {
        char[] buffer = new char[14];
        br.read(buffer, 0, 14);
        String message = new String(buffer);
        int game = buffer[6];
        int height = buffer[8];
        int width = buffer[10];
        System.out.println(message.substring(0, 6) + game + message.charAt(7) + height
                + message.charAt(9) + width + message.substring(11));
    }
    */

    //recevoir la liste des joueurs d'une partie
    //[LIST!␣m␣s***]
    public void receiveList(BufferedReader br) throws Exception {
        char[] buffer = new char[12];
        br.read(buffer, 0, 12);
        String message = new String(buffer);
        int game = buffer[6];
        int nbPlayers = buffer[8];
        System.out.println(message.substring(0, 6) + game + message.charAt(7) + nbPlayers + message.substring(9));
        receivePlayr(nbPlayers, br);
    }

    //recevoir les joueurs d'une partie
    //[PLAYR␣id***]
    public void receivePlayr(int nbPlayers, BufferedReader br) throws Exception {
        char[] buffer = new char[17];
        for (int i = 0; i < nbPlayers; i++) {
            br.read(buffer, 0, 17);
            String message = new String(buffer);
            System.out.println(message);
        }
    }

    //recevoir le message de début de partie
    //[WELCO␣m␣h␣w␣f␣ip␣port***]
    public void receiveWelco(BufferedReader br) throws Exception {
        char[] buffer = new char[39];
        br.read(buffer, 0, 39);
        String message = new String(buffer);
        int game = buffer[6];
        int height = buffer[8];
        int height2 = buffer[9];
        int width = buffer[11];
        int width2 = buffer[12];
        int ghosts = buffer[14];
        System.out.println(message.substring(0,6) + game + message.charAt(7) + height + height2
        + message.charAt(10) + width + width2 + message.charAt(13) + ghosts + message.substring(15));
    }
    /*
    public void receiveWelco(BufferedReader br) throws Exception {
        char[] buffer = new char[20];
        br.read(buffer, 0, 20);
        String message = new String(buffer);
        int game = buffer[6];
        int height = buffer[8];
        int width = buffer[10];
        int ghosts = buffer[12];
        int ip = buffer[14];
        int port = buffer[16];
        System.out.println(message.substring(0, 6) + game + message.charAt(7) + height + message.charAt(9)
                + width + message.charAt(11) + ghosts + message.charAt(13) + ip + message.charAt(15)
                + port + message.substring(17));
    }
    */

    //recevoir position dans le labyrinthe
    //[POSIT␣id␣x␣y***]
    public void receivePosit(BufferedReader br) throws Exception {
        char[] buffer = new char[25];
        br.read(buffer, 0, 25);
        String message = new String(buffer);
        System.out.println(message);
    }
    /*
    public void receivePosit(BufferedReader br) throws Exception {
        char[] buffer = new char[14];
        br.read(buffer, 0, 14);
        String message = new String(buffer);
        int id = buffer[6];
        int x = buffer[8];
        int y = buffer[10];
        System.out.println(message.substring(0, 6) + id + message.charAt(7) + x + message.charAt(9)
                + y + message.substring(11));
    }
    */

    //recevoir message d'au revoir
    //[GOBYE***]
    /*
    public void receiveGobye(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
    }
     */

    //recevoir le nombre de joueurs présents dans la partie
    //[GLIS!␣s***]
    public void receiveGlis(BufferedReader br) throws Exception {
        char[] buffer = new char[10];
        br.read(buffer, 0, 10);
        String message = new String(buffer);
        int s = buffer[6];
        System.out.println(message.substring(0, 6) + s + message.substring(7));
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
        }
    }

    //recevoir confirmation de multi-diffusion
    //[MALL!***]
    /*
    public void receiveMall(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
    }
     */

    //recevoir confirmation d'envoi de message
    //[SEND!***]
    /*
    public void receiveSend(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
    }
     */

    //recevoir message de non envoie de message
    //[NSEND***]
    /*
    public void receiveNsend(BufferedReader br) throws Exception {
        char[] buffer = new char[8];
        br.read(buffer, 0, 8);
        String message = new String(buffer);
        System.out.println(message);
    }
     */


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


    public static void main(String[] args) {
        if (args.length != 3) {
            System.out.println("Usage: java Client <host> <portUDPClient> <portTCP>");
        }

        else {
        //demande son id à l'utilisateur
        Scanner name = new Scanner(System.in);
        System.out.println("Enter your name: ");
        String id = name.nextLine() + "12345678";
        id = id.substring(0, 8);

            try {
                int port = Integer.parseInt(args[2]);
                Socket socket = new Socket(args[0], port);
                BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

                Client client = new Client(id, args[1]);
                while (true) {
                    System.out.println("What do you want to do? ");
                    System.out.println("1. Create a new game");
                    System.out.println("2. Join a game");
                    System.out.println("3. Start a game");
                    System.out.println("4. Unregister from a game");
                    System.out.println("5. Ask the size of a game");
                    System.out.println("6. Ask the list of players of a game");
                    System.out.println("7. Ask the list of games");
                    System.out.println("8. Quit");

                    Scanner sc = new Scanner(System.in);
                    int choice = sc.nextInt();
                    switch (choice) {
                        case 1:
                            client.newGame(pw);
                            break;
                        case 2:
                            client.joinGame(pw);
                            break;
                        case 3:
                            client.startGame(pw);
                            break;
                        case 4:
                            client.unregister(pw);
                            break;
                        case 5:
                            client.askSize(pw);
                            break;
                        case 6:
                            client.listPlayers(pw);
                            break;
                        case 7:
                            client.listGames(pw);
                            break;
                        case 8:
                            System.out.println("Goodbye!");
                            System.exit(0);
                            break;
                        default:
                            System.out.println("Invalid choice");
                    }
                }
                //br.close();
                //pw.close();
                //socket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
