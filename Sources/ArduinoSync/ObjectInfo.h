///////////////////////////////////////////////////////////
//  ObjectInfo.h
//  Implementation of the Class ObjectInfo
//  Created on:      31-Jul-2013 10:40:52 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_3C0BBC8C_3C93_47d6_B187_D18D6943B242__INCLUDED_)
#define EA_3C0BBC8C_3C93_47d6_B187_D18D6943B242__INCLUDED_

#include <vector>
#include "SignalInfo.h"

using std::vector;

class ObjectInfo
{

public:
	ObjectInfo(int* id) {
		_id = *id; 
		_signalsCollection = new vector<SignalInfo*>;
	}
	virtual ~ObjectInfo();

	int getId();
	void setId(int& id);
	vector<SignalInfo*>* getSignalsInfo();
	void insertSignalInfo(SignalInfo* si);

protected:
	int _id;
	vector<SignalInfo*>* _signalsCollection;

};
#endif // !defined(EA_3C0BBC8C_3C93_47d6_B187_D18D6943B242__INCLUDED_)
