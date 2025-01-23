public class Pr0420 {
    public static void main(String[] args) {
		do {
			int n = MyLibrary.getRandNum(1, 10);
			if  (n == 3) break;
			System.out.println(n);
		} while (true);

    }
}
