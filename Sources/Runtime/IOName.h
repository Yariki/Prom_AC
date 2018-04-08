


#if !defined(_IONAME_H)
#define _IONAME_H


class IOName 
{
public:
	IOName();
	IOName(QString name, QUuid uid);
	~IOName();
	QString getName();
	QUuid getId();
	bool IsEmpty();
protected:
	QUuid _uid;
	QString _name;
};

#endif  //_IONAME_H
