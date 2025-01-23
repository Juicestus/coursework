public class Pr0311 {
    public static char letterGrd(double a, double b, double c, double d, double e) {
        double avg = (a + b + c + d + e) / 5.;
        if (avg >= 90)
            return 'A';
        else if (avg >= 80)
            return 'B';
        else if (avg >= 70)
            return 'C';
        else if (avg >= 60)
            return 'D';
        else
            return 'F';
    }

    public static void main(String[] args) {
        System.out.println(letterGrd(
                MyLibrary.getDouble("Grade 1: "),
                MyLibrary.getDouble("Grade 2: "),
                MyLibrary.getDouble("Grade 3: "),
                MyLibrary.getDouble("Grade 4: "),
                MyLibrary.getDouble("Grade 5: ")));
    }
}
