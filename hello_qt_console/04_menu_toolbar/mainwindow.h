#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QAction>
#include <QPushButton>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QtGui>
#include <Qt>
#include <QToolBar>
#include <QTableView>

class MainWindow : public QMainWindow 
{
    Q_OBJECT        //makes the signals and slot mechanism work
public:
    MainWindow(); 
    
private slots:

private:
    // Menus
    QMenu *fileMenu;
    QMenu *helpMenu;

    // Menu actions
    QAction *quitAction;
    QAction *aboutAction;
    QAction *saveAction;
    QAction *cancelAction;
    QAction *openAction;
    QAction *newAction;
    QAction *aboutQtAction;
    
    //Toolbar and toolbar actions
    QToolBar *toolbar;
    QAction *newToolBarAction;
    QAction *openToolBarAction;
    QAction *closeToolBarAction;
}; 

#endif