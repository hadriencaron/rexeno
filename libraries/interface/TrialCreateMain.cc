#include "mainWindow.hh"
#include <wordexp.h>
#include "model.hh"

int main(int argc,
         char** argv)
{
  QApplication app(argc, argv);
  QMainWindow qmw;
  Ui_MainWindow* w = new Ui_MainWindow();
  Model* m = new Model();
  wordexp_t exp_result;
  wordexp("~/.rexeno/shape_prototypes", &exp_result, 0);
  
  m->fillAvailableShapes(exp_result.we_wordv[0]);
  w->setupUi(&qmw);
  qmw.show();
  app.exec();
}
