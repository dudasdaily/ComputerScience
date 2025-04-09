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

    Thread() : cpu_time(0), io_time(0) {}

    void cpu_work() { cpu_time -= 1; }
    void io_work() { io_time -= 1; }
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

    Process() : is_finished(false) {}

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

void readProcessInfo(ifstream& read_file, Process* process)
{
    string line;
    int num;

    getline(read_file, line);
    stringstream ss(line);

    ss >> num;
    process->generation_time = num;

    int cnt = 1;
    while(ss >> num)
    {
        if(num == -1) break;

        if(cnt % 2 != 0) process->cpu_burst_times.push_back(num);
        else process->io_burst_times.push_back(num);

        cnt++;
    }
}

// 포인터를 비교하는 우선순위 비교 함수
struct Compare {
    bool operator()(const Process* a, const Process* b) const {
        if(a->thread.cpu_time != b->thread.cpu_time)
            return a->thread.cpu_time > b->thread.cpu_time;
        if(a->queue_entrance_time != b->queue_entrance_time)
            return a->queue_entrance_time > b->queue_entrance_time;
        return a->pid > b->pid;
    }
};

void check_arrived_processes(vector<Process*>& processes, priority_queue<Process*, vector<Process*>, Compare>& ready_queue)
{
    for(auto it = processes.begin(); it != processes.end(); )
    {
        if ((*it)->generation_time == total_time)
        {
            (*it)->queue_entrance_time = total_time;
            ready_queue.push(*it);
            it = processes.erase(it);
        }
        else
            ++it;
    }
}

void update_io_processes(vector<Process*>& io_waiting, priority_queue<Process*, vector<Process*>, Compare>& ready_queue)
{
    for(auto it = io_waiting.begin(); it != io_waiting.end(); )
    {
        (*it)->thread.io_work();

        if((*it)->thread.io_time == 0)
        {
            if(!(*it)->cpu_burst_times.empty())
            {
                (*it)->update_thread();
                (*it)->queue_entrance_time = total_time;
                ready_queue.push(*it);
            }
            else
            {
                (*it)->finished_time = total_time;
                (*it)->is_finished = true;
            }

            it = io_waiting.erase(it);
        }
        else
            ++it;
    }
}

void run_current_process(priority_queue<Process*, vector<Process*>, Compare>& ready_queue, vector<Process*>& io_waiting)
{
    if(ready_queue.empty())
    {
        total_time++;
        idle_time++;
        return;
    }

    Process* current = ready_queue.top();
    ready_queue.pop();

    while(current->thread.cpu_time > 0)
    {
        current->thread.cpu_work();
        total_time += 1;
    }

    io_waiting.push_back(current);
}

bool is_allDone(const vector<Process*>& processes)
{
    for(auto process : processes)
        if(!process->is_finished)
            return false;
    return true;
}

int main()
{
    ifstream read_file("sjf.inp");
    ofstream write_file("sjf.out");

    if(!read_file.is_open() || !write_file.is_open())
    {
        cout << "파일 열기 오류 발생\n";
        return -1;
    }

    string first_line;
    getline(read_file, first_line);
    int n = stoi(first_line);

    priority_queue<Process*, vector<Process*>, Compare> ready_queue;
    vector<Process*> processes;      // 전체 프로세스 목록
    vector<Process*> io_waiting;     // I/O 대기 중

    for(int i = 0; i < n; i++)
    {
        Process* process = new Process();
        process->pid = i;
        readProcessInfo(read_file, process);
        process->update_thread();
        processes.push_back(process);
    }

    while(!is_allDone(processes))
    {
        check_arrived_processes(processes, ready_queue);
        update_io_processes(io_waiting, ready_queue);
        run_current_process(ready_queue, io_waiting);
    }

    cout << idle_time << endl;
    for(auto p : processes)
    {
        cout << p->finished_time << endl;
    }

    // 메모리 해제
    for(auto p : processes)
        delete p;

    read_file.close();
    write_file.close();

    return 0;
}
