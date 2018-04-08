
#if !defined(_BASESTRINGCOMMAND_H_)
#define _BASESTRINGCOMMAND_H_

#include "inputcommand.h"
#include <QStringList>


class BaseStringCommand :
	public InputCommand<QString>
{
public:
	BaseStringCommand(void);
	virtual ~BaseStringCommand(void);

	virtual QString getResult();
	virtual bool parse();

};

#endif // _BASESTRINGCOMMAND_H_