/*  System Shock 2 Mod Manager (SS2MM)
    Copyright (C) 2013  Ryan "zeebok" Kornheisl

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
