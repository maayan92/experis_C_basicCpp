#include <cstdio>
#include <cstring>
#include "memManager_t.h"

memManager_t::~memManager_t(){}

bool memManager_t::SetCurrentPosition(unsigned int _position)
{
	return (_position > m_actualSize) ? false : m_position = _position, true;
}



