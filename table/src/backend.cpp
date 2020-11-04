#include "backend.h"

#include <QDebug>

Backend::Backend(QObject *parent) : QAbstractTableModel{parent} {
  for (int i = 0; i < 20; i++) {
    data_.push_back({{First, "First"},{Second, "Second"}, {Third, "Third"}, {Fourth, "Fourth"}, {Fifth, "Fifth"}});
  }
}

Backend::~Backend() {}

int Backend::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return data_.size();
}

int Backend::columnCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return Count;
}

QVariant Backend::data(const QModelIndex &index, int role) const {
  switch (role) {
    case Qt::DisplayRole:
      return data_.at(index.row()).value((DataFields)index.column());
    default:
      break;
  }

  return QVariant();
}

QHash<int, QByteArray> Backend::roleNames() const {
  return {{Qt::DisplayRole, "backendData"}, {Qt::EditRole, "edit"}};
}

bool Backend::setData(const QModelIndex &index, const QVariant &value,
                      int role) {
  if (index.isValid() && role == Qt::EditRole) {
    if (data_.at(index.row()).value((DataFields)index.column()) !=
        value.toString()) {
      data_[index.row()].insert((DataFields)index.column(), value);
      emit dataChanged(index, index, {Qt::EditRole, Qt::DisplayRole});
      return true;
    }
  }
  return false;
}
