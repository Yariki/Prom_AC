


#if !defined(_BISMODEL_H)
#define _BISMODEL_H

#include "BaseModelObject.h"
#include "UISettings.h"

class BISModel : public BaseModelObject {
public:
	BISModel();
	virtual ~BISModel();
	void checkSignals() override;
	vector<UISettings>* getUISettings() override;
	void setUISettings(vector<UISettings> settings) override;
};

#endif  //_BISMODEL_H
