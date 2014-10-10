// This file does not need to be modified
// C.P.
/////////////////////////////////////////
#ifndef __OBJECT_H__
#define __OBJECT_H__

struct Color
{
	double r; // Red
	double g; // Green
	double b; // Blue
	double a; // Alpha
	Color() : r(1.0), g(1.0), b(1.0), a(0.0) {}
	Color(const double & nr, const double & ng, const double & nb, const double & na = 0.0)
		: r(nr), g(ng), b(nb), a(na)
	{}
};

//Default color definitions for easy descriptive names
#define WHITE Color(1.0, 1.0, 1.0)
#define BLACK Color(0.0, 0.0, 0.0)
#define RED Color(1.0, 0.0, 0.0)
#define GREEN Color(0.0, 1.0, 0.0)
#define BLUE Color(0.0, 0.0, 1.0)
#define YELLOW Color(1.0, 1.0, 0.0)
#define PINK Color(1.0, 0.0, 1.0)
#define CYAN Color(0.0, 1.0, 1.0)
#define ORANGE Color(1.0, 0.5, 0.0)
#define VIOLET Color(0.5, 0.0, 1.0)
#define GRAY Color(0.5, 0.5, 0.5)
#define BROWN Color(0.6, 0.3, 0.0)

//Base class of a 2D object
struct Object2D
{
	Color color;
	Object2D() : color() {}
	Object2D(const Color & c) : color(c) {}

	virtual void move(double dx, double dy) = 0;

	// Renders the object
	virtual void render() const;
	virtual void render(const Color & col) const;

	virtual ~Object2D() {}
};

struct Point2D : public Object2D
{
	double x;
	double y;

	Point2D() : Object2D(), x(0.0), y(0.0) {}
	Point2D(const double & nx, const double & ny, const Color & col = WHITE) 
		: Object2D(col), x(nx), y(ny)
	{}
	
	// Accessor Functions 
	double magnitude() const;
	double magnitude2() const;
	Point2D normalized() const;

	// Mutator Functions
	Point2D operator+(const Point2D & rhs) const { return Point2D(x + rhs.x, y + rhs.y); }
	Point2D operator-(const Point2D & rhs) const { return Point2D(x - rhs.x, y - rhs.y); }
	Point2D operator*(double val) const { return Point2D(x * val, y * val); }
	Point2D operator/(double val) const { return Point2D(x / val, y / val); }
	Point2D operator+=(const Point2D & rhs) { x += rhs.x; y += rhs.y; return *this; }
	Point2D operator-=(const Point2D & rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	Point2D operator*=(double val) { x *= val; y *= val; return *this; }
	Point2D operator/=(double val) { x /= val; y /= val; return *this; }
	void set(const Point2D & pos);
	virtual void move(double dx, double dy);

	// Graphical Functions
	virtual void render() const;
	virtual void render(const Color & col) const;

	virtual ~Point2D() {}
};

//Base class of a 2D shape
struct Shape2D : public Object2D
{
	bool filled; // Determines whether an object is filled with color

	Shape2D() : Object2D(), filled(false) {}
	Shape2D(const Color & c, bool f = false)
		: Object2D(c), filled(f)
	{}
	
	virtual void present() const = 0; // Helper function to render the shape

	virtual ~Shape2D() {}
};

struct Circle2D : public Shape2D
{
	Point2D center;
	double radius;

	Circle2D() : Shape2D(), center(), radius(0.0) {}
	Circle2D(const Point2D & p, double radius, Color col = Color(), bool fill = false)
		: Shape2D(col, fill), center(p), radius(radius)
	{}

	// Accessor Functions 
	double perimeter() const;
	double area() const;
	
	// Mutator Functions
	void set(const Point2D & pos);
	virtual void move(double dx, double dy);

	// Graphical Functions
	virtual void present() const;
	virtual void render() const;
	virtual void render(const Color & col) const;

	virtual ~Circle2D() {}
};

struct Balls2D : public Circle2D
{
	Circle2D c;
	double x;
	double y;
	
	Balls2D() : Circle2D(), x(0.0), y(0.0)
	{}
	
	Balls2D(Circle2D c1, double a, double b) : x(a), y(b)
	{
		c = Circle2D(c1.center, c1.radius, c1.color, true);
	}
	
	virtual void render() const;
	virtual void move(double dx, double dy);
	virtual ~Balls2D() {}
};

#endif
