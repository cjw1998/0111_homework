#include "iostream"
#include "QString"
#include "vector"
#include "QDebug"
#include "algorithm"


class student{
private:
    int id;
    QString name;
    double subject01;
    double subject02;
public:
    void setdata(int id, QString name, double subject01, double subject02){
        student::id=id;
        student::name=name;
        student::subject01=subject01;
        student::subject02=subject02;
    }

    void print(){
        qDebug()<<id<<"\t"<<name<<"\t"<<subject01<<"\t\t"<<subject02;
    }

    //template<typename T>
    static bool compname(const student &a, const student &b){
        if(a.name < b.name)
        return false;
    }
    static bool compsub01(const student &a, const student &b){
        if(a.subject01 < b.subject01)
        return false;
    }
    static bool compsub02(const student &a, const student &b){
        if(a.subject02 < b.subject02)
        return false;
    }
};
