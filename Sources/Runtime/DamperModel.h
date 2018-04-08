


#if !defined(_DAMPERMODEL_H)
#define _DAMPERMODEL_H

#include "BaseModelObject.h"
#include "UISettings.h"

class DamperModel : public BaseModelObject {
public:
	void checkSignals() override;
	vector<UISettings>* getUISettings() override;
	void setUISettings(vector<UISettings> settings) override;
	
};

#endif  //_DAMPERMODEL_H
