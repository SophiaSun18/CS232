/* CaesarCipherClient.java implements a client of the CaesarCipherServer.
 * 
 * Student Name: ZeAi Sun (zs35)
 * Date: April 16, 2023
 * 
 * Reference: https://www.infoworld.com/article/2853780/socket-programming-for-scalable-systems.html
 */

import java.util.Scanner;
import java.net.Socket;
import java.net.UnknownHostException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.io.IOException;

public class CaesarCipherClient {
    
    public static void main(String[] args) {

        // Check if the client provides exact 2 arguments.
        if (args.length != 2) {
            System.out.println("\nError: wrong number of arguments. Exiting...\n");
            System.exit(1);
        }

        // Initialize the server and port values.
        String server = args[0];
        int port = 0;
        
        // Check if the second argument is an valid integer.
        try {
            port = Integer.parseInt(args[1]);
        } catch (NumberFormatException n) {
            System.out.println("\nError: invalid port number. Exiting...\n");
            System.exit(1);
        }
        
        System.out.println("\nWelcome to the CaesarCipher!");

        // Get a rotation amount from the user, and check if it is valid.
        System.out.print("Enter a rotation amount between 1 and 25: ");
        Scanner Input = new Scanner(System.in);
        Integer rotationInt = Input.nextInt();

        if (rotationInt < 1 || rotationInt > 25) {
            System.out.println("\nError: invalid rotation amount. Exiting...\n");
            System.exit(1);
        }

        try {
            // Connect to the server.
            Socket socket = new Socket(server, port);
            PrintStream out = new PrintStream(socket.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedReader inStr = new BufferedReader(new InputStreamReader(System.in));

            // Send the rotation int to the server, and receive the echo from the server.
            out.println(rotationInt);
            out.println();
            System.out.print("This is your rotation amount: ");
            System.out.println(in.readLine());

            // Prompt for the text from the user.
            // Send the text to the server and receive the encrypted result from the server.
            System.out.print("Enter your text to encrypt (Enter quit to exit): ");
            String newStr;
            while (!(newStr = inStr.readLine()).equals("quit")) {
                out.println(newStr);
                System.out.print("The encrypted text is: ");
                System.out.println(in.readLine());
                System.out.print("Enter your text to encrypt (Enter quit to exit): ");
            }

            System.out.println("\nThanks for using the CaesarCipher!\n");

            // If the user enters "quit", quit the process and close the connection.
            Input.close();
            in.close();
            out.close();
            socket.close();

        } catch (UnknownHostException u) {
            System.out.println("\nError: unknown host. Exiting...\n");
            System.exit(1);
        } catch (IOException i) {
            System.out.println("\nError: IOException. Exiting...\n");
            System.exit(1);
        }

    }
}