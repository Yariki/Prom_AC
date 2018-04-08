#ifndef _PLAINTEXTAPPENDER_H_
#define _PLAINTEXTAPPENDER_H_

// Logger
#include "CuteLogger_global.h"
#include <AbstractStringAppender.h>

#include <qplaintextedit.h>

class CUTELOGGERSHARED_EXPORT PlainTextAppender : public AbstractStringAppender{
public:
	PlainTextAppender(QPlainTextEdit * textAppender);
	virtual ~PlainTextAppender();

private:
	QPlainTextEdit* _textPlainEdit;

protected:
	virtual void append(const QDateTime& timeStamp, Logger::LogLevel logLevel, const char* file, int line,
		const char* function, const QString& message);

private:
	mutable QMutex _logEditPlainMutex;
};


#endif //_PLAINTEXTAPPENDER_H_