//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by FernFlower decompiler)
//

package il.ac.shenkar.java.samples.reflectionutiles;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Arrays;

public class ReflectionUtils {

    public static String check(String class_name) throws ReflectionException {
        try {
            String info = "";
            Class<?> clss = null;
            clss = Class.forName(class_name);
            Field[] fields = clss.getDeclaredFields();
            Method[] methods = clss.getDeclaredMethods();
            Constructor<?>[] constructors = clss.getDeclaredConstructors();
            info = "{name: " + clss.getName() + ",fields: " + Arrays.toString(fields) + ",methods: " + Arrays.toString(methods) + ",constructors: " + Arrays.toString(constructors) + "}";
            return info;
        } catch (ClassNotFoundException var6) {
            throw new ReflectionException(var6.getMessage() + "Class doesnt exist");
        }
    }
}
