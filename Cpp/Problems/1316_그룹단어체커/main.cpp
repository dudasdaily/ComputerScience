#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n, cnt = 0;  
    string str;

    cin >> n;
    
    for(int i = 0; i < n; i++)
    {
        bool isUsed[26] = {0, };
        bool isGroup = true;
        char prev;

        cin >> str;

        prev = str[0];

        for(int j = 0; j < str.size(); j++)
        {
            int alphaIdx = str[j] - 'a';

            if(isUsed[alphaIdx] == true && prev != str[j])
                isGroup = false;

            isUsed[alphaIdx] = true;
            prev = str[j];
        }
        
        if(isGroup)
            cnt += 1;
    }

    cout << cnt << endl;

    return 0;
}