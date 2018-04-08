
#include <QtCore/QCoreApplication>
#include "../SvgParser/svgparser.h"
#include "../SvgParser/SvgObjectContainer.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	SvgParser parser("./sample.svg");
	if(parser.Parse())
	{
		printf("Parse done.");
		SvgObjectContainer* cont = parser.getSvgObjectContainer();
		for(auto i = 0; i < cont->getObjectsCount();i++)
		{
			BaseSvgObject* obj = cont->getObject(i);
			if(obj != NULL)
			{
				printf("Object: %s \n", obj->toString().toLatin1().data());
			}	
		}
	}
	else
	{
		printf("Error parse.");
	}
	return a.exec();
}
