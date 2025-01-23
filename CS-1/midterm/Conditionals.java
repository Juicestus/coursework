public class Conditionals {
	public static String str(boolean bool) {
		return bool ? "true" : "false";
	}

	public static void main(String args[]) {
		System.out.println("true ^ true = " + str(true ^ true));
		System.out.println("false ^ true = " + str(false ^ true));
		System.out.println("false ^ false = " + str(false ^ false));

	}
}

