#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <QtWidgets>
#include <QProcess>

namespace gitgui {
	
	class Process : public QObject {
		Q_OBJECT
	public:
		explicit Process(QString program, QStringList arguments = QStringList());
		Process();
		Process(Process &) = delete;
		Process& operator=(Process &) = delete;
	private:
		void setNewProgram(const QString program, const QStringList arguments);
		void init();
	private slots:
		void readData();	
		void finishProcess(int excode, QProcess::ExitStatus exStat);
		void errorExit(QProcess::ProcessError error);
	public:
		void setWorkDirectory(const QString& workdir);
		QString run();
		QString run(const QString program, const QStringList arguments = QStringList());
	private:
		QProcess mProcess;
		QString mStringResult;
	};
}

#endif // PROCESS_HPP

