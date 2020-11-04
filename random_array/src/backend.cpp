#include "backend.h"
#include <QDebug>

Backend::Backend(QObject* parent) : QObject{parent} {}

Backend::~Backend() {}

void Backend::start() {
  if (!worker_) {
    worker_ = new Worker{this};
    connect(
        worker_, &Worker::newRandArray, this,
        [&](QVector<double> arr) {
          emit update(QVariant::fromValue(arr));
        });
  }
  worker_->start();
}

void Backend::pause() {
  if (worker_) {
    worker_->pause();
  }
}

void Backend::stop() {
  if (worker_) {
    worker_->stop();
    worker_->deleteLater();
    worker_ = nullptr;
  }
}
