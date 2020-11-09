#include "backend.h"

#include <QDebug>

static const QHash<Backend::DataFields, QVariant> ROW_PROTOTYPE{
    {Backend::First, "First"},
    {Backend::Second, "Second"},
    {Backend::Third, "Third"},
    {Backend::Fourth, "Fourth"},
    {Backend::Fifth, "Fifth"}};

Backend::Backend(int dummyLength, QObject *parent)
    : QAbstractTableModel{parent} {
  for (int i = 0; i < dummyLength; i++) {
    data_.push_back(ROW_PROTOTYPE);
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
  if (!index.isValid()) {
    return {};
  }
  switch (role) {
    case Qt::DisplayRole:
      return data_.at(index.row()).value((DataFields)index.column());
    default:
      break;
  }

  return {};
}

QHash<int, QByteArray> Backend::roleNames() const {
  return {{Qt::DisplayRole, "display"}, {Qt::EditRole, "edit"}};
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

bool Backend::removeRows(int row, int count, const QModelIndex &parent) {
  if (count != 1) {
    return false;
  }

  if (row >= 0 && row < data_.size()) {
    beginRemoveRows(parent, row, row);
    data_.removeAt(row);
    endRemoveRows();
    return true;
  }

  return false;
}

bool Backend::copyRow(int row) {
  if (row >= 0 && row < data_.size()) {
    cache_ = data_.at(row);
    hasCacheChanged();
    return true;
  }

  return false;
}

bool Backend::hasCache() const { return cache_.size() != 0; }

bool Backend::insertRows(int row, int count, const QModelIndex &parent) {
  if (count != 1) {
    return false;
  }

  if (row >= 0 && row <= data_.size()) {
    beginInsertRows(parent, row, row);
    if(row == data_.size()){
      data_.insert(row, ROW_PROTOTYPE);
    } else {
      if (!hasCache()) {
        return false;
      }
      data_.insert(row, cache_);
    }
    endInsertRows();
    return true;
  }

  return false;
}
