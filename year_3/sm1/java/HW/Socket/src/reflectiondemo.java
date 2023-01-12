import il.ac.shenkar.java.samples.reflectionutiles.ReflectionUtils;
import il.ac.shenkar.java.samples.reflectionutiles.reflectionExeption;

public class reflectiondemo {
    public static void main(String[] args) {

        try {
            System.out.println(ReflectionUtils.check("Eggs"));
        } catch (reflectionExeption e) {
            throw new RuntimeException(e);
        }
    }
}
