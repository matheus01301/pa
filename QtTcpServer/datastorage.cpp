#include "datastorage.h"
#include <QMutexLocker>
#include <QDebug>

struct RangeTest{
  qint64 limit;
public:
  RangeTest(qint64 _limit) { limit = _limit;}
  bool operator()(qint64 n){
    return n > limit;
  }
};

DataStorage::DataStorage() : mutex(){
}

vector<Entry> DataStorage::getData(QHostAddress address, unsigned int lastn){


  vector<Entry> range;
  vector<Entry>::iterator vi;
  QMutexLocker ml(&mutex);
  dataIterator = data.find(address.toIPv4Address());
  if(dataIterator != data.end()){
    if(dataIterator.value().size() <= lastn){
      qDebug() << "dataIterator";
      return (dataIterator.value());
    }
    else{
      qDebug() << "entrou";
      qDebug() << "tam =" << dataIterator.value().size();
      qDebug() << "dis = " << distance(dataIterator.value().end()-lastn, dataIterator.value().end());
      for(vi=dataIterator.value().end()-lastn; vi!=dataIterator.value().end(); vi++){
        range.push_back(*vi);
      }
      qDebug() << "copy = " << range.size();
      return (range);
    }
  }
  else{
      return(vector<Entry>());
  }
}

void DataStorage::addData(QHostAddress address, qint64 time, float measurement){
  Entry entry;

  QMutexLocker ml(&mutex);

  entry.theTime = time;
  entry.measurement = measurement;
  dataIterator = data.find(address.toIPv4Address());
  if(dataIterator != data.end()){
    data[address.toIPv4Address()].push_back(entry);
  }
  else{
    vector<Entry> start;
    start.push_back(entry);
    data.insert(address.toIPv4Address(), start);
  }
}

vector<QHostAddress> DataStorage::getHostList()
{
  vector<QHostAddress> hostList;
  QList<quint32> uintList;
  uintList = data.keys();
  for(int i=0; i<uintList.size(); i++){
    hostList.push_back(QHostAddress(uintList[i]));
  }
  return hostList;
}













