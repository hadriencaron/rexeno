#ifndef VIEW_HH_
# define VIEW_HH_

# include "mainWindow.hh"
# include "model.hh"

class View : public Ui_MainWindow
{
public:
  View(Model* m);
  void Refresh();

private:
  Model* _m;
};



#endif /* VIEW_HH_ */


  
