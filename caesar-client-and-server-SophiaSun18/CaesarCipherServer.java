/* CaesarCipherServer.java implements a CaesarCipherServer.
 *
 * Student Name: ZeAi Sun (zs35)
 * Date: April 17, 2023
 * 
 * Reference: https://www.infoworld.com/article/2853780/socket-programming-for-scalable-systems.html
 */

import java.util.Date;
import java.net.Socket;
import java.net.ServerSocket;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;
import java.lang.Character;

public class CaesarCipherServer {

    public static void main(String[] args) {
        
        // Check if the client provides exact 1 argument.
        if (args.length != 1) {
            System.out.println("\nError: wrong number of arguments. Exiting...\n");
            System.exit(1);
        }

        // Initialize the port number.
        int port = Integer.parseInt(args[0]);
        System.out.println("Start server on port: " + port);

        // Initialize a new server socket.
        try {
            ServerSocket aServerSocket = new ServerSocket(port);
            System.out.println("Server name: " + aServerSocket.getInetAddress().getHostName() + ". Listening for connection...");

            // Wait and handle new connection.
            while (true) {
                Socket aSocket = aServerSocket.accept();
                String date = new Date().toString();
                System.out.println(date + ": connected with " + aSocket.getRemoteSocketAddress().toString());
                RequestHandler newRequest = new RequestHandler(aSocket);
                newRequest.start();
            }
            
        } catch (IOException i) {
            System.out.println("\nError: IOException. Exiting...\n");
            System.exit(1);
        }

    }
}

// Implement a new class to handle each request in a new thread.
class RequestHandler extends Thread {

    private Socket socket;

    // Initialize the socket.
    RequestHandler(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void run() {

        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintStream out = new PrintStream(socket.getOutputStream(), true);
            
            // Receive a rotation amount from the client and check if it is valid.
            int rotationInt = Integer.parseInt(in.readLine());
            out.print(rotationInt);

            // Receive the text from the client and send the encrypted result back to the client.
            String newStr;
            while(!(newStr = in.readLine()).equals("quit")) {
                out.println(cipher(newStr, rotationInt));
            }

            in.close();
            out.close();
            socket.close();

        } catch (IOException i) {
            System.out.println("\nError: IOException. Exiting...\n");
            System.exit(1);
        } catch (NullPointerException n) {
            ;
        } finally {
            String date = new Date().toString();
            System.out.println(date + ": disconnected with " + this.socket.getRemoteSocketAddress().toString());
        }
    }

    // Implement a method to encrypt the text.
    public static String cipher(String newStr, int rotationInt) {
        String result = "";
    
        for (int i = 0; i < newStr.length(); i++) {
            char c = newStr.charAt(i);

            if (!Character.isLetter(c)) {
                result += c;
            } else if (Character.isLowerCase(c)) {
                char newC = (char) ((int)c + rotationInt);

                if (newC > 'z') {
                    newC = (char) ((int)newC - 'z' + 'a' - 1);
                }

                result += newC;
            } else if (Character.isUpperCase(c)) {
                char newC = (char) ((int)c + rotationInt);

                if (newC > 'Z') {
                    newC = (char) ((int)newC - 'Z' + 'A' - 1);
                }

                result += newC;
            }
        }
        return result;
    }
}