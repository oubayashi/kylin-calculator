/*
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"
#include <QApplication>
#include <QStringList>
#include <QStandardPaths>
#include <fcntl.h>
#include <syslog.h>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 国际化
    QString locale = QLocale::system().name();
    QTranslator trans_global, trans_menu;
    if(locale == "zh_CN"){
        trans_global.load(":/data/kylin-calculator_zh_CN.qm");
        trans_menu.load(":/data/qt_zh_CN.qm");
        a.installTranslator(&trans_global);
        a.installTranslator(&trans_menu);
    }

    MainWindow w;
    w.show();
//    w.setFixedSize(350, 550);   //固定窗体大小 禁止窗体通过鼠标放大缩小
//    w.setGeometry(QRect(500, 200, 432, 628));

    // 实现VNC单例
    QStringList homePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
    //需要给文件锁加一个DISPLAY标识  QtSingleApplication-Name改为kylin-calculator
    int fd = open(QString(homePath.at(0) + "/.config/kylin-calculator%1.lock").arg(getenv("DISPLAY")).toUtf8().data(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) { exit(1); }
    if (lockf(fd, F_TLOCK, 0)) {
        syslog(LOG_ERR, "Can't lock single file, kylin-calculator is already running!");
        exit(0);
    }



    return a.exec();
}
