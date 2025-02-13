#include <iostream>
using namespace std;

void swap(int arr[], int idx1, int idx2)
{
    int temp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
}

int partition(int trees[], int left, int right)
{
    int pivot = trees[(left + right) / 2];
    int low = left, high = right;
    
    while(low < high)
    {
        while(trees[low] < pivot)
            low++;
        
        while(trees[high] > pivot)
            high--;
        
        swap(trees, low, high);
    }

    return low; // 피벗의 인덱스 반환
}

void quickSort(int trees[], int left, int right)
{
    if(left < right)
    {
        int p = partition(trees, left, right);

        quickSort(trees, left, p - 1);
        quickSort(trees, p + 1, right);
    }
}


int main()
{

    return 0;
}