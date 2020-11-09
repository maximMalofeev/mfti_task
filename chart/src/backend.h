#pragma once
#include <QAbstractListModel>
#include <QList>
#include <QObject>

class Backend : public QAbstractListModel {
  Q_OBJECT

 public:
  explicit Backend(QObject *parent = nullptr);
  ~Backend() override;

  int rowCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QHash<int, QByteArray> roleNames() const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role) override;
  Q_INVOKABLE QPoint point(int row) const;

 private:
  enum Roles { X = Qt::UserRole + 1, Y };
  QList<QPoint> points_;
};
