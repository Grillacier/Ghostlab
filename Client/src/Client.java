import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class Client {
    private String id;
    private String port;

    public Client(String id, String port) {
        this.id = id;
        this.port = port;
    }

    public void newGame(String host, int port, String portClient, PrintWriter pw) throws Exception {
        pw.print("NEWPL " + this.id + " " + portClient + "***");
        pw.flush();
        pw.close();
    }

    public static void main(String[] args) {
        if (args.length != 3) {
            System.out.println("Usage: java Client <host> <portUDPClient> <portTCP>");
        }
        else {
            try {
                int port = Integer.parseInt(args[2]);
                Socket socket = new Socket(args[0], port);
                BufferedReader br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                PrintWriter pw = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()));

                Client client = new Client("Client01", args[1]);
                while (true) {
                    client.newGame(args[0], port, args[1], pw);
                }
                //socket.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}
