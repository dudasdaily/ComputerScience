#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <unordered_map>

using namespace std;

int total_time = 0;
int idle_time = 0;

class Process
{
public:
    int pid;
    int arrived_time;
    int que_enter_time;
    int finished_time;

};

int readFirstLine(ifstream& read_file)
{
    string line;
    getline(read_file, line);

    return stoi(line);
}

void setProcesses(vector<Process*>& processes, unordered_map<int, Process*> arrival)
{
    
}

int main()
{
    ifstream read_file;
    ofstream write_file;

    read_file.open("./srtf.inp");
    write_file.open("./srtf.out");

    if(!read_file.is_open() || !write_file.is_open())
        return -1;
    // 파일 열기 완료!

    int n = readFirstLine(read_file);
    priority_queue<Process*, > ready_queue;
    vector<Process*> processes;
    unordered_map<int, Process*> arrival;

    for(int i = 0; i < n; i++)
    {
        setProcesses();
    }

    return 0;
}