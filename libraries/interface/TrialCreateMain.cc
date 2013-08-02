#include "mainWindow.hh"
#include <wordexp.h>
#include "model.hh"
#include "view.hh"

int main(int argc,
         char** argv)
{
  QApplication app(argc, argv);
  //Ui_MainWindow* w = new Ui_MainWindow();
  //QMainWindow qmw;
  Model* m = new Model();
  View* v = new View();
  v->SetModel(m);
  wordexp_t exp_result;
  wordexp("~/.rexeno/shape_prototypes", &exp_result, 0);
  m->fillAvailableShapes(exp_result.we_wordv[0]);
  v->setupUi(v);
  v->show();
  v->Refresh();
  app.exec();
}
