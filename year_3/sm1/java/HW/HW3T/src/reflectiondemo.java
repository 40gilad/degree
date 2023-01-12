// GILAD MEIR - 313416562
// SHAHR ARIEL- 314868977

import il.ac.shenkar.java.samples.reflectionutiles.ReflectionUtils;
import il.ac.shenkar.java.samples.reflectionutiles.ReflectionException;

public class reflectiondemo {
    public static void main(String[] args) {

        try {
            System.out.println(ReflectionUtils.check("Eggs"));
        } catch (ReflectionException e) {
             System.out.println(e);
        }
    }
}
