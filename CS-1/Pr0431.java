public class Pr0431 {
	public static int factorial(int n) {
		int f = 1, i = n;
		for (; i >= 1; i--) 
			f *= i;
		return f;
	}

    public static void main(String[] args) {
		int n = MyLibrary.getInt("Number:: ");
		System.out.printf("The factorial of thee number %d is:: %d\n",
				n, factorial(n));	
    }
}
