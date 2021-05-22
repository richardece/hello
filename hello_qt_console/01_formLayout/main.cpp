#include <QApplication> 
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QStringList>

/*
QFormLayout
Compared to gridlayout,
    - It will automatically add label 
    - And no need to specify row and column   

*/
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //Create window
    QWidget *window = new QWidget;

    //Create widgets
    QLineEdit *firstNameLineEdit= new QLineEdit;
    QLineEdit *lastNameLineEdit= new QLineEdit;
    QSpinBox *ageSpingBox = new QSpinBox;
    ageSpingBox->setRange(1, 100); 
    QComboBox *employmentStatusComboBox= new QComboBox;
    QStringList employmentStatus = {"Unemployed", "Employed", "NA"}; 
    employmentStatusComboBox->addItems(employmentStatus); 

    //Add form layout (2-column format)
    QFormLayout *personalInfoformLayout = new QFormLayout; 
    personalInfoformLayout->addRow("First Name:", firstNameLineEdit); 
    personalInfoformLayout->addRow("Last Name:", lastNameLineEdit ); 
    personalInfoformLayout->addRow("Age", ageSpingBox); 
    personalInfoformLayout->addRow("Employment Status", employmentStatusComboBox); 

    //Set layout of the window, then show window   
    window->setLayout(personalInfoformLayout);
    window->show();

    return app.exec();
}