


#if !defined(_BUNKERMODEL_H)
#define _BUNKERMODEL_H

#include "BaseModelObject.h"
#include "UISettings.h"

class BunkerModel : public BaseModelObject {
public:
	void checkSignals() override;
	vector<UISettings>* getUISettings() override;
	void setUISettings(vector<UISettings> settings) override;
};

#endif  //_BUNKERMODEL_H
