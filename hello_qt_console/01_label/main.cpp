   #include <QApplication>
   #include <QString>
   #include <QLabel>
   
   int main(int argc, char *argv[])
   {
        QApplication app(argc, argv);
        QString message = "'What do you know about this business?' the King said to Alice.\n'Nothing,' said Alice.\n'Nothing whatever?' persisted the King.\n'Nothing whatever,' said Alice.";
        //QString is a more capabale version of C++ string

        QLabel label(message);  //create a label with the sting message
        label.setFont(QFont("Comic Sans MS", 24));      //set font
        label.setAlignment(Qt::AlignCenter);    //align all text to center
        label.show();

        return app.exec();
}