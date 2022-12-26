package il.ac.shenkar.courses.java.samples;

public class Main {
    public static void main(String[] args) {

        Box box = new Box(20,20,20);
        box.print_box();

        Box.Fly fly = box.new Fly(-25,10,15 );

        fly.print_fly();

        fly.setX(25);

        fly.print_fly();

        fly.setX(17);

        fly.print_fly();
    }
}