{\rtf1\ansi\ansicpg1252\cocoartf2820
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <iostream>\
#include <vector>\
#include <bitset>\
using namespace std;\
\
class Instruction \{\
public:\
    string op;      // Operation: "PROG", "EXE", "END"\
    int pointer;    // 6-bit core pointer\
    int row_addr;   // 9-bit memory row address\
    bool read, write;\
\
    Instruction(string operation, int ptr = 0, int row = 0, bool rd = false, bool wr = false)\
        : op(operation), pointer(ptr), row_addr(row), read(rd), write(wr) \{\}\
\
    bitset<24> encode() const \{\
        bitset<2> op_code;\
        if (op == "PROG") op_code = 0b00;\
        else if (op == "EXE") op_code = 0b01;\
        else if (op == "END") op_code = 0b10;\
\
        bitset<6> pointer_bin(pointer);\
        bitset<9> row_bin(row_addr);\
        bitset<1> read_bit(read);\
        bitset<1> write_bit(write);\
\
        unsigned long instr_val = (op_code.to_ulong() << 22) |\
                                  (pointer_bin.to_ulong() << 16) |\
                                  (read_bit.to_ulong() << 15) |\
                                  (write_bit.to_ulong() << 14) |\
                                  (row_bin.to_ulong());\
        return bitset<24>(instr_val);\
    \}\
\};\
\
class InstructionMemory \{\
public:\
    vector<bitset<24>> instructions;\
\
    void add_instruction(const Instruction &instr) \{\
        instructions.push_back(instr.encode());\
    \}\
\
    void displayVerbose() \{\
        cout << "\\nInstruction Memory (Verbose):" << endl;\
        for (size_t i = 0; i < instructions.size(); i++) \{\
            unsigned long instr_val = instructions[i].to_ulong();\
            unsigned long opcode = (instr_val >> 22) & 0b11;\
            unsigned long core   = (instr_val >> 16) & 0b111111;\
            unsigned long read   = (instr_val >> 15) & 0b1;\
            unsigned long write  = (instr_val >> 14) & 0b1;\
            unsigned long row    = instr_val & 0b111111111;\
\
            string opName;\
            if (opcode == 0b00) opName = "PROG";\
            else if (opcode == 0b01) opName = "EXE";\
            else if (opcode == 0b10) opName = "END";\
            else opName = "UNKNOWN";\
\
            cout << "Instr " << i << ": " << instructions[i]\
                 << " | OP: " << opName\
                 << ", Core: " << core\
                 << ", RD: " << read\
                 << ", WR: " << write\
                 << ", Row: " << row << endl;\
        \}\
    \}\
\};\
\
int main() \{\
    int M, N, P;\
    cout << "Enter number of rows in Matrix A (and C): ";\
    cin >> M;\
    cout << "Enter number of columns in Matrix A (and rows in Matrix B): ";\
    cin >> N;\
    cout << "Enter number of columns in Matrix B (and C): ";\
    cin >> P;\
\
    int base_A = 0;\
    int base_B = M * N;\
    int base_C = base_B + N * P;\
\
    auto addr_A = [=](int i, int k) \{ return base_A + i * N + k; \};\
    auto addr_B = [=](int k, int j) \{ return base_B + j * N + k; \};\
    auto addr_C = [=](int i, int j) \{ return base_C + i * P + j; \};\
\
    InstructionMemory instrMem;\
    instrMem.add_instruction(Instruction("PROG", 0)); // multiplier core\
    instrMem.add_instruction(Instruction("PROG", 1)); // accumulator core\
\
    for (int i = 0; i < M; i++) \{\
        for (int j = 0; j < P; j++) \{\
            instrMem.add_instruction(Instruction("PROG", 1)); // reset accumulator\
            for (int k = 0; k < N; k++) \{\
                instrMem.add_instruction(Instruction("EXE", 0, addr_A(i, k), true, false));\
                instrMem.add_instruction(Instruction("EXE", 1, addr_B(k, j), true, false));\
            \}\
            instrMem.add_instruction(Instruction("EXE", 1, addr_C(i, j), false, true));\
        \}\
    \}\
\
    instrMem.add_instruction(Instruction("END"));\
    instrMem.displayVerbose();\
    return 0;\
\}\
}