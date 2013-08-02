#ifndef VIEW_HH_
# define VIEW_HH_

# include "mainWindow.hh"
# include "model.hh"

QT_BEGIN_NAMESPACE

class View : public QMainWindow, public Ui::MainWindow
{
  Q_OBJECT

public:
  View();
  ~View() {}
  void SetModel(Model* m);

  void Refresh();
public slots:
  void Hello();

private:
  Model* _m;
  //Ui_MainWindow* _window;
};

QT_END_NAMESPACE

#endif /* VIEW_HH_ */

