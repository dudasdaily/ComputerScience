#include <iostream>
using namespace std;

void move(int a, int b)
{
    printf("%d %d\n", a, b);
}

void hanoi(int n, int depart, int temp, int destination)
{
    if(n == 1)
    {
    }

    else if(n == 2)
    {
        move(depart, temp);
        move(depart, destination);
        move(temp, destination);
    }

    else
    {
        hanoi(n-1, depart, destination, temp);
    }
}

int main()
{
    int n;
    cin >> n;

    hanoi(n, 1, 2, 3);

    return 0;
}