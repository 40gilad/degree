package il.ac.shenkar.network;
import java.io.*;
import java.net.*;

public class Client {
    public static void main(String[] args) {
        String msg="beatles";
        String reply=null;
        Socket sock = null;
        OutputStream os = null;
        InputStream is = null;
        DataOutputStream dos = null;
        DataInputStream dis = null;
        try {
            sock=new Socket("127.0.0.1",1300);
            System.out.println("socket created");
            os=sock.getOutputStream();
            dos=new DataOutputStream(os);
            is=sock.getInputStream();
            dis=new DataInputStream(is);
            dos.writeUTF(msg);
            System.out.println("sent"+msg);
            reply=dis.readUTF();
            System.out.println("reply="+reply);

        } catch (IOException e) {
            System.out.println("Server socket failed");
        }
        finally {
            if(sock!=null) {
                try {
                    sock.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }

                if (dos != null) {
                    try {
                        dos.close();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }
                if (dis!=null){
                    try{
                        dis.close();
                    }
                    catch (IOException e){
                        throw new RuntimeException(e);
                    }
                }
            }

        }
    }
}
