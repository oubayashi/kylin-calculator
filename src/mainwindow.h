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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QRegExp>
#include <QTime>
#include <QVector>

#include "titlebar.h"
#include "widgetstyle.h"
#include "funclist.h"
#include "standardmodel.h"
#include "scientificmodel.h"
#include "toolmodel.h"
#include "InputProcess.h"
#include "InputSymbols.h"
#include "daemonipcdbus.h"
//class TitleBar;

class MainWindow : public QMainWindow, public InputSymbols
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle();

    // 公有组件，即标题栏和功能列表
    void setCommonUi();

    // 计算器输出窗口组件
    void setOutputUi();

    // 标准计算界面布局
    void setStandardUi();

    // 科学计算界面布局
    void setScientificUi();

    // 换算器界面布局
    void setToolUi();

    // 计算器界面切换布局
    void changeCalculatorUi();

    // 换算器界面切换布局
    void changeToolUi();

    // 显示输出
    void lab_output(QString s,QLabel *l);
    void updateOutput(QVector<QString> outVector);

    // 添加千分位
    QString addComma(QString s);

    // 换算器输入响应事件
    void unitCalc();

    // 将用于显示的表达式格式化为用于运算的表达式
    QString formatDisToCal(QString text);
public slots:
    // 键盘响应事件
    void keyPressEvent(QKeyEvent *event);


    void btn_merge(const QString &);
    // 处理按钮点击事件
    void btn_handler(bool);

    // 科学模式下专属按钮点击事件
    void sciBtnHandler(bool);

    // del按钮点击事件
    void delete_btn_handle(bool);

    // 功能列表按钮点击事件
    void funcListHandle(bool);

    // 功能列表项点击事件
    void funcListItemClicked(QListWidgetItem*);

    // 窗口置顶按钮点击事件
    void stayTop();

    // 汇率换算事件
    void unitConversion();

private:

    Qt::WindowFlags winFlags;

    QLabel *lab_last;
    QLabel *lab_now;
    QLabel *lab_prepare;

    QStackedWidget *stackedModelWid;
    QStackedWidget *stackedToolWod;

    QPushButton *btnNum[10];
    QPushButton *btnClear;
    QPushButton *btnDiv;
    QPushButton *btnMulti;
    QPushButton *btnDelete;
    QPushButton *btnSub;
    QPushButton *btnAdd;
    QPushButton *btnEqual;
    QPushButton *btnPer;
    QPushButton *btnPoint;

    // 整体界面布局
    QVBoxLayout *mainLayout;

    QWidget *mainWid;
    QWidget *titleBarWid;
    QWidget *outputWid;
    QWidget *buttonWid;
    QWidget *funcListWid;

    TitleBar *pTitleBar;
    FuncList *funcList;

    StandardOutput *standardOutput;
    StandardModel  *standardModel;

    ScientificOutput *scientificOutput;
    ScientificModel  *scientificModel;

    ToolModelOutput *toolModelOutput;
    ToolModelButton *toolModelButton;

//    QListWidget *funcListWid;

    QString dis_data;
    QString result;
    QString num_now;

    // 用于显示的表达式
    QString disData;
    // 用于运算的表达式
    QString calData;


    // 记录计算历史记录,输入'='时触发
    QVector<QString> disHistory;

    // 用户手册功能
    DaemonIpcDbus *mDaemonIpcDbus;

    // 重绘窗口
    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H