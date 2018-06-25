//-----------------------------------------------------------------------------------
//
//	2D Box class
//
//	Anton M. Krivtsov
//
//	29.10.2001
//
//-----------------------------------------------------------------------------------

#ifndef ___Box2D_h___
#define ___Box2D_h___

#include "vect2D.h"

#define Box2D_ const Box2D&

//-----------------------------------------------------------------------------------

class Box2D
{
public:
	struct SFLOAT									{ Vect2D::SFLOAT  r1;	Vect2D::SFLOAT  r2; };
	struct SDOUBLE									{ Vect2D::SDOUBLE r1;	Vect2D::SDOUBLE r2; };

	Box2D()											{}
	Box2D(FLA x1, FLA y1, FLA x2, FLA y2)			{ Set(x1, y1, x2, y2); }
	Box2D(Vect2D_ r1, Vect2D_ r2)					{ Set(r1, r2); }
	Box2D(const SFLOAT&  box)						{ Set(box); }
	Box2D(const SDOUBLE& box)						{ Set(box); }
	Box2D(Vect2D_ r, FLA d)							{ Set(r, d, d); }
	Box2D(Vect2D_ r, FLA dx, FLA dy)				{ Set(r, dx, dy); }

	void Set(FLA x1, FLA y1, FLA x2, FLA y2)		{ r1.Set(x1, y1); r2.Set(x2, y2); }
	void Set(Vect2D_ r1, Vect2D_ r2)				{ this->r1 = r1; this->r2 = r2; }
	void Set(Box2D_ box)							{ r1 = box.r1; r2 = box.r2; }
	void Set(const SFLOAT&  box)					{ r1 = box.r1; r2 = box.r2; }
	void Set(const SDOUBLE& box)					{ r1 = box.r1; r2 = box.r2; }
	void Set(Vect2D_ r, FLA d)						{ Set(r, d, d); }
	void Set(Vect2D_ r, FLA dx, FLA dy)				{ Set(r.x - dx, r.y - dy, r.x + dx, r.y + dy); }
						
	operator SFLOAT()						const;
	operator SDOUBLE()						const;

	BOOL operator ==(Box2D_ box)			const	{ return r1 == box.r1 && r2 == box.r2; }
	BOOL operator !=(Box2D_ box)			const	{ return !operator==(box); }

	BOOL operator > (Vect2D_ r)				const;	// r belongs to the box
	BOOL operator < (Vect2D_ r)				const;	// r don't belongs to the box

	Box2D GetDeflated(FLA d)				const   { return GetDeflated(d, d); }
	Box2D GetInflated(FLA d)				const	{ return GetDeflated(-d); }
	Box2D GetDeflated(FLA dx,FLA dy)		const	{ return Box2D(r1.x + dx, r1.y + dy, r2.x - dx, r2.y - dy); }
	Box2D GetInflated(FLA dx,FLA dy)		const	{ return GetDeflated(-dx, -dy); }

	void  Deflate(FLA dx, FLA dy)					{ r1.x += dx; r1.y += dy; r2.x -= dx; r2.y -= dy; }
	void  Deflate(FLA d)							{ Deflate(d, d); }
	void  Inflate(FLA d)							{ Deflate(-d); }
	void  Inflate(FLA dx, FLA dy)					{ Deflate(-dx, -dy); }

	Box2D GetZoomed(FLA kx, FLA ky)			const;
	Box2D GetZoomed(FLA k)					const	{ return GetZoomed(k, k); }
	void  Zoom(FLA kx, FLA ky)						{ Set(GetZoomed(kx, ky)); }
	void  Zoom(FLA k)								{ Zoom(k, k); }

	Box2D GetMoved(Vect2D_ r)				const	{ return Box2D(r1 + r, r2 + r); }
	Box2D GetMoved(FLA x, FLA y)			const	{ return GetMoved(Vect2D(x, y)); }
	void  Move(Vect2D_ r)							{ r1 += r; r2 += r; }
	void  Move(FLA x, FLA y)						{ Move(Vect2D(x, y)); }

	FLT	X1()								const	{ return r1.x; }
	FLT Y1()								const	{ return r1.y; }
	FLT X2()								const	{ return r2.x; }
	FLT Y2()								const	{ return r2.y; }

	void SetX1(FLA x)								{ r1.x = x; }
	void SetY1(FLA y)								{ r1.y = y; }
	void SetX2(FLA x)								{ r2.x = x; }
	void SetY2(FLA y)								{ r2.y = y; }

	Vect2D R1()								const	{ return r1; }
	Vect2D R2()								const	{ return r2; }

	void SetR1(Vect2D_ r)							{ r1 = r; }
	void SetR2(Vect2D_ r)							{ r2 = r; }

	FLT Width()								const	{ return X2() - X1(); }
	FLT Height()							const	{ return Y2() - Y1(); }
	FLT	MaxDiameter()						const	{ return max(Width(), Height()); }
	FLT	MinDiameter()						const	{ return min(Width(), Height()); }
	FLT Volume()							const	{ return Width() * Height(); }

	Vect2D GetCenter()						const	{ return (r1 + r2) / 2; }

	BOOL Save(const char* file_name)		const; 
	BOOL Load(const char* file_name);

	#ifdef _DEBUG
	void Dump()								const	{ r1.Dump(); r2.Dump(); }
	#endif

	friend ostream& operator <<(ostream&, Box2D_);
	friend istream& operator >>(istream&, Box2D&);

private:
	Vect2D r1, r2;
};

//-----------------------------------------------------------------------------------

inline ostream& operator <<(ostream& stream, Box2D_ box)	{ return stream << "(" << box.r1 << ", " << box.r2 << ")"; }
inline istream& operator >>(istream& stream, Box2D& box)	{ return stream >> box.r1 >> box.r2; }

//-----------------------------------------------------------------------------------

static const Box2D BOX2D_0(0,0,0,0);	// zero box

//-----------------------------------------------------------------------------------

static inline BOOL operator < (Vect2D_ r, Box2D_ box) { return box > r; }	// r belongs to the box
static inline BOOL operator > (Vect2D_ r, Box2D_ box) { return box < r; }	// r don't belongs to the box

//-----------------------------------------------------------------------------------

inline Box2D::operator Box2D::SFLOAT()	const	
{	
	SFLOAT box; 
	box.r1 = Vect2D::SFLOAT(r1);  
	box.r2 = Vect2D::SFLOAT(r2);  
	return box; 
}

inline Box2D::operator Box2D::SDOUBLE() const	
{ 
	SDOUBLE box; 
	box.r1 = Vect2D::SDOUBLE(r1); 
	box.r2 = Vect2D::SDOUBLE(r2); 
	return box; 
}

//-----------------------------------------------------------------------------------

inline BOOL Box2D::operator >(Vect2D_ r) const		// r belongs to the box
{ 
	return	X1() <= r.x && r.x < X2() && Y1() <= r.y && r.y < Y2(); 
}	

inline BOOL Box2D::operator <(Vect2D_ r) const		// r don't belongs to the box
{ 
	return	r.x < X1() || X2() <= r.x || r.y < Y1() || Y2() <= r.y; 
}	

//---------------------------------------------------------------------------------------


#endif //___Box2D_h___

