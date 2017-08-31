#include<cmath>
#include<iostream>
#include<map>
#include<sstream>
#include<iomanip>
#include"pca.h"
using std::ifstream;
using std::cout;
using std::endl;
const static int jt=200;//jcb���ѭ������
PCA::PCA(int m,int n,double e,double g):rows(m),columns(n),
                    data(m,vdouble(n,0)),p_data(nullptr),
                    wronginfo(),t(0),eps(e),getratio(g),l(0)
{
}
PCA::PCA_Data::PCA_Data(const int n):
                    matrixcov(n,vdouble(n,0)),
                    chvalue(n,0),
                    chvector(n,vdouble(n,0)),
                    value_ratio(n,0),
                    prin_load(n,vdouble(n,0))
{
}
bool PCA::getdata(ifstream&testdata)
{
    for(int i=0;i<rows;i++)
        for(int j=0;j<columns;j++)
        {
            if(!(testdata>>data[i][j]) )
            {
                std::ostringstream fos(wronginfo);
                fos<<"Wrong happens when read data: row"<<i+1<<" column"<<j+1;
                return 0;
            }
        }
    //��ȷ��ȡ���ݺ���ɴ󲿷ּ���
    standarddata();
    p_data=new PCA_Data(columns);//ֻ��Ҫ��ά��
    matrixproduct();
    jcb();
    if(!wronginfo.empty())
    {
        return 0;
    }
    t=selectcharactor();
    calprincipal_loading();
    return 1;
}

void PCA::standarddata() //�������滯\��׼��\��һ��
{
	double s,ss;
    for(int i=0;i<columns;++i)
	{		
		s=0;
		for(int j=0;j<rows;++j)			
			s+=data[j][i];
		s=s/rows;	
		ss=0;
		for(int j=0;j<rows;++j)
			ss+=pow((data[j][i]-s),2);
		ss=sqrt(ss/(rows-1));	
		for(int j=0;j<rows;++j)
			data[j][i]=(data[j][i]-s)/ss;		
	}	
}
void PCA::matrixproduct() //���Э�������
{
    vvdouble& m=p_data->matrixcov;
    vvdouble& a=data;
	for(int i=0;i<columns;i++)
		for(int j=0;j<columns;j++)
		{
			for(int k=0;k<rows;k++)
				m[i][j]+=a[k][i]*a[k][j];
			m[i][j]/=(rows-1);
		}
}
void PCA::jcb()
//jacobi��ʵ�Գƾ��������ֵ����������,������
{
    vvdouble &m=p_data->matrixcov;
    vvdouble &v=p_data->chvector;
	for(int i=0;i<columns;++i)
	{
        v[i][i]=1;//�����ѱ���ʼ��Ϊ0
	}
	while(true)
	{	
		double fm=0;
        int p=0,q=1;
		for(int i=0;i<columns;++i)
			for(int j=0;j<columns;++j)
			{
				double d=fabs(m[i][j]);
				if((i!=j)&&(d>fm))   //ȡ����a[p][q]
				{
					fm=d;p=i;q=j;
                }
			}
	    if(fm<eps) //����ﵽ�����ľ�������ѭ��
        {
            break;
		}
		if(l>jt) //����������
		{
            std::ostringstream fos(wronginfo);
            fos<<"Can't get chvalue and chvector. Loop for"<<l<<"times to jacobi.";
            return;
		}		
		++l;	 //��¼��������		

        //�µķ���
        double dbpp=m[p][p],dbpq=m[p][q],dbqq=m[q][q];
        double dbangle=0.5*atan2(-2*dbpq,dbqq-dbpp);
        double sn=sin(dbangle),cn=cos(dbangle);
        double sn2=sin(2*dbangle),cn2=cos(2*dbangle);
        m[p][p]=dbpp*cn*cn+dbqq*sn*sn+2*dbpq*cn*sn;
        m[q][q]=dbpp*sn*sn+dbqq*cn*cn-2*dbpq*cn*sn;
        m[p][q]=0.5*(dbqq-dbpp)*sn2+dbpq*cn2;
        m[q][p]=m[p][q];

		for(int i=0;i<columns;++i)
			if((i!=p)&&(i!=q))
			{
				fm=m[i][p];
				m[i][p]=fm*cn+m[i][q]*sn;
				m[i][q]=-fm*sn+m[i][q]*cn;
			}
		for(int j=0;j<columns;++j)
			if((j!=p)&&(j!=q))
			{					
				fm=m[p][j];
				m[p][j]=fm*cn+m[q][j]*sn;
				m[q][j]=-fm*sn+m[q][j]*cn;
			}

        //��������
		for(int i=0;i<columns;++i)
		{
			fm=v[i][p];
			v[i][p]=fm*cn+v[i][q]*sn;
			v[i][q]=-fm*sn+v[i][q]*cn;
		}
	}
    //����������ֵ��������ֵһ������
    selectionsort();
}
typedef std::vector<double>vdouble;//��typedefֻ���ڸ��ļ���ʹ��

