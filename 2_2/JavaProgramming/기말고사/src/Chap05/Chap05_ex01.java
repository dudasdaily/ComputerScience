package Chap05;

class Point {
    private int x, y;

    public void set(int x, int y) {
        this.x = x; this.y = y;
    }

    public void showPoint() {
        System.out.printf("(%d, %d)\n", x, y);
    }
}

class ColorPoint extends Point {
        private String color;
        public void setColor(String color) {
            this.color = color;
        }

        public void showColor() {
            System.out.printf("Color : %s \n", color);
            showPoint();
        }
}

public class Chap05_ex01 {
    public static void main(String[] args) {
        ColorPoint a = new ColorPoint();
        a.set(1, 2);
        a.setColor("red");
        a.showColor();
    }
}