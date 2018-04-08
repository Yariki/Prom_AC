


#if !defined(_IIOMODEL_H)
#define _IIOMODEL_H

#include "IOType.h"
#include "IOName.h"

class BaseModelObject;

__interface IIOModel {
public:
	virtual BaseModelObject* getSourceObject() = 0;
	virtual BaseModelObject* getDestinationObject() = 0;
	virtual IOType getType() = 0;
	virtual bool IsActive() = 0;
	virtual void SetActive(bool value) = 0;
};

#endif  //_IIOMODEL_H
