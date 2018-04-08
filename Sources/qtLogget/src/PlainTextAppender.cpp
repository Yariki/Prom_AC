
#include "PlainTextAppender.h"

PlainTextAppender::PlainTextAppender( QPlainTextEdit * textAppender )
{
	_textPlainEdit = textAppender;
}

PlainTextAppender::~PlainTextAppender()
{
	_textPlainEdit = NULL;
}

void PlainTextAppender::append( const QDateTime& timeStamp, Logger::LogLevel logLevel, const char* file, int line, const char* function, const QString& message )
{
	QMutexLocker locker(&_logEditPlainMutex);
	_textPlainEdit->appendPlainText(formattedString(timeStamp, logLevel, file, line, function, message));
}
