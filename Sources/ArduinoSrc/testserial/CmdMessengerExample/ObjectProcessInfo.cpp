#include "ObjectProcessInfo.h"


ObjectProcessInfo::ObjectProcessInfo(void){
	_internalMap = new HashMap<uint8_t,SignalProcessInfo*>(_internalRawArray,MAX_SIGNAL_COUNT);
	_counter = 0;
	_indicator = new IndicatorProcessObject();
}


ObjectProcessInfo::~ObjectProcessInfo(void){
	if(_internalMap != NULL){
		delete _internalMap;
		_internalMap = NULL;
	}
	if(_indicator != NULL)
	{
		delete _indicator;
	}
}

void ObjectProcessInfo::setInfo( uint8_t id, uint8_t initWorking, uint8_t portIndicator ){
	_id = id;
	_isWorking = initWorking;
	_indicator->setPort(portIndicator);
	_indicator->setIndicator(false);
}

void ObjectProcessInfo::addSignal(SignalProcessInfo* signal ){
	if(_counter == MAX_SIGNAL_COUNT - 1){
		return;
	}
	_internalMap->set(_counter,signal->getId(),signal);
	_counter++;
}

String ObjectProcessInfo::checkSignals(){
	boolean res = 1;
	String strRes;
	for(uint8_t i = 0; i < MAX_SIGNAL_COUNT;i++){
		SignalProcessInfo* signal = _internalRawArray[i].getValue();
		if(signal == 0)
			continue;
		res = signal->checkSignal();
		if(res > 0 ){
			if(strRes.length() == 0){
				strRes = strRes + _id; 
				strRes = strRes  + "(";
			}
			strRes = strRes + signal->getSignalValue();
			strRes = strRes + "/";
		}
	}
	if(strRes.length() > 0){
		strRes = strRes + ")";
	}
	return strRes;
}

boolean ObjectProcessInfo::isWorking(){
	return _isWorking;
}

void ObjectProcessInfo::indicate( bool valueIndicator )
{
	if(_indicator == NULL)
		return;
	_indicator->setIndicator(valueIndicator);
}

void ObjectProcessInfo::setWorking( uint8_t val )
{
	_isWorking = val;
	indicate((boolean)val);
}




