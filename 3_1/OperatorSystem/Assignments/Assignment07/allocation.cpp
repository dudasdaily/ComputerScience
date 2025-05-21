#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>

#define RAM_SIZE 1000

using namespace std;

class Process{
public:
    int pid;
    int request_time;
    int running_time;
    int size;

    Process(){}
    Process(int pid) {this->pid = pid;}
};

int read_n(ifstream& input_file)
{
    string temp;
    getline(input_file, temp);

    return stoi(temp);
}

void read_process(ifstream& input_file, Process& p)
{
    string line;
    getline(input_file, line);
    
    stringstream ss(line);
    ss >> p.request_time;
    ss >> p.running_time;
    ss >> p.size; 
}

void check_process_request(unordered_map<int, vector<Process *>> request_map, int total_time, queue<Process>& ready_q)
{
    if(request_map.count(total_time))
    {
        for(Process* p : request_map[total_time])
        {
            ready_q.push(*p);
        }
    }
}

void allocate(Process p, bool* ram, int start_idx)
{
    for(int i = start_idx; i < start_idx + p.size; i++)
    {
        ram[i] = true;
    }
}

void deallocate(Process p, bool* ram, int start_idx)
{
    for(int i = start_idx; i < start_idx + p.size; i++)
    {
        ram[i] = false;
    }
}

void first_fit(vector<Process> processes, unordered_map<int, vector<Process *>> request_map, ofstream& output_file)
{
    int total_time = 0;
    int finished_process_cnt = 0;
    queue<Process> ready_q;

    bool ram[RAM_SIZE] = {false, };

    while(true)
    {
        if(finished_process_cnt == processes.size())
            break;
        
        check_process_request(request_map, total_time, ready_q);
        

        total_time += 1;
    }
}

int main()
{
    ifstream input_file("./allocation.inp");
    ofstream output_file("./allocation.out");

    int n = read_n(input_file);

    vector<Process> processes;
    unordered_map<int, vector<Process *>> request_map;
    

    // 프로세스 설정
    for(int pid = 0; pid < n; pid++)
    {
        Process* p = new Process(pid);
        read_process(input_file, *p);
        processes.push_back(*p);
        request_map[p->request_time].push_back(p);
    }


    return 0;
}