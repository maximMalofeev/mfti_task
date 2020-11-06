#include <QtTest/QtTest>
#include "worker.h"

class TestWorker : public QObject {
  Q_OBJECT
 
 private slots:
  void testDoubleStart() {
    Worker w;
    w.start();
    w.start();
    w.stop();
    QVERIFY(true);
  }

  void testStopWithoutStart() {
    Worker w;
    w.stop();
    QVERIFY(true);
  }

  void testStartPauseStop() {
    Worker w;
    w.start();
    w.pause();
    w.stop();
    QVERIFY(true);
  }

  void testIfSignalEmitted() {
    Worker w;
    QSignalSpy spy{&w, SIGNAL(newRandArray(QVector<double>))};
    QVERIFY(spy.isValid());

    w.start();
    spy.wait(100);
    w.start();
    spy.wait(100);
    w.stop();
    QVERIFY(spy.count() > 0);
    auto first = qvariant_cast<QVector<double>>(spy.takeFirst().first());
    QVERIFY(first.size() >= 10);
  }
};

QTEST_MAIN(TestWorker)
#include "test_worker.moc"