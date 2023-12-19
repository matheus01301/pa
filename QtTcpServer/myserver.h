#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include <QStringList>

#include "mythread.h"
#include "datastorage.h"

/**
 * @brief
 * 
 */
class MyServer : public QTcpServer
{
  Q_OBJECT
public:
  /**
   * @brief 
   * @param parent 
   */
  MyServer(QObject *parent = 0);
  /**
   * @brief
   */
  void startServer();
  /**
   * @brief
   * @return
   */
  QStringList getIPList();

signals:
  void message(QString);

public slots:
  void receiveMsg(QString str);

protected:
  /**
   * @brief
   *
   * @param socketDescriptor
   *
   */
  void incomingConnection(qintptr socketDescriptor);
private:
  int ok;
  /**
   * @brief
   *
   */
  DataStorage storage;
  QStringList iplist;
};

#endif
