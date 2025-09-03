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
    
}
