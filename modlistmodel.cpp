#include "modlistmodel.h"

ModListModel::ModListModel(QObject *parent) : QStringListModel(parent)
{
}

Qt::ItemFlags ModListModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags; //= QStringListModel::flags(index);

    if (index.isValid())
        flags =  Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled;
    else
        flags =  Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled  | Qt::ItemIsEnabled;

    return flags;
}
