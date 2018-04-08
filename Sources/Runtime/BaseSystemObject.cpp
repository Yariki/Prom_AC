

#include "stdafx.h"
#include "BaseSystemObject.h"
#include "SystemState.h"
#include "SystemConfigurationReader.h"
#include "SystemModelFactory.h"
#include <algorithm>
#include "InputOutputModel.h"
#include "ConnectionUIObject.h"

using std::vector;

#define PROJECT_FILE_NAME "project_model.xml"

bool sortBaseModelByPriority(const BaseModelObject* model1, const BaseModelObject* model2)
{
	return ((BaseModelObject*)model1)->getPriority() < ((BaseModelObject*)model2)->getPriority();
}


BaseSystemObject::BaseSystemObject(QWidget* parent)
{
	_filenameSystem = QString(PROJECT_FILE_NAME);
	_parent = parent;
	_arduinoCommandHandler = new ArduinoCommandHandler();
}

BaseSystemObject::~BaseSystemObject()
{

}

bool BaseSystemObject::loadSystem() 
{
	
	if(_filenameSystem.isEmpty())
	{
		LOG_FATAL() << "_filenameSystem is empty";
		return false;
	}
	cfngReader = new SystemConfigurationReader(_filenameSystem);
	if(!cfngReader->Parse())
	{
		LOG_ERROR() << "Can't parse file project";
		return false;
	}
	createModels();
	auto listIO = createInputModels();
	return linkModels(listIO);
}

void BaseSystemObject::createModels()
{
	auto listTypes = cfngReader->getTypes();
	auto listModels = cfngReader->getModels();
	SystemModelFactory* factory = new SystemModelFactory();

	for(int i = 0;i < listModels->size(); i++)
	{
		QDomElement el = listModels->at(i);
		BaseModelObject* model = factory->createModel(el.attributeNode("type").value());
		if(model == nullptr)
			continue;
		if(el.elementsByTagName("core").count() > 0)
		{
			QDomElement core = el.elementsByTagName("core").at(0).toElement();
			model->readConfiguration(&core);
			_listModels.push_back(model);
			if(el.elementsByTagName("ui").count() > 0)
			{
				QDomElement ui = el.elementsByTagName("ui").at(0).toElement();
				WidgetUIObject* widget = new WidgetUIObject(_parent,model);
				widget->readConfiguration(&ui);
				_listUIModels.push_back(widget);
			}
		}
	}
}

vector<IOModelSettings>* BaseSystemObject::createInputModels()
{
	auto listIO = cfngReader->getConnections();
	vector<IOModelSettings>* res = new vector<IOModelSettings>;
	for(int i = 0; i < listIO->size();i++)
	{
		QDomElement el = listIO->at(i);
		IOModelSettings ioModel;
		if(el.elementsByTagName("core").count() > 0)
		{
			QDomElement core = el.elementsByTagName("core").at(0).toElement();
			ioModel.readConfiguration(&core);
			res->push_back(ioModel);
			if(el.elementsByTagName("ui").count() > 0)
			{
				QDomElement ui = el.elementsByTagName("ui").at(0).toElement();
				ConnectionUIObject* w = new ConnectionUIObject(_parent);
				w->readConfiguration(&ui);
				_listConUIObjects.push_back(w);
			}
		}
	}
	return res;
}

bool BaseSystemObject::readConfiguration() 
{
	return false;
}

bool BaseSystemObject::linkModels(vector<IOModelSettings>* listInputs) 
{
	if(listInputs == nullptr)
	{
		LOG_ERROR() << "Inputs are not found.";
		return false;
	}

	for(int i =0;i < listInputs->size();i++)
	{
		IOModelSettings ioModelSet = listInputs->at(i);
		QString source = ioModelSet.getSourceName();
		QString destination = ioModelSet.getDestinationName();
		BaseModelObject* sourceModel =  dynamic_cast<BaseModelObject*>(*find_if(_listModels.begin(),_listModels.end(),[&source](BaseModelObject* model) -> bool {
			return model->getName().getName() == source;
		}));// findModel(source);
		BaseModelObject* destinationModel = findModel(destination);
		if(sourceModel != nullptr && destinationModel  != nullptr)
		{
			InputOutputModel* connection = new InputOutputModel(sourceModel,destinationModel);
			connection->setName(ioModelSet.getName());
			connection->setPriority(ioModelSet.getPriority());
			sourceModel->addInput(connection);
			destinationModel->addInput(connection);
			_listInputs.push_back(connection);
		}
	}
	delete listInputs;
	return true;
}

