#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	public slots:
		void rename();
		void updatePlugin();
		void updateFiles();

	private:
		Ui::MainWindow *ui;
		QMap<QString,QString> m_files;
};

#endif // MAINWINDOW_H
