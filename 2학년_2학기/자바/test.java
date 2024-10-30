import java.util.Arrays;

public class test {
    static public void main(String args[])
    {
        int a[] = {3,4,5,2,1};
        System.out.println(solution(a));
    }
    
    static public int solution(int[] num_list) {
        int answer = 0;
        String odd_sequence = "";
        String even_sequence = "";
        
        for(int i : num_list)
        {
            even_sequence += (i % 2 == 0 ? i+"" : "");
            odd_sequence += (i % 2 == 1 ? i+"" : "");

            System.out.println(even_sequence);
            System.out.println(odd_sequence);
        }
        
        answer = Integer.parseInt(even_sequence) + Integer.parseInt(odd_sequence);
        
        return answer;
    }
}