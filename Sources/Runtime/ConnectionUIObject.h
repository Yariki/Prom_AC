///////////////////////////////////////////////////////////
//  ConnectionUIObject.h
//  Implementation of the Class ConnectionUIObject
//  Created on:      07-Jul-2013 7:21:11 PM
//  Original author: Yariki
///////////////////////////////////////////////////////////

#if !defined(EA_E16AA9F8_276C_49a0_AEFE_690DB1797933__INCLUDED_)
#define EA_E16AA9F8_276C_49a0_AEFE_690DB1797933__INCLUDED_

#include "QDomElement"
#include "BaseUIWidget.h"
#include "IConfigurationReader.h"
#include "../SvgParser/BaseSvgObject.h"

class ConnectionUIObject : public BaseUIWidget, public IConfigurationReader
{

public:
	ConnectionUIObject(QWidget* parent);
	virtual ~ConnectionUIObject();

	void prepareForRendering() override;
	void readConfiguration(QDomElement* input) override;
	void render() override;
	void renderTemplate(QPainter* canvas) override;

private:
	vector<BaseSvgObject*> _listRenderObjects;
	
protected:
	void paintEvent(QPaintEvent* args);

};
#endif // !defined(EA_E16AA9F8_276C_49a0_AEFE_690DB1797933__INCLUDED_)
