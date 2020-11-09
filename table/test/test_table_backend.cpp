#include <QtTest/QtTest>
#include "backend.h"

class TestTableBackend : public QObject {
  Q_OBJECT
 
 private slots:
  void testEmptyBackend() {
    Backend b;
    QCOMPARE(b.rowCount(QModelIndex{}), 0);
    QCOMPARE(b.columnCount(QModelIndex{}), Backend::Count);
    QVERIFY(b.removeRows(0, 1) == false);
    QVERIFY(b.copyRow(0) == false);
    QVERIFY(b.hasCache() == false);
  }

  void testFilledBackend() {
    Backend b{10};
    QCOMPARE(b.rowCount(QModelIndex{}), 10);
  }

  void testRemoveRows() {
    Backend b{10};
    QCOMPARE(b.rowCount(QModelIndex{}), 10);
    QVERIFY(b.removeRows(10, 1) == false);
    QVERIFY(b.removeRows(9, 1) == true);
    QCOMPARE(b.rowCount(QModelIndex{}), 9);

    QVERIFY(b.removeRows(-1, 1) == false);
    QVERIFY(b.removeRows(0, 2) == false);
  }

  void testCopy() {
    Backend b{10};

    QVERIFY(b.hasCache() == false);

    QVERIFY(b.copyRow(10) == false);
    QVERIFY(b.hasCache() == false);

    QVERIFY(b.copyRow(0) == true);
    QVERIFY(b.hasCache() == true);
  }

  void testInsertRow() {
    Backend b{10};

    QVERIFY(b.insertRows(10, 0) == false);
    QVERIFY(b.insertRows(-1, 0) == false);
    QCOMPARE(b.rowCount(QModelIndex{}), 10);

    QVERIFY(b.copyRow(0) == true);
    QVERIFY(b.insertRows(0, 1) == true);
    QCOMPARE(b.rowCount(QModelIndex{}), 11);
    QVERIFY(b.insertRows(11, 1) == true);
  }

  void testCopyInsertRemove() {
    Backend b{10};

    QVERIFY(b.copyRow(0) == true);
    QCOMPARE(b.rowCount(QModelIndex{}), 10);
    QVERIFY(b.insertRows(0, 1) == true);
    QCOMPARE(b.rowCount(QModelIndex{}), 11);
    QVERIFY(b.removeRows(0, 1) == true);
    QCOMPARE(b.rowCount(QModelIndex{}), 10);
  }
};

QTEST_MAIN(TestTableBackend)
#include "test_table_backend.moc"
