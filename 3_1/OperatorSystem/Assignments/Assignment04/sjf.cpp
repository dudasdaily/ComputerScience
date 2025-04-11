#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int total_time = 0;
int idle_time = 0;

class Burst{
public:
    int cpu_burst;
    int io_burst;
};

class Process{
public:
    int pid;
    int arrived_time; // 생성 시간
    int que_enter_time;
    int finished_time;
    
    bool is_arrived = false;

    Burst burst;
    vector<Burst> bursts;
};

struct Compare {
    bool operator()(const Process* a, const Process* b) const {
        if (a->burst.cpu_burst != b->burst.cpu_burst)
            return a->burst.cpu_burst > b->burst.cpu_burst;

        if (a->que_enter_time != b->que_enter_time)
            return a->que_enter_time > b->que_enter_time;

        return a->pid > b->pid;
    }
};

int readFirstLine(ifstream& read_file)
{
    string line;
    getline(read_file, line);

    return stoi(line);
}

void setProcesses(stringstream& line, vector<Process*>& processes,
                  unordered_map<int, vector<Process*>>& arrived_map, int pid)
{
    Process* process = new Process();
    process->pid = pid;
    line >> process->arrived_time; // 생성 시간 초기화
    
    int num;
    bool has_io;

    for(int i = 1; line >> num; i++)
    {
        if(num == -1)
            break;

        if(i % 2 != 0)
        {
            process->burst.cpu_burst = num;
            has_io = false;
        }

        else if(i % 2 == 0)
        {
            process->burst.io_burst = num;
            process->bursts.push_back(process->burst);
            has_io = true;
        }
    }

    if(!has_io)
    {
        process->burst.io_burst = 0;
        process->bursts.push_back(process->burst);
    }

    process->burst = process->bursts[0];
    process->bursts.erase(process->bursts.begin());

    processes.push_back(process);
    arrived_map[process->arrived_time].push_back(process);
}

void checkArrivedTime(int t, unordered_map<int, vector<Process*>>& arrived_map,
                priority_queue<Process*, vector<Process*>, Compare>& ready_queue)
{
   if(arrived_map.count(t))
   {
        for(Process* p : arrived_map[t])
        {
            if(p->is_arrived == false)
            {
                p->que_enter_time = t;
                ready_queue.push(p);
                p->is_arrived = true;
            }
        }
   }
}

void cpuWork(Process* p)
{
    p->burst.cpu_burst--;
}

void ioWork(vector<Process*>& io_list)
{
    for(Process* p : io_list)
    {
        p->burst.io_burst--;
    }
}

void refreshBurst(Process* p)
{
    Burst nextBurst = p->bursts.front();
    p->bursts.erase(p->bursts.begin());

    p->burst.cpu_burst = nextBurst.cpu_burst;
    p->burst.io_burst = nextBurst.io_burst;
}

void eraseProcess(Process* p, vector<Process*>& processes)
{
    auto it = find(processes.begin(), processes.end(), p);
    if (it != processes.end())
        processes.erase(it);
}

void ioCheck(vector<Process*>& io_list, vector<Process*>& processes,
    priority_queue<Process*, vector<Process*>, Compare>& ready_queue)
{
    if(io_list.empty())
        return;
    
    vector<Process*> remove_list;

    for(Process* p : io_list)
    {
        // io작업을 다했고, 프로세스의 모든 작업을 끝낸 친구들
        if(p->burst.io_burst <= 0 && p->bursts.empty())
        {
            remove_list.push_back(p); // io_list에서 제거해주기 위해 제거 리스트에 넣는다.
            p->finished_time = total_time;
            eraseProcess(p, processes); // 프로세스 벡터에서 제거
        }

        // io작업을 다했으나, 프로세스의 작업들을 다 못 끝낸 친구들
        else if(p->burst.io_burst <= 0)
        {
            refreshBurst(p);
            p->que_enter_time = total_time;
            ready_queue.push(p);
            remove_list.push_back(p);
        }
    }

    // io_list에서 제거
    for(Process* p : remove_list)
    {
        eraseProcess(p, io_list);
    }
}

void cpuCheck(Process* p, vector<Process*>& io_list,
    vector<Process*>& processes, priority_queue<Process*, vector<Process*>, Compare>& ready_queue)
{
    if(p->burst.cpu_burst == 0)
    {
        if(p->burst.io_burst != 0)
        {
            io_list.push_back(p);
        }

        else if(p->burst.io_burst == 0 && p->bursts.empty())
        {
            p->finished_time = total_time;
            eraseProcess(p, processes);
        }

        // io작업이 없고, 작업이 남았으면
        else if(p->burst.io_burst == 0 && !p->bursts.empty())
        {
            refreshBurst(p);
            io_list.push_back(p);
        }
    }
}

