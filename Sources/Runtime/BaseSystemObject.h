


#if !defined(_BASESYSTEMOBJECT_H)
#define _BASESYSTEMOBJECT_H
#include <vector>
#include <QWidget>
#include <QThread>
#include "BaseModelObject.h"
#include "SystemObserver.h"
#include "IObject.h"
#include "SystemState.h"
#include "ModelIdentity.h"
#include "IOName.h"
#include "BaseSystemConfigurationReader.h"
#include "IOModelSettings.h"
#include "WidgetUIObject.h"
#include "ConnectionUIObject.h"
#include "arduinocommandhandler.h"
#include "ISendDataCallback.h"


using namespace std;

class BaseSystemObject :public SystemObserver, public ISystemObject {
public:
	BaseSystemObject(QWidget* parent);
	virtual ~BaseSystemObject();

	bool loadSystem();
	void getState(SystemState ret);
	std::vector<BaseModelObject*>* getListObjects() ;
	std::vector<WidgetUIObject*>* getUIObjects() ;
	std::vector<ConnectionUIObject*>* getConnectionUIObjects();
	void setSystemState(SystemState input);
	void lockSystem();
	void unlockSystem();
	void runSystem();
	void stopSystem();
	void addActiveModel(BaseModelObject* model);
	void removeActiveModel(BaseModelObject* model);
	std::vector<BaseModelObject*>* getListActiveModels();
	void Update(IObject* input);
	void Start();
	void Stop();
	void EmergencyStop();
	IOName getName();
	int getPriority();
	void setPriority(int priority);
	void readData(QByteArray& res);
	void setSendDataCallback(ISendDataCallback* sender);

protected:
	virtual void prepareForManualConfigurartion();
	virtual void createModels();
	virtual bool readConfiguration();
	virtual std::vector<IOModelSettings>* createInputModels();
	virtual bool linkModels(vector<IOModelSettings>* listInputs);

private:
	IOName _name;
	int _priority;
	QString _filenameSystem;
	SystemState _state;
	std::vector<BaseModelObject*> _listModels;
	std::vector<WidgetUIObject*> _listUIModels;
	std::vector<ConnectionUIObject*> _listConUIObjects;
	std::vector<IIOModel*> _listInputs;
	std::vector<BaseModelObject*> _listActiveModels;
	QWidget* _parent;
	ISendDataCallback* _senderData;
	
	ArduinoCommandHandler* _arduinoCommandHandler;

	BaseSystemConfigurationReader* cfngReader;

private :
	BaseModelObject* findModel(QString& name);
	bool IsModelInActiveList(BaseModelObject* model);
	void onStopedObject(QByteArray& response);
	void onStartedObject(QByteArray& response);
	void onCommonErrorResult(QByteArray& response);
	void onErrorResult(QByteArray& response);
	void onOkResult(QByteArray& response);
	void onReadyResult(QByteArray& response);
	void onAlertResult(QByteArray& response);
	void sendDataToArduino(QByteArray& data);
};

#endif  //_BASESYSTEMOBJECT_H
