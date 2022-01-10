#include "process.hpp"
#include <iostream>
#include <stdexcept>

namespace gitgui {
	
	Process::Process(QString program, QStringList arguments)
		: QObject(nullptr)	
	{
		setNewProgram(program, arguments);
		init();
	}

	Process::Process() 
		: QObject(nullptr) 
	{
		init();
	}
	
	void Process::init() {
		QObject::connect(&mProcess, &QProcess::readyReadStandardOutput, this, &Process::readData); 
		QObject::connect(&mProcess, &QProcess::errorOccurred, this, &Process::errorExit); 
		QObject::connect(&mProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), 
						this, &Process::finishProcess);
	}

	void Process::finishProcess(int excode, QProcess::ExitStatus exStat) {
		if (exStat == QProcess::ExitStatus::NormalExit) {
			// std::cout << "CLOSE CORRECT\n";
			//QCoreApplication::quit();
		} else {
			// std::cout << "CLOSE WHITH ERROR CODE: " << excode << std::endl;
			//QCoreApplication::exit(excode);
		}
	}
	
	void Process::errorExit(QProcess::ProcessError error) {
		QString strerror = "gitgui::Process::errorExit() => "; 
		switch(mProcess.error()) {
			case QProcess::FailedToStart:
				strerror = strerror + "FailedToStart";
				break;
			case QProcess::Crashed:
				strerror = strerror + "Crashed"; 
				break;
			case QProcess::Timedout:
				strerror = strerror + "Timedout"; 
				break;
			case QProcess::WriteError:
				strerror = strerror + "WriteError"; 
				break;
			case QProcess::ReadError:
				strerror = strerror + "ReadError"; 
				break;
			case QProcess::UnknownError:
				strerror = strerror + "UnknoError"; 
				break;
			default:
				strerror = strerror + "Undefine"; 
		}
		QTextStream err(stderr);
		err << strerror << endl;
		throw std::invalid_argument(strerror.toStdString().c_str());
	}

	void Process::setNewProgram(const QString program, const QStringList arguments) {
		mProcess.setReadChannel(QProcess::StandardOutput);
		mProcess.setProgram(program);
		mProcess.setArguments(arguments);
	}

	void Process::readData() {
		mStringResult += QString(mProcess.readAllStandardOutput());
	}
	
	void Process::setWorkDirectory(const QString& workdir) {
		mProcess.setWorkingDirectory(workdir);
	}
	
	QString Process::run(const QString program, const QStringList arguments) {
		setNewProgram(program, arguments);
		return run();
	}

	QString Process::run() {
		QString().swap(mStringResult);
		mProcess.start(QIODevice::ReadOnly);
		mProcess.waitForFinished();
		return mStringResult;
	}
}


