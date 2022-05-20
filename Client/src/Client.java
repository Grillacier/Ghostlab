import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.*;
import java.util.Scanner;

public class Client {
    private final Requests requests; //requêtes du client

    public Client(String id, String port) {
        this.requests = new Requests();
        this.requests.setId(id);
        this.requests.setPort(port);
    }

    public Requests getRequests() {
        return this.requests;
    }

    public static void main(String[] args) {
        if (args.length != 4) {
            System.out.println("Usage: java Client <host> <portUDPClient> <portTCP> <y/n>");
            System.out.println("<p/r> : p : afficher les messages sous forme de phrases");
            System.out.println("<p/r> : r : afficher les messages sous forme de requêtes");
            System.exit(1);
        } else {
            //demande son id à l'utilisateur
            Scanner name = new Scanner(System.in);
            System.out.println("Entrez votre nom : ");
            String id = name.nextLine() + "12345678";
            id = id.substring(0, 8);

            while (!id.matches("[a-zA-Z0-9]+")) {
                System.out.println("Votre nom ne doit contenir que des caractères alphanumériques");
                System.out.println("Entrez votre nom : ");
                id = name.nextLine() + "12345678";
                id = id.substring(0, 8);
            }

            try {
                int port = Integer.parseInt(args[2]);
                Socket socket = new Socket(args[0], port);
                BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
                DatagramSocket dso = new DatagramSocket(Integer.parseInt(args[1]));

                Client client = new Client(id, args[1]);
                if (args[3].equalsIgnoreCase("p"))
                    client.getRequests().setShow(true);
                else if (args[3].equalsIgnoreCase("r"))
                    client.getRequests().setShow(false);
                else {
                    System.out.println("p : afficher les messages sous forme de phrases");
                    System.out.println("r : afficher les messages sous forme de requêtes");
                    System.exit(1);
                }

                client.getRequests().game(br, pw, dso);

            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