int main()
{
    ifstream read_file;
    ofstream write_file;

    read_file.open("./sjf.inp");
    write_file.open("./sjf.out");

    if(!read_file.is_open() || !write_file.is_open())
        return -1;
    // 파일 열기 완료!

    int n = readFirstLine(read_file);
    vector<Process*> processes;
    vector<Process*> io_list;
    priority_queue<Process*, vector<Process*>, Compare> ready_queue;
    unordered_map<int, vector<Process*>> arrived_map; 
    
    // 프로세스를 설정하고 벡터에 넣음
    for(int i = 0; i < n; i++)
    {
        string line;
        getline(read_file, line); // 한줄 읽기
        stringstream ss(line);
        
        setProcesses(ss, processes, arrived_map, i); // 입력 파일로 부터 프로세스들을 설정함
    }

    vector<Process*> ended_processes = processes;

    // 메인 루프 시작!
    while(true)
    {
        // 메인 루프 종료 조건
        // 모든 프로세스가 작업을 끝낼 시 종류
        if(processes.empty())
            break;
       
        // 생성 시간 체크
        checkArrivedTime(total_time, arrived_map, ready_queue);

        // 레디큐가 있으면, 즉 cpu작업할 것들이 있으면
        if(!ready_queue.empty())
        {           
            Process* current = ready_queue.top(); ready_queue.pop(); // 레디큐에서 뺀다

            // 
            while(current->burst.cpu_burst > 0)
            {
                cpuWork(current);
                ioWork(io_list);
                total_time++;
                
                checkArrivedTime(total_time, arrived_map, ready_queue);
    
                ioCheck(io_list, processes, ready_queue);

                cpuCheck(current, io_list, processes, ready_queue);
            }
        }

        // 레디큐는 없지만, io작업을 할 프로세스들이 있는 경우
        else if(ready_queue.empty() && !io_list.empty())
        {
            bool is_last_process = (processes.size() == 1 && processes.front()->burst.cpu_burst == 0 && processes.front()->bursts.empty());

            ioWork(io_list);
            total_time++;

            if(!is_last_process)
                idle_time++;

            checkArrivedTime(total_time, arrived_map, ready_queue);

            ioCheck(io_list, processes, ready_queue);
        }

        else
        {
            total_time++;
            idle_time++;

            checkArrivedTime(total_time, arrived_map, ready_queue);
        }
    }

    // pid기준으로 오름차순 정렬
    sort(ended_processes.begin(), ended_processes.end(), [](const Process* a, const Process* b){
       return a->pid < b->pid;
    });

    write_file << idle_time << endl;

    for(Process* p : ended_processes)
    {
        write_file << p->finished_time << endl;
    }

    return 0;
}


/*
# 메인 루프 로직(프로그램 설계한 방법)
==============================================================================================================================
1. 모든 프로세스들의 생성 시간(arrived_time)을 검색해서 현재 시간과 같은 프로세스가 있으면,
   레디 큐에 넣는다.

2. 레디 큐에 프로세스가 있으면, cpu작업
3. io리스트들을 작업한다.
(+) 로직의 1번을 한다. 즉 프로세스들의 생성 시간을 확인한다.

4. io작업들이 끝난 프로세스가 있는지 확인한다

4-1. 만약 io작업이 끝난 프로세스가 있을 경우 -> 프로세스의 bursts를 확인한다.
4-1-1. 만약 프로세스의 bursts가 있으면 현재 burst를 갱신하고, 레디큐에 넣는다.
4-1-2. 만약 프로세스의 bursts가 없으면, 프로세스가 모든 작업을 끝낸 것이므로 프로세스 벡터에서 제거한다.


5. cpu작업이 끝났는지 확인한다.(cpu_burst > 0인 동안 반복)
5-1. cpu작업이 끝났으면 (io_burst가 있는지 확인하고)
(5-1-1. io_burst가 있다면, io_list에 프로세스를 넣는다
5-1-2. io_burst가 없다면, bursts를 확인한다.
5-1-3. bursts가 있다면 burst를 갱신하고, io_list에 넣는다.
5-1-4. bursts가 없다면 프로세스를 프로세스 벡터에서 제거한다.)


6. cpu작업은 없지만, io작업이 있는경우. 즉, 레디큐는 없지만 io할 io_list가 있는경우
6-1. io작업을 한다.
6-3. total_time과 idle_time을 증가시킨다. //// 마지막 프로세스의 마지막 버스트에서 io작업을하는경우 idle_time을 증가시키지 않는다
(+) 로직의 1번을 한다. 즉 프로세스들의 생성 시간을 확인한다.
6-5. io작업들이 끝난 프로세스가 있는지 확인한다.
==============================================================================================================================

어려웠던 점
: 원래 짰던 프로그램이 프로세스들의 생성시간에 레디 큐에 넣어 줄 때, 함수에서
  processes의 모든 프로세스들을 확인하는 방법으로 해서
  엄청 오랜 시간이 걸려, 실패했었다.
  unordered_map<Process*>을 사용해서 생성 시간을 키, 프로세스 포인터를 값으로 해서,
  프로세스들의 생성시간을 확인하는 함수에서 O(n)의 시간이 들게 바꿨더니 훨씬 빨라졌다! 굳굳

  또 변화하는 total_time에 따라 객체들의 값이 변하는걸 생각하는게 너무 어려웠다

배운 점
: 큰 문제를 작은 문제로 쪼개서 생각하는 법을 배웠다.
  total_time 때문에 작은 단위로 코딩을 하지 않으면 너무 많은것들이 꼬여버리는 경우가 너무 많았다.
  생각을 글로 먼저 적어보고, 그 글을 따라서 코딩을 하니 훨씬 오류도 적고 편하게 코딩이 가능했다!

  이렇게 하면 값 복사 
  그 외에 과제를 하면서 STL의 사용법들을 많이 배웠다.
  특히 함수 객체의 개념이 새로웠다.
  
  그리고 포인터랑 call by reference의 활용법도 많이 배웠다.
  처음에는 processes를 vector<Process>로 만들었는데, 이렇게 하면 함수의 파라미터로 넘길 때,
  레퍼런스로 넘겨도 원본 내용을 못 바꾸는 경우가 생겼다.
  그래서 다시 Process* 로 바꿨는데 이렇게 바꿔버리니 코드 전체를 수정해야해서 너무 힘들었다.

  다음부터는 자료구조를 선택할 때, 신중하게 많이 생각하고 나서 선택할 것 같다!

  디버깅 실력도 좀 는거 같다.
*/