


#if !defined(_GRAINDRYERMODEL_H)
#define _GRAINDRYERMODEL_H

#include "BaseModelObject.h"
#include "UISettings.h"

class GrainDryerModel : public BaseModelObject {
public:
	float _minTemperature;
	float _maxTemperature;
	void temperatureControl();
	void drySimulation();
	void checkSignals() override;
	vector<UISettings>* getUISettings() override;
	void setUISettings(vector<UISettings> settings) override;
	
};

#endif  //_GRAINDRYERMODEL_H
