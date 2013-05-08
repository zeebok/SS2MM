#ifndef MODLISTMODEL_H
#define MODLISTMODEL_H

#include <QStringListModel>

class ModListModel : public QStringListModel
{
    public:
        ModListModel(QObject* parent);
        Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // MODLISTMODEL_H
