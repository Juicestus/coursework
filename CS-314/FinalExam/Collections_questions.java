import java.util.ArrayList;
import java.util.Comparator;



public class Collections_questions {
	//Q3: Implement Static method reverse_array that returns a reversed student array.
	//Use the array passed in from the Driver class.
	static ArrayList<Student> reverse_array(ArrayList<Student> fwd)
	{
		ArrayList<Student> rev = new ArrayList<Student>();
		for (int i = fwd.size()-1; i >= 0; i--)
		{
			rev.add(fwd.get(i));
		}
		return rev;
	}
}

class Student implements Comparable<Student> {
	float gpa;
	String name;
	
	public Student(float g, String n) {
		gpa = g;
		name = n;
	}

	//Q1: Implement Comparable interface for Student's name (alphabetically). (yes I know there should be a last and first. Trying to keep this simple for you)
	public int compareTo(Student other) {
		return this.name.compareTo(other.name);
	}
	
	
}

//Q2: Create and implement Student_gpa_Comparator, order GPA from HIGH to low

class Student_gpa_Comparator implements Comparator<Student> {

	public int compare(Student student1, Student student2) {
		return student1.gpa > student2.gpa ? -1 : 1;
	}
	
}