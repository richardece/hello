#include "mainwindow.h"

MainWindow::MainWindow()
{
    setWindowTitle("RMS System");
    setFixedSize(500, 500);

    setWindowIcon(QIcon("window_logo.png"));    //icon that will show up in the taskbar when app is running, DOES NOT WORK

    createIcons();
    setupCoreWidgets();
    createMenuBar();
    createToolBar();

    centralWidgetLayout->addLayout(formLayout);     //will be diplayed on top
    centralWidgetLayout->addWidget(appTable);       //will be displayed in the middle
    //centralWidgetLayout->addStretch();
    centralWidgetLayout->addLayout(buttonsLayout);  //will be diplayed at the bottom

    mainWidget->setLayout(centralWidgetLayout);

    setCentralWidget(mainWidget);

    setupSignalsAndSlots();

}



void MainWindow::createIcons() {
    newIcon     = QPixmap("new.png");
    openIcon    = QPixmap("open.png");
    closeIcon   = QPixmap("close.png");
    clearIcon   = QPixmap("clear.png");
    deleteIcon  = QPixmap("delete.png");
}

void MainWindow::setupCoreWidgets() {
    mainWidget          = new QWidget();
    centralWidgetLayout = new QVBoxLayout();
    formLayout          = new QGridLayout();
    buttonsLayout       = new QHBoxLayout();

    //1. Add labels and input box for name, birthdate, phone number
    nameLabel           = new QLabel("Name:");
    dateOfBirthLabel    = new QLabel("Date Of Birth:");
    phoneNumberLabel    = new QLabel("Phone Number");
    nameLineEdit        = new QLineEdit();
    dateOfBirthEdit     = new QDateEdit(QDate(1980, 1, 1));
    phoneNumberLineEdit = new QLineEdit();

    //2. Add buttons
    savePushButton      = new QPushButton("Save");
    clearPushButton     = new QPushButton("Clear All");

    //3. TableView
    appTable = new QTableView();    //Will use rows and columns to display name, birthdate, phone number
    appTable->setContextMenuPolicy(Qt::CustomContextMenu);
    appTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //enables the header to fully stretch out the full window 
    
    //3.1 model will hold the data for the QTable
    model   = new QStandardItemModel(1, 3, this);   //1 row and 3 columns
    appTable->setModel(model);

    //3.2 Create header for the table
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Date of Birth")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Phone Number")));

    //3.3 Add default data to the table
    QStandardItem *firstItem    = new QStandardItem(QString("G. Sohne"));
    QDate dateOfBirth(1980, 1, 1);
    QStandardItem *secondItem   = new QStandardItem(dateOfBirth.toString());
    QStandardItem *thirdItem    = new QStandardItem(QString("05443394858"));
    model->setItem(0,0, firstItem);
    model->setItem(0,1, secondItem);
    model->setItem(0,2, thirdItem);

    //4. Data entry layouts
    //This being grid layout, we can put widgets in rows and columns
    formLayout->addWidget(nameLabel,            0, 0);
    formLayout->addWidget(nameLineEdit,         0, 1);
    formLayout->addWidget(dateOfBirthLabel,     1, 0);
    formLayout->addWidget(dateOfBirthEdit,      1, 1);
    formLayout->addWidget(phoneNumberLabel,     2, 0);
    formLayout->addWidget(phoneNumberLineEdit,  2, 1);

    //5. Button layout
    //This is a horizontal layout
    buttonsLayout->addStretch();    //This will fill the space on the left so that the buttons will be placed on the right
    buttonsLayout->addWidget(savePushButton);
    buttonsLayout->addWidget(clearPushButton);

}


void MainWindow::createMenuBar() {
    //1.  Setup File Menu
    fileMenu = menuBar()->addMenu("&File");

    newAction   = new QAction(newIcon, "&New", this);
    newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    openAction  = new QAction(openIcon, "&New", this);
    openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    quitAction  = new QAction(closeIcon, "Quit", this);
    quitAction->setShortcuts(QKeySequence::Quit);

    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    //2. Setup Help menu
    helpMenu = menuBar()->addMenu("Help");

    aboutAction = new QAction("About", this);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));

    helpMenu->addAction(aboutAction);

}


void MainWindow::createToolBar() {
    //1. Setup Tool bar menu
    toolbar = addToolBar("main toolbar");
    // toolbar->setMovable( false );

    newToolBarAction    = toolbar->addAction(QIcon(newIcon), "New File");
    openToolBarAction   = toolbar->addAction(QIcon(openIcon), "Open File");
    toolbar->addSeparator();
    clearToolBarAction  = toolbar->addAction(QIcon(clearIcon), "Clear All");
    deleteOneEntryToolBarAction = toolbar->addAction(QIcon(deleteIcon), "Delete a record");
    closeToolBarAction  = toolbar->addAction(QIcon(closeIcon), "Quit Application");

}


