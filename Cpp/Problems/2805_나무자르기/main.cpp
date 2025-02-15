#include <iostream>
using namespace std;

int findMax(int trees[], int n)
{
    int max = trees[0];

    for(int i = 0; i < n; i++)
    {
        max = max < trees[i] ? trees[i] : max;
    }

    return max;
}

int main()
{
    int n, m;
    
    cin >> n;
    cin >> m;

    int trees[n];

    for(int i = 0; i < n; i++)
    {
        cin >> trees[i];
    }

    int start = 0;
    int end = findMax(trees, n);
    int result = 0;

    // end초기값이 배열의 최대값인데, 1씩 줄여서 0까지 체크
    while(start <= end)
    {
        long long sum = 0;
        int h = (start + end) / 2;

        for(int idx = 0; idx < n; idx++)
        {
            if(trees[idx] > h)
                sum += trees[idx] - h;
        }

        if(sum < m)
        {
            end = h - 1;
        }
        
        else
        {
            result = h;
            start = h + 1;
        }
    }

    cout << result << endl;

    return 0;
}