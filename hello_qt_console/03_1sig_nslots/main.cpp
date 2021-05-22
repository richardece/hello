
#include <QApplication> 
#include <QVBoxLayout>
#include <QLabel>
#include <QDial>
#include <QLCDNumber>

/*
An example of how to connect same signal to several slots
*/
int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);

    QWidget *window = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    //Create 2 display widgets and 1 control widget
    QLabel *volumeLabel = new QLabel("0");
    QLCDNumber *volumeLCD = new QLCDNumber; //displays information in LCD-like format
    QDial *volumeDial= new QDial;
    
    volumeLCD->setPalette(Qt::red);             //set the color of the LCD display
    volumeLabel->setAlignment(Qt::AlignHCenter);//align to the center
    volumeDial->setNotchesVisible(true);        //graduations around the dial are visible
    volumeDial->setMinimum(0);                  //set minimum and maximum values
    volumeDial->setMaximum(50);

    //Add widgets to vertical layout
    layout->addWidget(volumeDial);
    layout->addWidget(volumeLabel);
    layout->addWidget(volumeLCD);

    //Connect 1 signal to 2 slots
    QObject::connect(volumeDial, SIGNAL(valueChanged(int)), volumeLabel, SLOT(setNum(int)));
    QObject::connect(volumeDial, SIGNAL(valueChanged(int)), volumeLCD , SLOT(display(int)));
    
    //Set window layout, then display
    window->setLayout(layout);
    window->show();
    return app.exec();
}