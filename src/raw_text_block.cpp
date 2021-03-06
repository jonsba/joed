#include "raw_text_block.h"
#include "escaper.h"
#include "styles.h"
#include "writer.h"

Raw_Text_Block::Raw_Text_Block() : Abstract_Block(Styles::Raw_Text_Style) {
	this->the_text = "";
}

void Raw_Text_Block::set_text(QString text) {
	this->the_text = text;
}

void Raw_Text_Block::add_loaded_text(QString quoted_text) {
	// Remove the "" enclosing the loaded text
	QString text = quoted_text.mid(1, quoted_text.length() - 2);
	if (this->the_text == "") {
		this->the_text = text;
	} else {
		this->the_text += '\n' + text;
	}
}

QString Raw_Text_Block::text() {
	return this->the_text;
}

QString Raw_Text_Block::translate(Escaper* escaper) {
	return escaper->escape(this->the_text);
}

void Raw_Text_Block::save(Writer* writer, int level) {
	writer->write_end_key(Field::Id::Text, level);
	writer->write_value(this->the_text, level + 1, "\"");
}
