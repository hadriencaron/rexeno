/**
 * @file   view.hh
 * @author hadrien <hadrien@barbow>
 * @date   Sun Aug 11 00:58:54 2013
 * 
 * @brief  The view Class inherits from the Ui::MainWindow which was designed with a QtDesigner program
 * it adds to it a number of slots to modify the model and render the model's change
 * NOTE : This class was done a little quickly, the MVC design pattern is not completely respected
 * 
 * 
 */

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

  void Init();
public slots:
  void Hello();
  void SetShapeType(QString);
  void AddShape();
  void DrawProtocole();
  void Clear();
  void DeleteShape();
  void Up();
  void Down();
  void Edit();
  void Save();

private:
  Model* _m;
};

QT_END_NAMESPACE

#endif /* VIEW_HH_ */

