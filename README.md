ISA Simulator: Dynamic Matrix Multiplication Translator

This project implements a custom Instruction Set Architecture (ISA) simulator that dynamically generates 24-bit instructions for matrix multiplication on specialized hardware cores.

Project Structure:

- ‘docs/’ → Reports & algorithm design docs  
- ‘src/’ → Source code  
- ‘basic_matrix_multiply.cpp’ → Simple 3×3 multiplication  
- ‘isa_simulator.cpp’ → Full ISA instruction simulator  
- ‘datasets/’ → Raw uploaded files (optional, original `dataset.txt`)

How to Run:

Compile ISA Simulator:
g++ src/isa_simulator.cpp -o isa_simulator
./isa_simulator

Compile Basic Matrix Multiply:
g++ src/basic_matrix_multiply.cpp -o basic_mm
./basic_mm
