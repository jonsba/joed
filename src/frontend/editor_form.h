#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

class Document_Form;

QT_BEGIN_NAMESPACE
namespace Ui {
   class Editor_Form;
}
QT_END_NAMESPACE

class Editor_Form : public QMainWindow {

 public:
	Editor_Form(QString document_path, QWidget* parent = nullptr);
	~Editor_Form();

 private:
	Ui::Editor_Form* ui;
	Document_Form* document_form;
};

#endif // EDITOR_H
