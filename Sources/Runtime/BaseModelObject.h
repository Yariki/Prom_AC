


#if !defined(_BASEMODELOBJECT_H)
#define _BASEMODELOBJECT_H
#include <list>

using namespace std;

#include "ISystemObject.h"
#include "IObserver.h"
#include "IOName.h"
#include "IIOModel.h"
#include "IConfigurationReader.h"
#include "ISignal.h"
#include "ObjectObserver.h"
#include "SystemNotificator.h"
#include "UINotificator.h"
#include "StateObject.h"
#include "TypeObject.h"
#include "SystemObserver.h"
#include "InputOutputModel.h"
#include "UISettings.h"

class BaseModelObject : public ObjectObserver, public SystemNotificator, public ISystemObject, public UINotificator,  public IConfigurationReader 
{
public:

	BaseModelObject();
	virtual ~BaseModelObject();

	virtual void Start();
	virtual void Stop();
	virtual void EmergencyStop();
	virtual StateObject getState();
	virtual TypeObject getType();
	virtual void addInput(InputOutputModel* input);
	virtual void removeInput(InputOutputModel* input);
	virtual int getDeviceId();
	virtual vector<IOName> getInputsListName() const;
	virtual vector<IOName> getOutputListName() const;
	virtual void setActiveInput(IOName& inputName);
	virtual void setActiveOutput(IOName& active);
	virtual IOName getActiveInput() const;
	virtual IOName getActiveOutput() const;
	virtual void checkSignals() = 0;
	virtual vector<UISettings>* getUISettings() = 0;
	virtual void setUISettings(vector<UISettings> settings) = 0;
	virtual void Update(IObject* input);
	virtual void Notify(IObject* input);
	virtual void Attach(IObserver* observer);
	virtual void Deattach(IObserver* observer);
	virtual IOName getName();
	virtual int getPriority();
	virtual void setPriority(int priority);
	virtual void readConfiguration(QDomElement* xmlEl);
	virtual bool IsActive();
	virtual void setActive(bool state);
protected:
	bool _isRunning;
	StateObject _state;
	int _priority;
	TypeObject _type;
	vector<InputOutputModel*> _listConnections;
	vector<ISignal*> _listSignals;
	vector<IObserver*> _observers;
	int _id;
	IOName _name;
	bool _isActive;
};

#endif  //_BASEMODELOBJECT_H
