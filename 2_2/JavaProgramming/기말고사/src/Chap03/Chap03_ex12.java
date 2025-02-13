package Chap03;

/*
접근 지정자
- 클래스 접근 지정자
 : 이거는 말 그대로 클래스 앞에 붙는 접근 지정자다.
 1.public 
public 클래스 접근 지정자 : 이거는 다른 패키지의 파일에서도 이 클래스를 사용할 수 있게 해줌.
public class A {} 이런식으로 만들어 놓으면 다른 자바 파일에서 A = new A()이런식으로 쓸 수 있음.

 2.default
 이거는 다른 패키지에서는 못쓰게 만들고 같은 패키지 내에서만 쓸 수 있게
 class A {} 이렇게 하면 선언 됨.



- 멤버 접근 지정자
1.public / 2.protected / 3.default / 4.private




 */

public class Chap03_ex12 { 
    public static void main(String[] args) {
        Chap03_ex11 a = new Chap03_ex11();

    }
}