void MainWindow::setupSignalsAndSlots() {
    // Setup Signals and Slots
    connect(quitAction,         &QAction::triggered, this, &QApplication::quit);
    connect(aboutAction,        SIGNAL(triggered()), this, SLOT(aboutDialog()));
    connect(clearToolBarAction, SIGNAL(triggered()), this, SLOT(clearAllRecords()));
    connect(closeToolBarAction, &QAction::triggered, this, &QApplication::quit);
    connect(savePushButton,     SIGNAL(clicked()),   this, SLOT(saveButtonClicked()));
    connect(clearPushButton,    SIGNAL(clicked()),   this, SLOT(clearAllRecords()));
    connect(deleteOneEntryToolBarAction,    SIGNAL(triggered()), this, SLOT(deleteSavedRecord()));

}

void MainWindow::deleteSavedRecord()
{
    bool ok;
    int rowId = QInputDialog::getInt(this, 
                                    tr("Select Row to delete"),     //window title
                                    tr("Please enter Row ID of record (Eg. 1)"),    //main message
                                    1,                  //default
                                    1,                  //minimum
                                    model->rowCount(),  //maximum
                                    1,                  //incrememntal step between min and max
                                    &ok );              //if user presses Ok, True will be set
    if (ok)
    {
        model->removeRow(rowId-1);
    }
}



void MainWindow::saveButtonClicked()
{
    //Extract the information that the user typed
    QStandardItem *name = new QStandardItem(nameLineEdit->text());
    QStandardItem *dob = new QStandardItem(dateOfBirthEdit->date().toString());
    QStandardItem *phoneNumber = new QStandardItem(phoneNumberLineEdit->text());

    //Append to the table
    model->appendRow({ name, dob, phoneNumber});
    
    //Clear input fields
    clearFields();

    //Display information box
    QMessageBox::information(this, 
                            tr("RMS System"),                //??
                            tr("Record saved successfully!"),       //Message
                             QMessageBox::Ok|QMessageBox::Default,  //Ok button, default selected
                             QMessageBox::NoButton,                 //Second button (not displayed)
                             QMessageBox::NoButton);                //THird button (not displayed)

}

void MainWindow::clearFields()
{
    //Clear fields
    nameLineEdit->clear();              //Either call clear method
    phoneNumberLineEdit->setText("");   //or call setText("")
    QDate dateOfBirth(1980, 1, 1);
    dateOfBirthEdit->setDate(dateOfBirth);

}


void MainWindow::clearAllRecords()
{
    /*
    int status = QMessageBox::question( this, 
                                        tr("Delete Records ?"),
                                        tr("You are about to delete all saved records "
                                           "<p>Are you sure you want to delete all records "),
                                        QMessageBox::No|QMessageBox::Default, 
                                        QMessageBox::No|QMessageBox::Escape, 
                                        QMessageBox::NoButton);
    if (status == QMessageBox::Yes)
        return model->clear();
    */


    int status = QMessageBox::question(this, 
                                        tr("Delete all Records ?"), //Window title
                                        tr("This operation will delete all saved records."  //main message
                                          "<p>Do you want to remove all saved records?"), 
                                        tr("Yes, Delete all records"),  //First button, will return 0 status
                                        tr("No !"),                     //Second button, will return 1 status
                                        QString(),                      //THird button, not displayed
                                        1,        //means "No" button will be the default   
                                        1);       //means "No" button will be selected when Escape key is pressed
    if (status == 0) {      //if "Yes" is pressed
        int rowCount = model->rowCount();
        model->removeRows(0, rowCount); //remove rows from 0 until rowCount, IS THERE AN OVERFLOW?
    }

}


void MainWindow::aboutDialog()
{
    //App logo is supposed to be displayed here, but does not work
    //App logo is defined by by setWindowIcon()
    QMessageBox::about(this, 
                        "About RMS System",     //Window title, DOES NOT WORK
                        "RMS System 2.0"        //Main message
                        "<p>Copyright &copy; 2005 Inc."
                        "This is a simple application to demonstrate the use of windows,"
                        "tool bars, menus and dialog boxes");
    /*
    This is called the static method. There is another way to do this using set property method, which is more flexible.
    TODO: make a dialog box using set property
    */
    
}