void  PCA::selectionsort()  
{
    vdouble &c=p_data->chvalue;
    vvdouble &m=p_data->matrixcov;
    vvdouble &v=p_data->chvector;
    vvdouble vvtemp(columns,vdouble(columns,0));//�������������,��ȫ��Ϊ0
    
    std::multimap<double,int>maptemp;

    //map��first��second����ֵ��Ĭ�ϰ�firstֵ��С��������
    for(int i=0;i<columns;++i)
    {
        c[i]=m[i][i];
        maptemp.insert(std::make_pair(c[i],i));//map���� ����ֵ������ ��pair
    }
    std::map<double,int>::reverse_iterator iter=maptemp.rbegin();//���������
    for(int j=0; iter!=maptemp.rend()&&j<columns; ++iter,++j)
    {
        int col=iter->second;
        for(int i=0;i<columns;++i)
        {
            vvtemp[i][j]=v[i][col];//��col��  
        }
        c[j]=iter->first;//����ֵ�����ʼ����
    }//�������

    using std::swap;
    swap(vvtemp,v);//ʹ�ñ�׼��Ĭ�ϵ�swap���и�Ч�ʽ���
}
int PCA::selectcharactor() //����ֵ����ȡ��
{
	if(getratio>1||getratio<0)
	{
        wronginfo="Wrong ratio.";
        return 0;
    }
    vdouble& A=p_data->chvalue;
    vdouble& B=p_data->value_ratio;
    vdouble sumtemp(columns,0);
	double s=0;
	for(int i=0;i<columns;i++)
		s+=A[i];
    sumtemp[0]=B[0]=A[0]/s;
	for(int i=1;i<columns;i++)
	{
        B[i]=A[i]/s; //����ֵ���ۼƹ�����
        sumtemp[i]=sumtemp[i-1]+B[i];
    }
	for(int i=0;i<columns;i++)
	{
	    if(sumtemp[i]>=getratio)
		{
		   return i+1;
		}
	}
    wronginfo="Fail!";
	return 0;
}
void PCA::calprincipal_loading()
{
    vdouble &c=p_data->chvalue;
    vvdouble &v=p_data->chvector;
    vvdouble &p=p_data->prin_load;
    for(int j=0;j<t;++j)//��
        for(int i=0;i<columns;++i)//��
        {
            double temp=sqrt(c[j]);
            p[i][j]=temp*v[i][j];
        }
}
typedef std::vector<vdouble>vvdouble;
vvdouble PCA::setScores() //��ȡ����ͶӰ  
{
    if(t&&t<=columns)//��������ض�ͨ��
    {
        vvdouble &p=p_data->prin_load;
        vvdouble c(rows,vdouble(t,0));
	    for(int i=0;i<rows;++i)
	    {
		    for(int j=0;j<t;++j)
			    for(int k=0;k<columns;++k)
			        c[i][j]+=data[i][k]*p[k][j];			
	    }

        //�任������
        //��Ϊ������������Ϊ��Ҳ����Ϊ����ʹ����ֵ����Ϊ��
        for(int j=0;j<t;++j)
        {
            int l=0;
            double temp=fabs(c[0][j]);
            for(int i=1;i<rows;++i)
            {
                double d=fabs(c[i][j]);
                if(d>temp)
                {
                    temp=d;
                    l=i;
                }
            }
            if(c[l][j]<0)
            {
                for(int i=0;i<rows;++i)
                    c[i][j]*=-1;
            }
        }
	    return  c;
    }
    else
    {
        //����1ά����
        return vvdouble(1,vdouble(1,0));
    }
}
void PCA::saveProject(std::ofstream& fsout)
{
    const vvdouble project=setScores();
    fsout.setf(std::ios::fixed | std::ios::right);
    fsout.precision(8);
	for(int i=0;i<rows;++i)
	{
		for(int j=0;j<t;++j)
        {
            fsout.width(12);
            fsout<<project[i][j]<<" ";
        }
        fsout<<endl;
	}
}


