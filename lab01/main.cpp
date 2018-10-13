#include "QCoreApplication"
#include "student.h"
#include "iostream"
#include "QString"
#include "vector"
#include "QDebug"
#include "algorithm"
#include "set"
#define num 4

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    student stu[num];
    stu[0].setdata(1403130209,"鲁智深",80,72);
    stu[1].setdata(1403140101,"林冲",82,76);
    stu[2].setdata(1403140102,"宋江",76,85);
    stu[3].setdata(1403140103,"武松",88,80);
    std::vector<student> STU(stu,stu+4);
    qDebug() << "===========排序前================" << endl;
    qDebug()<<"学号"<<"\t\t"<<"姓名"<<"\t\t"<<"课目一"<<"\t"<<"课目二";
    for(int i=0;i<num;i++){
        STU[i].print();
}
    std::sort(STU.begin(),STU.end(),student::compname);

    qDebug()<< "===========按姓名排序后================" << endl;
    qDebug()<<"学号"<<"\t\t"<<"姓名"<<"\t\t"<<"课目一"<<"\t"<<"课目二";
    for(int i=0;i<num;i++){
        STU[i].print();
}
    std::sort(STU.begin(),STU.end(),student::compsub01);

    qDebug()<< "===========按课目一排序后================" << endl;
    qDebug()<<"学号"<<"\t\t"<<"姓名"<<"\t\t"<<"课目一"<<"\t"<<"课目二";
    for(int i=0;i<num;i++){
        STU[i].print();
    }
    std::sort(STU.begin(),STU.end(),student::compsub02);

    qDebug()<< "===========按课目二排序后================" << endl;
    qDebug()<<"学号"<<"\t\t"<<"姓名"<<"\t\t"<<"课目一"<<"\t"<<"课目二"<<endl;
    for(int i=0;i<num;i++){
        STU[i].print();
}
    return a.exec();
}
