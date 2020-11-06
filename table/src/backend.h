#pragma once
#include <QAbstractTableModel>
#include <QHash>
#include <QList>
#include <QObject>
#include <QVariant>

class Backend : public QAbstractTableModel {
  Q_OBJECT
  Q_PROPERTY(bool hasCache READ hasCache NOTIFY hasCacheChanged)

 public:
  explicit Backend(QObject *parent = nullptr);
  ~Backend() override;

  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override;
  Q_INVOKABLE bool removeRows(
      int row, int count, const QModelIndex &parent = QModelIndex()) override;
  Q_INVOKABLE bool insertRows(
      int row, int count, const QModelIndex &parent = QModelIndex()) override;
  Q_INVOKABLE bool copyRow(int row);

  bool hasCache() const;

 signals:
  void hasCacheChanged();

 private:
  enum DataFields { First, Second, Third, Fourth, Fifth, Count };
  QList<QHash<DataFields, QVariant>> data_;
  QHash<DataFields, QVariant> cache_;
};
