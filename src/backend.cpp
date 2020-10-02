#include "backend.h"

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QTextStream>

#define TEX_DOCUMENT "./tex/document.tex"

Backend::Backend() {}

void Backend::Compile(QString code) {
	QFile file(TEX_DOCUMENT);
	if (file.open(QIODevice::WriteOnly)) {
		QTextStream stream(&file);
		stream << code.toUtf8() << endl;
	}
	file.close();
	//
	QProcess *process = new QProcess();
	process->setWorkingDirectory("tex");
	process->start("/opt/context/tex/texmf-linux-64/bin/context", QStringList() << "document.tex");
}