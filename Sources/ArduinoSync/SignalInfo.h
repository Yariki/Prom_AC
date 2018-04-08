///////////////////////////////////////////////////////////
//  SignalInfo.h
//  Implementation of the Class SignalInfo
//  Created on:      31-Jul-2013 10:40:54 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_AA3D0FAF_AEE4_4343_9C64_05097769B487__INCLUDED_)
#define EA_AA3D0FAF_AEE4_4343_9C64_05097769B487__INCLUDED_

class SignalInfo
{

public:
	SignalInfo(int* id, int* val);
	virtual ~SignalInfo();

	int getId();
	int getValue();

protected:
	int _id;
	int _value;

};
#endif // !defined(EA_AA3D0FAF_AEE4_4343_9C64_05097769B487__INCLUDED_)
