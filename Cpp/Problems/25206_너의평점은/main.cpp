#include <iostream>
using namespace std;

double convertGrade(string grade)
{
    if(grade == "A+")
        return 4.5;

    if(grade == "A0")
        return 4.0;

    if(grade == "B+")
        return 3.5;
    
    if(grade == "B0")
        return 3.0;

    if(grade == "C+")
        return 2.5;

    if(grade == "C0")
        return 2.0;
    
    if(grade == "D+")
        return 1.5;

    if(grade == "D0")
        return 1.0;

    if(grade == "F")
        return 0.0;    
}

int main()
{
    string str, grade;
    double credit;

    double creditSum = 0.0f;
    double sum = 0;

    for(int i = 0; i < 20; i++)
    {
        cin >> str >> credit >> grade;

        if(grade == "P")
            continue;
        
        else
        {
            creditSum += credit;
            sum += credit * convertGrade(grade);
        }
    }

    printf("%g\n", sum / creditSum);

    return 0;
}