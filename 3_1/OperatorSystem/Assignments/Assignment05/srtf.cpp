#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

int total_time = 0;

class Job
{
public:
    int cpu_job;
    int io_job;
};

class Process
{
public:
    int pid;
    int enter_time;
    int rq_enter_time;
    vector<Job> jobs;

    Job job;

    void cpuWork()
    {
        job.cpu_job--;
    }

    void ioWork()
    {
        job.io_job--;
    }
};

struct Compare
{
    bool operator()(const Process *a, const Process *b) const
    {
        if (a->job.cpu_job != b->job.cpu_job)
            return a->job.cpu_job > b->job.cpu_job; // a가 크면 -> b보다 우선순위가 낮음..

        if (a->enter_time != b->enter_time)
            return a->enter_time > b->enter_time;

        return a->pid > b->pid;
    }
};

// 입력 파일의 첫 줄을 읽음
int readFirstLine(ifstream &input_file)
{
    string line;
    getline(input_file, line);

    return stoi(line);
}

Process *setProcess(int pid, ifstream &input_file, unordered_map<int, vector<Process *>> &enter_map)
{
    Process *p = new Process();

    p->pid = pid;

    string line;
    getline(input_file, line);

    stringstream ss(line);

    ss >> p->enter_time;

    int data, i = 0;

    Job job;
    bool has_io;

    for (int i = 0; ss >> data; i++)
    {
        if (data == -1)
        {
            if (!has_io)
            {
                job.io_job = 0;
                p->jobs.push_back(job);
            }

            break;
        }

        if (i % 2 == 0)
        {
            job.cpu_job = data;
            has_io = false;
        }

        if (i % 2 != 0)
        {
            job.io_job = data;
            has_io = true;

            p->jobs.push_back(job);
        }
    }

    p->job = p->jobs[0];
    p->jobs.erase(p->jobs.begin());

    enter_map[p->enter_time].push_back(p);
    return p;
}

void checkEnterTime(int t, unordered_map<int, vector<Process *>> &enter_map,
                    priority_queue<Process *, vector<Process *>, Compare> &rq)
{
    if (enter_map.count(t))
    {
        for (Process *p : enter_map[t])
        {
            p->rq_enter_time = t;
            rq.push(p);
        }
    }
}

void ioWork(priority_queue<Process *, vector<Process *>, Compare> &rq,
            vector<Process *> &io_q)
{
}

void cpuWork(priority_queue<Process *, vector<Process *>, Compare> &rq,
             vector<Process *> &io_q)
{
    Process *current = rq.top();
    rq.pop();

    current->cpuWork();
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

    int n = readFirstLine(input_file); // 테스트 케이스 횟수

    vector<Process *> processes;                              // 여러 프로세스들을 담을 리스트
    unordered_map<int, vector<Process *>> enter_map;          // 큐에 들어갈 시간을 체크 해줄 맵
    priority_queue<Process *, vector<Process *>, Compare> rq; // 레디 큐
    vector<Process *> io_q;

    for (int i = 0; i < n; i++)
    {
        Process *p = setProcess(i, input_file, enter_map);

        processes.push_back(p);
    }

    // 메인 루프 시작!
    while (true)
    {
        checkEnterTime(total_time, enter_map, rq);

        if (rq.empty() && io_q.empty())
            break;

        total_time++;
    }

    return 0;
}