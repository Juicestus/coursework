import java.util.*;

class Student
{
	private String firstname, lastname;
	private float score;

	Student(String f, String l, float a)
	{
		firstname = f;
		lastname = l;
		score = a;
	}

	public String getlastName()	{ return lastname; }
	public String getfirstName()	{ return firstname; }
	public float getscore()	{ return score; }
	public void setscore(float newscore) { score = newscore; }


	public String toString() { return firstname + " " + lastname + " " + score; } 
}
	
