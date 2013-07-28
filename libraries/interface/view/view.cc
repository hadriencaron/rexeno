#include "view.hh"

View::View(Model* m)
{
  _m = m;
}


void
View::Refresh()
{
  this->TrialNameLabel->setText(_m->trialName().c_str());

}
