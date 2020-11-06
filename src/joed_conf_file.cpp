#include "joed_conf_file.h"

Joed_Conf_File::Joed_Conf_File() : Abstract_Loadable_File(Version) {}

State Joed_Conf_File::process_key(QString key, int level) {
	if (key == Joed::Keys[Defaults_E]) {
		return State::Parsing_Key;
	}
	return State::Parsing_Value;
}

void Joed_Conf_File::assign(QString end_key, QString value, bool is_first_value_line) {
	if (end_key == Joed::Keys[Backend_E]) {
		this->the_backend_name = value;
	} else if (end_key == Joed::Keys[Document_Class_E]) {
		this->the_document_class = value;
	}
}

QString Joed_Conf_File::backend_name() {
	return this->the_backend_name;
}
QString Joed_Conf_File::document_class() {
	return this->the_document_class;
}
