#include "view.hh"

void
View::SetModel(Model* m)
{
  _m = m;
}

View::View()
{
  _m = NULL;
}

void
View::SetShapeType(int t)
{
  QString shapeName = ShapesComboBox->currentText();
  AttributesTableWidget->clear();
  map<string, vector<string> > prototype = _m->shapePrototypes();
  int size = prototype[shapeName.toStdString()].size() - 1;
  AttributesTableWidget->setRowCount(size);
  for (int i = 0; i < size; ++i)
  {
    string curString = prototype[shapeName.toStdString()][i];
    uint pos = curString.find("=");
    if (pos != string::npos)
    {
      string shapeName, shapeValue;
      shapeName = curString.substr(0, pos);
      shapeValue = curString.substr(pos+1);
      QTableWidgetItem *item = new QTableWidgetItem(tr(shapeName.c_str()).arg(pow(1, 0)));
      AttributesTableWidget->setItem(i, 0, item);
      QTableWidgetItem *item2 = new QTableWidgetItem(tr(shapeValue.c_str()).arg(pow(1, 0)));
      AttributesTableWidget->setItem(i, 1, item2);
    }
    else
    {
      QTableWidgetItem *item = new QTableWidgetItem(tr(curString.c_str()).arg(pow(1, 0)));
      AttributesTableWidget->setItem(i, 0, item);
    }
  }
}

void
View::Refresh()
{
  connect(OKButton, SIGNAL(clicked()), (View*) this, SLOT(Hello()));
  connect(ShapesComboBox, SIGNAL(currentIndexChanged(int)), (View*) this, SLOT(SetShapeType(int)));
  connect(AddShapeButton, SIGNAL(clicked()), (View*) this, SLOT(AddShape()));

  this->TrialNameLabel->setText(_m->trialName().c_str());
  vector<string>::iterator it;
  vector<string>& shapes = _m->availableShapes();

  for (it = shapes.begin(); it != shapes.end(); ++it)
    this->ShapesComboBox->addItem(it->c_str());

}

void
View::Hello()
{
  cout << "hello" << endl;
}

void
View::AddShape()
{
  QString shapeName = ShapesComboBox->currentText();
  QString newLine = shapeName;
  map<string, vector<string> > prototype = _m->shapePrototypes();
  int size = prototype[shapeName.toStdString()].size() - 1;
  int lineSize = _mprototype[shapeName.toStdString()].size() - 1;
  AttributesTableWidget->setRowCount(size);
  for (int i = 0; i < size; ++i)
  {
    QTableWidgetItem *item = AttributesTableWidget->itemAt(i, 1);
    QString curArg = item->text();

    newLine += curArg;
  }
  ShapesListWidget->insertItem(0, newLine);
}
