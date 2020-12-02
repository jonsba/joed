#include "block_widget.h"
#include "children_block_widget.h"
#include "color_scheme.h"
#include "text_edit.h"

#include "src/joed.h"
#include "src/styles.h"
#include "src/text_block.h"

#include <QLayout>

Block_Widget::Block_Widget(QWidget* parent, Abstract_Multi_Block* block, int level,
                           bool insertion_allowed)
    : QWidget(parent) {
	this->the_block = block;
	this->level = level;
	//
	Color_Scheme color_scheme(level);
	this->setPalette(color_scheme.palette(Widget_State::Highlighted_E));
	this->setAutoFillBackground(true);
	QHBoxLayout* top_container = new QHBoxLayout(this);
	top_container->setMargin(0);
	top_container->addItem(
	    new QSpacerItem(Horizontal_Spacing, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));
	QVBoxLayout* blocks_container = new QVBoxLayout();
	blocks_container->setAlignment(Qt::AlignTop);
	blocks_container->setSpacing(2);
	blocks_container->setMargin(0);
	//
	QWidget* sub_block_widget;
	if (block->style()->type == Style_Type::Text_E) {
		sub_block_widget =
		    new Text_Edit(this, (Text_Block*)block, level, Insertion_Type::Text_Block_Insertion_E);
		blocks_container->addWidget(sub_block_widget);
		sub_block_widget->setFocus();
	} else {
		for (Abstract_Block* sub_block = block->first_child(); sub_block != nullptr;
		     sub_block = sub_block->next()) {
			switch (sub_block->style()->type) {
			case Style_Type::Children_E:
				sub_block_widget = new Children_Block_Widget(this, (Children_Block*)sub_block, level);
				break;
			case Style_Type::Layouted_E:
				sub_block_widget =
				    new Block_Widget(this, (Abstract_Multi_Block*)sub_block, level, insertion_allowed);
				break;
			case Style_Type::Text_E: {
				Insertion_Type allowed_insert = Insertion_Type::Denied_E;
				if (insertion_allowed) {
					allowed_insert = Insertion_Type::Layout_Block_Insertion_E;
				}
				sub_block_widget = new Text_Edit(this, (Text_Block*)sub_block, level, allowed_insert);
				break;
			}
			default:
				throw Exceptions::Not_Implemented();
			}
			blocks_container->addWidget(sub_block_widget);
		}
	}
	top_container->addLayout(blocks_container);
	this->setLayout(top_container);
}

Abstract_Multi_Block* Block_Widget::block() {
	return this->the_block;
}

void Block_Widget::insert() {
	this->insert(this->block()->insert_sibling(this->block()->style(), true));
}

void Block_Widget::insert(Abstract_Block* block) {
	emit((Children_Block_Widget*)this->parent())->insert((Abstract_Multi_Block*)block, this);
}

Block_Widget::~Block_Widget() = default;