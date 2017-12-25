#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QEvent>
#include <QPainter>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include "viewwidget.h"

class QRadioButton;
class QCheckBox;
class ViewWidget;

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	QMenu* file; 
	QMenu* edit;
	QMenu* oper;
	QToolBar* toolbar_main_;
	QToolBar* toolbar_paint_;

	QAction* open_action_;
	QAction* save_action_;
	QAction* draw_action_;
	QAction* dele_action_;
	QAction* eval_action_;
	QAction* subd_action_;
	QAction* degr_action_;

	QSlider* slider_;
	QRadioButton* radiobutton_bezier_;
	QRadioButton* radiobutton_fourpoint_;
	QCheckBox* checkbox_frame_;
	QCheckBox* checkbox_curve_;

	ViewWidget*	view_widget_;

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	void CreateButtons();

private:
	Ui::MainWindowClass ui;
};


#endif // MAINWINDOW_H
