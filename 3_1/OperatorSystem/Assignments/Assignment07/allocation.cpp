#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <algorithm>
using namespace std;

#define RAM_SIZE 1000

struct Process {
    int pid;
    int request_time;
    int running_time;
    int size;
    int start_time;
    int end_time;
    int start_addr;

    Process() {
        start_time = -1;
        end_time = -1;
        start_addr = -1;
    }
};

struct Block {
    int start;
    int size;
    int pid; // -1 = hole
};

struct EndEvent {
    int end_time;
    int pid;
    bool operator>(const EndEvent& other) const {
        return end_time > other.end_time;
    }
};

int allocate(list<Block>& mem, Process& p, const string& strategy) {
    list<Block>::iterator best = mem.end();
    int best_size = (strategy == "worst") ? -1 : 1e9;

    for (list<Block>::iterator it = mem.begin(); it != mem.end(); ++it) {
        if (it->pid == -1 && it->size >= p.size) {
            if (strategy == "first") {
                best = it;
                break;
            } else if (strategy == "best" && it->size < best_size) {
                best = it;
                best_size = it->size;
            } else if (strategy == "worst" && it->size > best_size) {
                best = it;
                best_size = it->size;
            }
        }
    }
    if (best == mem.end()) return -1;

    int addr = best->start;
    Block proc_block;
    proc_block.start = addr;
    proc_block.size = p.size;
    proc_block.pid = p.pid;
    int remain = best->size - p.size;

    list<Block>::iterator next_it = best;
    ++next_it;
    mem.erase(best);
    mem.insert(next_it, proc_block);
    if (remain > 0) {
        Block hole_block;
        hole_block.start = addr + p.size;
        hole_block.size = remain;
        hole_block.pid = -1;
        mem.insert(next_it, hole_block);
    }
    return addr;
}

bool compare_proc_time(const Process& a, const Process& b) {
    return a.request_time < b.request_time;
}

int simulate(vector<Process> processes, const string& strategy) {
    list<Block> mem;
    Block init;
    init.start = 0; init.size = RAM_SIZE; init.pid = -1;
    mem.push_back(init);

    queue<Process> ready;
    priority_queue<EndEvent, vector<EndEvent>, greater<EndEvent> > end_events;

    sort(processes.begin(), processes.end(), compare_proc_time);

    int time = 0, finished = 0, idx = 0, n = processes.size();

    while (finished < n) {
        while (!end_events.empty() && end_events.top().end_time == time) {
            int pid = end_events.top().pid;
            end_events.pop();

            for (list<Block>::iterator it = mem.begin(); it != mem.end(); ++it) {
                if (it->pid == pid) {
                    it->pid = -1;
                    list<Block>::iterator prev = it;
                    if (it != mem.begin()) --prev; else prev = mem.end();
                    list<Block>::iterator next = it; ++next;

                    if (prev != mem.end() && prev->pid == -1 && prev->start + prev->size == it->start) {
                        prev->size += it->size;
                        it = mem.erase(it);
                        it = prev;
                    }
                    if (next != mem.end() && it->start + it->size == next->start && next->pid == -1) {
                        it->size += next->size;
                        mem.erase(next);
                    }
                    break;
                }
            }
            finished++;
        }

        while (idx < n && processes[idx].request_time == time) {
            ready.push(processes[idx]);
            idx++;
        }

        int ready_size = ready.size();
        for (int i = 0; i < ready_size; ++i) {
            Process p = ready.front(); ready.pop();
            int addr = allocate(mem, p, strategy);
            if (addr != -1) {
                p.start_time = time;
                p.end_time = time + p.running_time;
                p.start_addr = addr;
                EndEvent e;
                e.end_time = p.end_time;
                e.pid = p.pid;
                end_events.push(e);
                if (p.pid == n - 1) return p.start_addr;
            } else {
                ready.push(p);
            }
        }

        if (!end_events.empty() && !ready.empty()) {
            time = end_events.top().end_time;
        } else {
            time++;
        }
    }

    return -1;
}

int main() {
    ifstream input("allocation.inp");
    ofstream output("allocation.out");

    int n;
    input >> n;
    vector<Process> procs(n);
    for (int i = 0; i < n; ++i) {
        input >> procs[i].request_time >> procs[i].running_time >> procs[i].size;
        procs[i].pid = i;
    }

    int ff = simulate(procs, "first");
    int bf = simulate(procs, "best");
    int wf = simulate(procs, "worst");

    output << ff << endl;
    output << bf << endl;
    output << wf << endl;

    return 0;
}