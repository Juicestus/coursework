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

  
}
