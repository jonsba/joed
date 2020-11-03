#include "backend.h"
#include "environment.h"
#include "joed.h"
#include "layout_block.h"
#include "lua_client.h"
#include "style.h"

#include <QFile>
#include <QProcess>
#include <QTextStream>

Backend::Backend(Lua_VM* lua_vm) {
	this->lua_client = new Lua_Client(lua_vm);
	this->the_compile_process = new QProcess();
}

State Backend::process_key(QString key, int level) {
	return State::Parsing_Value;
}

void Backend::assign(QString end_key, QString value, bool is_first_value_line) {
	if (end_key == Keys[Output_E]) {
		this->lua_client->add_output_line(value, is_first_value_line);
	} else if (end_key == Keys[File_Extension_E]) {
		this->translated_file_extension = value;
		this->translated_document_path = BACKEND_WORKING_DIRECTORY DOCUMENT_BASENAME + value;
		this->translated_environment_path = BACKEND_WORKING_DIRECTORY ENVIRONMENT_BASENAME + value;
	} else if (end_key == Keys[Viewer_E]) {
		this->compiled_file_extension = value;
		this->the_compiled_document_path = BACKEND_WORKING_DIRECTORY DOCUMENT_BASENAME "." + value;
	}
}

void Backend::write_to_file(QString code, QString file_path) {
	QFile file(file_path);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		QTextStream stream(&file);
		stream << code.toUtf8() << endl;
	}
	file.close();
}

void Backend::compile(QString document_code, QString environment_code) {
	this->write_to_file(document_code, this->translated_document_path);
	this->write_to_file(environment_code, this->translated_environment_path);
	//
	QHash<QString, QString> global_dict = {};
	global_dict[Translated_Document_Id] = this->translated_document_path;
	global_dict[Compiled_Document_Id] = this->the_compiled_document_path;
	QString exec_command = this->lua_client->eval(global_dict);
	this->the_compile_process->setWorkingDirectory(BACKEND_WORKING_DIRECTORY);
	this->the_compile_process->start(exec_command);
}

QProcess* Backend::compile_process() {
	return this->the_compile_process;
}

QString Backend::compiled_document_path() {
	return this->the_compiled_document_path;
}

QString Backend::viewer_type() {
	return this->compiled_file_extension;
}
