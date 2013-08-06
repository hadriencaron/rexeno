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
  map<string, vector<string> > prototype = _m->shapePrototypes;
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
  connect(ClearButton, SIGNAL(clicked()), (View*) this, SLOT(Clear()));
  connect(DeleteShapeButton, SIGNAL(clicked()), (View*) this, SLOT(DeleteShape()));
  connect(UpButton, SIGNAL(clicked()), (View*) this, SLOT(Up()));
  connect(BottomButton, SIGNAL(clicked()), (View*) this, SLOT(Down()));
  connect(EditShapeButton, SIGNAL(clicked()), (View*) this, SLOT(Edit()));

  this->TrialNameLabel->setText(_m->trialName().c_str());
  vector<string>::const_iterator it;
  const vector<string>& shapes = _m->availableShapes();

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
  vector<string> newShape;
  QString shapeName = ShapesComboBox->currentText();
  QString newLine = shapeName;
  map<string, vector<string> > prototype = _m->shapePrototypes;
  int size = prototype[shapeName.toStdString()].size() - 1;
  AttributesTableWidget->setRowCount(size);
  newShape.push_back(shapeName.toStdString());
  for (int i = 0; i < size; ++i)
  {
    QTableWidgetItem *item = AttributesTableWidget->item(i, 1);
    QString curArg = item->text();
    newShape.push_back(curArg.toStdString());
  }
  _m->protocole.push_back(newShape);
  DrawProtocole();
}

void
View::DrawProtocole()
{
  //QString shapeName = ShapesComboBox->currentText();
  QString shapeName;
  ShapesListWidget->clear();
  vector<vector<string> >::iterator it;
  int lineNumber = 0;
  for (it = _m->protocole.begin(); it != _m->protocole.end(); ++it, ++lineNumber)
  {
    vector<string>& curVect = *it;
    vector<string>::iterator it2;
    QString newLine = shapeName + " ";
    for (it2 = curVect.begin(); it2 != curVect.end(); ++it2)
      newLine += (*it2 + " ").c_str();
    ShapesListWidget->insertItem(lineNumber, newLine);
  }
}

void
View::Clear()
{
  _m->protocole.clear();
  DrawProtocole();
}

void
View::DeleteShape()
{
  int curRow = ShapesListWidget->currentRow();
  _m->protocole.erase(_m->protocole.begin() + curRow);
  DrawProtocole();
}


void
View::Up()
{
  int curRow = ShapesListWidget->currentRow();
  if ((curRow) && (curRow != -1))
  {
    vector<string> tmp;
    tmp = _m->protocole[curRow];
    _m->protocole[curRow] = _m->protocole[curRow - 1];
    _m->protocole[curRow - 1] = tmp;
    DrawProtocole();
  }
}

void
View::Down()
{
  int curRow = ShapesListWidget->currentRow();
  int size = _m->protocole.size() - 1;;
  if ((curRow != size) && (curRow != -1))
  {
    vector<string> tmp;
    tmp = _m->protocole[curRow];
    _m->protocole[curRow] = _m->protocole[curRow + 1];
    _m->protocole[curRow + 1] = tmp;
    DrawProtocole();
  }
}

void
View::Edit()
{
  AttributesTableWidget->clear();

  int curRow = ShapesListWidget->currentRow();
  vector<string> curShape = _m->protocole[curRow];
  QString shapeName(curShape[0].c_str());
  cout << curShape[0] << endl;
  map<string, vector<string> > prototype = _m->shapePrototypes;
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
    }
    else
    {
      QTableWidgetItem *item = new QTableWidgetItem(tr(curString.c_str()).arg(pow(1, 0)));
      AttributesTableWidget->setItem(i, 0, item);
    }
  }

  vector<string>::iterator it;
  int i = 0;
  for (it = curShape.begin() + 1; it != curShape.end(); ++it, ++i)
  {
    string shapeValue = *it;
    QTableWidgetItem *item2 = new QTableWidgetItem(tr(shapeValue.c_str()).arg(pow(1, 0)));
    AttributesTableWidget->setItem(i, 1, item2);
  }
}

