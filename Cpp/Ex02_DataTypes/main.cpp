#include <iostream>
using namespace std;

int main()
{
    int a; // 변수를 정의할 때 자료형을 미리 지정
    a = 123; // 변수 명 == 메모리 주소 (객체 레퍼런스 아님)    

    // * sizeof
    int b = sizeof(int); // b = 4
    cout << 123 + 4 << " " << sizeof(123 + 4) << endl; // 127 4 출력

    // * float, double
    float f = 123.456f; // float는 리터럴로 쓸 때, f를 붙여야함.
    double d = 123.456; // double은 리터럴로 쓸 때, f필요 없음.
    
    // * char char[]
    // 글자 하나와 != 문자열
    char c = 'a';
    char str[] = "Hello, World!"; // 문자열을 char의 배열로 취급, std::string을 쓰면 문자열을 편리하게 쓸 수 있음
    cout << c << " " << sizeof(c) << endl; // a 1


    // * 형변환(type casting)
    int i = 987.654; // double을 int에 강제로 저장
    f = 567.89; // double을 float에 강제로 저장

    // * 기본 연산자
    // i = 987;
    i += 100; // 1087
    i++; // 1088

    // * bool
    bool is_good = true; // 1
    is_good = false; // 0

    cout << is_good << endl; // 0

    // boolalpha : bool값을 0, 1이 아닌 알파벳 true, false로 출력하도록 해주는 옵션(토글)
    cout << boolalpha << true << endl; // true
    cout << false << endl; // false

    cout << noboolalpha << true << endl; // 1
    cout << false << endl; // 0

    /*
    && 이 << 보다 우선순위가 낮기 때문에,
    cout << true && true << endl; 는
    ((cout << true) && true) << endl; ->
    (cout && true) << endl;
    과 같아짐.
    */
    cout << (true && true) << endl;


    // * 영역(scope)
    i = 123;

    {
        // 영역이 있을 경우 영역 내에서 먼저 변수를 찾고 없으면 더 넓은 영역에서 찾음.
        int i = 345;
        cout << i << endl; // 345
    }

    cout << i << endl; // 123

    


    return 0;
}