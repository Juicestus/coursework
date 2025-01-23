public class Pr0433 {
	public static boolean palindrome(String w) {
		for (int i = 0, j = w.length() - 1; i <= j;)
			if (w.charAt(i++) != w.charAt(j--))
				return false;
		return true;
	}

    public static void main(String[] args) {
		System.out.println(palindrome(MyLibrary.getWord("Word:")));
   	} 
}
