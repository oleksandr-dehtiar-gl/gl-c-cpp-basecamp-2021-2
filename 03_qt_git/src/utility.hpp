#ifndef UTITLIY_HPP
#define UTITLIY_HPP

// #include <QList>
#include <QStringList>
#include <QRegExp>

namespace gitutility {
	
	QList<QStringList> splitStringToListStringList(const QStringList &str, const QString &separator);
	QString getStringMatchRegex(const QRegExp& regex, const QString& str);
	
}

#endif // UTITLIY_HPP
