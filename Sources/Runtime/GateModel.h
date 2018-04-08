


#if !defined(_GATEMODEL_H)
#define _GATEMODEL_H

#include "BaseModelObject.h"
#include "UISettings.h"

class GateModel : public BaseModelObject {
public:
	void checkSignals() override;
	vector<UISettings>* getUISettings() override;
	void setUISettings(vector<UISettings> settings) override;
	
};

#endif  //_GATEMODEL_H
