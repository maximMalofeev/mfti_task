#pragma once
#include <QObject>
#include <QThread>

class Backend : public QObject {
  Q_OBJECT

 public:
  explicit Backend(QObject* parent = nullptr);
  ~Backend() override;

  Q_INVOKABLE void start();
  Q_INVOKABLE void pause();
  Q_INVOKABLE void stop();

 signals:
  void update(QVariant points);

 private:
  QThread* backgroundThread_{};
};