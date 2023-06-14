/* cipherTester.java implements a tester for the cipher() method.

 * Student Name: ZeAi Sun (zs35)
 * Date: April 17, 2023
 */

public class cipherTester {

    public static void main(String[] args) {

        assert(cipher("hello", 5) == "mjqqt");
        assert(cipher("sophia", 5) == "xtumnf");
        assert(cipher("hello", 10) == "rovvy");
        assert(cipher("sophia", 10) == "cyzrsk");
        assert(cipher("mjqqt", 21) == "hello");
        assert(cipher("cyzrsk", 16) == "sophia");
        assert(cipher("MJQQT", 21) == "HELLO");
        assert(cipher("CYZRSK", 16) == "SOPHIA");

        System.out.println("All tests passed!");
    }

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