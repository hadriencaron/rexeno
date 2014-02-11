#include "rectangle.hh"
#include <boost/lexical_cast.hpp>

using namespace boost;

Rectangle3d::Rectangle3d(const ShapeInfo& si,
                     VariableManager& vm,
                     Trial* father)
{
  assert(si.attributes.size() == 14);
  assert(!father);
  _name = si.attributes[0];
  //vm.addVariable(_id = new Variable(2));
  //std::cout << id() << endl;
  vm.addVariable(_x = new Variable(si.attributes[1]));
  vm.addVariable(_y = new Variable(si.attributes[2]));
  vm.addVariable(_z = new Variable(si.attributes[3]));
  vm.addVariable(_frameStart = new Variable(si.attributes[4]));
  vm.addVariable(_frameEnd = new Variable(si.attributes[5]));
  vm.addVariable(_R = new Variable(si.attributes[6]));
  vm.addVariable(_G = new Variable(si.attributes[7]));
  vm.addVariable(_B = new Variable(si.attributes[8]));
  vm.addVariable(_width = new Variable(si.attributes[9]));
  vm.addVariable(_height = new Variable(si.attributes[10]));
  vm.addVariable(_repeat = new Variable(si.attributes[11]));
  vm.addVariable(_velo = new Variable(si.attributes[12]));
  vm.addVariable(_dir = new Variable(si.attributes[13]));
  _ttl = lexical_cast<int>(si.attributes[10]);

  _father = father;
}

void
Rectangle3d::React2input(Status& s,
                       datas& ds,
                       int frameId,
                       ms displayTime)
{
  Shape::React2input(s, ds, frameId, displayTime);
}

Rectangle3d::~Rectangle3d()
{

}
