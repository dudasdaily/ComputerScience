#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

int total_time = 0;
int idle_time = 0;

// CPU 및 IO 작업을 나타내는 스레드 클래스
class Thread{
public:
    int cpu_time;
    int io_time;
};

// 프로세스 클래스: 프로세스의 생성 시간, 큐에 들어간 시간, 종료 시간 등을 포함
class Process{
public:
    int generation_time = 0;
    int que_enter_time = 0;
    int finished_time = 0;
    int pid;

    vector<Thread> threads;
};

// ready queue에서 SJF 기준으로 정렬하기 위한 비교 함수
struct Compare {
    bool operator()(const Process* a, const Process* b) const {
        if (a->threads.front().cpu_time != b->threads.front().cpu_time)
            return a->threads.front().cpu_time > b->threads.front().cpu_time;

        if (a->que_enter_time != b->que_enter_time)
            return a->que_enter_time > b->que_enter_time;

        return a->pid > b->pid;
    }
};

// 입력 파일의 첫 번째 줄에서 프로세스 개수를 읽음
int processFirstLine(ifstream& read_file)
{
    string line;
    getline(read_file, line);
    return stoi(line);
}

// 한 줄씩 읽어 각 프로세스의 생성 시간과 (CPU, IO) 버스트 쌍을 파싱
void processLine(ifstream& read_file, Process* process)
{
    string line;
    getline(read_file, line);
    stringstream ss(line);

    ss >> process->generation_time;

    int num = 0;
    bool flag = false;
    Thread thread;

    for (int i = 1; ss >> num; i++)
    {
        if (num == -1)
            break;

        if (i % 2 != 0) // 홀수번째는 CPU burst
        {
            thread = Thread();
            thread.cpu_time = num;
            flag = true;
        }
        else // 짝수번째는 IO burst
        {
            thread.io_time = num;
            process->threads.push_back(thread);
            flag = false;
        }
    }

    if (flag) // 마지막이 CPU burst만 있는 경우
    {
        thread.io_time = 0;
        process->threads.push_back(thread);
    }
}

// 현재 시간에 생성되는 프로세스들을 ready queue에 넣음
void checkTime(vector<Process*>& processes,
               priority_queue<Process*, vector<Process*>, Compare>& ready_queue)
{
    for (Process* process : processes)
    {
        if (process->generation_time == total_time)
        {
            process->que_enter_time = total_time;
            ready_queue.push(process);
        }
    }
}

// CPU 작업을 한 사이클 수행
void cpuWork(Process* process)
{
    process->threads.front().cpu_time -= 1;
}

// IO 작업을 한 사이클 수행
void ioWork(Process* io_process)
{
    io_process->threads.front().io_time -= 1;
}

// 해당 프로세스를 주어진 큐에서 제거
void eraseProcess(Process* process, vector<Process*>& processes)
{
    auto it = find(processes.begin(), processes.end(), process);
    if (it != processes.end())
        processes.erase(it);
}

// IO 작업 중인 프로세스들의 상태를 체크해 완료 시 ready queue 또는 종료 처리
void ioCheck(Process* io_process, vector<Process*>& processes,
             vector<Process*>& io_remove_list,
             priority_queue<Process*, vector<Process*>, Compare>& ready_queue,
             vector<Process*>& finished_queue)
{
    if (io_process->threads.front().io_time <= 0)
    {
        io_process->threads.erase(io_process->threads.begin()); // cpuburst와 ioburst를 갱신 
        io_remove_list.push_back(io_process); // io_time이 0이 됐으므로 io_queue에서 제거하기 위해

        if (io_process->threads.empty()) // 모든 작업이 끝났을 경우
        {
            io_process->finished_time = total_time;
            finished_queue.push_back(io_process);
            eraseProcess(io_process, processes);
        }
 
        else // 다시 ready queue에 삽입
        {
            io_process->que_enter_time = total_time;
            ready_queue.push(io_process);
        }
    }
}

int main()
{
    ifstream read_file;
    ofstream write_file;

    read_file.open("./sjf.inp");
    write_file.open("./sjf.out");

    if (!read_file.is_open() || !write_file.is_open())
        return -1;

    vector<Process*> processes;
    priority_queue<Process*, vector<Process*>, Compare> ready_queue;
    vector<Process*> io_queue;
    vector<Process*> finished_queue;

    int n = processFirstLine(read_file); // 프로세스 개수

    for (int i = 0; i < n; i++)
    {
        Process* process = new Process();
        process->pid = i;

        processLine(read_file, process); // 프로세스 정보 읽기
        processes.push_back(process);
    }

    // 메인 루프
    while (true)
    {
        if (processes.empty())
            break;

        checkTime(processes, ready_queue); // 현재 시간에 도착한 프로세스 추가

        if (!ready_queue.empty())
        {
            
            Process* current = ready_queue.top(); ready_queue.pop();

            // 현재 프로세스의 CPU burst 처리
            while (current->threads.front().cpu_time > 0)
            {
                cpuWork(current); // CPU 작업 1 cycle
                total_time += 1;
                checkTime(processes, ready_queue); // 새로 도착한 프로세스 확인

                vector<Process*> io_remove_list;
                for (Process* io_process : io_queue)
                {
                    ioWork(io_process); // IO 작업 1 cycle
                    ioCheck(io_process, processes, io_remove_list, ready_queue, finished_queue);
                }

                for (Process* p : io_remove_list)
                {
                    eraseProcess(p, io_queue); // IO 작업 끝난 프로세스 제거
                }

                // cpu도 다 쓰고, io도 다 쓴 경우
                if(current->threads.front().cpu_time == 0 && current->threads.front().io_time == 0)
                {
                    io_queue.push_back(current); // IO 작업을 위해 대기
                    ioCheck(current, processes, io_remove_list, ready_queue, finished_queue);
                    eraseProcess(current, processes);
                }

                // cpu를 다 썼지만, io를 해야하는 경우
                else if (current->threads.front().cpu_time == 0)
                    io_queue.push_back(current); // IO 작업을 위해 대기
            }
        }

        else if(!io_queue.empty()) // ready queue는 비어있고, IO 작업만 있는 경우
        {
            total_time += 1;
            checkTime(processes, ready_queue);

            vector<Process*> io_remove_list;
            for (Process* io_process : io_queue)
            {
                ioWork(io_process);
                ioCheck(io_process, processes, io_remove_list, ready_queue, finished_queue);
            }

            for (Process* p : io_remove_list)
            {
                eraseProcess(p, io_queue);
            }

            if(processes.empty())
                continue;
            
            // 마지막 프로세스의 마지막 작업은 idle_time을 증가시키지 않기 위해서
            if(processes.size() == 1 && processes.front()->threads.size() == 1 && processes.front()->threads.front().cpu_time == 0)
                continue;

            idle_time += 1; // CPU 유휴 시간 증가
        }

        else
        {
            total_time += 1;
            idle_time += 1;
        }
    }

    write_file << idle_time << endl;

    // 
    sort(finished_queue.begin(), finished_queue.end(), [](const Process* a, const Process* b){
        return a->pid < b->pid;
    });

    for(Process* p : finished_queue)
    {
        write_file << p->finished_time << endl;
        // delete(p);
    }

    read_file.close();
    write_file.close();

    return 0;
}