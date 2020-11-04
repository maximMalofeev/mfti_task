#include "worker.h"

#include <QRandomGenerator>

Worker::Worker(QObject* parent) : QThread{parent} {
  length_ = QRandomGenerator::global()->bounded(100);
  if(length_ < 10) {
    length_ = 10;
  }
}

Worker::~Worker() {
  if (isRunning()) {
    stop();
    wait();
  }
}

void Worker::start() {
  QMutexLocker lock{&mutex_};
  if (isRunning()) {
    if (onPause_) {
      onPause_ = false;
      resume_.wakeAll();
    }
  } else {
    doWork_ = true;
    QThread::start();
  }
}

void Worker::pause() {
  QMutexLocker lock{&mutex_};
  if (isRunning()) {
    onPause_ = true;
  }
}

void Worker::stop() {
  {
    QMutexLocker lock{&mutex_};
    doWork_ = false;
    if (onPause_) {
      onPause_ = false;
      resume_.wakeAll();
    }
  }
}

void Worker::run() {
  QRandomGenerator* g = QRandomGenerator::global();
  while (true) {
    QVector<double> arr(length_);
    for (auto& i : arr) {
      i = g->generateDouble();
    }

    {
      QMutexLocker lock{&mutex_};
      if (onPause_) {
        resume_.wait(&mutex_);
      }
      if (!doWork_) {
        break;
      }
      emit newRandArray(arr);
    }

    msleep(50);
  }
}
