#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

class Resource
{
public:
    int resource_id;
    int available;
};

class Process
{
public:
    int process_id;

    vector<int> max;
    vector<int> allocation;
    vector<int> need;
};

queue<vector<int>> ready_queue;

void read_n_m(ifstream &input_file, int &n, int &m)
{
    string line;
    getline(input_file, line);

    stringstream ss(line);

    ss >> n;
    ss >> m;
}

void push_new_resource(const int m, vector<Resource> &resources)
{
    for (int i = 0; i < m; i++)
    {
        Resource *r = new Resource();
        r->resource_id = i;

        resources.push_back(*r);
    }
}

void read_resource_available(ifstream &input_file, const int m, vector<Resource> &resources)
{
    string line;
    getline(input_file, line);

    stringstream ss(line);

    for (int i = 0; i < m; i++)
    {
        int resource_available;
        ss >> resource_available;

        resources[i].available = resource_available;
    }
}

void push_new_process(const int n, vector<Process> &processes)
{
    for (int i = 0; i < n; i++)
    {
        Process *p = new Process();
        p->process_id = i;

        processes.push_back(*p);
    }
}

void read_max_request_num(ifstream &input_file, const int m, const int n, vector<Process> &processes)
{
    string line;

    for (int i = 0; i < n; i++)
    {
        getline(input_file, line);
        stringstream ss(line);

        for (int j = 0; j < m; j++)
        {

            int max_request_num; // processes[i]가 resources[j]를 최대 몇개 사용할 수 있는가
            ss >> max_request_num;

            processes[i].max.push_back(max_request_num);
        }
    }
}

void read_allocation(ifstream &input_file, const int m, const int n, vector<Process> &processes)
{
    string line;

    for (int i = 0; i < n; i++)
    {
        getline(input_file, line);
        stringstream ss(line);

        for (int j = 0; j < m; j++)
        {

            int allocation; // 현재 processes[i]가 resources[j]를 사용하고 있는 갯수.
            ss >> allocation;

            processes[i].allocation.push_back(allocation);
        }
    }
}

void read_empty_line(ifstream &input_file)
{
    string temp;
    getline(input_file, temp);
}

void set_need(const int m, const int n, vector<Process> &processes)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int max = processes[i].max[j];               // processes[i]가 resources[j] 자원을 쓸 수 있는 최대 개수
            int allocation = processes[i].allocation[j]; // 현재 processes[i]가 resources[j]를 현재 몇개 할당받아서 쓰고 있는가.

            int need = max - allocation; // processes[i]가 작업을 끝내려면 resources[j]를 추가로 얼마나 더 할당받아야 하는가?

            processes[i].need.push_back(need);
        }
    }
}

void refresh_available(const int m, const int n, vector<Process> &processes, vector<Resource> &resources)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int allocation = processes[i].allocation[j]; // 현재 process[i]는 resource[j]를 얼마나 할당하고 있는가.
            resources[j].available -= allocation;
        }
    }
}

string read_command(ifstream &input_file)
{

    string command;
    input_file >> command;

    return command;
}

vector<int> read_resource_request(ifstream &input_file, const int m, vector<Process> &processes)
{
    string line;
    getline(input_file, line);

    stringstream ss(line);

    int process_id;
    ss >> process_id;

    vector<int> request_query;

    int resource_request;
    while (ss >> resource_request)
    {
        request_query.push_back(resource_request);
    }

    request_query.push_back(process_id);

    // request_query는
    //{r0 request, r1 request, ..., rm request, 자원을 요청하는 process_id}로 구성됨
    return request_query;
}

bool isSafe(const int m, const int n, vector<Process> processes, vector<Resource> resources, vector<int> request_query)
{
    int process_id = request_query.back();

    for (int j = 0; j < m; j++)
    {
        if (request_query[j] > processes[process_id].need[j])
            return false;

        if (request_query[j] > resources[j].available)
            return false;
    }

    vector<int> work(m);
    vector<bool> finish(n, false);

    // 요청 반영
    for (int j = 0; j < m; j++)
    {
        int &allocation = processes[process_id].allocation[j];
        int &request = request_query[j];
        int &need = processes[process_id].need[j];
        int &max = processes[process_id].max[j];

        allocation += request;
        need = max - allocation;
        resources[j].available -= request;

        work[j] = resources[j].available;
    }

    bool is_changed; // 한 프로세스가 작업을 했는가?
    do
    {
        is_changed = false;
        for (int i = 0; i < n; i++)
        {
            if (finish[i])
                continue;

            bool can_finish = true; // processes[i]의 자원 필요량이 resources[0] ~ resources[m-1]의 자원량보다 작은가?
            for (int j = 0; j < m; j++)
            {
                int need = processes[i].need[j];

                if (need > work[j])
                {
                    can_finish = false;
                    break;
                }
            }

            // processes[i]가 자원을 할당 받을 경우 작업을 다 할 수 있음!
            if (can_finish)
            {
                for (int j = 0; j < m; j++)
                    work[j] += processes[i].allocation[j]; // 일을 다 하고 자원을 반납했다고 가정

                finish[i] = true;
                is_changed = true;
            }
        }

    } while (is_changed);

    for (bool f : finish)
    {
        if (f == false)
            return false;
    }

    return true;
}

