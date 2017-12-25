#include <QFileDialog>
#include <fstream>
#include <string>
#include <algorithm>
#include "viewwidget.h"

QPoint		prev_pos;
bool		move_signal;

ViewWidget::ViewWidget( QWidget *parent )
{
	ui.setupUi(this);
	closed_ = false;
	draw_frame_ = true;
	draw_curve_ = true;
	draw_point_ = false;
	is_drawing_ = false;
	current_curve_ = NULL;
	id_ = INFINITY;
	t_ = 0.5;
}


ViewWidget::~ViewWidget()
{
	delete current_curve_;
	curves_.clear();
}


void ViewWidget::mousePressEvent( QMouseEvent *event )
{
	if( id_==INFINITY )
		return;
	if( draw_point_ )
		draw_point_ = false;
	if( current_curve_->PointNum()==0 )
	{
		is_drawing_ = true;
		current_curve_->AddPoint(event->pos());
	}
	if( Qt::LeftButton == event->button() )
	{
		if( is_drawing_ )
			current_curve_->AddPoint(event->pos());
		else
		{
			if( chooseCurve(event->pos()) )
				current_curve_ = curves_[id_];
			if( draw_frame_ )
				current_curve_->SelectPoint(event->pos());
			move_signal = id_<INFINITY && current_curve_->selected==INFINITY;
		}
	}
	if( Qt::RightButton == event->button() )
	{
		if( closed_ )
			current_curve_->closed = true;
		is_drawing_ = false;
	}
	prev_pos = event->pos();
}

void ViewWidget::mouseMoveEvent( QMouseEvent *event )
{
	if( id_==INFINITY )
		return;
	if( is_drawing_ )
	{
		setMouseTracking(true);
		current_curve_->ChangeLastPoint(event->pos());
	}
	else
	{
		setMouseTracking(false);
		if( move_signal )
		{
			current_curve_->Move(prev_pos,event->pos());
			calIntersect(current_curve_);
		}
		if( draw_frame_ )
			current_curve_->ChangeSelectedPoint(event->pos());
	}
	prev_pos = event->pos();
}

void ViewWidget::mouseReleaseEvent( QMouseEvent *event )
{
	if( id_<INFINITY && !is_drawing_ )
	{
		if( !current_curve_->closed )
		{
			current_curve_->CalBezier();
			calIntersect(current_curve_);
		}
		else
			current_curve_->Interpolate();
	}
	move_signal = false;
}

void ViewWidget::paintEvent( QPaintEvent * )
{
	QPainter painter(this);
	int i,j,k;
	for( i=0; i<curves_.size(); i++ )
		if( curves_[i]!=NULL )
			curves_[i]->Draw( painter, draw_frame_, draw_curve_, i==id_ );
	painter.setPen( QPen(Qt::red,POINT_SIZE,Qt::SolidLine,Qt::RoundCap) );
	for( k=0; k<insec.size(); k++ )
		painter.drawPoint(insec[k].rx(),insec[k].ry());
	if( draw_point_ == true )
	{
		painter.setPen( QPen(Qt::magenta,POINT_SIZE,Qt::SolidLine,Qt::RoundCap) );
		painter.drawPoint(p_.rx(),p_.ry());
	}
	update();
}

bool ViewWidget::chooseCurve( QPoint point )
{
	int i;
	for( i=0; i<curves_.size(); i++ )
		if( curves_[i]->Distance(point) < 3*LINE_WIDTH )
		{
			id_ = i;
			curves_[i]->selected = INFINITY;
			return true;
		}
	return false;
}

void ViewWidget::calIntersect( Bezier* b )
{
	vector<QPointF> tmp;
	int i,j;
	insec.clear();
	for( i=0; i<curves_.size(); i++ )
		if( i!=id_ && curves_[i]!=NULL && current_curve_->Intersect(*curves_[i],tmp) )
			for( j=0; j<tmp.size(); j++ )
				insec.push_back(tmp[j]);
}

