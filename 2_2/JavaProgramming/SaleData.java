import java.util.Random;
import java.util.Scanner;

public class SaleData {
    static public void main(String args[])
    {
        Random rand = new Random();
        Scanner s = new Scanner(System.in);

        String[] goods = {"A", "B", "C", "D", "E"};

        int salesData[][] = new int[goods.length][12];
        double[] yearSales = new double[goods.length];
        
        for(int i = 0; i < goods.length; i++)
        {
            // 1월 ~ 12월까지 각 월별 판매량을 0~100까지 무작위로 초기화 
            for (int j = 0; j < salesData[i].length; j++)
            {
                salesData[i][j] = rand.nextInt(101);
                
                yearSales[i] += salesData[i][j];
            }
        }

        for (int i = 0; i < 12; i++)
        {
            System.out.printf("=== %d월 판매 데이터 ===\n", i+1);
            for (int j = 0; j < goods.length; j++)
            {
                System.out.printf("상품 %s의 판매 수량 : %d\n", goods[j], salesData[j][i]);
            }
            System.out.println();
        }

        System.out.println("=== 상품별 연간 판매 ===");
        for (int i = 0; i < goods.length; i++)
        {
            System.out.printf("상품 %s : 총 판매 수량 = %d, 평균 판매 수량 = %.2f\n", goods[i], (int)yearSales[i], yearSales[i] / goods.length);
        }
        
        int bestGoodsIdx = getMaxIdx(yearSales);

        System.out.printf("연간 판매 수량이 가장 높은 상품 : %s", goods[bestGoodsIdx]);

        System.out.println();

        System.out.printf("총 판매 수량을 알고 싶은 월을 입력하세요 (1~12) : ");
        int targetMonth = s.nextInt();

        while(targetMonth < 1 || targetMonth > 12)
        {
            System.out.print("잘못된 수를 입력했습니다. 총 판매 수량을 알고 싶은 월을 입력하세요 (1~12) : ");
            targetMonth = s.nextInt();
        }

        System.out.printf("%d월의 총 판매 수량 : %d", targetMonth, (int)salesData[bestGoodsIdx][targetMonth - 1]);
    }

    static public int getMaxIdx(double yearSales[])
    {
        double max = yearSales[0];
        int idx = 0;

        for(int i = 0; i < yearSales.length; i++)
        {
            if (max < yearSales[i])
            {
                max = yearSales[i];
                idx = i;
            }
        }

        return idx;
    }
}
