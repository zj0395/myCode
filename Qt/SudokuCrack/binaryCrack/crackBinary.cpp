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

void crackBinary::initAll()
{
    backUps = new int*[81];
    for( int i=0; i<81; ++i )
    {
        backUps[i] = new int[81];
    }
}

int crackBinary::init(int i, int j, const int nums[9][9])
{
    myTimes = -1;
    int result=511;
    for( int m=0; m<9; ++m )
    {
        result &= ALLABLE - V[nums[i][m]];
        result &= ALLABLE - V[nums[m][j]];
    }
    int a=i/3*3, b=j/3*3;
    for( int m=0; m<3; ++m )
    {
        for( int n=0; n<3; ++n )
        {
            result &= ALLABLE - V[nums[a+m][b+n]];
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

crackBinary::crackBinary( const int nums[9][9] )
{
    table = new int[81];
    for( int i=0; i<9; ++i )
    {
        for( int j=0; j<9; ++j )
        {
            table[ getIndex(i,j) ] = -nums[i][j];
        }
    }
    for( int i=0; i<9; ++i )
    {
        for( int j=0; j<9; ++j )
        {
            if( table[ getIndex(i,j) ] == 0 )
            {
                table[ getIndex(i,j) ] = init( i, j, nums );
            }
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
bool crackBinary::checkWrong()
{
    int FLAG=0;
    for( int i=0; i<9; ++i )
    {
        int rowNum = 0;
        for( int j=9*i; j<9*i+9; ++j )
        {
            if( table[j]<0 )
            {
                if( !FLAG )
                {
                    rowNum = V[-table[j]];
                }
                else
                    rowNum &= V[-table[j]];
                ++FLAG;
            }
        }
        if( rowNum && FLAG>1 )
        {
            //cout<<"Wrong in Row "<<i<<endl;
            return FAIL;
        }
        FLAG = 0;
        int colNum = 0;
        for( int j=i; j<81; j+=9 )
        {
            if( table[j]<0 )
            {
                if( !FLAG )
                {
                    colNum = V[-table[j]];
                }
                else
                    colNum &= V[-table[j]];
                ++FLAG;
            }
        }
        if( colNum && FLAG>1 )
        {
            //cout<<"Wrong in Col "<<i<<endl;
            return FAIL;
        }
    }
    for( int i=0; i<9; i+=3 )
    {
        for( int j=0; j<9; j+=3 )
        {
            int tabNum = 0;
            FLAG=0;
            for( int a=i; a<i+3; ++a )
            {
                for(int b=j; b<j+3; ++b)
                {
                    if( table[getIndex(a,b)] < 0 )
                    {
                        if( !FLAG )
                        {
                            tabNum = V[-table[getIndex(a,b)]];
                        }
                        else
                            tabNum &= V[-table[getIndex(a,b)]];
                        ++FLAG;
                    }
                }
            }
            if( tabNum && FLAG>1 )
            {
                //cout<<"Wrong in Tab "<<i<<" "<<j<<endl;
                return 1;
            }
        }
    }
    return 0;
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
    int tmp = table[i];
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
        if( begin() == SUCCESS )
            return SUCCESS;
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
