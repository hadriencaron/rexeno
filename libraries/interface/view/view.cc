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
View::Refresh()
{
  connect(OKButton, SIGNAL(clicked()), (View*) this, SLOT(Hello()));

  this->TrialNameLabel->setText(_m->trialName().c_str());
  vector<string>::iterator it;
  vector<string>& shapes = _m->availableShapes();

  for (it = shapes.begin(); it != shapes.end(); ++it)
    this->ShapesComboBox->addItem("test");

}

void
View::Hello()
{
  cout << "hello" << endl;
}
