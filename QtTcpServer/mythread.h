#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QHostAddress>
#include "datastorage.h"

/**
 * @brief
 *
 */
class MyThread : public QThread {
  Q_OBJECT
public:
  /**
   * @brief
   * @param ID
   * @param parent
   * @param storage
   */
  MyThread(int ID, QObject *parent, DataStorage* storage);
  void run();

signals:
  void error(QTcpSocket::SocketError socketerror);
  void message(QString);

public slots:
  void readyRead();
  void disconnected();

private:
  QTcpSocket *socket;
  int socketDescriptor;
  int* ok;
  QHostAddress peerAddress;
  DataStorage *storage;
  QString str;
};

#endif // MYTHREAD_H
