#include <stdio.h>
//#include <stdint.h> // <inttypes.h>안에 include되어 있다.
#include <inttypes.h> // 고정너비정수를 printf에서 사용할 때, format specifier를 저장해둔 라이브러리

int main()
{
    // 고정 너비 정수
    // 시스템마다 변수들의 크기가 다를 수 있다.
    // A 시스템에서는 int가 4byte고 B 시스템에서는 int가 2byte면
    // 같은 코드라도 같은 동작을 못한다.

    // 이럴 때 변수의 크기를 고정시키는 것이 고정너비정수이다.
    // 프로그램의 이식성을 높여줌

    // <stdint.h>에 정의돼어 있음
    int32_t i32 = 0; // 32bit integers, typedef로 내부적으로 구현돼 있다
    int_least8_t i8 = 0; // smallest 8bit integers, 적어도 8비트는 보장하는 가장 작은 비트로 초기화
    int_fast8_t f8 = 0; // fastest minimum, 8비트 중에서 가장 빠른것
    intmax_t imax = 0; // biggest signed integers, 정수중에서 가장 큰 것
    uintmax_t umax = 0; // biggest unsigned integers, unsigned중에서 가장 큰 것

    printf("%" PRId8 "\n", i8); // PRId8 : 8비트 int에 해당하는 format specifier가 매크로로 inttypes.h에 정의돼어 있음.

    scanf("%" SCNdMAX, &imax);
    printf("%" PRIdMAX "\n", imax);

    return 0;
}