import java.util.Scanner;

public class MovieRating {
    static public void main(String args[])
    {
        Scanner s = new Scanner(System.in);
        int numMovie = 3;

        String movieName[] = new String[numMovie];
        String text[] = { "스토리 : ", "연출 : ", "연기 : ", "음악 : ", "시각효과 : " };
        int[][] rating = new int[numMovie][text.length];
        double[] avgRating = new double[numMovie];

        for(int i = 0; i < numMovie; i++)
        {
            System.out.printf("영화 %s의 제목을 입력하세요 : ", i + 1);
            movieName[i] = s.nextLine();

            System.out.printf("\'%s\' 영화의 각 카테고리 평점을 입력하세요 (1~5)\n", i + 1);


            int sum = 0;

            for(int j = 0; j < text.length; j++)
            {
                System.out.print(text[j]);
                rating[i][j] = s.nextInt();

                sum += rating[i][j];
            }

            s.nextLine();

            avgRating[i] = sum / (double)text.length;

            System.out.println();
        }

        System.out.println("=== 영화 평균 평점 ===");
        for(int i = 0; i < numMovie; i++)
        {
            System.out.printf("%s 평균 평점 : %g\n", movieName[i], avgRating[i]);
        }
        System.out.println();

        int bestmovieIdx = find_MaxIdx(avgRating);

        System.out.printf("평균 평점이 제일 높은 영화 : %s (평점 : %g)\n\n", movieName[bestmovieIdx], avgRating[bestmovieIdx]);

        System.out.println("=== 카테고리별 평균 평점 ===");
        for(int i = 0; i < 5; i++)
        {
            System.out.printf("%s %g\n", text[i], avgRating[bestmovieIdx]);
        }
        
        s.close();
    }

    static int find_MaxIdx(double arr[])
    {
        double max = arr[0];
        int idx = 0;

        for(int i = 0; i < arr.length; i++)
        {
            if (max <= arr[i])
            {
                max = arr[i];
                idx = i;
            }
        }

        return idx;
    }
}

