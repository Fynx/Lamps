#pragma once

#include <QtCore>

namespace CSVWriter {
	QString fromVector(const QVector<QVariant> &vector);
	bool saveVectors(const QString &fileName, const QVector<QVector<QVariant> > &vectors);
}

QString CSVWriter::fromVector(const QVector<QVariant> &vector)
{
	QString output;
	for (const QVariant &var : vector) {
		if (!output.isEmpty())
			output += ",";
		if (var.canConvert(QMetaType::QString)) {
			output += var.toString();
		} else {
			output += var.toInt();
		}
	}

	return output;
}

bool CSVWriter::saveVectors(const QString &fileName, const QVector<QVector<QVariant> > &vectors)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	for (const QVector<QVariant> &vector : vectors) {
		QString outputString = fromVector(vector);
		file.write(outputString.toStdString().c_str(), outputString.size());
		file.write("\n", sizeof(char));
	}

	return true;
}