package il.ac.shenkar.network;
import java.io.*;
import java.net.*;
import java.sql.PreparedStatement;

public class Server {
    public static void main(String[] args) {
        ServerSocket server = null;
        Socket sock = null;
        OutputStream os = null;
        InputStream is = null;
        DataOutputStream dos = null;
        DataInputStream dis = null;
        String reply = null;
        while (true) {
            try {
                server = new ServerSocket(1300);
                System.out.println("waiting for accept");
                sock = server.accept();
                System.out.println("accepted");
                is = sock.getInputStream();
                dis = new DataInputStream(is);
                os = sock.getOutputStream();
                dos = new DataOutputStream(os);
                String recive = dis.readUTF();
                switch (recive) {
                    case "beatles":
                        reply = "A day in the life";
                        break;
                    case "Pink Floyd":
                        reply = "See emily play";
                        break;
                    case "led zeppelin":
                        reply = "black dog";
                        break;
                    default:
                        reply = "dont know this band";
                        break;
                }
                dos.writeUTF(reply);
                System.out.println("im replying: " + reply);

            } catch (IOException e) {
                System.out.printf("new Server Socket failed");
            } finally {
                if (server != null) {
                    try {
                        server.close();
                        if (dos !=null)
                            dos.close();
                        if (dis!=null)
                            dis.close();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        }
    }
}
