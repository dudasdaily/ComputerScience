#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int total_time = 0;

class Thread{
public:
    int cpu_time;
    int io_time;

    Thread() {}
    Thread(int cpu_time, int io_time)
    {
        this->cpu_time = cpu_time;
        this->io_time = io_time;
    }
};

class Process{
public:
    int generation_time;
    int pid;
    Thread thread;
    vector<int> cpu_burst_times;
    vector<int> io_burst_times;

    Process() {}

    void update_thread_cpu()
    {
        if(!cpu_burst_times.empty())
        {
            thread.cpu_time = cpu_burst_times.front();
            cpu_burst_times.erase(cpu_burst_times.begin());
        }
    }

    void update_thread_io()
    {
        if(!io_burst_times.empty())
        {
            thread.io_time = io_burst_times.front();
            io_burst_times.erase(io_burst_times.begin());
        }
    }
};

void readProcessInfo(ifstream& read_file, Process& process)
{
    string line;
    int num;

    getline(read_file, line);

    stringstream ss(line);

    ss >> num;
    process.generation_time = num; // 생성시간 초기화

    int cnt = 1;

    while(ss >> num)
    {
        if(num == -1)
            break;

        if(cnt % 2 != 0)
        {
            process.cpu_burst_times.push_back(num);
            cnt += 1;
        }

        else if(cnt % 2 == 0)
        {
            process.io_burst_times.push_back(num);
            cnt += 1;
        }
    }
}



// 우선순위 큐의 우선순위를 정해주는 함수
struct Compare{
    bool operator()(const Process& a, const Process& b) const {
        if(a.thread.cpu_time != b.thread.cpu_time)
            return a.thread.cpu_time > b.thread.cpu_time;
        
        if(a.generation_time != b.generation_time)
            return a.generation_time > b.generation_time;
        
        return a.pid > b.pid;
    }
};

int main()
{
    ifstream read_file;
    ofstream write_file;

    read_file.open("sjf.inp");
    write_file.open("sjf.out");

    if(!read_file.is_open())
    {
        printf("파일 열기 오류 발생\n");
        return -1;
    }

    if(!write_file.is_open())
    {
        printf("출력 파일 열기 오류 발생\n");
        return -1;
    }

    string first_line;
    getline(read_file, first_line);
    int n = stoi(first_line);

    Process processes[n];

    for(int i = 0; i < n; i++)
    {
        Process process;

        process.pid = i;
        readProcessInfo(read_file, process);

        process.update_thread_cpu();
        process.update_thread_io();

        processes[i] = process;
    }

    while(true)
    {
        

        total_time += 1;
    }

    return 0;
}