

#include "stdafx.h"
#include "IOName.h"

IOName::IOName(){

}

IOName::IOName(QString name, QUuid uid)
{
	_name = name;
	_uid = uid;
}

IOName::~IOName()
{

}

QString IOName::getName() {
	return _name;
}

QUuid IOName::getId() {
	return _uid;
}

bool IOName::IsEmpty()
{
	return _name.isEmpty()  && _uid.isNull();
}

