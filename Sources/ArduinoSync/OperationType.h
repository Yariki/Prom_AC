///////////////////////////////////////////////////////////
//  OperationType.h
//  Implementation of the Class OperationType
//  Created on:      30-Jul-2013 12:57:47 AM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_08AC3A95_3846_4765_B35C_6159EB867735__INCLUDED_)
#define EA_08AC3A95_3846_4765_B35C_6159EB867735__INCLUDED_

enum OperationType
{
	OperationTypeUnknown = -1,
	OTCommonError = 0,
	OTOk = 1,
	OTArduinoReady = 2,
	OTError = 3,
	OTStart = 4,
	OTStop = 5,
	OTEmergencyStop = 6,
	OTStarted = 7,
	OTStoped = 8,
	OTAlert = 9
};
#endif // !defined(EA_08AC3A95_3846_4765_B35C_6159EB867735__INCLUDED_)
