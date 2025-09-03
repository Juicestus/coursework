import java.util.ArrayList;
import java.util.Collections;

public class Driver {
	
	public static void main(String[] args) {
		//Implement all three solutions in the collections_questions file
		//comment out what is needed to get certain parts of the code running
		//All of the code below is correct, and does not need to be changed.
		
		//Collections Questions
		ArrayList<Student> student_array = new ArrayList<Student>(5);
		Student s1 = new Student(2.0f, "Bobby");
		Student s2 = new Student(3.5f, "Alice");
		Student s3 = new Student(3.0f, "Claire");
		Student s4 = new Student(4.0f, "Douglas");
		
		student_array.add(s1);
		student_array.add(s2);
		student_array.add(s3);
		student_array.add(s4);
		
		System.out.println("Unsorted Array:");
		for (Student s : student_array) {
			System.out.println(s.name);
		}
		
		Collections.sort(student_array);
		
		System.out.println("\nDefault Sorted Array by Name:");
		for (Student s : student_array) {
			System.out.println(s.name);
		}
		
		Collections.sort(student_array,new Student_gpa_Comparator());
		
		System.out.println("\nSorted Array by GPA(high to low):");
		for (Student s : student_array) {
			System.out.println(s.name);
		}
		
		ArrayList<Student> rev_array = Collections_questions.reverse_array(student_array);
		
		System.out.println("\nSorted by GPA(low to high):");
		for (Student s : rev_array) {
			System.out.println(s.name);
		}
		
		
		
	//Polymorphism Questions
	//Implement all four parts in the Polymorphism_questions file.
      Vehicle car = new Car();
      Vehicle bike = new Motorcycle();
      Vehicle bus = new Bus();
      
      ParkingSpot spot1 = new ParkingSpot(4);
      ParkingSpot spot2 = new ParkingSpot(2);

      ParkingLot p = new ParkingLot();
      p.addNewSpot(spot1);
      p.addNewSpot(spot2);
      
      boolean first = p.fillFirstAvailableEmptySpot(bus);
      boolean second = p.fillFirstAvailableEmptySpot(car);
      boolean third = p.check_all_spots_full();
      boolean fourth = p.fillFirstAvailableEmptySpot(bike);
      boolean fifth = p.check_all_spots_full();

      
      System.out.println("\nShould be true: "+first);
      System.out.println("Should be false: "+second);
      System.out.println("Should be false: "+third);
      System.out.println("Should be true: "+fourth);
      System.out.println("Should be true: "+fifth);
	}
	
	
	

}
