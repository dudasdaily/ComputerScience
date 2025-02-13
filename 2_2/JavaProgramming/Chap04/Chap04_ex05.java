package Chap04;

class MyMath {
    static int myabs(int n) {
        if(n >= 0)
            return n;
        
        else
            return -n;
    }

    private MyMath() {}
}

class Test {
    int a;
    static void change_a(){
        // static함수에서 필드 초기화 불가
        // a = 10;
    }
}
public class Chap04_ex05 {
    public static void main(String args[]) {
        int a = -10;
        int b = -20;

        // err : MyMath의 생성자가 private임.
        // MyMath mm = new MyMath();

        a = MyMath.myabs(a);
        b = MyMath.myabs(b);

        System.out.println(a);
        System.out.println(b);
    }
}
