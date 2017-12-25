#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <qevent.h>
#include <qpainter.h>
#include "ui_viewwidget.h"
#include "Bezier.h"

class ViewWidget : public QWidget
{
	Q_OBJECT

private:
	bool	closed_;
	bool	draw_frame_;
	bool	draw_curve_;
	bool	draw_point_;
	bool    is_drawing_;
	Bezier *current_curve_;
	vector<Bezier*> curves_;
	vector<QPointF> insec;
	int		id_;
	float	t_;
	QPointF p_;
	
public:
	ViewWidget(QWidget *parent = 0);
	~ViewWidget();
	void mousePressEvent( QMouseEvent *event );
	void mouseMoveEvent( QMouseEvent *event );
	void mouseReleaseEvent( QMouseEvent *event );
	void paintEvent( QPaintEvent * );
	bool chooseCurve( QPoint point );
	void calIntersect( Bezier *b );

public slots:
	void OpenFile();
	void SaveFile();
	void newFigure();
	void deleteFigure();
	void Evaluate();
	void Subdivide();
	void DegreeElevate();
	void SetParameter( int n );
	void CheckBezier( bool bv );
	void CheckFourPoint( bool bv );
	void CheckDrawFrame( bool bv );
	void CheckDrawCurve( bool bv );

private:
	Ui::ViewWidget ui;
};

#endif // VIEWWIDGET_H

