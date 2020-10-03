#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

class Backend;

class QProcess;
class QPdfDocument;
class QPdfView;

QT_BEGIN_NAMESPACE
namespace Ui {
class Editor;
}
QT_END_NAMESPACE

class Editor : public QMainWindow {

 public:
	Editor(QWidget *parent = nullptr);
	~Editor();

 private:
	void Text_Changed();
	void Bookmark_Selected(const QModelIndex &index);
	void Compile_When_Needed(int tab_index);
	void Compilation_Completed();

	Ui::Editor *ui;
	Backend *backend;
	QProcess *compilation_process;
	bool text_changed;
	QPdfView *pdf_view;
	QPdfDocument *pdf_document;
};

#endif // EDITOR_H
