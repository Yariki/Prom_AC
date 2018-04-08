#ifndef _BASE_MODEL_FACTORY_H_
#define _BASE_MODEL_FACTORY_H_
#include "stdafx.h"
#include "BaseModelObject.h"

class BaseModelFactory
{
public:
	virtual BaseModelObject * createModel(QString type) = 0;
};



#endif // _BASE_MODEL_FACTORY_H_