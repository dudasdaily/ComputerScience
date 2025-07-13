// #include <iostream>
// #include <vector>
// #include <fstream>
// #include <algorithm>
// using namespace std;

// #define RAM_SIZE 1000

// struct Process {
//     int pid;
//     int request_time;
//     int running_time;
//     int size;
//     int start_time = -1;
//     int end_time = -1;
//     int start_addr = -1;
// };

// struct Block {
//     int start;
//     int pid;
//     int size;
// };

// using Memory = vector<Block>;

// bool compare_by_start(const Block& a, const Block& b) {
//     return a.start < b.start;
// }

// void merge_holes(Memory& mem) {
//     sort(mem.begin(), mem.end(), compare_by_start);
//     vector<Block> merged;
//     for (auto& b : mem) {
//         if (!merged.empty() && merged.back().pid == -1 && b.pid == -1 &&
//             merged.back().start + merged.back().size == b.start) {
//             merged.back().size += b.size;
//         } else {
//             merged.push_back(b);
//         }
//     }
//     mem = merged;
// }

// bool allocate(Memory& mem, Process& p, int now, const string& strategy) {
//     sort(mem.begin(), mem.end(), compare_by_start);
//     int idx = -1;
//     int best_size = (strategy == "worst") ? -1 : 1e9;

//     for (int i = 0; i < mem.size(); ++i) {
//         if (mem[i].pid == -1 && mem[i].size >= p.size) {
//             if (strategy == "first") {
//                 idx = i;
//                 break;
//             } else if (strategy == "best") {
//                 if (mem[i].size < best_size) {
//                     best_size = mem[i].size;
//                     idx = i;
//                 }
//             } else if (strategy == "worst") {
//                 if (mem[i].size > best_size) {
//                     best_size = mem[i].size;
//                     idx = i;
//                 }
//             }
//         }
//     }

//     if (idx == -1) return false;

//     int addr = mem[idx].start;
//     int remain = mem[idx].size - p.size;

//     mem[idx] = {addr, p.pid, p.size};
//     if (remain > 0)
//         mem.insert(mem.begin() + idx + 1, {addr + p.size, -1, remain});

//     p.start_addr = addr;
//     p.start_time = now;
//     p.end_time = now + p.running_time;
//     return true;
// }

// int simulate(vector<Process> input_procs, const string& strategy) {
//     vector<Process> procs = input_procs;
//     Memory mem = {{0, -1, RAM_SIZE}};
//     vector<Process> ready, running;
//     int time = 0, finished = 0, total = procs.size();

//     while (finished < total) {
//         // 1. 종료 처리
//         for (auto it = running.begin(); it != running.end(); ) {
//             if (it->end_time == time) {
//                 for (auto& b : mem) {
//                     if (b.pid == it->pid) {
//                         b.pid = -1;
//                         break;
//                     }
//                 }
//                 it = running.erase(it);
//                 merge_holes(mem);
//                 finished++;
//             } else ++it;
//         }

//         // 2. 요청 시각 도달한 프로세스 ready 큐로
//         for (auto& p : procs) {
//             if (p.request_time == time)
//                 ready.push_back(p);
//         }

//         // 3. ready 큐에서 할당 시도
//         for (auto it = ready.begin(); it != ready.end(); ) {
//             if (allocate(mem, *it, time, strategy)) {
//                 running.push_back(*it);
//                 for (auto& p : procs) {
//                     if (p.pid == it->pid)
//                         p = *it;
//                 }
//                 it = ready.erase(it);
//             } else ++it;
//         }

//         time++;
//     }

//     return procs.back().start_addr;
// }

// int main() {
//     ifstream input("allocation.inp");
//     ofstream output("allocation.out");

//     int n;
//     input >> n;
//     vector<Process> procs(n);
//     for (int i = 0; i < n; ++i) {
//         input >> procs[i].request_time >> procs[i].running_time >> procs[i].size;
//         procs[i].pid = i;
//     }

//     int addr_first = simulate(procs, "first");
//     int addr_best  = simulate(procs, "best");
//     int addr_worst = simulate(procs, "worst");

//     output << addr_first << endl;
//     output << addr_best << endl;
//     output << addr_worst << endl;

//     return 0;
// }