


#if !defined(_INPUTOUTPUTMODEL_H)
#define _INPUTOUTPUTMODEL_H

#include "ObjectNotificator.h"
#include "IObject.h"
#include "IIOModel.h"
#include "IOType.h"
#include "IOName.h"
#include "ObjectObserver.h"

class InputOutputModel : public ObjectNotificator, public IObject, public IIOModel {
public:
	InputOutputModel(BaseModelObject* inputObject, BaseModelObject* outputObject);
	virtual ~InputOutputModel();
	virtual BaseModelObject* getSourceObject();
	virtual BaseModelObject* getDestinationObject();
	virtual int getPriority();
	virtual void setPriority(int priority);
	void Notify(IObject* input);
	void Attach(IObserver* observer);
	void Deattach(IObserver* observer);
	virtual IOType getType();

	virtual IOName getName();
	void setName(IOName& name);
	void Start();
	void Stop();
	void EmergencyStop();
	virtual bool IsActive() 
	{
		return _isActive;
	}

	virtual void SetActive(bool active);
protected:
	BaseModelObject* _sourceObject;
	BaseModelObject* _destinationObject;
	int _priority;
	bool _isActive;
	IOType _ioType;
	IOName _name;
	int _priorityInputObject;
};

#endif  //_INPUTOUTPUTMODEL_H
