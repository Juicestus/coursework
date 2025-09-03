import java.util.ArrayList;

public class GameMechanics {

    public static boolean BattleTester(ArrayList<? extends Item> array)
    {
        for (Item e : array)
        {
            if (!(e instanceof Hero)) 
                return false;
        }
        return true;
    }

    public static void basicWinChances(
        Character c1, Character c2
    ) {
        if (!((c1 instanceof Hero) && (c2 instanceof Villain)
        || (c1 instanceof Villain) && (c2 instanceof Hero)))
        {
            System.out.println("basicWinChances must have inputs of Hero vs. Villain or Villain vs. Hero");
            return;
        }

        double ratio = (c1.getHearts() + 0f) / c2.getHearts();
        if (ratio > 1)
            System.out.printf("Ratio: %.2f to 1, Winner: %s\n", ratio, c1.getName());
        else
            System.out.printf("Ratio: %.2f to 1, Winner: %s\n", 1f/ratio, c2.getName());
    }

    public static void advancedWinChances(
        Character c1, Character c2
    ) {
        // We were not sure if this was to be interpreted as:
        //    a conditional: if (armor == 100) hearts *= 1.5
        // or 
        //   a ratio: hearts *= 1.5*(armor/100)
        // we put both, one commented out, on not, they 
        // perform the same for the tests so idk

        double hearts1, hearts2;
        if ((c1 instanceof Hero) && (c2 instanceof Villain)) {
            hearts1 = c1.getHearts() 
                    * (((Hero)c1).getArmour() == 100 ? 1.5 : 1.0);
                    // * ((((Hero)c1).getArmour() * 1.5) / 100);
            hearts2 = c2.getHearts();
        }
        else if ((c1 instanceof Villain) && (c2 instanceof Hero)) {
            hearts1 = c1.getHearts();
            hearts2 = c2.getHearts() 
                    * (((Hero)c2).getArmour() == 100 ? 1.5 : 1.0);
                    // * ((((Hero)c2).getArmour() * 1.5) / 100);
        }
        else {
            System.out.println("basicWinChances must have inputs of Hero vs. Villain or Villain vs. Hero");
            return;
        }

        double ratio = hearts1 / hearts2;
        if (ratio > 1)
            System.out.printf("Ratio: %.2f to 1, Winner: %s\n", ratio, c1.getName());
        else
            System.out.printf("Ratio: %.2f to 1, Winner: %s\n", 1f/ratio, c2.getName());
    }
   
}
