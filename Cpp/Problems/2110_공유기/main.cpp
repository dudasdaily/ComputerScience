#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n, c;
    vector<int> v;

    cin >> n;
    cin >> c;

    for(int i = 0; i < n; i++)
    {
        int item;
        cin >> item;
        v.push_back(item);
    }

    sort(v.begin(), v.end());

    int left = 1; // 최소 간격
    int right = v[n - 1] - v[0]; // 최대 간격
    
    int result = -1;

    while(left <= right)
    {
        int installed = 1;
        int mid = (left + right) / 2; // 중간 간격

        // 간격을 이진탐색할거임.
        
        int start = v[0]; // i번째 집의 직전에 위치한 집.

        for(int i = 1; i < n; i++)
        {
            int end = v[i]; // i번째 집
            
            // 만약 start집과 i번째 집의 간격이 mid보다 크거나 같다면
            // 공유기를 설치하고, i번째 집을 start로 바꾼다.
            if(end - start >= mid)
            {
                installed += 1;
                start = end; 
            }
        }

        // 설치한 공유기가 설치해야 되는 공유기 수 보다 작은 경우
        // mid를 조정한다.(좁게)
        if (installed < c)
        {
            right = mid - 1;
        }
        
        // 설치한 공유기가 설치해야 되는 공유기 수 보다 크거나 같은 경우
        // mid를 조정한다.(넓게)
        else
        {   
            result = mid;
            left = mid + 1;
        }
    }

    cout << result << endl;

    return 0;
}