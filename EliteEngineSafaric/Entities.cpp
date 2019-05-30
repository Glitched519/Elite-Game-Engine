#include "Entities.h"

std::vector<Entities>Entities::_entityList;

Entities::Entities() :_componentMask(0)
{
}
Entities::Entities(size_t ID) : _ID(ID), _componentMask(0) {

}

size_t Entities::getID() {
	return _ID;
}

std::vector<Entities>&Entities::getEntityList() {
	return Entities::_entityList;
}
Entities&Entities::create() {
	Entities E(_entityList.size());
	_entityList.push_back(E);
	return _entityList.back();
}
uint32_t Entities::getComponentMask() {
	return _componentMask;
}

//Entities::~Entities()
//{
//}
