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

#include "ss2mm.h"
#include "ui_ss2mm.h"
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>
#include <QMessageBox>
#include <QTextStream>
#include <quazip/JlCompress.h>

SS2MM::SS2MM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SS2MM),
    inactiveModel(new ModListModel(this)),
    activeModel(new ModListModel(this)) {

    ui->setupUi(this);

    ui->InactiveList->setModel(inactiveModel);
    ui->ActiveList->setModel(activeModel);
    // Should scan for available and already active mods
    QStringList inactiveList;
    QStringList activeList;
    readModIni(&activeList);
    scan(&inactiveList, activeList);

    inactiveModel->setStringList(inactiveList);
    activeModel->setStringList(activeList);
    originalActiveList = activeList;
}

SS2MM::~SS2MM() {
    delete ui->InactiveList;
    delete ui->ActiveList;
    delete ui;
}

void SS2MM::on_action_Scan_triggered() {
    QStringList iList = inactiveModel->stringList();
    QStringList aList = activeModel->stringList();
    scan(&iList, aList);
    inactiveModel->setStringList(iList);
}

void SS2MM::on_action_Install_triggered() {
    QString filename = QFileDialog::getOpenFileName(this);
    if(!filename.isEmpty()) {
        QRegExp regex;
        regex.setPattern("[a-z0-9-_\\.\\s]*(\\.zip|\\.ss2mod)");
        regex.setCaseSensitivity(Qt::CaseInsensitive);
        int pos = regex.indexIn(filename);
        if(pos > -1) {
            QString modName = regex.cap(0).replace(QRegExp(".zip|.ss2mod", Qt::CaseInsensitive), "");

            // Call QuaZip library to extract compressed file to <ModDir>/<ModName>
            QStringList zipList = JlCompress::extractDir(filename, QString(MODDIR + '/' + modName));
            if(zipList.isEmpty()) {
                // Dialog saying it failed to load
                return;
            }

            QStringList list = inactiveModel->stringList();
            list.append(modName);
            inactiveModel->setStringList(list);
            QModelIndex index = inactiveModel->index(inactiveModel->rowCount());
            ui->InactiveList->setCurrentIndex(index);
        }
    }
}

void SS2MM::on_action_Activate_Deactivate_triggered() {
    if(ui->InactiveList->hasFocus()) {
        QModelIndex index = ui->InactiveList->currentIndex();
        QVariant value = ui->InactiveList->model()->data(index);
        if(value.isValid()) {
            QString mod = value.toString();

            QStringList activeMods = activeModel->stringList();
            activeMods.append(mod);
            activeModel->setStringList(activeMods);
            inactiveModel->removeRow(index.row());
        }
    }
    else if(ui->ActiveList->hasFocus()) {
        QModelIndex index = ui->ActiveList->currentIndex();
        QVariant value = ui->ActiveList->model()->data(index);
        if(value.isValid()) {
            QString mod = value.toString();

            QStringList inactiveMods = inactiveModel->stringList();
            inactiveMods.append(mod);
            inactiveModel->setStringList(inactiveMods);
            activeModel->removeRow(index.row());
        }
    }
}

void SS2MM::on_action_Apply_triggered() {
    if(activeModel->stringList().count() == 0) {
        return;
    } else {
        writeModIni(activeModel->stringList());
    }
}

void SS2MM::on_action_About_triggered() {
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

void SS2MM::on_action_Quit_triggered() {
    this->close();
}

void SS2MM::scan(QStringList *iList, QStringList aList) {
    QDir dir(MODDIR);
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList info = dir.entryInfoList();
    for (int i = 0; i < info.size(); ++i) {
        QFileInfo fileInfo = info.at(i);
        if(fileInfo.isDir() && fileInfo.dir().count() > 0) {
            iList->append(fileInfo.fileName());
        }
    }

    // Need to compare active list with installed mods
    QStringList::iterator it = aList.begin();
    while(it != aList.end()) {
        int pos = iList->indexOf(*it);
        if(pos != -1) {
            iList->removeAt(pos);
        }
        it++;
    }
}

void SS2MM::readModIni(QStringList *list) {
    // Read cam_mod.ini for mod_path that is in the SaltedFries directory
    QFile camMod("cam_mod.ini");

    if(!camMod.open(QIODevice::ReadOnly | QIODevice::Text))
        return; // Should probably display error about not seeing the file

    QTextStream inStream(&camMod);
    while(!inStream.atEnd()) {
        QString line = inStream.readLine();
        if(line.contains(QRegExp("^mod_path"))) {
            QRegExp modRE("SaltedFries/([a-zA-Z0-9-_\\.\\s]+)");
            modRE.indexIn(line);
            QStringList modList = modRE.capturedTexts();
            QStringList::iterator it = modList.begin();
            while(it != modList.end()) {
                if(!it->contains("SaltedFries/") && *it != "") {
                    list->append(*it);
                }
                it++;
            }
        }
    }
}

void SS2MM::writeModIni(QStringList modList) {
    QFile camMod("cam_mod.ini");
    if(!camMod.open(QIODevice::ReadOnly | QIODevice::Text))
        return; // Should probably display error about not seeing the file

    QFile outFile("ss2mmtemp");
    outFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream outStream(&outFile);
    QTextStream inStream(&camMod);
    while(!inStream.atEnd()) {
        QString line = inStream.readLine();
        if(line.contains(QRegExp("^mod_path"))) {
            QString modPath = "mod_path ";
            foreach (QString mod, modList) {
                modPath += MODDIR + "/" + mod + "+";
            }
            modPath += "DataPermMods/+patch_ext";
            outStream << modPath;
        }
        else
            outStream << line << endl;
    }
    outFile.close();
    camMod.close();
    camMod.remove();
    outFile.rename("cam_mod.ini");
    originalActiveList = modList;
}

void SS2MM::closeEvent(QCloseEvent *event) {
    // Check for changes in active mod list (compare against loaded StringList?)
    if(activeModel->stringList() != originalActiveList) {
        QMessageBox msg;
        msg.setText("You have changed what mods are active.");
        msg.setDetailedText("Would you like to save these changes?");
        msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Save);
        int ret = msg.exec();
        switch(ret) {
            case QMessageBox::Save:
                writeModIni(activeModel->stringList());
                break;
            case QMessageBox::Cancel:
                event->ignore();
                break;
            case QMessageBox::Discard:
            default:
                break;
        }
    }
    event->accept();
}
