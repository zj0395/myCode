#ifndef SUDUKUCRACKFROMFILE_H
#define SUDUKUCRACKFROMFILE_H

#include <fstream>

class sudukuCrackFromFile
{
public:
    sudukuCrackFromFile(std::ifstream& ifs, std::ofstream&ofs);
    void beginCrack();
    ~sudukuCrackFromFile(){    delete[]sudoku;    }

private:
    class crack
    {
    public:
        crack(int* table) : sudoku(table){}
        void begin();
    private:
        int* sudoku;
    };

    bool newSudoku();
    void outResult();
    int * sudoku;
    std::ifstream & in;
    std::ofstream & out;
};

#endif // SUDUKUCRACKFROMFILE_H
