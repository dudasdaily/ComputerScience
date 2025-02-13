#include <iostream>
using namespace std;

int calcMaxHeight(int trees[], int need)
{
    int height = 0;
    int sum = 0;

    while(sum <= need)
    {
        height++;

        for(int i = 0; i < sizeof(trees) / sizeof(int); i++)
        {
            
        }
    }

    return height;
}

int main()
{
    int treeNum; // 나무의 수
    int need; // 필요한 나무의 총 길이
    int height;

    cin >> treeNum;
    cin >> need;

    int trees[treeNum];

    for(int i = 0; i < treeNum; i++)
    {
        cin >> trees[i];
    }
    
    

    return 0;
}