#include "writer.h"
#include "exceptions.h"
#include "joed.h"

Writer::Writer() {}

void Writer::open(QString file_path) {
	this->file_descr.setFileName(file_path);
	if (! this->file_descr.open(QIODevice::WriteOnly | QIODevice::Text)) {
		throw Exceptions::Cannot_Open(file_path);
	}
}

void Writer::write_key(QString key, int level) {
	this->write_line(key + ":\n", level);
}
void Writer::write_end_key(QString end_key, int level) {
	this->write_line(end_key + " :=\n", level);
}

void Writer::write_value(QString value, int level, QString escape_char) {
	for (QString line : value.split('\n')) {
		this->write_line(escape_char + line + escape_char + '\n', level);
	}
}

void Writer::write_pair(QString end_key, QString value, int level) {
	this->write_line(end_key + " := " + value + '\n', level);
}

void Writer::close() {
	this->file_descr.close();
}

void Writer::write_line(QString line, int level) {
	this->write_tabulations(level);
	this->file_descr.write(line.toUtf8());
}

void Writer::write_tabulations(int level) {
	QString tabulations = "";
	for (int i = 0; i < level; i++) {
		tabulations += '\t';
	}
	this->file_descr.write(tabulations.toUtf8());
}