void ViewWidget::OpenFile()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("BEZIER(*.bzr)"));
	if(filename.isEmpty())
		return;
	string file = filename.toLocal8Bit().constData();
	ifstream infile; 
	infile.open(file.data());

	string s, temps;
	int i,j,k;
	int curve_num, point_num;
	bool closed;
	getline(infile,s);
	temps.assign(s, 7, s.length()-7);
	curve_num = atoi(temps.c_str());			// total amount of curves
	for ( i=0; i<curve_num; i++ )
	{
		getline(infile,s);
		point_num = 0;
		temps.clear();
		j = 0;
		while( s[j]!=' ' )
			j++;
		j++;
		while( s[j]!=' ' )
		{
			temps.push_back(s[j]);
			j++;
		}
		point_num = atoi(temps.c_str());		// amount of control points
		j++;
		if( s[j]=='c' )
			closed = true;
		else
			closed = false;

		current_curve_ = new Bezier;
		QPointF new_point;
		for( j=0; j<point_num; j++ )
			if( getline(infile,s) )
			{
				string sx,sy;
				k=0;
				while( s[k]!=' ' )
				{
					sx.push_back(s[k]);
					k++;
				}
				k++;
				while( k<s.length() )
				{
					sy.push_back(s[k]);
					k++;
				}
				new_point = QPointF( atof(sx.c_str()), atof(sy.c_str()) );
				current_curve_->AddPoint(new_point);
			}
		current_curve_->closed = closed;
		if( closed )
			current_curve_->Interpolate();
		else
			current_curve_->CalBezier();
		curves_.push_back(current_curve_);
	}
	id_ = curves_.size()-1;

	infile.close();
	update();
}

void ViewWidget::SaveFile()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("BEZIER(*.bzr)"));
	if (filename.isNull())
	{
		return;
	}	
	string file = filename.toLocal8Bit().constData();
	ofstream outfile(file); 
	int i,j;
	if (outfile.is_open())
	{
		outfile <<"Curves " << curves_.size() << endl;	
		for (i=0; i<curves_.size(); i++)
		{
			outfile << "#" << i+1 << " " << curves_[i]->control_points.size() << " ";
			if( curves_[i]->closed )
				outfile << "c" << endl;
			else
				outfile << "s" << endl;
			for ( j=0; j<curves_[i]->control_points.size(); j++ )
				outfile << curves_[i]->control_points[j].rx()<<" "<< curves_[i]->control_points[j].ry() << endl;
		}
		outfile.close();  
	}
}

void ViewWidget::newFigure()
{
	if( current_curve_!=NULL )
		current_curve_->selected = INFINITY;
	current_curve_ = new Bezier;
	curves_.push_back(current_curve_);
	id_ = curves_.size()-1;
}

void ViewWidget::deleteFigure()
{
	if( id_<INFINITY )
	{
		delete current_curve_;
		curves_.erase(curves_.begin()+id_);
		if( curves_.size()>0 )
		{
			current_curve_ = curves_.back();
			id_ = curves_.size()-1;
		}
		else
			current_curve_ = NULL;
	}
}

void ViewWidget::Evaluate()
{
	if( id_==INFINITY || current_curve_->closed )
		return;
	p_ = current_curve_->Evaluate(t_);
	draw_point_ = true;
}

void ViewWidget::Subdivide()
{
	if( id_==INFINITY )
		return;
	if( !current_curve_->closed )
	{
		Bezier *left, *right;
		current_curve_->Subdivide(left,right,t_);
		left->CalBezier();
		right->CalBezier();
		delete(current_curve_);
		curves_.pop_back();
		curves_.push_back(left);
		curves_.push_back(right);
		current_curve_ = right;
		id_ = curves_.size()-1;
	}
	else
		current_curve_->Subdivide();
	update();
}

void ViewWidget::DegreeElevate()
{
	if( id_==INFINITY || current_curve_->closed )
		return;
	current_curve_->DegreeElevate();
	current_curve_->CalBezier();
	update();
}

void ViewWidget::SetParameter( int n )
{
	t_ = 0.01*n;
	update();
}

void ViewWidget::CheckBezier( bool bv )
{
	closed_ = !bv;
	update();
}

void ViewWidget::CheckFourPoint( bool bv )
{
	closed_ = bv;
	update();
}

void ViewWidget::CheckDrawFrame( bool bv )
{
	draw_frame_ = bv;
	update();
}

void ViewWidget::CheckDrawCurve( bool bv )
{
	draw_curve_ = bv;
	update();
}