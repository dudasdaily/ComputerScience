#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int total_time = 0;
int idle_time = 0;
int finishedProc = 0;

class Job
{
public:
    int cpuTime;
    int ioTime;
};

class Process
{
public:
    int pid;
    int rqEnterTime;
    int finishedTime;

    Job job;
    vector<Job> jobs;

    void cpuWork()
    {
        job.cpuTime--;
    }

    void ioWork()
    {
        job.ioTime--;
    }

    void refreshJob()
    {
        if (!jobs.empty())
        {
            job = jobs.front();
            jobs.erase(jobs.begin());
        }
    }
};

unordered_map<int, vector<Process *>> processArrivalTime;
vector<Process *> processes;
vector<Process *> io_q;

struct Compare
{
    const bool operator()(const Process *a, const Process *b)
    {
        if (a->job.cpuTime != b->job.cpuTime)
            return a->job.cpuTime > b->job.cpuTime;

        if (a->rqEnterTime != b->rqEnterTime)
            return a->rqEnterTime > b->rqEnterTime;

        return a->pid > b->pid;
    }
};

priority_queue<Process *, vector<Process *>, Compare> rq; // 레디큐

int readFirstInt(ifstream &inputFile)
{
    string line;
    getline(inputFile, line);

    return stoi(line);
}

void setProcessJob(Process *&proc, stringstream &line)
{
    int data;

    Job job;

    int i = 0;

    while (line >> data)
    {
        if (data == -1)
            break;

        if (i % 2 == 0)
        {
            job.cpuTime = data;
        }

        if (i % 2 != 0)
        {
            job.ioTime = data;
            proc->jobs.push_back(job);
        }

        i++;
    }

    if (i % 2 != 0)
    {
        job.ioTime = 0;
        proc->jobs.push_back(job);
    }

    proc->refreshJob();
}

// set process's pid, push process to processArrivalTime map!
Process *createProcess(int pid, stringstream &line)
{
    Process *proc = new Process();
    proc->pid = pid; // set pid

    int arrivalTime;
    line >> arrivalTime;

    processArrivalTime[arrivalTime].push_back(proc);
    setProcessJob(proc, line);

    return proc;
}

void pushArrivedProc()
{
    if (processArrivalTime.count(total_time))
    {
        for (Process *p : processArrivalTime[total_time])
        {
            p->rqEnterTime = total_time;
            rq.push(p);
        }
    }
}

Process *scheduling()
{
    Process *proc = rq.top();
    rq.pop();

    return proc;
}

void eraseProc(Process *&proc, vector<Process *> &v)
{
    auto it = find(v.begin(), v.end(), proc);

    if (it != v.end())
        v.erase(it);
}

void pushToReadyQueueIfIoDone()
{
    vector<Process *> removeList;
    for (Process *p : io_q)
    {
        // IO작업을 다 끝냈으면
        if (p->job.ioTime <= 0)
        {
            removeList.push_back(p);

            // 프로세스 종료
            if (p->jobs.empty())
            {
                p->finishedTime = total_time;
                finishedProc++;
            }

            else
            {
                p->refreshJob();
                p->rqEnterTime = total_time;
                rq.push(p);
            }
        }
    }

    for (Process *p : removeList)
    {
        eraseProc(p, io_q);
    }
}

void pushToIoQueueIfCpuDone(Process *&current)
{
    if (current->job.cpuTime <= 0)
    {
        bool isCurrentFinished = current->job.ioTime <= 0 && current->jobs.empty();
        if (isCurrentFinished)
        {
            current->finishedTime = total_time;
            finishedProc++;

            return;
        }

        if (current->job.ioTime > 0)
        {
            io_q.push_back(current);
        }
    }
}

void WorkIoQueue()
{
    for (Process *p : io_q)
    {
        p->ioWork();
    }
}

void printInfo(Process *&p)
{
    printf("Time=%d selectedProcess=%d idleTime=%d\n", total_time, p->pid, idle_time);
}

int main()
{
    ifstream inputFile;
    ofstream outputFile;

    inputFile.open("./srtf.inp");
    outputFile.open("./srtf.out");

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        cout << "파일열기 실패!" << endl;
        return -1;
    }

    int numProcesses = readFirstInt(inputFile);

    // 프로세스 생성
    for (int i = 0; i < numProcesses; i++)
    {
        string lineStr;
        getline(inputFile, lineStr);
        stringstream line(lineStr);

        Process *proc = createProcess(i, line);
        processes.push_back(proc);
    }

    // 메인 루프 시작
    while (true)
    {
        if (finishedProc == numProcesses)
            break;

        pushArrivedProc();

        // 레디큐가 있는 경우
        if (!rq.empty())
        {
            Process *current = scheduling();
            current->cpuWork();
            WorkIoQueue();
            total_time += 1;

            pushToReadyQueueIfIoDone();
            pushToIoQueueIfCpuDone(current);

            if (current->job.cpuTime > 0)
            {
                // current->rqEnterTime = total_time; // ❌ rqEnterTime 갱신 금지
                rq.push(current);
            }

            continue;
        }

        // 이 밑은 다, 레디큐가 없는 경우임.
        if (io_q.empty())
        {
            idle_time++;
            total_time++;

            continue;
        }

        bool isLastProc = (finishedProc == (numProcesses - 1) && io_q.front()->jobs.empty() && io_q.front()->job.ioTime > 0);
        if (!isLastProc)
        {
            idle_time++;
        }

        WorkIoQueue();
        total_time += 1;
        pushToReadyQueueIfIoDone();
    }

    outputFile << idle_time << endl;

    for (auto p : processes)
    {
        outputFile << p->finishedTime << endl;
    }

    return 0;
}
