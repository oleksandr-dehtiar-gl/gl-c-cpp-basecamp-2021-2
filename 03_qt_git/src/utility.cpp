#include "utility.hpp"

namespace gitutility {
	
	// Splitt string with separate string(symbol)
	QList<QStringList> splitStringToListStringList(const QStringList &str, const QString &separator) {
		QList<QStringList> splitCommits;	
		for (int i = 0; i < str.size(); ++i){
			auto commits = str[i].split(separator, QString::SkipEmptyParts);	
			if (commits.isEmpty()) 
				continue;
			splitCommits << commits;
		}
		return splitCommits;
	}
	
	QString getStringMatchRegex(const QRegExp& regex, const QString& str) {
		int pos = regex.indexIn(str);
		if (pos == -1)
			return QString{};
		return regex.cap(0);
	}

}
