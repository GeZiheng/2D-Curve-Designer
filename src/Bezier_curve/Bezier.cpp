#include "Bezier.h"
#include <cmath>
#include <queue>

Bezier::Bezier()
{
	closed = false;
	selected = INFINITY;
}

Bezier::~Bezier()
{
}

void Bezier::AddPoint( QPoint point )
{
	QPointF new_point;
	new_point.setX(point.rx());
	new_point.setY(point.ry());
	control_points.push_back(new_point);
}

void Bezier::AddPoint( QPointF point )
{
	control_points.push_back(point);
}

void Bezier::ChangeLastPoint( QPoint point )
{
	control_points.pop_back();
	QPointF new_point;
	new_point.setX(point.rx());
	new_point.setY(point.ry());
	control_points.push_back(new_point);
}

bool Bezier::SelectPoint( QPoint point )
{
	int i;
	float distance;
	selected = INFINITY;
	for( i=0; i<PointNum(); i++ )
	{
		distance = sqrt(pow(float(point.rx()-control_points[i].rx()),2)+pow(float(point.ry()-control_points[i].ry()),2));
		if( distance<2*POINT_SIZE )
		{
			selected = i;
			return true;
		}
	}
	selected = INFINITY;
	return false;
}

void Bezier::ChangeSelectedPoint( QPoint point )
{
	if( selected<INFINITY )
	{
		control_points[selected].setX(point.rx());
		control_points[selected].setY(point.ry());
	}
}

void Bezier::Move( QPoint start, QPoint end )
{
	int i;
	for( i=0; i<control_points.size(); i++ )
	{
		control_points[i].setX(control_points[i].rx()+end.rx()-start.rx());
		control_points[i].setY(control_points[i].ry()+end.ry()-start.ry());
	}
	for( i=0; i<bezier_curve.size(); i++ )
	{
		bezier_curve[i].setX(bezier_curve[i].rx()+end.rx()-start.rx());
		bezier_curve[i].setY(bezier_curve[i].ry()+end.ry()-start.ry());
	}
}

int Bezier::PointNum()
{
	return control_points.size();
}

void Bezier::Draw( QPainter &paint, bool draw_ctrl_plgn, bool draw_bezier, bool chosen )
{
	int i;
	if( draw_bezier && bezier_curve.size()>0 )
	{
		if( chosen )
			paint.setPen( QPen(Qt::green,LINE_WIDTH) );
		else
			paint.setPen( QPen(Qt::blue,LINE_WIDTH) );
		for( i=1;i<bezier_curve.size();i++ )
			paint.drawLine( bezier_curve[i-1], bezier_curve[i] );
		if( closed )
			paint.drawLine( bezier_curve[i-1], bezier_curve[0] );
	}
	if( draw_ctrl_plgn && PointNum()>0 )
	{
		paint.setPen( QPen(Qt::black,LINE_WIDTH) );
		for( i=1;i<control_points.size();i++ )
			paint.drawLine( control_points[i-1], control_points[i] );
		if( closed )
			paint.drawLine( control_points[i-1], control_points[0] );
		for( i=0;i<control_points.size();i++ )
		{
			if( i==selected )
				paint.setPen( QPen(Qt::yellow,POINT_SIZE,Qt::SolidLine,Qt::RoundCap) );
			else
				paint.setPen( QPen(Qt::red,POINT_SIZE,Qt::SolidLine,Qt::RoundCap) );
			paint.drawPoint( control_points[i] );
		}
	}
}

float Bezier::Distance( QPointF point )
{
	int i;
	float min_d=INFINITY,d;
	for( i=0; i<bezier_curve.size(); i++ )
	{
		d = sqrt( pow((bezier_curve[i].rx()-point.rx()),2) + pow((bezier_curve[i].ry()-point.ry()),2) );
		if( d<min_d )
			min_d = d;
	}
	return min_d;
}