void PCA::showdata()const
{
    cout<<"data:\n";
    for(const vdouble& temp:data)
    {
        for(int i=0;i<columns;++i)
            cout<<std::setw(10)<<temp[i]<<" ";
        cout<<"\n";
    }
    cout<<endl;
}
void PCA::showmatrixcov()const
{
    cout<<"matrixcov:\n";
    for(const vdouble& temp:p_data->matrixcov)
    {
        for(int i=0;i<columns;++i)
            cout<<std::setw(10)<<temp[i]<<" ";
        cout<<"\n";
    }
    cout<<endl;
}
void PCA::showchvalue()const
{
    const vdouble &c=p_data->chvalue;
    cout<<"chvalue:\n";
    for(int i=0;i<columns;++i)
        cout<<std::setw(10)<<c[i]<<" ";
    cout<<endl;
}
void PCA::showchvector(int m)const
{
    m=m?columns:t;
    cout<<"chvector:\n";
    for(const vdouble&temp:p_data->chvector)
    {
        for(int j=0;j<m;++j)
        {
            cout<<std::setw(10)<<temp[j]<<" ";
        }
        cout<<"\n";
    }
    cout<<endl;
}
void PCA::showratio()const
{
    const vdouble &r=p_data->value_ratio;
    cout<<"ratio:\n";
    for(int i=0;i<columns;++i)
        cout<<std::setw(10)<<r[i]<<" ";
    cout<<endl;
}
void PCA::showprin_load()const
{
    cout<<"principal component loading: \n";
    for(const vdouble&temp:p_data->prin_load)
    {
        for(int j=0;j<t;++j)
            cout<<std::setw(10)<<temp[j]<<" ";
        cout<<"\n";
    }
    cout<<endl;
}


void PCA::savedata(std::ofstream& fcout)const
{
    fcout<<"data:\n";
    for(const vdouble& temp:data)
    {
        for(int i=0;i<columns;++i)
            fcout<<std::setw(10)<<temp[i]<<" ";
        fcout<<"\n";
    }
    fcout<<"\n";
}
void PCA::savematrixcov(std::ofstream& fcout)const
{
    fcout<<"matrixcov:\n";
    for(const vdouble& temp:p_data->matrixcov)
    {
        for(int i=0;i<columns;++i)
            fcout<<std::setw(10)<<temp[i]<<" ";
        fcout<<"\n";
    }
    fcout<<"\n";
}
void PCA::savechvalue(std::ofstream& fcout)const
{
    const vdouble &c=p_data->chvalue;
    fcout<<"chvalue:\n";
    for(int i=0;i<columns;++i)
        fcout<<std::setw(10)<<c[i]<<" ";
    fcout<<"\n";
}
void PCA::savechvector(std::ofstream& fcout)const
{
    fcout<<"chvector:\n";
    for(const vdouble&temp:p_data->chvector)
    {
        for(int j=0;j<t;++j)
        {
            fcout<<std::setw(10)<<temp[j]<<" ";
        }
        fcout<<"\n";
    }
    fcout<<"\n";
}
void PCA::saveratio(std::ofstream& fcout)const
{
    const vdouble &r=p_data->value_ratio;
    fcout<<"ratio:\n";
    for(int i=0;i<columns;++i)
        fcout<<std::setw(10)<<r[i]<<" ";
    fcout<<"\n";
}
void PCA::saveprin_load(std::ofstream& fcout)const
{
    fcout<<"principal component loading: \n";
    for(const vdouble&temp:p_data->prin_load)
    {
        for(int j=0;j<t;++j)
            fcout<<std::setw(10)<<temp[j]<<" ";
        fcout<<"\n";
    }
    fcout<<"\n";
}
