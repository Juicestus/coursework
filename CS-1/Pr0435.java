public class Pr0435 {
	public static boolean perfect(int n) {
		int s = 0;
		for (int i = n - 1; i >= 1; i--) 
			if (n % i == 0)  
				s += i;
		return s == n;
	}

    public static void main(String[] args) {
		System.out.println(perfect(MyLibrary.getInt("num")));
    }
}
