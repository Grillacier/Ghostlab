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

    //recevoir le nombre de parties pas commencées
    public void receiveGames(BufferedReader br) throws Exception {
        char[] buffer = new char[10];
        br.read(buffer, 0, 10);
        String message = new String(buffer);
        int nbGames = buffer[6];
        System.out.println(message.substring(0, 6) + nbGames + message.substring(7));
        receiveOgame(nbGames, br);
    }

    //recevoir les parties disponibles
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

    //créer une partie
    public void newGame(PrintWriter pw) throws Exception {
        pw.print("NEWPL " + this.id + " " + this.port + "***");
        pw.flush();
    }

    //rejoindre une partie
    public void joinGame(PrintWriter pw) throws Exception {
        Scanner game = new Scanner(System.in);
        System.out.println("Enter the game's number: ");
        byte gameNumber = (byte) game.nextInt();
        pw.print("REGIS " + this.id + " " + this.port + " " + (char) gameNumber + "***");
        pw.flush();
    }

    public static void main(String[] args) {
        //demande son id à l'utilisateur
        Scanner name = new Scanner(System.in);
        System.out.println("Enter your name: ");
        String id = name.nextLine() + "$$$$$$$$";
        id = id.substring(0, 8);

        if (args.length != 3) {
            System.out.println("Usage: java Client <host> <portUDPClient> <portTCP>");
        }
        else {
            try {
                int port = Integer.parseInt(args[2]);
                Socket socket = new Socket(args[0], port);
                BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

                Client client = new Client(id, args[1]);
                while (true) {
                    //client.receiveGames(br);
                    client.joinGame(pw);
                    //client.newGame(pw);

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
