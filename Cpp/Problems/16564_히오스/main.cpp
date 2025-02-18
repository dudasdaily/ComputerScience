#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // n : 캐릭터 수
    // k : 올릴 수 있는 레벨 총합
    int n, k, t;
    vector<int> v;

    cin >> n;
    cin >> k;

    for(int i = 0; i < n; i++)
    {
        int item;
        cin >> item;
        v.push_back(item);
    }
    // 입력 완료

    sort(v.begin(), v.end());

    if(v[1] - v[0] >= k)
    {
        cout << v[0] + k << endl;
        return 0;
    }

    



    return 0;
}