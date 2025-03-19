#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

int main()
{
    // 맵 정의
    unordered_map<string, string> mapping = {
        {"ls", "dir"},
        {"mkdir", "md"},
        {"rmdir", "rd"},
        {"rm", "del"},
        {"cp", "copy"},
        {"mv", "rename"},
        {"clear", "cls"},
        {"pwd", "cd"},
        {"cat", "type"},
        {"man", "help"},
        {"date", "time"},
        {"find", "find"},
        {"grep", "findstr"},
        {"more", "more"},
        {"diff", "comp"},
        {"ed", "edlin"},
        {"sort", "sort"},
        {"lsattr", "attrib"},
        {"pushd", "pushd"},
        {"popd", "popd"},
        {"ps", "taskmgr"},
        {"kill", "tskill"},
        {"halt", "shutdown"},
        {"ifconfig", "ipconfig"},
        {"fsck", "chkdsk"},
        {"free", "mem"},
        {"debugfs", "scandisk"},
        {"lpr", "print"}
    };

    // 값 -> 키 매핑
    unordered_map<string, string> reverse_mapping;
    for (const auto& pair : mapping) {
        reverse_mapping[pair.second] = pair.first;
    }

    // 입출력 파일 오픈
    ifstream read_file;
    ofstream write_file;
    read_file.open("./command.inp");
    write_file.open("./command.out", ios::trunc); // ios::trunc = 파일을 열 때 기존 내용 삭제

    // 파일이 열렸는지 확인
    if(read_file.is_open() && write_file.is_open())
    {
        // 파일의 첫번째 줄, n 읽기
        string first_line;
        getline(read_file, first_line); 
        int n = stoi(first_line);

        // n번만큼 파일 한줄 씩 읽기
        for(int i = 0; i < n; i++)
        {
            string str;
            string output_line;

            getline(read_file, str);

            // 캐리지 리턴(\r) 제거
            if(!str.empty() && str.back() == '\r')
                str.pop_back();

            // 명령어가 mapping된 상태면 파일 쓰기
            // UNIX명령어 -> DOS명령어
            if(mapping.find(str) != mapping.end())
            {
                output_line = str + " -> " + mapping[str] + "\n";
                write_file.write(output_line.c_str(), output_line.size());
            }

            // DOS명령어 -> UNIX명령어
            else if(reverse_mapping.find(str) != reverse_mapping.end())
            {
                output_line = str + " -> " + reverse_mapping[str] + "\n";
                write_file.write(output_line.c_str(), output_line.size());
            }
        }
    }

    read_file.close();
    write_file.close();

    return 0;
}