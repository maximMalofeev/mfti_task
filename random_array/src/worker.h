#pragma once
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class Worker : public QThread
{
  Q_OBJECT
 public:
  explicit Worker(QObject* parent = nullptr);
  ~Worker() override;

  void start();
  void pause();
  void stop();

 signals:
  void newRandArray(QVector<double> arr);

 protected:
  void run() override;

 private:
  int length_{};
  bool doWork_{};
  bool onPause_{};
  QMutex mutex_;
  QWaitCondition resume_;
};
