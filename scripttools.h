#ifndef SCRIPTTOOLS_H
#define SCRIPTTOOLS_H

#include <QObject>
#include <QString>


class ScriptTools : public QObject
{
	Q_OBJECT

	public:
		ScriptTools();

	public slots:
		QString loadPage(QString url);
		QString loadFile(QString path);
		void saveFile(QString path, QString contents);
};

#endif // SCRIPTTOOLS_H
