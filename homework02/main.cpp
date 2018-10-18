#include <QDebug>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QCoreApplication>

struct studData{
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
    }
    return result;

}


class ScoreSorter
{
public:
    ScoreSorter(QString dataFile);
    void readFile();
    void doSort(int j);
    void myMessageOutput();
    friend QDebug operator << (QDebug d,const studData &data);
private:
    QVector<studData> stuList;
    QString Filepath;
    QString title;
};

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
    }
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
    int num=stuList.size();
    output<<title;
    for(int i=0; i<num;i++){
        output<<stuList[i].id<<stuList[i].name<<"\t\t"<<stuList[i].subj;
        output<<"\r\n";
    }
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
