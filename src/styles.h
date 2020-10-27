#ifndef STYLES_H
#define STYLES_H

#include "abstract_loadable_tree.h"

#include <QHash>
#include <QString>

class Lua_VM;
class Style;

class Styles : public Abstract_Loadable_Tree {
 public:
	Styles(Lua_VM* lua_vm);
	State process_key(QString key, int level);
	void assign(QString end_key, QString value);

	Style* find(QString key);
	//
	inline static const QStringList Keys_Object = {Keys[Child_Of_E], Keys[Layout_E],
	                                               Keys[Inherits_E], Keys[Default_Child_Style_E]};

 private:
	//
	Style* add_style(QString name);
	Style* add_style_if_nil(QString name);

 private:
	QHash<QString, Style*> list;
	Style* new_style;
	Lua_VM* lua_vm;
};

#endif // STYLES_H
