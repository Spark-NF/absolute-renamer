#include "scripttools.h"
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QFile>


ScriptTools::ScriptTools()
{
}

QString ScriptTools::loadPage(QString surl)
{
	QUrl url(surl);

	QNetworkAccessManager manager;
	QNetworkRequest request;
	request.setUrl(url);
	request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
	QNetworkReply *reply = manager.get(request);

	QEventLoop loop;
	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	QUrl redir = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
	if (!redir.isEmpty())
		return loadPage(url.resolved(redir).toString());

	return reply->readAll();
}

QString ScriptTools::loadFile(QString path)
{
	QFile file(path);
	if (!file.exists())
		return "";

	file.open(QFile::ReadOnly);
	QString ret = file.readAll();
	file.close();

	return ret;
}

void ScriptTools::saveFile(QString path, QString contents)
{
	QFile file(path);
	file.open(QFile::WriteOnly | QFile::Truncate);
	file.write(contents.toUtf8());
	file.close();
}
