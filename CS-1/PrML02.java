public class PrML02 {
  public static String symbol(String s) {
    return "" + (char) (s.charAt(0) + 123);
  }

  public static void main(String[] args) {
    System.out.println(symbol(MyLibrary.getWord("Gimme a letter: ")));
  }
}
