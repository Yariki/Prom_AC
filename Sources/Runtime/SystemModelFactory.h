#ifndef _SYSTEMMODElFACTORY_H_ 
#define _SYSTEMMODElFACTORY_H_

#include "basemodelfactory.h"
#include "BaseModelObject.h"

class SystemModelFactory :
	public BaseModelFactory
{
public:
	SystemModelFactory(void);
	virtual ~SystemModelFactory(void);

	virtual BaseModelObject * createModel( QString type );

};

#endif //_SYSTEMMODElFACTORY_H_