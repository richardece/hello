
#include <QApplication> 
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QDateTimeEdit> 
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QStringList>

/*
QGridLayout can place widgets in specific rows and columns.
If one row contains fewer columns, the widgets will be stretched.
*/
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget;      //new window

    //Create widgets
    QLabel *nameLabel = new QLabel("Open Happiness");

    QLineEdit *firstNameLineEdit= new QLineEdit;    //textbox
    QLineEdit *lastNameLineEdit= new QLineEdit;

    QSpinBox *ageSpinBox = new QSpinBox;            //allows for selection of value within a range
    ageSpinBox->setRange(1, 100);

    QComboBox *employmentStatusComboBox= new QComboBox;

    QStringList employmentStatus = {"Unemployed", "Employed", "NA"}; //drop-down values specified by a string list
    employmentStatusComboBox->addItems(employmentStatus); 
    
    //Create a grid layout
    QGridLayout *layout = new QGridLayout; 

    //Add the widget to the layout by specifying rows and columns
    layout->addWidget(nameLabel,                        0, 0); 
    layout->addWidget(firstNameLineEdit,                0, 1); 
    layout->addWidget(lastNameLineEdit,                 0, 2); 
    layout->addWidget(ageSpinBox,                       1, 0); 
    layout->addWidget(employmentStatusComboBox, 1, 1,   1, 2); 
    
    //Set the layout of the window and then display
    window->setLayout(layout);
    window->show();

    return app.exec();
}