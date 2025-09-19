{\rtf1\ansi\ansicpg1252\cocoartf2820
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\paperw11900\paperh16840\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 #include <iostream>\
#define N 3 // Define the matrix size\
\
void multiply(int A[N][N], int B[N][N], int C[N][N]) \{\
    for (int i = 0; i < N; i++) \{\
        for (int j = 0; j < N; j++) \{\
            C[i][j] = 0;\
            for (int k = 0; k < N; k++) \{\
                C[i][j] += A[i][k] * B[k][j];\
            \}\
        \}\
    \}\
\}\
\
void printMatrix(int M[N][N]) \{\
    for (int i = 0; i < N; i++) \{\
        for (int j = 0; j < N; j++) \{\
            std::cout << M[i][j] << " ";\
        \}\
        std::cout << "\\n";\
    \}\
\}\
\
int main() \{\
    int A[N][N] = \{\{1, 2, 3\}, \{4, 5, 6\}, \{7, 8, 9\}\};\
    int B[N][N] = \{\{9, 8, 7\}, \{6, 5, 4\}, \{3, 2, 1\}\};\
    int C[N][N];\
\
    multiply(A, B, C);\
\
    std::cout << "Resultant Matrix:\\n";\
    printMatrix(C);\
\
    return 0;\
\}\
}