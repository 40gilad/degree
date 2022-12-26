/***********        Shahar Ariel - 314868977         ***********/
/***********        Gilad Meir - 313416562           ***********/
import il.co.shenkar.courses.Java.hw2.Box;

public class Main {
    public static void main(String[] args){
        Box box = new Box(20,20,20);
        System.out.println(box);

        Box.Fly fly = box.new Fly(25,10,15 );

        System.out.println(fly);

        fly.setxSize(25);

        System.out.println(fly);

        fly.setxSize(17);

        System.out.println(fly);
    }
}