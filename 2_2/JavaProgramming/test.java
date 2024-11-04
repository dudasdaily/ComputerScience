public class test {
    static int n; // 이거는 프로그램 실행 시 생성됨.

    static public void main(String args[])
    {
        // 24.11.04(월)
        // 가비지 컬렉터
        /*
        Person a = new Person("a")
        Person b = new Person("b")
        b = a // 이 순간 b가 가리키던 메모리가 쓰레기값을 가지게됨
        */
        
        // 자바 접근 지정자
        // private, public, protected, default

        // default(java 기본 접근 지정자)
        // 동일 패키지내에서만 접근 할 수 있음

        // protected
        // 동일 패키지와 자식 클래스에서 접근 할 수 있음

        // private < default < protected < public

        // 클래스 내 static 초기화 방법
        test.n = 55;

        System.out.println(test.n);
        test p = new test();
        p.n = 30;
        System.out.println(p.n);
    }
}