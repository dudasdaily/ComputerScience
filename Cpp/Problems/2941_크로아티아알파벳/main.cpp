#include <iostream>
using namespace std;

void adjustCnt(string str, int* cnt)
{
    string croatias[] = {"c=", "c-", "d-", "lj", "nj", "s=", "z="};

    for(int i = 0; i < 7; i++)
    {
        int idx = 0;

        while(idx < str.size())
        {
            idx = str.find(croatias[i], idx);

            if(idx == string::npos)
                break;
            
            else
            {
                idx += 2; 
                *cnt -= 1;
            }
        }
    }
    
    int idx = 0;

    while(idx < str.size())
    {
        idx = str.find("dz=", idx);

        if(idx == string::npos)
            break;
            
        else
        {
            idx += 3; 
            *cnt -= 1;
        }
    }
}
int main()
{
    string str;
    cin >> str;

    int cnt = str.size();

    adjustCnt(str, &cnt);
    cout << cnt << endl;
    
    return 0;
}