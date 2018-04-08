


#if !defined(_WIDGETUIOBJECT_H)
#define _WIDGETUIOBJECT_H

#include "IObserver.h"
#include "baseuiwidget.h"
#include "BaseModelObject.h"
#include "IConfigurationReader.h"

class BaseSvgObject;




class WidgetUIObject : public BaseUIWidget,public IObserver, public IConfigurationReader{
public:
	WidgetUIObject(QWidget* parent);
	WidgetUIObject(QWidget* parent,BaseModelObject* modelObject);
	virtual ~WidgetUIObject();

	void Update(IObject* input) override;
	void render() override;
	void renderTemplate(QPainter* canvas) override;
	void readConfiguration(QDomElement* input) override;
	void prepareForRendering() override;
	BaseModelObject* getModel() const;

protected:
	void renderIndicators(QPainter* canvas);

protected:
	BaseModelObject* _baseModelObject;
	vector<BaseSvgObject*> _listRenderObjects;
	map<StateObject,bool> _mapStates;

private:
	void init();
};

#endif  //_WIDGETUIOBJECT_H
