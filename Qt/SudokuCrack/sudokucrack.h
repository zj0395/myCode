#ifndef SUDOKUCRACK_H
#define SUDOKUCRACK_H


#include <vector>
#include <set>

typedef std::vector<int> vint;
typedef std::vector<vint> vvint;
typedef std::set<int> sint;
class SudokuCrack
{
public:
    const vvint& getResult(){return result;}
    SudokuCrack(vvint &);
    void setInitNum(vvint&);
    int beginCrack();
private:
    void fillAllOnly();
    bool checkwin();
    int isBad();
    int selectBetter();
    int countLackNum(int i, int j);
    sint &getLackedNumSet( int i, int j );
    int attemptLocate( int i, int j);


    vvint vvnum;//0是没有数字，1-9为正常数字
    static vvint result;
};

#endif // SUDOKUCRACK_H
