#ifndef ABSTRACT_LOADABLE_FILE_H
#define ABSTRACT_LOADABLE_FILE_H

#include "abstract_loadable_tree.h"

struct File_Version {
	int Major;
	int Minor;
	int Revision;
};

class Abstract_Loadable_File : public Abstract_Loadable_Tree {
 public:
	Abstract_Loadable_File();
	void load(QString file_path);
	QString version_string();

 protected:
	virtual const File_Version Version() = 0;

 private:
	struct Line_Context {
		QString key;
		QString value;
		int line_number;
		int key_line_number;
	};
	//
	State tokenize_line(QString trimmed_line, Line_Context& context);
	bool is_comment(QString line);
	int count_levels(QString line);
	void set_last_key_level(int& last_key_level, int level);
	void check_version_validity(Line_Context& context);
	void abort_parse(Exception& exception, Line_Context& context);
	QString msg_line(QString text, int line_number);
	QString file_path;
};

#endif // ABSTRACT_LOADABLE_FILE_H
