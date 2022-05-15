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
        if (args.length != 3) {
            System.out.println("Usage: java Client <host> <portUDPClient> <portTCP>");
        }

        else {
        //demande son id à l'utilisateur
        Scanner name = new Scanner(System.in);
        System.out.println("Entrez votre nom : ");
        String id = name.nextLine() + "12345678";
        id = id.substring(0, 8);

            try {
                int port = Integer.parseInt(args[2]);
                Socket socket = new Socket(args[0], port);
                BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));
                DatagramSocket dso = new DatagramSocket(port);

                Client client = new Client(id, args[1]);
                client.getRequests().game(br, pw, dso);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
