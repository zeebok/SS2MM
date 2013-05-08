#ifndef SS2MM_H
#define SS2MM_H

#include <QMainWindow>
#include "modlistmodel.h"

const QString MODDIR = "DataPermMods";

namespace Ui {
    class SS2MM;
}

class SS2MM : public QMainWindow
{
        Q_OBJECT

    public:
        explicit SS2MM(QWidget *parent = 0);
        ~SS2MM();

    private slots:
        void on_action_Scan_triggered();

        void on_action_Install_triggered();

        void on_action_Activate_Deactivate_triggered();

        void on_action_Apply_triggered();

        void on_action_About_triggered();

    private:
        Ui::SS2MM *ui;
        ModListModel *inactiveModel;
        ModListModel *activeModel;
};

#endif // SS2MM_H
