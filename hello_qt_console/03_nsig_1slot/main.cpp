#include <QApplication> 
#include <QVBoxLayout>
#include <QLabel>
#include <QDial>
#include <QSlider>
#include <QLCDNumber>

int main(int argc, char *argv[]) 
{
    QApplication app(argc, argv);
    QWidget *window = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;

    //Create 2 control widgets and 1 display widget
    QDial *volumeDial= new QDial;
    QSlider *lengthSlider = new QSlider(Qt::Horizontal); //horizontal slider
    QLCDNumber *volumeLCD = new QLCDNumber; 

    //Set widget properties
    volumeLCD->setPalette(Qt::red); 
    lengthSlider->setTickPosition(QSlider::TicksAbove); 
    lengthSlider->setTickInterval(10); //display ticks above slider, every 10 steps
    lengthSlider->setSingleStep(1);     //1 step
    lengthSlider->setMinimum(0);
    lengthSlider->setMaximum(100); 
    volumeDial->setNotchesVisible(true);
    volumeDial->setMinimum(0);
    volumeDial->setMaximum(100);

    //Add widgets to vertical layout
    layout->addWidget(volumeDial);
    layout->addWidget(lengthSlider);
    layout->addWidget(volumeLCD);

    //Connect 2 signals to same slot
    QObject::connect(volumeDial,    SIGNAL(valueChanged(int)), volumeLCD , SLOT(display(int)));
    QObject::connect(lengthSlider,  SIGNAL(valueChanged(int)), volumeLCD , SLOT(display(int)));
    
    window->setLayout(layout);
    window->show();
    return app.exec(); 
}
