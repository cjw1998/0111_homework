#include <iostream>
#include <qglobal.h>
#include <QDebug.h>
#include <stdio.h>
#include <string>
#include <algorithm>

#define _max(A,B) (((A)-(B))>>8 ? (B) : (A))
#define max(A,B)_max(A,B)//取A,B中的最大值
#define _min(A,B) (((B)-(A))>>8 ? (B) : (A))
#define min(A,B)_min(A,B)//取A,B中的最小值
#define HHI(A) ((A)&(0XFF))//取出32位无符号整型数的最高8位
#define LHI(A) (((A)>>8)&(0XFF))//取出32位无符号整型数的次高8位
#define HLI(A) (((A)>>16)&(0XFF))//取出32位无符号整型数的次低8位
#define LLI(A) (((A)>>24)&(0XFF))//取出32位无符号整型数的最低8位
#define _LINK(A,B,C,D) ((A)<<24)+((B)<<16)+((C)<<8)+(D)
#define LINK(A,B,C,D)_LINK(A,B,C,D)//将A,B,C,D按顺序连接成一个数

bool compare(qint8 a,qint8 b)
{
  return a>b; //升序排列，如果改为return a>b，则为降序
}

int main()
{
    quint32 num=0x12345678;

    QList<qint8> values;

    values<<LLI(num)<<HLI(num)<<LHI(num)<<HHI(num);//将给定的数存到QList<qint8> values
    qDebug()<<"原数据"<<hex<<values<<endl;//输出原数据
    std::sort(values.begin(),values.end(),compare);//将values中的数排序
    qDebug()<<"从大到小"<<hex<<values<<endl;//输出排序后的数据

    qDebug()<<"HHI is "<<hex<<HHI(num)<<endl;//输出最高8位
    qDebug()<<"LHI is "<<hex<<LHI(num)<<endl;//输出次高8位
    qDebug()<<"HLI is "<<hex<<HLI(num)<<endl;//输出次低8位
    qDebug()<<"LLI is "<<hex<<LLI(num)<<endl;//输出最低8位

    qDebug()<<"max(HHI,LHI) is "<<hex<<max(HHI(num),LHI(num))<<endl;//输出最高与次高8位中的最大值
    qDebug()<<"min(HLI,LLI) is "<<hex<<min(HLI(num),LLI(num))<<endl;//输出次低与最低8位中的最小值

    qDebug()<<"10进制"<<LINK(LHI(num),LLI(num),HHI(num),HLI(num))<<endl;//以10进制输出重组后的数
    qDebug()<<"16进制"<<hex<<LINK(LHI(num),LLI(num),HHI(num),HLI(num))<<endl;//以16进制输出重组后的数

    return 0;
}
