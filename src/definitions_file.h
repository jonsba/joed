#ifndef DEFINITIONS_FILE_H
#define DEFINITIONS_FILE_H

#include "abstract_loadable_file.h"
#include "joed.h"

#include <QHash>
#include <QString>

class Lua_VM;
class Document_Styles;
class Backend;
class Environment;

struct Definitions_Objects {
	Backend* backend;
	Environment* environment;
	Document_Styles* document_styles;
};

struct Definitions_Info {
	QString name;
	QString path;
};

class Definitions_File final : public Abstract_Loadable_File {
 public:
	Definitions_File(QString name, Definitions_Objects definitions_object,
	                 Definitions_File* parent = nullptr);
	Definitions_Info* info();
	//
	inline static const QString Root_Directory = Joed::System_Data_Path;
	inline static const QString File_Extension = ".def";

 protected:
	const File_Version Version() { return {0, 0, 0}; }
	void process_key(QString key, int level);
	void assign(QString end_key, QString value, bool is_first_value_line);

 private:
	QString base_path; // = path without file extension
	Definitions_Info the_file_info;
	QHash<QString, Abstract_Loadable_Object*> objects_table;
	Abstract_Loadable_Object* current_object;
};

#endif // DEFINITIONS_FILE_H
