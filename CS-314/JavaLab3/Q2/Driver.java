import java.util.ArrayList;
import java.util.Arrays;

public class Driver {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Block testBlock = new Block("copper", new Location(0, 0, 0), 5);
		System.out.println(testBlock);
		
		// Character textCharacter = new Character
		// good, just checking, but since Character is abstract, can't create an instance
		
		Villain testVillain = new Villain("Creeper", new Location(0, 1, 0), false, "axe", 6);
		System.out.println(testVillain);

		
		Hero testHero = new Hero("Bowen", new Location(0, 0, 40), Arrays.asList("iron sword", "beef", "flare"), 5, 0) ;
		System.out.println(testHero);

		
		ArrayList<Character> BattleRoyale = new ArrayList<Character>();
		//BattleRoyale.add(testBlock); won't work!! (Thankfully)
		BattleRoyale.add(testVillain);
		BattleRoyale.add(testHero);
		System.out.println("Printing the mother of all battles");
		System.out.println(BattleRoyale);
		
		// MODIFICATIONS FOR Q2 BEGIN HERE

		System.out.println("BattleTester(BattleRoyale) = " + GameMechanics.BattleTester(BattleRoyale));

		ArrayList<Character> AllHeroes = new ArrayList<Character>();
		AllHeroes.add(testHero);
		System.out.println("BattleTester(AllHeroes) = " + GameMechanics.BattleTester(AllHeroes));

		ArrayList<Character> AllVillains = new ArrayList<Character>();
		AllVillains.add(testVillain);
		System.out.println("BattleTester(AllVillains) = " + GameMechanics.BattleTester(AllVillains));


		
	}

}