QPointF Bezier::Evaluate( float t )
{
	vector<QPointF> points;
	int num,i,k;
	float rx,ry;
	num = PointNum();
	for( i=0; i<num; i++ )
		points.push_back(control_points[i]);
	for( k=1; k<num; k++ )
	{
		for( i=0; i<num-k; i++ )
		{
			rx = (1-t) * points[i].rx() + t * points[i+1].rx();
			ry = (1-t) * points[i].ry() + t * points[i+1].ry();
			points[i].setX(rx);
			points[i].setY(ry);
		}
		points.pop_back();
	}
	return points[0];
}

void Bezier::Subdivide( Bezier* &left, Bezier* &right, float t )
{
	if( PointNum()==0 || closed )
		return;
	vector<QPointF> new_points;
	QPointF *point;
	int num,k,i;
	float rx,ry;

	num = PointNum();
	for( i=0; i<num; i++ )
		new_points.push_back(control_points[i]);

	// compute position for new points
	for( k=1; k<num; k++ )
	{
		point = new QPointF;
		rx = (1-t) * new_points[k-1].rx() + t * new_points[k].rx();
		ry = (1-t) * new_points[k-1].ry() + t * new_points[k].ry();
		point->setX(rx);
		point->setY(ry);
		new_points.insert(new_points.begin()+k,*point);
		for( i=k+1; i<num; i++ )
		{
			rx = (1-t) * new_points[i].rx() + t * new_points[i+1].rx();
			ry = (1-t) * new_points[i].ry() + t * new_points[i+1].ry();
			new_points[i].setX(rx);
			new_points[i].setY(ry);
		}
	}

	// build sub polygons
	left = new Bezier;
	right = new Bezier;
	for( k=0; k<num; k++ )
	{
		left->AddPoint(new_points[k]);
		right->AddPoint(new_points[num+k-1]);
	}
}

void Bezier::DegreeElevate()
{
	QPointF point;
	int i,num;
	float rx,ry;
	num = PointNum();
	point.setX(control_points.back().rx());
	point.setY(control_points.back().ry());
	control_points.push_back(point);
	for( i=num; i>0; i-- )
	{
		rx = i/(float)num * control_points[i-1].rx() + (1-i/(float)num) * control_points[i].rx();
		ry = i/(float)num * control_points[i-1].ry() + (1-i/(float)num) * control_points[i].ry();
		control_points[i].setX(rx);
		control_points[i].setY(ry);
	}
}

void Bezier::CalBezier()
{
	if( PointNum()==0 || closed )
		return;

	queue<Bezier*> pieces;					// use a queue to store the pieces of subpolygon
	Bezier *left,*right,*current,*bezier;
	int i,j,num,piece_num;

	current = new Bezier;
	num = PointNum();
	for( i=0; i<num; i++ )
		current->AddPoint(control_points[i]);
	pieces.push(current);
	
	for( i=0; i<REFINE_TIMES; i++ )
		for( j=0; j<pow(2,float(i)); j++ )
		{
			// subdivide a polygon, and replace it with two subpolygons
			current = pieces.front();
			current->Subdivide(left,right,0.5);
			pieces.push(left);
			pieces.push(right);
			pieces.pop();
		}

	// connect all pieces into the Bezier curve
	piece_num = pieces.size();
	bezier_curve.clear();
	for( i=0; i<piece_num; i++ )
	{
		current = pieces.front();
		if( i==0 )
			bezier_curve.push_back(current->control_points[0]);
		for( j=1; j<num; j++ )
			bezier_curve.push_back(current->control_points[j]);
		pieces.pop();
		delete current;
	}
}

// Calculate Boundary Box for a polygon
void CalBB( vector<QPointF> points, float &left, float &right, float &bottom, float &top )
{
	int i;
	left=bottom=INFINITY;
	right=top=0;
	for( i=0; i<points.size(); i++ )
	{
		if( points[i].rx()<left )
			left=points[i].rx();
		if( points[i].rx()>right )
			right=points[i].rx();
		if( points[i].ry()<bottom )
			bottom=points[i].ry();
		if( points[i].ry()>top )
			top=points[i].ry();
	}
}

