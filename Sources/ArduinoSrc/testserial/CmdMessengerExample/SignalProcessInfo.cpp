#include "SignalProcessInfo.h"


SignalProcessInfo::SignalProcessInfo(void){
}


SignalProcessInfo::~SignalProcessInfo(void){
}

void SignalProcessInfo::setInfo( uint8_t id,uint8_t port ){
	_id = id;
	_port = port;
	pinMode(port,INPUT);
}

uint8_t SignalProcessInfo::checkSignal(){
	int val = digitalRead(_port);
	_value = val;
	return val;
}

uint8_t& SignalProcessInfo::getValue(){
	return _value;
}

String SignalProcessInfo::getSignalValue(){
	String temp = String(_id);
	temp = temp + ":";
	temp = temp + _value;
	return temp;
}
