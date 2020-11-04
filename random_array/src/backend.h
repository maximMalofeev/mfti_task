#pragma once
#include <QObject>
#include <QVariant>
#include "worker.h"

class Backend : public QObject {
  Q_OBJECT

 public:
  explicit Backend(QObject* parent = nullptr);
  ~Backend() override;

  Q_INVOKABLE void start();
  Q_INVOKABLE void pause();
  Q_INVOKABLE void stop();

 signals:
  void update(QVariant arr);

 private:
  int count_{};
  Worker* worker_{};
};
