#include "ss2mm.h"
#include "ui_ss2mm.h"
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>

SS2MM::SS2MM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SS2MM),
    inactiveModel(new QStringListModel(this)),
    activeModel(new QStringListModel(this))
{
    ui->setupUi(this);
    QStringList list;
    list << "Test 1" << "Test 2";

    inactiveModel->setStringList(list);
    ui->InactiveList->setModel(inactiveModel);
    // Should scan for available and already active mods
}

SS2MM::~SS2MM()
{
    delete ui;
}

void SS2MM::on_action_Scan_triggered()
{
    // Scan <ModDir> for non-empty folders; name will dictate name of mod
    QStringList list = inactiveModel->stringList();
    QDir dir(MODDIR);
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList info = dir.entryInfoList();
    for (int i = 0; i < info.size(); ++i)
    {
        QFileInfo fileInfo = info.at(i);
        if(fileInfo.isDir() && fileInfo.dir().count() > 0)
        {
            list.append(fileInfo.fileName());
        }
    }
    inactiveModel->setStringList(list);
}

void SS2MM::on_action_Install_triggered()
{
    // Display open dialog to select zipped file containing mod, extract to <ModDir>
    QString filename = QFileDialog::getOpenFileName(this);
    if(!filename.isEmpty())
    {
        // Strip location and extension for human readability
        QRegExp regex;
        regex.setPattern("[a-z0-9-_\\.\\s]*(\\.zip|\\.ss2mod)");
        regex.setCaseSensitivity(Qt::CaseInsensitive);
        int pos = regex.indexIn(filename);
        if(pos > -1)
        {
            QString modName = regex.cap(0);

            // Unzip and place in <ModDir>

            QStringList list = inactiveModel->stringList();
            list.append(modName);
            inactiveModel->setStringList(list);
            QModelIndex index = inactiveModel->index(inactiveModel->rowCount());
            ui->InactiveList->setCurrentIndex(index);
        }
    }
}

void SS2MM::on_action_Activate_Deactivate_triggered()
{
    // Toggle last clicked mod from either list (if possible)
}

void SS2MM::on_action_About_triggered()
{
    // Open dialog with application info
}
