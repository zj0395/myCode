/*************************************************************************
	> File Name: crackBinary.cpp
	> Author: zj
	> Mail: zhangjian0395@163.com
	> Created Time: Sun 16 Jul 2017 06:58:52 PM CST
 ************************************************************************/

#include "crackBinary.h"
#include <iostream>
#include <cstring>
#include <unistd.h>

#define SUCCESS 0
#define FAIL 1

const int SIZE = sizeof(int);
const int crackBinary::V[10]={0,1,2,4,8,16,32,64,128,256};
int** crackBinary::backUps;
int crackBinary::successTimes = 0;

void crackBinary::initAll()
{
    backUps = new int*[81];
    for( int i=0; i<81; ++i )
    {
        backUps[i] = new int[81];
    }
}

int crackBinary::init(int i, int j, int *nums)
{
    myTimes = -1;
    int result=511;
    for( int m=0; m<9; ++m )
    {
        result &= ALLABLE - V[nums[i*9+j]];
        result &= ALLABLE - V[nums[i+9*j]];
    }
    int a=i/3*3, b=j/3*3;
    for( int m=0; m<3; ++m )
    {
        for( int n=0; n<3; ++n )
        {
            result &= ALLABLE - V[nums[(a+m)*9+b+n]];
        }
    }
    return result;
}

crackBinary::crackBinary( const crackBinary& rhs )
{
    myTimes = rhs.myTimes+1;
    table = new int[81];
    memcpy( table, rhs.table, 81*SIZE );
}

crackBinary::crackBinary( int *nums )
{
    successTimes = 0;
    table = new int[81];
    for( int i=0; i<81; ++i )
    {
        table[ i ] = -nums[i];
    }
    for( int i=0; i<9; ++i )
    {
        if( table[ i ] == 0 )
        {
            table[ i ] = init( i/9, i%9 , nums );
        }
    }
}

void crackBinary::showResult()
{
    for( int i=0; i<81; ++i )
    {
        std::cout<<-table[i];
    }
    std::cout<<"\n";
}

bool crackBinary::checkWin()
{
    for( int i=0; i<81; ++i )
    {
        if( table[i] >0 )
            return false;
    }
    return true;
}

int crackBinary::begin()
{
    wrongVal = 0;
    for( int i=0; i<9; ++i )
    {
        for( int j=0; j<9; ++j )
        {
            if( table[ getIndex(i,j) ] < 0 )
            {
                continue;
            }
            judgeToRm(i,j);
        }
    }
    if( wrongVal )
        return FAIL;
    if( checkWin() )
    {
        //showResult();
        return SUCCESS;
    }
    else
    {
        return getBestPoint();
    }
}

int crackBinary::getBestPoint()
{
    int least = 10;
    int index = 0;
    for(int i=0; i<81; ++i)
    {
        if(table[i]<0)
            continue;
        int num = numsLack(table[i]);
        if( num < least )
        {
            index = i;
            least = num;
        }
    }
    //cout<<"\nLeast is: "<<least<<" index is: "<<index/9<<" "<<index%9<<" "<<table[index]<<endl;
    if( least == 1 )
    {
        //showResult();
        return begin();
    }
    if( least <10 )
    {
        crackBinary s(*this);
        return s.tryChange(index);
    }
}

int crackBinary::tryChange(int i)
{
    int *backUp = backUps[myTimes];
    memcpy( backUp, table, 81*SIZE );
    int temp = table[i];
    int n=1;
    do
    {
        while( temp%2 == 0 )
        {
            ++n;
            temp>>=1;
        }
        table[i] = -n;
        ++n;
        temp>>=1;
        //cout<<"guess "<<i/9<<" "<<i%9<<" :"<<table[i]<<"\n";
        rmNum( i/9, i%9, ALLABLE-V[-table[i]] );
        //showResult();
        if( begin() == SUCCESS && ++successTimes>1 )
        {
            return SUCCESS;
        }
        memcpy( table, backUp, 81*4 );
    }while( temp !=0  );
    return FAIL;
}

void crackBinary::rmNum(int row, int col, int number)
{
    for( int m=0; m<9; ++m )
    {
        rmNumOne(row, m, number);
        rmNumOne(m, col, number);
    }
    int m=row/3*3, n=col/3*3;
    for(int a=0; a<3; ++a)
    {
        for(int b=0; b<3; ++b)
        {
            rmNumOne( m+a, n+b, number );
        }
    }
}

void crackBinary::recoverFromNegative(int i)
{
    if(table[i] < 0)
    {
        //cout<<"Done "<<i/9<<" "<<i%9<<" From "<<-table[i];
        table[i]=-table[i];
        int n=1;
        while(table[i]!=1)
        {
            table[i]>>=1;
            ++n;
        }
        table[i]=-n;
        //cout<<" to "<< -n<<"\n";
    }
}
