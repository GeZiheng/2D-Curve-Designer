#pragma once
#include <qpainter.h>
#include <vector>
using namespace std;
#define REFINE_TIMES 5
#define POINT_SIZE 8
#define LINE_WIDTH 3
#define INFINITY 10000
#define EPSILON 0.5

class Bezier
{
public:
	vector<QPointF> control_points;         // control points
	vector<QPointF> bezier_curve;			// Bezier curve
	bool		closed;						// is the curve open or closed?
	int			selected;					// id of the selected point

public:
	Bezier(void);
	~Bezier(void);

public:	
	/* Basic operations*/
	void AddPoint( QPoint point );				// add new vertex
	void AddPoint( QPointF point );				// add new vertex
	void ChangeLastPoint( QPoint point );		// change the last control point
	bool SelectPoint( QPoint point );			// select point
	void ChangeSelectedPoint( QPoint point );   // change the seltected control point
	void Move( QPoint start, QPoint end );		// move the curve to given point
	int PointNum();								// count number of vontrol points
	void Draw( QPainter &paint, bool draw_ctrl_plgn, bool draw_bezier, bool chosen );			// draw control polygon or Bezier curve on screen
	float Distance( QPointF point );			// compute the distance between the curve and a given point

	/* Operations related to Bezier curve */
	QPointF Evaluate( float t );				// evaluate a point on Bezier curve
	void Subdivide( Bezier* &left, Bezier* &right, float t );	// subdivide control polygon
	void DegreeElevate();						// degree elevate control polygon
	void CalBezier();							// compute Bezier curve for the control polygon
	bool Intersect( Bezier b, vector<QPointF> &insec );	// compute intersections with another Bezier curve

	/* Operations related to 4-point subdivision */
	void Subdivide();                           // 4-point subdivision
	void Interpolate();						    // Calculate interpolating curve
};