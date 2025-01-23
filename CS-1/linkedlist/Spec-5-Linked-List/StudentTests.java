public class StudentTests {
    public static void main(String[] args) {
        LinkedList<Integer> list = new LinkedList<Integer>();
        list.add(5);
        list.add(2);
        list.add(4);
        list.add(6);
        list.add(5);
        list.add(6);
        System.out.println(list.toString());
        System.out.println(list.indexOf(5));
        System.out.println(list.indexOf(5, 2));
        System.out.println(list.remove(6));
    }
}
