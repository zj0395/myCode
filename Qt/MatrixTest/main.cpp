#include <QCoreApplication>
#include "armadillo"
#include <QDebug>
#include <vector>
#include "Eigen/Dense"
#include <iostream>

typedef std::vector<double> VDouble;//double型一维数组

VDouble readTxtDouble(const char *txtFile)
{
    typedef std::istream_iterator<double> iterDouble;
    std::ifstream fin( txtFile );
    if( !fin )
    {
        qDebug()<<"can't open"<<txtFile;
        return VDouble();//返回空数组
    }

    //读取整个文件的 double 数据
    //第一个参数是指向文件开头位置的迭代器；第二个参数为指向空数据的迭代器，代表文件结尾
    VDouble fileData( (iterDouble(fin)), iterDouble() );

    return fileData;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    VDouble ss = readTxtDouble("C:/Users/Public/T_01.txt");

    int siz = sqrt( ss.size() );
    int size1 = siz;
    int size2 = siz;

    //Armadillo库
    arma::mat A( size1, size2 );
    for( int i=0; i<size1; ++i )
    {
        for( int j=0; j<size2; ++j )
            A(i,j) = ss[j*size1+i];
    }

    arma::mat U, V;
    arma::colvec S;
    svd( U, S, V, A );
//    A.print("原矩阵A:");
//    U.print("正交矩阵U=\n");
//    V.print("正交矩阵V=\n");
//    S.print("奇异值列向量S=\n");
    arma::mat VM ( size1, size2 );
    for( int i=0; i<size1; ++i )
    {
        for( int i=0; i<size1; ++i )
        {
            for( int j=0; j<size2; ++j )
                VM(i,j) = 0;
        }
        VM(i, i) = S[i];
    }
    std::cout<<norm( (U * VM * V.t() - A), 2 )<<std::endl;


    //Eigen库
//    Eigen::MatrixXd mat2D( size1, size2 );
//    for( int i=0; i<size1; ++i )
//    {
//        for( int j=0; j<size2; ++j )
//            mat2D(i, j) = ss[j*size1+i];
//    }
//    Eigen::JacobiSVD<Eigen::MatrixXd> svd( mat2D, Eigen::ComputeFullU | Eigen::ComputeFullV );
//    Eigen::MatrixXd V = svd.matrixV();
//    Eigen::VectorXd S = svd.singularValues();
//    Eigen::MatrixXd U = svd.matrixU();

//    std::cout<<(U * S.asDiagonal() * V.transpose() - mat2D).norm()<<std::endl;


    return 0;
}
