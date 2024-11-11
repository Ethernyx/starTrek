#include "Cle.h"

Cle::Cle(const string name, const int id) : _name(name), _id(id)
{
}

Cle::~Cle()
{
}

int Cle::getId() const {
    return this->_id;
}

string  Cle::getName() const {
    return this->_name;
}

bool    Cle::operator==(Cle &cle) {
    if (cle.getName() != "" && this->_name == cle.getName()) return true;
    if (cle.getId() != 0 && this->_id == cle.getId()) return true;
    return false;
}