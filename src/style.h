#ifndef STYLE_H
#define STYLE_H

#include "abstract_block.h"
#include "abstract_loadable_object.h"
#include "joed.h"

#include <QLinkedList>
#include <QScopedPointer>
#include <QString>

class Lua_Client;
class Lua_VM;
class Layout_Entry;

// The final keyword suppresses a warning when destructing object in styles.cpp
// Another option would be to make the destructor virtual
class Style final : Abstract_Loadable_Object {

 public:
	Style(QString the_name, Lua_VM* lua_vm);
	~Style();
	void assign(QString key, QString value, bool is_first_value_line);
	void assign(QString key, Style* object, bool is_first_value_line);
	QString name();
	Block_Type type();
	QLinkedList<Layout_Entry*> layout_entries();
	Style* default_child_style();
	bool is_multiblock();
	QString translate(QHash<QString, QString> key_value);

 private:
	//
	QString the_name;
	QString declare;
	QLinkedList<Layout_Entry*> the_layout_entries;
	Style* base_style = nullptr;
	Style* parent = nullptr;
	Style* the_default_child_style = nullptr;
	QScopedPointer<Lua_Client> lua_client;
	Block_Type block_type = Block_Type::Uninitialized_E;
};

#endif // STYLE_H
