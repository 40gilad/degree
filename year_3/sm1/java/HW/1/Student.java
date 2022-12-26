import java.util.*;


public class Student {
    private int id;
    private String name;
    private double avg = 0;

    public Student(int id, String name) {
        this(id, name, 0);
    }

    public Student(int id, String name, double avg) {
        this.id = id;
        this.name = name;
        this.avg = avg;
    }

    public int getId() {
        return this.id;
    }

    public String getName() {
        return this.name;
    }

    public double getAvg() {
        return this.avg;
    }

    public String toString() {
        return "[Id: " + this.id + ", name: " + this.name + ", average: " + this.avg + "]";
    }


@Override
    public int compareTo(Student a){
        Double.compare(a.getAvg(),this.getAvg());
        if(a.getAvg() > this.getAvg()){
            return 1;
        }
        else if (a.getAvg() < this.getAvg()){
            return -1;
        }
        else return 0;
    }
}
