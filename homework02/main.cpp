#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QCoreApplication>

//namespace SK {
//enum SortKind{
//    col01    =   0x00000001<<0,         //!< 第1列
//    col02    =   0x00000001<<1,         //!< 第2列
//    col03    =   0x00000001<<2,         //!< 第3列
//    col04    =   0x00000001<<3,         //!< 第4列
//    col05    =   0x00000001<<4,         //!< 第5列
//    col06    =   0x00000001<<5,         //!< 第6列
//    col07    =   0x00000001<<6,         //!< 第7列
//    col08    =   0x00000001<<7,         //!< 第8列
//    col09    =   0x00000001<<8,         //!< 第9列
//    col10    =   0x00000001<<9,         //!< 第10列
//    col11    =   0x00000001<<10,        //!< 第11列
//    col12    =   0x00000001<<11,        //!< 第12列
//    col13    =   0x00000001<<12,        //!< 第13列
//    col14    =   0x00000001<<13,        //!< 第14列
//    col15    =   0x00000001<<14,        //!< 第15列
//    col16    =   0x00000001<<15,        //!< 第16列
//    col17    =   0x00000001<<16,        //!< 第17列
//    col18    =   0x00000001<<17,        //!< 第18列
//    col19    =   0x00000001<<18,        //!< 第19列
//    col20    =   0x00000001<<19,        //!< 第20列
//    col21    =   0x00000001<<20,        //!< 第21列
//    col22    =   0x00000001<<21,        //!< 第22列
//    col23    =   0x00000001<<22,        //!< 第23列
//    col24    =   0x00000001<<23,        //!< 第24列
//    col25    =   0x00000001<<24,        //!< 第25列
//    col26    =   0x00000001<<25,        //!< 第26列
//    col27    =   0x00000001<<26,        //!< 第27列
//    col28    =   0x00000001<<27,        //!< 第28列
//    col29    =   0x00000001<<28,        //!< 第29列
//    col30    =   0x00000001<<29,        //!< 第30列
//    col31    =   0x00000001<<30,        //!< 第31列
//    col32    =   0x00000001<<31,        //!< 第32列
//};
//}


struct studData{
    // 请补全结构定义
private:
    QString id;
    QString name;
    QString subj;
public:
    studData();
    friend QDebug operator << (QDebug d,const studData &data);
    friend class myCmp;
    friend class ScoreSorter;
};

studData::studData(){
    id="0";
    name="none";
}

QDebug operator << (QDebug d,const studData &data){
    d << data.id <<data.name<<"\t"<<data.subj;
    return d;
}

//studData::setid(QString data){
//    this->id=data;
//}

//studData::setname(QString data){
//    this->name=data;
//}

//studData::setsubj(QString data){
//    this->subj=data;
//}

// 比较类，用于std::sort第三个参数
class myCmp {
public:
    myCmp(int selectedColumn) { this->currentColumn = selectedColumn; }
    bool operator() (const studData& d1,const studData& d2);
private:
    int currentColumn;
};

bool myCmp::operator()(const studData &d1, const studData &d2)
{
    bool result = false;
    quint32 sortedColumn =currentColumn;
    switch (sortedColumn) {
    case 1 : return d1.subj.section("    ",0,0)>d2.subj.section("    ",0,0);
    case 2 : return d1.subj.section("    ",1,1)>d2.subj.section("    ",1,1);
    case 3 : return d1.subj.section("    ",2,2)>d2.subj.section("    ",2,2);
    case 4 : return d1.subj.section("    ",3,3)>d2.subj.section("    ",3,3);
    case 5 : return d1.subj.section("    ",4,4)>d2.subj.section("    ",4,4);
    case 6 : return d1.subj.section("    ",5,5)>d2.subj.section("    ",5,5);
    // ...
    // 请补全运算符重载函数
    // ...
    // ...
    }
    return result;

}


class ScoreSorter
{
public:
    ScoreSorter(QString dataFile);
    // ...
    // 请补全该类，使其实现上述要求
    // ...
    void readFile();
    void doSort(int j);
    void myMessageOutput();
    friend QDebug operator << (QDebug d,const studData &data);
private:
    QVector<studData> stuList;
    QString Filepath;
    QString title;
};

// 请补全
ScoreSorter::ScoreSorter(QString dataFile)
{
    this->Filepath=dataFile;
}

void ScoreSorter::readFile(){
    studData stu;
    QFile file("data.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text )){
        return;
    }
        title=file.readLine();
        title=title.trimmed();
        qDebug()<<title;
    while( file.atEnd() == 0 ){
        QString str;
        str = file.readLine();
        str=str.replace(QRegExp("[\\s]+"), "    ");
        stu.id=str.section("    ",0,0);
        stu.name=str.section("    ",1,1);;
        stu.subj=str.section("    ",2,7);
        stuList<<stu;
        //qDebug()<<stu;

    }
    //qDebug()<<stuList;

}

void ScoreSorter::doSort(int j){
    int i=0;
    int num=stuList.size();
    std::sort(stuList.begin(),stuList.end(),myCmp(j));
    for (i=0;i<num;i++) {
        qDebug()<<stuList[i];
    }

}

    void ScoreSorter::myMessageOutput(){
    // 输出信息至文件中（读写、追加形式）
    QFile file("sorted_"+this->Filepath);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream output(&file);
    output.setCodec("UTF-8");  //编码方式
//    stream<<QString("排序后输出，当前排序第 ")<<lie <<QString(" 列：")<<"\r\n";
//    stream<<"\t";  //输出表头
    int num=stuList.size();
    output<<title;
    for(int i=0; i<num;i++){
        //s=stuList[i];
        output<<stuList[i].id<<stuList[i].name<<"\t\t"<<stuList[i].subj;
        output<<"\r\n";
    }
//    stream<<"----------------------------------------------------------------------------------------"<<"\r\n\r\n";
    file.close();
}

int main()
{
    int j;
    //qInstallMessageHandler(myMessageOutput);
    QString datafile = "data.txt";
    //如果排序后文件已存在，则删除之
    QFile f("sorted_"+datafile);
    if (f.exists()){
        f.remove();
    }

    ScoreSorter s(datafile);
    qDebug()<<"输入排序列数";
    QTextStream qin(stdin);
    qin>>j;
    s.readFile();
    s.doSort(j);
    s.myMessageOutput();
    return 0;
}
