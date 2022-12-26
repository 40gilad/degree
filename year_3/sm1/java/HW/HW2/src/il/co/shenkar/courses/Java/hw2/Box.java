package il.co.shenkar.courses.Java.hw2;

public class Box {
    private int xSize, ySize, zSize;

    @Override
    public String toString() {
        return "Box size: (x,y,z): (" + xSize +","+ ySize +"," +  zSize + ")";
    }

    public int getxSize() {
        return xSize;
    }

    public int getySize() {
        return ySize;
    }

    public int getzSize() {
        return zSize;
    }

    public Box(int xSize, int ySize, int zSize) {
        this.xSize = xSize;
        this.ySize = ySize;
        this.zSize = zSize;
    }
    public class Fly{
        private int xSize, ySize, zSize;

        public Fly(int x,int y,int z) {
            this.setxSize(x);
            this.setySize(y);
            this.setzSize(z);

        }

        public Fly(){
            this.setxSize(0);
            this.setySize(0);
            this.setzSize(0);
        }

        @Override
        public String toString() {
            return "Fly size: (x,y,z): (" + xSize +","+ ySize +"," +  zSize+")";
        }

        public void setxSize(int xSize) {
            if(xSize> Box.this.getxSize()){
                System.out.println("Error: Fly can not leave the box\n" +
                        "Fly got the maximum value of the box x axis");
                this.xSize=Box.this.getxSize();
                return;
            }
            this.xSize = xSize;
        }

        public void setySize(int ySize) {
            if(ySize> Box.this.getySize()) {
                System.out.println("Error: Fly can not leave the box\n" +
                        "Fly got the maximum value of the box y axis");
                this.ySize=Box.this.getySize();
                return;
            }
                this.ySize = ySize;
        }

        public void setzSize(int zSize) {
                if(zSize> Box.this.getzSize()){
                    System.out.println("Error: Fly can not leave the box\n" +
                            "Fly got the maximum value of the box z axis");
                    this.zSize=Box.this.getzSize();
                    return;
            }
            this.zSize = zSize;
        }
    }
}
