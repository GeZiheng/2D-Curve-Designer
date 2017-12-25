#include "mainwindow.h"
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLayout>
#include <QtWidgets/QSlider>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	QPalette pal(palette());
	pal.setColor(QPalette::Background, Qt::cyan);
	setPalette(pal);
	setWindowTitle("Bezier Curve");
	view_widget_ = new ViewWidget();
	setCentralWidget(view_widget_);
	setGeometry(300, 150, 700, 450);

	CreateButtons();
}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateButtons()
{
	open_action_ = new QAction(QIcon(":/Resources/images/open.png"), tr("&Open"), this);
	save_action_ = new QAction(QIcon(":/Resources/images/save.png"), tr("&Save"), this);
	draw_action_ = new QAction(QIcon(":/Resources/images/draw.png"), tr("&Draw"), this);
	dele_action_ = new QAction(QIcon(":/Resources/images/delete.png"), tr("&Delete"), this);
	eval_action_ = new QAction(tr("Evaluate"), this);
	subd_action_ = new QAction(tr("Subdivide"), this);
	degr_action_ = new QAction(tr("Degree Elevate"), this);

	connect(open_action_, SIGNAL(triggered()), view_widget_, SLOT(OpenFile()));
	connect(save_action_, SIGNAL(triggered()), view_widget_, SLOT(SaveFile()));
	connect(draw_action_, SIGNAL(triggered()), view_widget_, SLOT(newFigure()));
	connect(dele_action_, SIGNAL(triggered()), view_widget_, SLOT(deleteFigure()));
	connect(eval_action_, SIGNAL(triggered()), view_widget_, SLOT(Evaluate()));
	connect(subd_action_, SIGNAL(triggered()), view_widget_, SLOT(Subdivide()));
	connect(degr_action_, SIGNAL(triggered()), view_widget_, SLOT(DegreeElevate()));

	open_action_->setStatusTip(tr("Open a stored file"));
	save_action_->setStatusTip(tr("Save the curves to a file"));
	draw_action_->setStatusTip(tr("Draw control polygon"));
	dele_action_->setStatusTip(tr("Delete last polygon"));
	eval_action_->setStatusTip(tr("Evaluate position for given parameter"));
	subd_action_->setStatusTip(tr("Subdivide the curve to two pieces"));
	degr_action_->setStatusTip(tr("Degree elevate the curve"));

	file = menuBar()->addMenu(tr("&File"));
	file->addAction(open_action_);
	file->addAction(save_action_);
	edit = menuBar()->addMenu(tr("&Edit"));
	edit->addAction(draw_action_);
	edit->addAction(dele_action_);
	oper = menuBar()->addMenu(tr("&Operation"));
	oper->addAction(eval_action_);
	oper->addAction(subd_action_);
	oper->addAction(degr_action_);

	toolbar_main_ = addToolBar(tr("&Main"));
	toolbar_main_->addAction(open_action_);
	toolbar_main_->addAction(save_action_);
	toolbar_main_->addAction(draw_action_);
	toolbar_main_->addAction(dele_action_);

	slider_ = new QSlider(Qt::Horizontal,this);
	slider_->setMinimum(0);
	slider_->setMaximum(100);
	slider_->setValue(50);
	connect(slider_, SIGNAL(valueChanged(int)), view_widget_, SLOT(SetParameter(int)));

	radiobutton_bezier_ = new QRadioButton(tr("Bezier"), this);
	connect(radiobutton_bezier_, SIGNAL(clicked(bool)), view_widget_, SLOT(CheckBezier(bool)));
	radiobutton_bezier_->setChecked(true);

	radiobutton_fourpoint_ = new QRadioButton(tr("FourPoint"), this);
	connect(radiobutton_fourpoint_, SIGNAL(clicked(bool)), view_widget_, SLOT(CheckFourPoint(bool)));

	checkbox_frame_ = new QCheckBox(tr("Control Polygon"), this);
	connect(checkbox_frame_, SIGNAL(clicked(bool)), view_widget_, SLOT(CheckDrawFrame(bool)));
	checkbox_frame_->setChecked(true);

	checkbox_curve_ = new QCheckBox(tr("Bezier Curve"), this);
	connect(checkbox_curve_, SIGNAL(clicked(bool)), view_widget_, SLOT(CheckDrawCurve(bool)));
	checkbox_curve_->setChecked(true);

	toolbar_paint_ = addToolBar(tr("&Paint"));
	toolbar_paint_->addWidget(radiobutton_bezier_);
	toolbar_paint_->addWidget(radiobutton_fourpoint_);
	toolbar_paint_->addWidget(checkbox_frame_);
	toolbar_paint_->addWidget(checkbox_curve_);
	toolbar_paint_->addWidget(slider_);
}