// Judge if Boundary Boxes of two polygons intersect with each other
bool BBinsec( vector<QPointF> v1, vector<QPointF> v2 )
{
	float l1,l2,r1,r2,b1,b2,t1,t2;
	CalBB(v1,l1,r1,b1,t1);
	CalBB(v2,l2,r2,b2,t2);
	if( l1>r2 || r1<l2 || b1>t2 || t1<b2 )
		return false;
	else
		return true;
}

// Calculate the size of Boundary Box
float BBsize( vector<QPointF> points )
{
	float l,r,b,t,s;
	CalBB(points,l,r,b,t);
	s = sqrt( (r-l)*(r-l) + (t-b)*(t-b) );
	return s;
}

// Calculate the center of Boundary Box
QPointF BBcenter( vector<QPointF> points )
{
	float l,r,b,t,cx,cy;
	CalBB(points,l,r,b,t);
	cx = (l+r)/2;
	cy = (t+b)/2;
	return QPointF(cx,cy);
}

bool Bezier::Intersect( Bezier b, vector<QPointF> &insec )
{
	if( PointNum()==0 || closed || b.PointNum()==0 || b.closed )
		return false;
	insec.clear();

	Bezier *c,*l,*r,*cb,*lb,*rb;
	float s,sb;
	queue<Bezier*> pieces;					// use a queue to store subpolygons
	int i,j,n,nb;

	c = new Bezier;
	n= PointNum();
	for( i=0; i<n; i++ )
		c->AddPoint(control_points[i]);
	cb = new Bezier;
	nb= b.PointNum();
	for( i=0; i<nb; i++ )
		cb->AddPoint(b.control_points[i]);
	// push initial polygons into the queue
	if( BBinsec(c->control_points,cb->control_points) )
	{
		pieces.push(c);
		pieces.push(cb);
	}
	
	while( !pieces.empty() )
	{
		// pop a couple of polygons
		c = pieces.front();
		pieces.pop();
		cb = pieces.front();
		pieces.pop();
		s = BBsize(c->control_points);
		sb = BBsize(cb->control_points);

		// if they are not two small, subdivide each one into two subpolygons
		if( s>EPSILON && sb>EPSILON )
		{
			c->Subdivide(l,r,0.5);
			cb->Subdivide(lb,rb,0.5);
			// check all couples and push available ones into queue
			if( BBinsec(l->control_points,lb->control_points) )
			{
				pieces.push(l);
				pieces.push(lb);
			}
			if( BBinsec(l->control_points,rb->control_points) )
			{
				pieces.push(l);
				pieces.push(rb);
			}
			if( BBinsec(r->control_points,lb->control_points) )
			{
				pieces.push(r);
				pieces.push(lb);
			}
			if( BBinsec(r->control_points,rb->control_points) )
			{
				pieces.push(r);
				pieces.push(rb);
			}
		}
		else
			if( s<sb )
				insec.push_back( BBcenter(c->control_points) );
			else
				insec.push_back( BBcenter(cb->control_points) );
	}
	return !insec.empty();
}

void Bezier::Subdivide()
{
	if( PointNum()==0 || !closed )
		return;
	vector<QPointF> old_points;
	QPointF new_point;
	int i,num=control_points.size();
	for( i=0; i<num; i++ )
		old_points.push_back( control_points[i] );
	control_points.clear();
	for( i=0; i<num; i++ )
	{
		new_point = old_points[(i+1)%num];
		control_points.push_back(new_point);
		new_point = - 0.0625 * old_points[i] + 0.5625 * old_points[(i+1)%num] + 0.5625 * old_points[(i+2)%num] - 0.0625 * old_points[(i+3)%num];
		control_points.push_back(new_point);
	}
}

void Bezier::Interpolate()
{
	if( PointNum()==0 || !closed )
		return;

	int i,num;
	vector<QPointF> tmp;
	num = control_points.size();
	for( i=0; i<num; i++ )
		tmp.push_back(control_points[i]);
	for( i=0; i<REFINE_TIMES; i++ )
		Subdivide();
	bezier_curve.clear();
	for( i=0; i<control_points.size(); i++ )
		bezier_curve.push_back(control_points[i]);
	control_points.clear();
	for( i=0; i<num; i++ )
		control_points.push_back(tmp[i]);
}