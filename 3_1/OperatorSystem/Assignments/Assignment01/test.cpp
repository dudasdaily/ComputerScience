#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
using namespace std;

int main()
{
    map<string, int> lastname_cnt;
    map<string, string> name_map;

    ifstream file_read;
    file_read.open("./test.inp");

    if(file_read.is_open())
    {
        string first_line;
        getline(file_read, first_line);
        
        string id_num, first_name, last_name;

        

    }
    

    return 0;
}