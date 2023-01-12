package il.ac.shenkar.java.samples.reflectionutiles;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.Arrays;


public class ReflectionUtils {
public static String check(String class_name) throws reflectionExeption {
    try {
        String info = "";
        Class<?> clss = null;
        clss = Class.forName(class_name);
        Field[] fields = clss.getFields();
        Method[] methods = clss.getMethods();
        Constructor<?>[] constructors = clss.getConstructors();
        info = "{name: " + clss + ",fields: " + fields.toString() + ",methods: " + methods.toString() + ",constructors: " + constructors.toString() + "}";
        return info;
    } catch (ClassNotFoundException e) {
        throw new reflectionExeption(e.getMessage() + "Class doesnt exist");
    }

}
}
