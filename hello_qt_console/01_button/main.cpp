#include <QApplication> 
#include <QPushButton>

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);

    QPushButton myButton(QIcon("filesaveas.png"),"Push Me");    //button with icon
    myButton.setToolTip("Click this to turn back the hands of time"); //add tooltip
    myButton.show();
    return app.exec();
}