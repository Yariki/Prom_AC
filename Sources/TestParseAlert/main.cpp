
#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>

int main(int argc, char *argv[])
{
	QString input = "2,536(2:3/3:5/4:6)|999(2:1/3:1/4:1);";

	// TODO: for another command should cut last symbol in last token, because it will be ';'

	QStringList tokens = input.split(",");
	if(tokens.count() > 0)
	{
		printf("Command: %s\n",tokens[0].toLatin1().data());
		for(int i = 1; i < tokens.count();i++)
		{
			QString current = tokens[i];
			if(i == tokens.count() - 1)
			{
				current = current.remove(";");
			}
			QString strIdObject = current.left(current.indexOf("("));
			printf("\tId Object: %s\n",strIdObject.toLatin1().data());
			int index1 = current.indexOf("(") + 1;
			int lenght = current.indexOf(")") - index1;
			QString strData = current.mid(index1,lenght);
			QStringList tokSignals = strData.split("/");
			if(!tokSignals.count())
				continue;
			for (int j = 0; j < tokSignals.count();j++)
			{
				QString strSignal = tokSignals[j];
				if(!strSignal.length())
					continue;
				QStringList	toks = strSignal.split(":");
				if(!toks.count())
					continue;
				printf("\t\tID Signal: %s\n",toks[0].toLatin1().data());	
				printf("\t\tValue Signal: %s\n",toks[1].toLatin1().data());	
			}

		}
	}

	/*QString temp = "1,4";

	if(temp.indexOf(";") == -1)
	{
		printf("NO tokens\n");
	}
	else
	{
		QStringList tokens = temp.split(";");
		printf("%s\n",temp.toLatin1().data());
		if(tokens.count() > 0)
		{
			for(auto i = 0; i < tokens.count(); i++)
			{
				printf("\tToken: %s\n",tokens[i].toLatin1().data());	
			}
		}
	}*/
	


	system("pause");
	return 0;
}
