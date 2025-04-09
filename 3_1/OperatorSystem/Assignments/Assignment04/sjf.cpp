#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int total_time = 0;
int idle_time = 0;

class Thread{
public:
    int cpu_time;
    int io_time;

    Thread()
    {
        cpu_time = 0;
        io_time = 0;
    }

    void cpu_work()
    {
        cpu_time -= 1;
    }

    void io_work()
    {
        io_time -= 1;
    }
};

class Process{
public:
    int generation_time;
    int queue_entrance_time;
    int pid;
    int finished_time;
    bool is_finished;
    Thread thread;
    vector<int> cpu_burst_times;
    vector<int> io_burst_times;
    
    Process()
    {
        is_finished = false;
    }

    void update_thread()
    {
        if(!cpu_burst_times.empty() && thread.cpu_time == 0)
        {
            thread.cpu_time = cpu_burst_times.front();
            cpu_burst_times.erase(cpu_burst_times.begin());
        }

        if(!io_burst_times.empty() && thread.io_time == 0)
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

// 우선순위 큐의 우선순위를 정해주는 함수 객체
struct Compare{
    bool operator()(const Process& a, const Process& b) const {
        if(a.thread.cpu_time != b.thread.cpu_time)
            return a.thread.cpu_time > b.thread.cpu_time;
        
        if(a.queue_entrance_time != b.queue_entrance_time)
            return a.queue_entrance_time > b.queue_entrance_time;
        
        return a.pid > b.pid;
    }
};

// processes에 있는 process들을 하나하나 체크해서 그 프로세스의 generation_time이 total_time과 같아지면 레디큐에 넣음
void check_arrived_processes(vector<Process>& processes, priority_queue<Process, vector<Process>, Compare>& ready_queue)
{
    for(auto it = processes.begin(); it != processes.end(); )
    {
        if (it->generation_time == total_time)
        {
            it->queue_entrance_time = total_time;
            ready_queue.push(*it);
            it = processes.erase(it); // 삭제 및 이터레이터 갱신, erase()는 삭제한 위치의 다음 요소를 가리킴
        }
        else
            ++it; // 다음 processes 확인
    }
}

void update_io_processes(vector<Process>& io_waiting, priority_queue<Process, vector<Process>, Compare>& ready_queue)
{
    for(auto it = io_waiting.begin(); it != io_waiting.end(); )
    {
        it->thread.io_work();

        if(it->thread.io_time == 0)
        {
            if(!it->cpu_burst_times.empty())
            {
                it->update_thread();
                it->queue_entrance_time = total_time;
                ready_queue.push(*it); // ready_queue에 넣음
            }

            // 한 프로세스의 작업이 다 끝남
            else
            {
                it->finished_time = total_time;
                it->is_finished = true;
            }
            
            it = io_waiting.erase(it); // io_waiting에서 삭제 및 이터레이터 갱신
            
        }
        
        else
            ++it; // 다음 io_waiting 확인
    }
}

void run_current_process(priority_queue<Process, vector<Process>, Compare>& ready_queue, vector<Process>& io_waiting)
{
    // 레디 큐가 비었으면 idle_time도 늘려줌
    if(ready_queue.empty())
    {
        total_time++;
        idle_time++;

        return;
    }

    // 레디 큐에 있는 process를 가져옴
    Process current = ready_queue.top();
    ready_queue.pop();

    // process의 cpu_time이 0이 될때까지 cpu를 씀
    while(current.thread.cpu_time > 0)
    {
        current.thread.cpu_work();
        total_time += 1;
    }
    
    io_waiting.push_back(current);
}

bool is_allDone(vector<Process>& processes)
{
    bool allDone = true;

    for(auto process : processes)
    {
        if(process.is_finished == false)
            allDone = false;
    }

    return allDone;
}

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

    // 입출력 설정 완료!
    // ================

    priority_queue<Process, vector<Process>, Compare> ready_queue;
    vector<Process> processes;
    vector<Process> io_waiting;

    for(int i = 0; i < n; i++)
    {
        Process process;

        process.pid = i;
        readProcessInfo(read_file, process); // 입력 파일을 한 줄 읽어서 process의 cpu_burst_time과 io_burst_time에 나눠서 넣음.

        process.update_thread();

        processes.push_back(process);
    }

    while(!is_allDone(processes))
    {
        check_arrived_processes(processes, ready_queue);
        update_io_processes(io_waiting, ready_queue);
        run_current_process(ready_queue, io_waiting);
    }

    return 0;
}