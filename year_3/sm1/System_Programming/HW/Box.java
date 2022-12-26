package il.ac.shenkar.courses.java.samples;

public class Box {

    int x;
    int y;
    int z;

    public Box(int x, int y, int z) {
        if (x < 0 || y < 0 || z < 0)
        {
            System.out.println("The box must have positive values");
            return;
        }

        this.x = x;
        this.y = y;
        this.z = z;

    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public int getZ() {
        return z;
    }

    public void print_box()
    {
        System.out.println("The sizes of the box are : x = " + getX() + " y = " + getY() + " z = " + getZ());
    }

    class Fly {
        int x;
        int y;
        int z;

        public Fly(int x, int y, int z) {
            if ((x >= Box.this.x || x < 0) || (y >= Box.this.y || y < 0) || (z >= Box.this.z || z < 0))
            {
                System.out.println("The fly is out of the box - please try again");
                return;
            }
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public void setX(int x) {
            if (x >= Box.this.x || x < 0)
            {
                System.out.println("The fly is out of the box - please try again");
                return;
            }

            this.x = x;
        }

        public void setY(int y) {
            if (y >= Box.this.y || y < 0)
            {
                System.out.println("The fly is out of the box - please try again");
                return;
            }
            this.y = y;
        }

        public void setZ(int z) {
            if (z >= Box.this.z || z < 0)
            {
                System.out.println("the fly is out of the box - please try again");
                return;
            }
            this.z = z;
        }

        public int getX() {
            return x;
        }

        public int getY() {
            return y;
        }

        public int getZ() {
            return z;
        }

        public void print_fly()
        {
            System.out.println("The fly's coordinates : x = " + getX() + " y = " + getY() + " z = " + getZ());
        }

    }
}
