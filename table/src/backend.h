#pragma once
#include <QAbstractTableModel>
#include <QList>
#include <QHash>
#include <QVariant>

class Backend : public QAbstractTableModel {
  Q_OBJECT

 public:
  explicit Backend(QObject* parent = nullptr);
  ~Backend() override;

  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role) override;

 private:
  enum DataFields {First, Second, Third, Fourth, Fifth, Count};
  QList<QHash<DataFields, QVariant>> data_;
};
