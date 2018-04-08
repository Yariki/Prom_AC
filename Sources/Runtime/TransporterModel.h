


#if !defined(_TRANSPORTERMODEL_H)
#define _TRANSPORTERMODEL_H

#include "BaseModelObject.h"
#include "UISettings.h"

class TransporterModel : public BaseModelObject {
public:
	void checkSignals() override;
	vector<UISettings>* getUISettings() override;
	void setUISettings(vector<UISettings> settings) override;
	
};

#endif  //_TRANSPORTERMODEL_H
