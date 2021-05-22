#include <QApplication> 
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include <QHBoxLayout>
/*
Vertical layout - widgets are added vertically downwards
Horizontal layout - widgets are added horizontally to the right
*/

int main(int argc, char *argv[]) 
{
    #if 0
    QApplication app(argc, argv);

    QWidget *window = new QWidget;

    //Create widgets
    QLabel *label1 = new QLabel("Username");
    QLabel *label2 = new QLabel("Password");
    QLineEdit *usernameLineEdit = new QLineEdit; 
    usernameLineEdit->setPlaceholderText("Enter your username"); //Placeholder gives more information about the purpose of the textbox
    QLineEdit *passwordLineEdit = new QLineEdit; 
    passwordLineEdit->setEchoMode(QLineEdit::Password);         //Masks the typed text with dots
    passwordLineEdit->setPlaceholderText("Enter your password"); 
    QPushButton *button1 = new QPushButton("&Login");
    QPushButton *button2 = new QPushButton("&Register");

    //Create vertical box layout
    QVBoxLayout *layout = new QVBoxLayout; 
    layout->addWidget(label1); 
    layout->addWidget(usernameLineEdit); 
    layout->addWidget(label2); 
    layout->addWidget(passwordLineEdit);
    layout->addWidget(button1); 
    layout->addWidget(button2); 
    
    //Set window layout, then display
    window->setLayout(layout);
    window->show();
    return app.exec(); 
    #else
    QApplication app(argc, argv);
    
    QWidget *window = new QWidget;
    
    //Create widgets
    QLineEdit *urlLineEdit= new QLineEdit;
    QPushButton *exportButton = new QPushButton("Export"); 
    urlLineEdit->setPlaceholderText("Enter Url to export. Eg, http://yourdomain.com/items"); 
    urlLineEdit->setFixedWidth(400); 
    
    //Create horzontal layout
    QHBoxLayout *layout = new QHBoxLayout; 
    layout->addWidget(urlLineEdit); 
    layout->addWidget(exportButton); 
    
    //Set layout to window, then display
    window->setLayout(layout); 
    window->show();
    return app.exec();

    #endif


}