#include "ss2mm.h"
#include "ui_ss2mm.h"
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>
#include <QMessageBox>
#include <quazip/JlCompress.h>

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
    delete ui->InactiveList;
    delete ui->ActiveList;
    delete ui;
}

void SS2MM::on_action_Scan_triggered()
{
    // Scan <ModDir> for non-empty folders; name of dir will dictate name of mod
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
            // Get mod name + extension
            QString modName = regex.cap(0).replace(QRegExp(".zip|.ss2mod", Qt::CaseInsensitive), "");

            // Call QuaZip library to extract compressed file to <ModDir>/<ModName>
            QStringList zipList = JlCompress::extractDir(filename, QString(MODDIR + '/' + modName));
            if(zipList.isEmpty())
                return;

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
    if(ui->InactiveList->hasFocus())
    {

    }
    else if(ui->ActiveList->hasFocus())
    {

    }
}

void SS2MM::on_action_About_triggered()
{
    // Open dialog with application info
    QString aboutText;
    aboutText += "Ryan <zeebok> Kornheisl\n";
    aboutText += QChar(0x00A9);
    aboutText += " 2013";
    QMessageBox about;
    about.setWindowTitle("About SS2MM");
    about.setText("System Shock 2 Mod Manager v0.1");
    about.setInformativeText(aboutText);
    about.exec();
}
