import java.util.ArrayList;
import java.util.Arrays;

public class Driver {

	public static void main(String[] args) {

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

		// MODIFICATIONS FOR Q3 BEGIN HERE		

		Hero bowen = new Hero("Bowen", new Location(0, 0, 40), Arrays.asList("iron sword", "beef", "flare"), 5, 0) ;
		Villain creeper = new Villain("Creeper", new Location(0, 1, 0), false, "axe", 10);
		Villain zombie = new Villain("Zombie", new Location(0, 1, 0), false, "axe", 2);
		Villain enderman = new Villain("Enderman", new Location(0, 1, 0), false, "axe", 12);

		GameMechanics.basicWinChances(bowen, creeper);
		bowen.setHearts(10);
		GameMechanics.basicWinChances(bowen, zombie);
		bowen.setHearts(3);
		GameMechanics.basicWinChances(enderman, bowen);

		GameMechanics.basicWinChances(enderman, creeper); // fails w/ error msg -- good!
		
		// GameMechanics.basicWinChances(testBlock, bowen); // doesnt compile -- good!

		// MODIFICATIONS FOR Q4 BEGIN HERE		
		bowen.setArmour(100);
		bowen.setHearts(5);
		GameMechanics.advancedWinChances(bowen, creeper);

		bowen.setHearts(10);
		bowen.setArmour(0);
		GameMechanics.advancedWinChances(bowen, zombie);

		bowen.setHearts(3);
		bowen.setArmour(100);
		enderman.setHearts(7);
		GameMechanics.advancedWinChances(enderman, bowen);

		GameMechanics.advancedWinChances(enderman, creeper); // fails w/ error msg -- good!

		// MODIFICATIONS FOR Q5 BEGIN HERE		
		ArrayList<Character> BattleRoyale2 = new ArrayList<Character>();

		BattleRoyale2.add(new Villain("Creeper", new Location(0, 1, 0), false, "axe", 10));
		BattleRoyale2.add(new Villain("Zombie", new Location(0, 1, 0), false, "axe", 2));
		BattleRoyale2.add(new Villain("Enderman", new Location(0, 1, 0), false, "axe", 12));
		BattleRoyale2.add(new Hero("Bowen", new Location(0, 0, 40), Arrays.asList("iron sword", "beef", "flare"), 5, 0));

		System.out.println("BattleRoyale2 before sorting:");
		System.out.println(BattleRoyale2);
		GameMechanics.sortedBattlefieldCharacters(BattleRoyale2);
		System.out.println("BattleRoyale2 after sorting:");
		System.out.println(BattleRoyale2);
	}

}
