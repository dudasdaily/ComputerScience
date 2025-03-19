#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;

class Person
{
public:
    int id = 0;
    string first_name;
    string last_name;
};

void read_id(ifstream& read_file, Person& p)
{
    string id_str;
    char c;

    for(int i = 0; i < 5; i++)
    {
        read_file.get(c);

        if(c != '\r')
            id_str.push_back(c);
    }

    read_file.get(c);

    p.id = stoi(id_str);
}

void read_first_name(ifstream& read_file, Person& p)
{
    string first_name;
    char c;

    do{
        read_file.get(c);

        if(c != ' ')
            first_name.push_back(c);
    }while(c != ' ' && !read_file.eof());

    p.first_name = first_name;
}

void read_last_name(ifstream& read_file, Person& p)
{
    string last_name;
    char c;

    do{
        read_file.get(c);

        if(read_file.eof())
            break;

        if(c != '\n' && c != '\r')
            last_name.push_back(c);

    }while(c != '\n' && !read_file.eof());

    p.last_name = last_name;
}

int main()
{
    ifstream read_file;
    ofstream write_file;

    map<string, int> last_name_cnt;
    vector<Person> people;

    read_file.open("./test.inp");
    write_file.open("./test.out");

    if(read_file.is_open() && write_file.is_open())
    {
        Person p;
        int n = 0;
        string first_line;
        
        getline(read_file, first_line);
        n = stoi(first_line);

        for(int i = 0; i < n; i++)
        {
            read_id(read_file, p);
            read_first_name(read_file, p);
            read_last_name(read_file, p);

            people.push_back(p);
            ++last_name_cnt[p.last_name];
        }

        // id기준으로 정렬
        sort(people.begin(), people.end(), [](const Person& a, const Person& b){
            return a.id < b.id;
        });

        auto max_person = max_element(people.begin(), people.end(), [](const Person& a, const Person& b){
            return a.first_name.length() < b.first_name.length();
        });

        int space_num = max_person->first_name.length();

        for(const auto& p : people)
        {
            // id 쓰기
            string id_write = to_string(p.id);
            while(id_write.length() < 5)
                id_write.insert(0, "0");

            id_write += " ";
            write_file.write(id_write.c_str(), id_write.size());
            
            // first_name 쓰기
            write_file.write(p.first_name.c_str(), p.first_name.size());

            // 공백 맞추기
            for(int i = 0; i < space_num - p.first_name.length() + 1; i++)
                write_file.write(" ", 1);
            
            // last_name 쓰기
            write_file.write(p.last_name.c_str(), p.last_name.size());
            write_file.write("\n", 1);
        }

        write_file.write("\n", 1);

        // 중복된 성씨 출력
        for(const auto& p : last_name_cnt)
        {
            if(p.second > 1)
            {
                string temp = p.first + " " + to_string(p.second) + "\n";
                write_file.write(temp.c_str(), temp.size());
            }
        }
    }

    read_file.close();
    write_file.close();

    return 0;
}