import java.util.Arrays;

public class Main {
    public static void main(String[] args)
    {
        Student one = new Student(111111111, "James Smith",85);
        Student two = new Student(453753414, "Robert Johnson",91);
        Student three = new Student(583897534, "John Williams",82);
        Student four = new Student(123489876, "Michael Brown",63);
        Student five = new Student(654732483, "David Jones",68);
        Student six = new Student(142348987, "William Miller",92);
        Student seven = new Student(876195865, "Richard Davis",87);
        Student eight = new Student(324988766, "Joseph Garcia",81);
        Student nine = new Student(213245786, "Charles Wilson",86);
        Student ten = new Student(843123468, "Thomas Martin",71);

        Student arr[] = {one,two,three,four,five,six,seven,eight,nine,ten};
        for (Student i:arr
             ) {
            System.out.println(i);
        }
        System.out.println("After sort:");
        Arrays.sort(arr);
        for (Student i:arr
             ) {
            System.out.println(i);
        }
    }
}