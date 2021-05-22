
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QDial>

/*
An example of 1 signal, 1 slot configuration.
*/
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);

    //Create window and vertical layout
    QWidget *window = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    //Create widgets
    QLabel *volumeLabel = new QLabel("0");  //Initial value = 0
    QDial *volumeDial= new QDial;           //Looks liek a volume knob

    //Add widgets to layout
    layout->addWidget(volumeDial);
    layout->addWidget(volumeLabel);

    /*
    Whenever the knob is changed, a signal "valueChanged(int)" is emitted.
    Slot "setNum(int)" is called to receive the value int.
    While there could be many other state changes in the knob, the connect method
    makes it explicit that we are only interested in the knob value, which in turn
    emitted its value through the "valueChanged(int)" signal
    */ 
    QObject::connect(volumeDial,                //objectA, observable object
                    SIGNAL(valueChanged(int)),  //methodObjectA, signal when objectA is clicked
                    volumeLabel,                //objectB, observer object
                    SLOT(setNum(int)));         //methodObjectB, method ot be called in the observer object
    
    window->setLayout(layout);
    window->show();
    return app.exec();
}