void commit_request_to_process(const int m, vector<Process> &processes, vector<Resource> &resources, vector<int> &request_query)
{
    int process_id = request_query.back();

    for (int j = 0; j < m; j++)
    {
        int &need = processes[process_id].need[j];             // 자원 할당 요청을 한 프로세스의 resources[j]에 대한 need
        int &allocation = processes[process_id].allocation[j]; // 자원 할당 요청을 한 프로세스의 resources[j]에 대한 allocation
        int &max = processes[process_id].max[j];               // 자원 할당 요청을 한 프로세스의 resources[j]에 대한 max

        int &available = resources[j].available;

        int request = request_query[j];

        if (need < request)
            continue;

        // 프로세스 정보 갱신
        allocation += request;
        need = max - allocation;

        // 자원 정보 갱신
        available -= request;
    }
}

void write_available(const int m, vector<Resource> &resources, ofstream &output_file)
{
    for (int j = 0; j < m; j++)
    {
        int available = resources[j].available;

        output_file << available << " ";
    }
    output_file << endl;
}

vector<int> read_release_query(ifstream &input_file)
{
    vector<int> release_query;

    string line;
    getline(input_file, line);
    stringstream ss(line);

    int process_id;
    ss >> process_id;

    int resource_release;

    while (ss >> resource_release)
    {
        release_query.push_back(resource_release);
    }

    release_query.push_back(process_id);

    return release_query;
}

void release_resource(int m, vector<Process> &processes, vector<Resource> &resources, vector<int> &release_query)
{
    int process_id = release_query.back();

    for (int j = 0; j < m; j++)
    {
        int &allocation = processes[process_id].allocation[j];
        int &need = processes[process_id].need[j];
        int &max = processes[process_id].max[j];

        int &available = resources[j].available;

        // 프로세스의 정보 변경
        allocation -= release_query[j]; // 자원 반환
        need = max - allocation;        // need 갱신

        // 리소스의 정보 변경
        available += release_query[j];
    }
}

void check_ready_queue(const int m, const int n, vector<Process> &processes, vector<Resource> &resources)
{
    if (ready_queue.empty())
        return;

    int check_times = ready_queue.size();

    for (int i = 0; i < check_times; i++)
    {
        vector<int> request_query = move(ready_queue.front());
        ready_queue.pop();

        if (isSafe(m, n, processes, resources, request_query))
        {
            commit_request_to_process(m, processes, resources, request_query); // 안전하면, request를 처리
        }

        else
        {
            ready_queue.push(request_query); // 안전하지 않으면 요청을 ready_queue에 넣음
        }
    }
}

int main()
{
    ifstream input_file;
    input_file.open("./banker.inp");
    ofstream output_file;
    output_file.open("./banker.out");

    if (!input_file.is_open() || !output_file.is_open())
    {
        cout << "파일 열기 실패!" << endl;
    }

    // n : 프로세스 수
    // m : 자원 종류의 개수
    int n, m;

    vector<Resource> resources;
    vector<Process> processes;

    read_n_m(input_file, n, m);

    push_new_resource(m, resources);
    read_resource_available(input_file, m, resources);

    read_empty_line(input_file); // 빈 줄 제거

    push_new_process(n, processes);
    read_max_request_num(input_file, m, n, processes);

    read_empty_line(input_file); // 빈 줄 제거

    read_allocation(input_file, m, n, processes);
    set_need(m, n, processes);

    refresh_available(m, n, processes, resources);

    read_empty_line(input_file); // 빈 줄 제거

    string command;

    do
    {
        command = read_command(input_file);

        if (command == "request")
        {
            vector<int> request_query = read_resource_request(input_file, m, processes);

            if (isSafe(m, n, processes, resources, request_query))
            {
                commit_request_to_process(m, processes, resources, request_query); // 안전하면, request를 처리
            }

            else
            {
                ready_queue.push(request_query); // 안전하지 않으면 요청을 ready_queue에 넣음
            }

            write_available(m, resources, output_file);
            continue;
        }

        if (command == "release")
        {
            vector<int> release_query = read_release_query(input_file);
            release_resource(m, processes, resources, release_query);

            check_ready_queue(m, n, processes, resources);

            write_available(m, resources, output_file);
        }

    } while (command != "quit");

    return 0;
}