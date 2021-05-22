#include "mainwindow.h"

MainWindow::MainWindow()
{
    setWindowTitle("Form in Window");
    setFixedSize(500, 500);

    //Create icons
    QPixmap newIcon("new.png");
    QPixmap openIcon("open.png");
    QPixmap closeIcon("close.png");

    // Setup File Menu
    quitAction = new QAction(closeIcon, //closeIcon is the icon that will be associated with this sub-menu
                            "Quit",     //"Quit" is the display name
                            this);      //makes quitAction a child widget of MainWindow
    quitAction->setShortcuts(QKeySequence::Quit);   //by using this instead of a specific key, it will not matter that platform is used (Windows or Mac)
                                                    //either Command + Q (Mac) or Alt + F4 (Linux) will close the app 
    newAction = new QAction(newIcon, "&New", this); 
    newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C)); 
    openAction = new QAction(openIcon, "&New", this);
    openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    fileMenu = menuBar()->addMenu("&File"); //Add menu called "File", & sign will make a shortcut Alt + F
    fileMenu->addAction(newAction);         //Add sub-menu
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    //Setup help menu
    aboutAction = new QAction("About", this); 
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H)); 
    helpMenu = menuBar()->addMenu("Help");  //Add menu called "Help"
    helpMenu->addAction(aboutAction);
    
    // Setup Tool bar menu
    toolbar = addToolBar("main toolbar");
    
    // toolbar->setMovable( false );    //Toolbar is movable by default
    newToolBarAction = toolbar->addAction(QIcon(newIcon),   //icon
                                            "New File");    //tooltip
    openToolBarAction = toolbar->addAction(QIcon(openIcon), "Open File"); 
    toolbar->addSeparator();
    closeToolBarAction = toolbar->addAction(QIcon(closeIcon), "Quit Application");
    
    // Setup Signals and Slots
    connect(quitAction,         
            &QAction::triggered,    //All QAction objects emit a "triggered" signal, same as writing SIGNAL(triggered())
            this,                   //Refers to MainWindow object
            &QApplication::quit);   
    connect(closeToolBarAction, &QAction::triggered, this, &QApplication::quit);
}
