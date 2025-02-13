package Chap04;
import java.util.Scanner;

public class Chap04_ex12 {
    private static double rate;
    public static double toDollar(double won) {
        return won/rate;
    }

    public static double toKWR(double dollar) {
        return dollar * rate;
    }

    public static void setRate(double r) {
        rate = r;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("환율(1달러) : ");
        double rate = scanner.nextDouble();
        
        Chap04_ex12.rate = rate;

        double dollar = toDollar(1000000);
        

        System.out.printf("100만원은 $%g입니다.\n", toDollar(1000000));
        System.out.printf("$100는 %g원 입니다.\n", toKWR(dollar));

        scanner.close();
    }
}
