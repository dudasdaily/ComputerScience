#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

class Job
{
    int cpu_job;
    int io_job;
};

class Process
{
    int pid;
    int que_enter_time;
    vector<Job> jobs;
};

int readFirstLine(ifstream &input_file)
{
    string line;
    getline(input_file, line);

    return stoi(line);
}

int main()
{
    ifstream input_file;
    ofstream output_file;

    input_file.open("./srtf.inp");
    output_file.open("./srtf.out");

    if (!input_file.is_open() || !output_file.is_open())
    {
        cout << "파일 열기 중 오류가 발생했습니다. 프로그램을 종료합니다!\n"
             << endl;

        return -1;
    }

    // 테스트 케이스 횟수
    int n = readFirstLine(input_file);

        for (int i = 0; i < n; i++)
    {
    }

    return 0;
}