BaseModelObject* BaseSystemObject::findModel(QString& name)
{
	if(name.isEmpty())
	{
		return NULL;
	}
	BaseModelObject* res = NULL;
	for(int i = 0;i < _listModels.size();i++)
		if(_listModels.at(i)->getName().getName() == name)
		{
			res = _listModels.at(i);
			break;
		}
	return res;
}


void BaseSystemObject::getState(SystemState ret) 
{

}

vector<BaseModelObject*>* BaseSystemObject::getListObjects()
{
	return &_listModels;
}

void BaseSystemObject::setSystemState(SystemState input) 
{


}

void BaseSystemObject::lockSystem() {

}

void BaseSystemObject::unlockSystem() {

}

void BaseSystemObject::runSystem() {

}

void BaseSystemObject::stopSystem() {

}

void BaseSystemObject::addActiveModel(BaseModelObject* model) {
	if(model == nullptr)
	{
		LOG_ERROR("model is null");
		return;
	}
	if(!IsModelInActiveList(model))
	{
		_listActiveModels.push_back(model);
	}	
}

void BaseSystemObject::removeActiveModel(BaseModelObject* model) {

	if(model == nullptr)
	{
		LOG_ERROR("model is null");
		return;
	}
	if(IsModelInActiveList(model))
	{
		int i = -1;
		for(auto iter = _listActiveModels.begin();  iter != _listActiveModels.end();iter++)
		{
			i++;
			if(*iter == model)
				break;
		}
		_listActiveModels.erase(_listActiveModels.begin() + i);
	}
}

vector<BaseModelObject*>* BaseSystemObject::getListActiveModels() 
{
	return &_listActiveModels;
}

void BaseSystemObject::Update(IObject* input) {

}

void BaseSystemObject::Start() {
	// todo  sort list and start all models
	// from low priority to high
	// 
	std::sort(_listActiveModels.begin(),_listActiveModels.end(),sortBaseModelByPriority);
	vector<int> startList;
	for(auto iter = _listActiveModels.rbegin();iter != _listActiveModels.rend();++iter)
	{
		startList.push_back((*iter)->getDeviceId());
	}
	if(startList.size() > 0)
	{
		QByteArray sendData = _arduinoCommandHandler->getStartCommand(&startList);
		LOG_INFO(QString(sendData));
		sendDataToArduino(sendData);
	}
	
}


void BaseSystemObject::Stop() {
	// todo  sort list and start all models
	// from low priority to high
	std::sort(_listActiveModels.begin(),_listActiveModels.end(),sortBaseModelByPriority);
	vector<int> stopList;
	for(auto iter = _listActiveModels.begin();iter != _listActiveModels.end();++iter)
	{
		stopList.push_back((*iter)->getDeviceId());
	}
	if(stopList.size() > 0)
	{
		QByteArray sendData = _arduinoCommandHandler->getStopCommand(&stopList);
		LOG_INFO(QString(sendData));
		sendDataToArduino(sendData);
	}
}

void BaseSystemObject::EmergencyStop() {
	
	std::sort(_listActiveModels.begin(),_listActiveModels.end(),sortBaseModelByPriority);
	for(auto iter = _listActiveModels.begin();iter != _listActiveModels.end();++iter)
	{
		(*iter)->EmergencyStop();
	}
}

IOName BaseSystemObject::getName() {
	return _name;
}

int BaseSystemObject::getPriority() {
	return _priority;
}

