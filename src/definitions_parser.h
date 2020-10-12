#ifndef DEFINITIONS_PARSER_H
#define DEFINITIONS_PARSER_H

#include <QString>

class Style_List;
class Backend_Translater;

class Definitions_Parser {
 public:
	static const int Max_Ident_Level = 3;
	Definitions_Parser(Style_List* styles, Backend_Translater* translater);

 private:
	static const int Major_Version = 1;
	static const int Minor_Version = 0;
	static const int Revision_Version = 0;
	//
	void Parse(QString definition_file);
	QString Parse_Key(QString line, QString& trimmed_line);
	void Check_Version_Validity(QString version_string);
	void Add_Value_Line(QString value_line);
	bool Is_Comment(QString line);
	int Count_Levels(QString line);
	//
	QString keys_hierarchy[Max_Ident_Level];
	Style_List* styles;
	Backend_Translater* translater;
	QString current_key;
	int level;
	// DEBUG ///////////////////////////////////////////////////////////////////////////////////////
	void Print_Indent(QString text);
	QString To_String(QString string_vector[]);
};

#endif // DEFINITIONS_PARSER_H
