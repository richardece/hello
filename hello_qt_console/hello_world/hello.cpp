#include <QApplication> 
#include <QLabel>
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);   //instance of QApplication is created
    QLabel label("Hello world !");  //creates a widget
    label.show();                   //shows the widget
    return app.exec();              //creates the even tloop
}


/*
Steps to build
1. qmake -project   //will create pro file
2. qmake            //generates makefile
2. make             //compile
*/