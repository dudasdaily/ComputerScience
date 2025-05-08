#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// TO-DO
/*
    read_max_request_num() 함수 완성.
*/

class Resource {
public:
    int resource_id;
    int instance_num;
};

class Process {
public:
    int process_id;
    
    vector<int> max;
    vector<int> allocation;
    vector<int> need;
};

void read_n_m(ifstream &input_file, int& n, int& m)
{
    string line;
    getline(input_file, line);

    stringstream ss(line);

    ss >> n;
    ss >> m;
}

void read_resource_instance_num (ifstream &input_file, const int m, vector<Resource>& resources)
{
    string line;
    getline(input_file, line);

    stringstream ss(line);

    for(int i = 0; i < m; i++)
    {
        Resource* r = new Resource();
        r->resource_id = i;
        ss >> r->instance_num;

        resources.push_back(*r);
    }
}

// 미완성
void read_max_request_num(ifstream &input_file, const int m, vector<Process>& processes)
{
    string line;
    getline(input_file, line);

    stringstream ss(line);

    for(int i = 0; i < m; i++)
    {
        Process* p = new Process();
    }
}

int main()
{
    ifstream input_file; input_file.open("./banker.inp");
    ofstream output_file; output_file.open("./banker.out");

    if(!input_file.is_open() || !output_file.is_open())
    {
        cout << "파일 열기 실패!" << endl;
    }

    // n : 프로세스 수
    // m : 자원 종류의 개수
    int n, m;

    vector<Resource> resources;
    vector<Process> processes;
    
    read_n_m(input_file, n, m);
    read_resource_instance_num(input_file, m, resources);
    read_max_request_num(input_file, m, processes);


    return 0;
}