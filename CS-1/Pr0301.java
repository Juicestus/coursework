public class Pr0301 {
    // Wait have we not learned boolean type yet???
    public static boolean verify(int n) {
        return n > MyLibrary.getRandNum(1, 100);
    }

    public static void main(String[] args) {
        int n = MyLibrary.getInt("Give me an integer between 1 and 100");
        if (verify(n))
            System.out.println("You win");
        else
            System.out.println("You loose");
    }
}
