public class Pr0312 {
    public static double curve(double a, double b, double c, double d, double e) {
        double min = Math.min(Math.min(Math.min(a, b), Math.min(c, d)), e);
        double max = Math.max(Math.max(Math.max(a, b), Math.max(c, d)), e);
        return MyLibrary.round((a + b + c + d + e - min - max) / 3., 2);
    }

    public static void main(String[] args) {
        System.out.println(curve(
                MyLibrary.getDouble("Grade 1: "),
                MyLibrary.getDouble("Grade 2: "),
                MyLibrary.getDouble("Grade 3: "),
                MyLibrary.getDouble("Grade 4: "),
                MyLibrary.getDouble("Grade 5: ")));
    }
}
