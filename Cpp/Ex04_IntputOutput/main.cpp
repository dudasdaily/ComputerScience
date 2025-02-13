#include <iostream>
using namespace std;

int main()
{
    char user_input[100];
    int number = -1;

    cin >> user_input;
    // cin.getline(user_input, sizeof(user_input));
    // cin.ignore(100, '\n');
    // 참고 : cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cin >> number;

    cout << user_input << " " << number << endl;

    return 0;
}