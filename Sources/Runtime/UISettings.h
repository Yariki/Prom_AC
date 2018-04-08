
#if !defined(_UISETTINGS_H)
#define _UISETTINGS_H

#include "SettingsType.h"

class UISettings
{
public:
	UISettings();
	virtual ~UISettings(void);
	SettingsType getType() {return _type;} 
	const void* getValue() { return _value ;}

private:
	SettingsType _type;
	void*	_value;

};

#endif  //_UISETTINGS_H
