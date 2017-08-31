#include "sudukucrackfromfile.h"

sudukuCrackFromFile::sudukuCrackFromFile(std::ifstream &ifs, std::ofstream &ofs)
    : sudoku(new int[81]), in(ifs), out(ofs)
{
    newSudoku();
}

bool sudukuCrackFromFile::newSudoku()
{
    static char s[81];
    in.read(s, 81);
    for( int i=0; i<81 ; ++i)
        sudoku[i] = s[i] - 48;
}

void sudukuCrackFromFile::outResult()
{
    static char s[81];
    for( int i=0; i<81 ; ++i)
        s[i] = sudoku[i] + 48;
    out.write(s, 81);
    out<<"\n";
}

void sudukuCrackFromFile::beginCrack()
{
    crack ck(sudoku);
    ck.begin();
    outResult();
}

void sudukuCrackFromFile::crack::begin()
{

}
