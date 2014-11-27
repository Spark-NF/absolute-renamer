#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QtScript>
#include "scripttools.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QStringList files = QDir("test").entryList(QDir::Files);
	for (QString file : files)
	{
		m_files.insert(file, "");
		ui->listBefore->addItem(file);
	}

	QStringList plugins = QDir("plugins").entryList(QStringList("*.js"), QDir::Files);
	for (QString plugin : plugins)
		ui->comboPlugin->addItem(plugin);
	ui->comboPlugin->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::rename()
{
	for (QString file : m_files.keys())
		QFile::rename("test/" + file, "test/" + m_files.value(file));

	updateFiles();
}

void MainWindow::updateFiles()
{
	m_files.clear();
	ui->listBefore->clear();

	QStringList files = QDir("test").entryList(QDir::Files);
	for (QString file : files)
	{
		m_files.insert(file, "");
		ui->listBefore->addItem(file);
	}

	updatePlugin();
}

void MainWindow::updatePlugin()
{
	ui->listAfter->clear();

	QFile f("plugins/" + ui->comboPlugin->currentText());
	f.open(QFile::ReadOnly);
	QString script = f.readAll();
	f.close();

	QScriptEngine engine;
	ScriptTools *tools = new ScriptTools;
	QScriptValue scriptTools = engine.newQObject(tools);
	engine.globalObject().setProperty("tools", scriptTools);
	engine.evaluate(script);

	int position = 0;
	for (QString file : m_files.keys())
	{
		int extPos = file.lastIndexOf('.');
		QString filename = file.left(extPos);
		QString ext = file.right(file.length() - extPos - 1);;
		QString result = engine.evaluate("rename('"+filename+"', '"+ext+"', '"+file+"', "+QString::number(position)+")").toString();

		m_files[file] = result;
		ui->listAfter->addItem(m_files.value(file));
		if (result != file)
			ui->listAfter->item(position)->setForeground(QColor(0, 128, 0));

		position++;
	}
}
