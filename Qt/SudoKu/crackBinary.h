/*************************************************************************
	> File Name: crackBinary.h
	> Author: zj
	> Mail: zhangjian0395@163.com
	> Created Time: Sun 16 Jul 2017 06:58:58 PM CST
 ************************************************************************/

#ifndef _CRACKBINARY_H
#define _CRACKBINARY_H

#define ALLABLE 511
#include <iostream>
using namespace std;
class crackBinary
{
public:
    crackBinary(int *num);
    crackBinary(const crackBinary& );
    ~crackBinary(){delete []table;}
    int begin();
    void showResult();
    void inline judgeToRm(int i, int j)
    {
        if( numsLack( table[getIndex(i,j)] ) == 1 )
        {
            int temp = table[getIndex(i,j)];
            table[getIndex(i,j)]=-temp;
            recoverFromNegative( getIndex(i,j) );
            rmNum( i, j, ALLABLE-temp);
        }
    }
    inline int getIndex(int row, int col){return 9*row+col;}
    static void initAll();
private:
    static const int V[10];
    int *table;
    int wrongVal;
    static int successTimes;
    static int **backUps;
    int myTimes;

    int tryChange(int i);
    int getBestPoint();
    bool checkWin();
    int init(int i, int j, int *nums );
    void rmNum(int row, int col, int number);
    inline void rmNumOne(int row, int col, int number)
    {
        if( table[ getIndex(row,col) ] < 0 )
            return ;
        //cout<<"  rm "<<row<<" "<<col<<" from "<<table[getIndex(row,col)];
        table[ getIndex(row ,col)  ] &= number;
        if( table[ getIndex(row,col) ] == 0 )
        {
            wrongVal = 1;
        }
        //cout<<" to "<<table[getIndex(row,col)]<<"\n";
    }
    inline int numsLack(int num)
    {
        int n=0;
        while( num > 0 )
        {
            num &= num-1;
            ++n;
        }
        return n;
    }
    void recoverFromNegative(int i);

};

#endif
