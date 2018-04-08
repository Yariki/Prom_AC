


#if !defined(_IUIOBJECT_H)
#define _IUIOBJECT_H
#include <vector>

#include "QDomElement"
#include "UIObserver.h"
#include "baseuiwidget.h"

using namespace std;

class IUIObject : public UIObserver, public BaseUIWidget {
public:
	
	IUIObject(QWidget* parent) : BaseUIWidget(parent){}
	virtual ~IUIObject(){}
	virtual void render() = 0;
	virtual void prepareForRendering() = 0;
protected:
	QString _templateName;
	QString _activeInput;
	QString _activeOutput;
	vector<QString> _listInputs;
	vector<QString> _listOutputs;
	int _x;
	int _y;
	int _width;
	int _height;
};

#endif  //_IUIOBJECT_H
