#include "parser.hh"
#include "mainWindow.hh"
#include "interface.hh"

Interface::Interface(QWidget* parent)
{
}


int main(int argc,
         char** argv)
{
  QApplication app(argc, argv);
  //Ui::MainWindow ui;
  QMainWindow qmw;
  Ui_MainWindow* m = new Ui_MainWindow();
  m->setupUi(&qmw);
  qmw.show();
  app.exec();
}
