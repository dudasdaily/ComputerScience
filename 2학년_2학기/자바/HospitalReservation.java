import java.util.Scanner;

// TODO : reservationFunc() 예외처리, printStatus()완성
public class HospitalReservation {
    public static void main(String[] args)
    {
        Scanner s = new Scanner(System.in);
        
        String[] departments = {"내과", "외과", "소아과", "정형외과"};
        String[][] timeSlots = {
            {"09:00", "10:00", "11:00"},
            {"13:00", "14:00", "15:00"},
            {"10:00", "11:00", "12:00"},
            {"14:00", "15:00", "16:00"}
        };

        int[][] reservationNum = {
            {0, 0, 0},
            {0, 0, 0},
            {0, 0, 0}
        };
        
        while(true)
        {
            int task = home();            

            if (task == 1)
            {
                boolean a =reservationFunc(departments, timeSlots, reservationNum);

                while(a)
                {
                    a = reservationFunc(departments, timeSlots, reservationNum);
                }
            }

            else if(task == 2)
            {
                
            }

            else if(task == 3)
            {
                System.out.println("프로그램을 종료하겠습니다.");
                break;
            }

        }
                
    }

    public static int home()
    {
        Scanner s = new Scanner(System.in);

        int task = 0;

        System.out.println("=== 병원 예약 시스템 ===");
        System.out.println("1. 예약하기");
        System.out.println("2. 예약 현황 보기");
        System.out.println("3. 종료");
        System.out.println("원하는 작업을 선택하세요");

        task = s.nextInt();

        return task;
    }
    
    // 1. 예약하기를 입력했을 경우
    public static boolean reservationFunc(String[] departments, String[][] timeSlots, int[][] reservationNum)
    {
        Scanner s = new Scanner(System.in);
        System.out.print("이름 : ");
        String name = s.nextLine();
        
        System.out.print("진료과목 : ");
        int index_depart;

        for(int i=0; i < departments.length; i++)
        {
            System.out.print(i + ". " + departments[i] + " ");
        }

        System.out.println(" : ");

        index_depart = s.nextInt();
        int index_time;

        System.out.println("진료 시간 : ");
        for (int i = 0; i < 3; i++)
        {
            System.out.printf("%d. \"%s\" ", i, timeSlots[index_depart][i]);
        }
        System.out.print(" : ");

        index_time = s.nextInt();        
    
        if (reservationNum[index_depart][index_time] <= 3)
        {
            System.out.printf("%s의 %s시간으로 예약 되었습니다!", departments[index_depart], timeSlots[index_depart][index_time]);
            reservationNum[index_depart][index_time] += 1;

            return false;
        }

        else
        {
            System.out.println("예약이 다 찼습니다.");
            return true;
        }
    }

    // 2. 예약 현황 보기 를 입력했을 경우
    public static void printStatus(String[] departments, String[][] timeSlots, int[][] reservationNum)
    {
    }
}
