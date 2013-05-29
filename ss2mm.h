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

#ifndef SS2MM_H
#define SS2MM_H

#include <QtWidgets>
#include <QMainWindow>
#include "modlistmodel.h"

const QString MODDIR = "SaltedFries";

namespace Ui {
    class SS2MM;
}

class SS2MM : public QMainWindow {
        Q_OBJECT

    public:
        explicit SS2MM(QWidget *parent = 0);
        ~SS2MM();

    protected:
        void closeEvent(QCloseEvent *event);

    private slots:
        void on_action_Scan_triggered();

        void on_action_Install_triggered();

        void on_action_Activate_Deactivate_triggered();

        void on_action_Apply_triggered();

        void on_action_About_triggered();

        void on_action_Quit_triggered();

    private:
        Ui::SS2MM *ui;
        QStringList originalActiveList;
        ModListModel *inactiveModel;
        ModListModel *activeModel;
        void scan(QStringList *list);
        void readModIni(QStringList *list);
        void writeModIni(QStringList modList);
};

#endif // SS2MM_H