void BaseSystemObject::setPriority(int priority) {

}

void BaseSystemObject::prepareForManualConfigurartion() {

}

vector<WidgetUIObject*>* BaseSystemObject::getUIObjects()
{
	return  &_listUIModels;
}

vector<ConnectionUIObject*>* BaseSystemObject::getConnectionUIObjects()
{
	return &_listConUIObjects;
}

bool BaseSystemObject::IsModelInActiveList( BaseModelObject* model )
{
	if(_listActiveModels.size() == 0)
		return false;
	BaseModelObject* obj = nullptr;
	for(auto iter = _listActiveModels.begin(); iter != _listActiveModels.end();iter++)
		if( (obj = *iter) == model)
			break;
		else
			obj = nullptr;

	return obj != nullptr;
}

void BaseSystemObject::readData( QByteArray& res )
{
	LOG_INFO(QString(res));
	if(_arduinoCommandHandler->firstPreviewCommand(res))
	{
		if(_arduinoCommandHandler->getCommandType() == CTInput)
		{
			switch(_arduinoCommandHandler->getOperationType())
			{
			case OTStoped:
				onStopedObject(res);
				break;
			case OTStarted:
				onStartedObject(res);
				break;
			case OTAlert:
				onAlertResult(res);
				break;
			case OTCommonError:
				onCommonErrorResult(res);
				break;
			case OTError:
				onErrorResult(res);
				break;
			case OTOk:
				onOkResult(res);
				break;
			case OTArduinoReady:
				onReadyResult(res);
				break;
			}
		}

	}
}

void BaseSystemObject::onStopedObject(QByteArray& response)
{
	int id = _arduinoCommandHandler->getStopedObjectResult(response);
	for(auto iter = _listActiveModels.begin(); iter != _listActiveModels.end(); ++iter)
	{
		if((*iter)->getDeviceId() == id)
		{
			(*iter)->Stop();
		}
	}
}

void BaseSystemObject::onStartedObject( QByteArray& response )
{
	int id = _arduinoCommandHandler->getStartedObjectResult(response);
	for(auto iter = _listActiveModels.begin(); iter != _listActiveModels.end(); ++iter)
	{
		if((*iter)->getDeviceId() == id)
		{
			(*iter)->Start();
		}
	}

}

void BaseSystemObject::onCommonErrorResult( QByteArray& response )
{
	QString resp = _arduinoCommandHandler->getCommonErrorResult(response);
	LOG_INFO(resp);
}

void BaseSystemObject::onErrorResult( QByteArray& response )
{
	QString resp = _arduinoCommandHandler->getErrorResult(response);
	LOG_INFO(resp);
}

void BaseSystemObject::onOkResult( QByteArray& response )
{
	QString resp = _arduinoCommandHandler->getOkResult(response);
	LOG_INFO(resp);
}

void BaseSystemObject::onReadyResult( QByteArray& response )
{
	QString resp = _arduinoCommandHandler->getReadyResult(response);
	LOG_INFO(resp);
}

void BaseSystemObject::onAlertResult( QByteArray& response )
{
	vector<ObjectInfo*>* result = _arduinoCommandHandler->getAlertResult(response);
	if(result != nullptr)
	{
		for(auto it = result->begin(); it != result->end(); it++)
		{
			ObjectInfo* obj = static_cast<ObjectInfo*>(*it);
			
			vector<SignalInfo*>* listSignals = obj->getSignalsInfo();
			for(auto itSig = listSignals->begin(); itSig != listSignals->end(); itSig++)
			{
				SignalInfo* sig = static_cast<SignalInfo*>(*itSig);
			}
			delete (*it);
			*it = nullptr;
		}
		delete result;
		result = nullptr;
	}
}

void BaseSystemObject::sendDataToArduino( QByteArray& data )
{
	if(_senderData != nullptr)
	{
		_senderData->sendData(data);
	}
}

void BaseSystemObject::setSendDataCallback( ISendDataCallback* sender )
{
	_senderData = sender;
}







