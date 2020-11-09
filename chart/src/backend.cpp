#include "backend.h"

#include <QDebug>

Backend::Backend(QObject *parent) : QAbstractListModel{parent} {
  QPoint point{0, 0};
  for (int i = 0; i < 10; i++) {
    points_.push_back(point);
    if ((i % 2) == 0) {
      point.setX(point.x() + 20);
    } else {
      point.setY(point.y() + 20);
    }
  }
}

Backend::~Backend() {}

int Backend::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent)
  return points_.size();
}

QVariant Backend::data(const QModelIndex &index, int role) const {
  if (!index.isValid()) {
    return {};
  }

  switch (role) {
    case X:
      return points_.at(index.row()).x();
      break;
    case Y:
      return points_.at(index.row()).y();
      break;
  }

  return {};
}

QHash<int, QByteArray> Backend::roleNames() const {
  return {{X, "X"}, {Y, "Y"}};
}

bool Backend::setData(const QModelIndex &index, const QVariant &value,
                      int role) {
  if (!index.isValid()) {
    return false;
  }

  int row = index.row();
  if (row < 0 || row >= points_.size()) {
    return false;
  }

  int val = value.toInt();
  switch (role) {
    case X:
      if (points_.at(row).x() != val) {
        points_[row].setX(val);
        if ((row % 2) == 0) {
          setData(createIndex(row - 1, index.column()), value, X);
        } else {
          setData(createIndex(row + 1, index.column()), value, X);
        }
        emit dataChanged(index, index, {X});
      }
      break;
    case Y:
      if (points_.at(row).y() != val) {
        points_[row].setY(val);
        if ((row % 2) == 0) {
          setData(createIndex(row + 1, index.column()), value, Y);
        } else {
          setData(createIndex(row - 1, index.column()), value, Y);
        }
        emit dataChanged(index, index, {Y});
      }
      break;
    default:
      return false;
  }

  return true;
}

QPoint Backend::point(int row) const {
  if (row < 0 || row >= points_.size()) {
    return {};
  }
  return points_.at(row);
}
