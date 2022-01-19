#include <iostream>

#include <fstream>
#include <sstream>

#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <vector>
#include <cassert>

enum Operation {
    NOP, ACC, JMP
};

std::string op_name[] = { "nop", "acc", "jmp"};

std::unordered_map<std::string, Operation> op_code {
    {"nop", NOP },
    {"acc", ACC },
    {"jmp", JMP }
};


struct Instr {
    Operation op_code;
    int value;
};

std::ostream& operator<<(std::ostream &out, const Instr & instr)
{
    return out << "\t" << op_name[instr.op_code] <<"\t"<< instr.value ;
}



std::vector<Instr> read_prog(const std::string &filename)
{
    std::ifstream file(filename);
    if (file.fail()) {
        std::cerr << "FAILURE. Can't open '" << filename
                  << "' file." << std::endl;
        exit (EXIT_FAILURE);
    }
    std::vector<Instr> instrs;

    std::string line;
    while( std::getline(file, line)) {
        std::stringstream ss(line);
        Instr i;
        std::string mnemo;
        ss >> mnemo >> i.value;
        i.op_code = op_code[mnemo];
        instrs.push_back(i);
    };
    return instrs;
}

void part1(const  std::string &filename)
{
    std::cout << "# Part 1 " << filename << " :" << std::endl;
    auto prog = read_prog(filename);
    std::cout << "- contains " << prog.size() << " instructions" << std::endl;

    /*   int n = 0;
        for (Instr i : prog) {
            std::cout <<  n << i std::endl;
            n += 1;
        }
    */
    std::unordered_set<int> visited;
    int pc = 0;
    int acc = 0;
    while (visited.find(pc) == visited.end()) {
        auto i = prog[pc];
        visited.emplace(pc);
        int next_pc = pc + 1;
        switch (i.op_code) {
        case NOP :
            break;
        case ACC :
            acc += i.value;
            break;
        case JMP :
            next_pc = pc + i.value;
            break;
        }
        pc = next_pc;
    }
    std::cout << "- stops at " << pc << " with acc = " << acc << std::endl;
}


void interpret_fixed_program(const std::vector<Instr> &prog)
{
    size_t pc = 0;
    int acc = 0;
    while (pc < prog.size()) {
        auto i = prog[pc];
        int next_pc = pc + 1;
        switch (i.op_code) {
        case NOP :
            break;
        case ACC :
            acc += i.value;
            break;
        case JMP :
            next_pc = pc + i.value;
            break;
        }
        pc = next_pc;
    }
    std::cout << "- stops at @" << pc <<
              ", acc contains " << acc << "." << std::endl;
}

bool fix_program(std::vector<Instr> & prog)
{
    //
    // Find reachable locations
    //
    std::unordered_set<int> reachable;
    std::stack<int> todo;
    todo.push(0);
    reachable.emplace(0);

    while (!todo.empty()) {
        int pc = todo.top();
        todo.pop();
        auto i = prog[pc];
        int next_pc = (i.op_code == JMP) ? pc + i.value :  pc + 1;
        if (reachable.find(next_pc) == reachable.end()) {
            todo.push(next_pc);
            reachable.emplace(next_pc);
        }
        pc = next_pc;
    }

    std::cout << "- " << reachable.size()
              << " instructions can be reached" << std::endl;

    //
    // compute predecessors of locations
    //
    int exit_point = prog.size();

    std::vector<std::vector<int>> predecessors( exit_point + 1);
    for (size_t pc = 0; pc < prog.size(); pc++) {
        auto i = prog[pc];
        int next_pc = (i.op_code == JMP) ? pc + i.value : pc + 1;
        predecessors[next_pc].push_back(pc);
    }

    //
    // compute terminating locations (with a path to exit point)
    //
    std::unordered_set<int> terminating;
    terminating.emplace(exit_point);

    assert (todo.empty());
    todo.push(exit_point);

    while (!todo.empty()) {
        int pc = todo.top();
        todo.pop();
        for (auto p : predecessors[pc]) {
            if (terminating.find(p) == terminating.end()) {
                terminating.emplace(p);
                todo.push(p);
            }
        }
    }
    std::cout << "- can be terminated from " <<
              terminating.size() << " locations" << std::endl;

    //
    // fix NOP or JMP instruction at a reachable location
    // so it goes to a terminating one
    //
    for (auto pc : reachable) {
        auto i = prog[pc];
        switch (i.op_code) {
        case NOP :
            if (terminating.find(pc + i.value) != terminating.end()) {
                std::cout << "- NOP instruction @" << pc
                          << " changed to JMP." <<std::endl;
                prog[pc].op_code = JMP;
                return true;
            }
            break;
        case JMP :
            if (terminating.find(pc + 1) != terminating.end()) {
                std::cout << "- JMP instruction @" << pc <<
                          " changed to NOP" <<std::endl;
                prog[pc].op_code = NOP;
                return true;
            }
            break;
        case ACC:
            break;
        }
    }
    return false;
}

void part2(const  std::string &filename)
{
    std::cout << "# Part 2 " << filename << " :" << std::endl;
    auto prog = read_prog(filename);
    std::cout << "- contains " << prog.size() << " instructions." << std::endl;

    if (fix_program(prog)) {
        interpret_fixed_program(prog);
    } else {
        std::cout << "SORRY, CANNOT RUN." << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    // part1(""../small.txt")
    // part1("../large.txt");

    part2("../small.txt");
    part2("../large.txt");

}
