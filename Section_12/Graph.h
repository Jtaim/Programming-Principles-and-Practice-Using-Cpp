
#ifndef GRAPH_GUARD
#define GRAPH_GUARD

#include "fltk.h"
#include "Point.h"
#include "utility.h"
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>
//#include<cmath>

namespace Graph_lib
{
// defense against ill-behaved Linux macros:
#undef major
#undef minor

	struct Color
	{
		static enum class Color_type
		{
			red = FL_RED, blue = FL_BLUE, green = FL_GREEN,
			yellow = FL_YELLOW, white = FL_WHITE, black = FL_BLACK,
			magenta = FL_MAGENTA, cyan = FL_CYAN, dark_red = FL_DARK_RED,
			dark_green = FL_DARK_GREEN, dark_yellow = FL_DARK_YELLOW, dark_blue = FL_DARK_BLUE,
			dark_magenta = FL_DARK_MAGENTA, dark_cyan = FL_DARK_CYAN
		} color_type;
		static enum class Transparency { invisible = 0, visible = 255 } transparency;

		Color(Color_type color) : c{color}, v{Transparency::visible} {}
		Color(Color_type color, Transparency vv) : c{color}, v{vv} {}
		Color(int color) : c{static_cast<Color::Color_type>(color)}, v(Transparency::visible) {}
		Color(Transparency vv) : c{}, v{vv} {}
		Color() : c{Color::Color_type::red}, v(Transparency::visible) {}

		int as_int() const { return static_cast<int>(c); }
		Transparency visibility() const { return v; }
		void set_visibility(Transparency vv) { v = vv; }
	private:
		Transparency v;	// 0 or 255 for now
		Color_type c;
	};

	struct Line_style
	{
		static enum class Line_style_type
		{
			solid = FL_SOLID,			// -------
			dash = FL_DASH,				// - - - -
			dot = FL_DOT,				// ....... 
			dashdot = FL_DASHDOT,		// - . - . 
			dashdotdot = FL_DASHDOTDOT,	// -..-..
		} line_style;
		Line_style(Line_style_type style) :s{style}, w{} {}
		Line_style(Line_style_type style, int width) :s{style}, w{width} {}
		Line_style(int style) :s{static_cast<Line_style::Line_style_type>(style)}, w{} {}

		int width() const { return w; }
		Line_style_type style() const { return s; }
	private:
		Line_style_type s;
		int w;
	};

	class Font
	{
	public:
		static enum class Font_type
		{
			helvetica = FL_HELVETICA,
			helvetica_bold = FL_HELVETICA_BOLD,
			helvetica_italic = FL_HELVETICA_ITALIC,
			helvetica_bold_italic = FL_HELVETICA_BOLD_ITALIC,
			courier = FL_COURIER,
			courier_bold = FL_COURIER_BOLD,
			courier_italic = FL_COURIER_ITALIC,
			courier_bold_italic = FL_COURIER_BOLD_ITALIC,
			times = FL_TIMES,
			times_bold = FL_TIMES_BOLD,
			times_italic = FL_TIMES_ITALIC,
			times_bold_italic = FL_TIMES_BOLD_ITALIC,
			symbol = FL_SYMBOL,
			screen = FL_SCREEN,
			screen_bold = FL_SCREEN_BOLD,
			zapf_dingbats = FL_ZAPF_DINGBATS
		} font_type;

		Font(Font_type ff) :f{ff} {}
		Font(int ff) :f{static_cast<Font_type>(ff)} {}

		int as_int() const { return static_cast<int>(f); }
	private:
		Font_type f;
	};

	template<class T> class Vector_ref
	{
		std::vector<T*> v;
		std::vector<T*> owned;
	public:
		Vector_ref() {}

		Vector_ref(T* a, T* b = 0, T * c = 0, T * d = 0)
		{
			if(a != 0) push_back(a);
			if(b != 0) push_back(b);
			if(c != 0) push_back(c);
			if(d != 0) push_back(d);
		}

		~Vector_ref()
		{
			for(T* i : owned){ delete i; }
			//for(int i = 0; i < owned.size(); ++i) { delete owned[i]; }
		}

		void push_back(T& s) { v.push_back(&s); }
		void push_back(T* p) { v.push_back(p); owned.push_back(p); }

		// ???void erase(???)

		T& operator[](int i) { return *v[i]; }
		const T& operator[](int i) const { return *v[i]; }
		decltype(v.size()) size() const { return v.size(); }
	};

	typedef double Fct(double);

	class Shape
	{	// deals with color and style, and holds sequence of lines
	protected:
		Shape() {}
		Shape(std::initializer_list<Point> lst);  // add() the Points to this Shape

	//	Shape() : lcolor(fl_color()),
	//		ls(0),
	//		fcolor(Color::invisible) { }

		void add(Point p) { points.push_back(p); }
		void set_point(int i, Point p) { points.at(i) = p; }
	public:
		void draw() const;					// deal with color and draw_lines
		virtual void move(int dx, int dy);	// move the shape +=dx and +=dy
		void set_color(Color col) { lcolor = col; }
		Color color() const { return lcolor; }
		void set_style(Line_style sty) { ls = sty; }
		Line_style style() const { return ls; }
		void set_fill_color(Color col) { fcolor = col; }
		Color fill_color() const { return fcolor; }
		Point point(int i) const { return points[i]; }
		int number_of_points() const { return int(points.size()); }

		virtual ~Shape() {}
		/*
		struct Window* attached;
		Shape(const Shape& a)
			:attached(a.attached), points(a.points), line_color(a.line_color), ls(a.ls)
		{
			if (a.attached)error("attempt to copy attached shape");
		}
		*/
		Shape(const Shape&) = delete;
		Shape& operator=(const Shape&) = delete;

	protected:
		virtual void draw_lines() const;	// simply draw the appropriate lines

	private:
		std::vector<Point> points;	// not used by all shapes
		Color lcolor{static_cast<Color::Color_type>(fl_color())};
		Line_style ls{Line_style::Line_style_type::solid};
		Color fcolor{Color::Transparency::invisible};

	//	Shape(const Shape&);
	//	Shape& operator=(const Shape&);
	};

	struct Function: Shape
	{
// the function parameters are not stored
		Function(Fct f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
		//Function(Point orig, Fct f, double r1, double r2, int count, double xscale = 1, double yscale = 1);	
	};

	struct Fill
	{
		Fill() : no_fill{true}, fcolor{} {}
		Fill(Color c) :no_fill{false}, fcolor{c} {}

		void set_fill_color(Color col) { fcolor = col; }
		Color fill_color() { return fcolor; }
	protected:
		bool no_fill;
		Color fcolor;
	};

	struct Line: Shape
	{
		Line(Point p1, Point p2) { add(p1); add(p2); }
	};

	struct Rectangle: Shape
	{

		Rectangle(Point xy, int ww, int hh) :w{ww}, h{hh}
		{
			if(h <= 0 || w <= 0) throw std::runtime_error("Bad rectangle: non-positive side");
			add(xy);
		}
		Rectangle(Point x, Point y) :w{y.x - x.x}, h{y.y - x.y}
		{
			if(h <= 0 || w <= 0) throw std::runtime_error("Bad rectangle: first point is not top left");
			add(x);
		}
		void draw_lines() const;

	//	void set_fill_color(Color col) { fcolor = col; }
	//	Color fill_color() { return fcolor; }

		int height() const { return h; }
		int width() const { return w; }
	private:
		int h;			// height
		int w;			// width
	//	Color fcolor;	// fill color; 0 means "no fill"
	};

	bool intersect(Point p1, Point p2, Point p3, Point p4);


	struct Open_polyline: Shape
	{	// open sequence of lines
		using Shape::Shape;
		void add(Point p) { Shape::add(p); }
		void draw_lines() const;
	};

	struct Closed_polyline: Open_polyline
	{	// closed sequence of lines
		using Open_polyline::Open_polyline;
		void draw_lines() const;

	//	void add(Point p) { Shape::add(p); }
	};


	struct Polygon: Closed_polyline
	{	// closed sequence of non-intersecting lines
		using Closed_polyline::Closed_polyline;
		void add(Point p);
		void draw_lines() const;
	};

	struct Lines: Shape
	{	// independent lines
		Lines() {}
		Lines(std::initializer_list<Point> lst) : Shape{lst} { if(lst.size() % 2) throw std::runtime_error("odd number of points for Lines"); }
		void draw_lines() const;
		void add(Point p1, Point p2) { Shape::add(p1); Shape::add(p2); }
	};

	struct Text: Shape
	{
// the point is the bottom left of the first letter
		Text(Point x, const std::string& s) : lab{s} { add(x); }

		void draw_lines() const;

		void set_label(const std::string& s) { lab = s; }
		std::string label() const { return lab; }

		void set_font(Font f) { fnt = f; }
		Font font() const { return Font(fnt); }

		void set_font_size(int s) { fnt_sz = s; }
		int font_size() const { return fnt_sz; }
	private:
		std::string lab;	// label
		Font fnt{fl_font()};
		int fnt_sz{(14 < fl_size()) ? fl_size() : 14};	// at least 14 point
	};


	struct Axis: Shape
	{
// representation left public
		enum class Orientation { x, y, z };
		Axis(Orientation d, Point xy, int length, int nummber_of_notches = 0, std::string label = "");

		void draw_lines() const;
		void move(int dx, int dy);

		void set_color(Color c);

		Text label;
		Lines notches;
	//	Orientation origin;
	//	int notches;
	};

	struct Circle: Shape
	{
		Circle(Point p, int rr)	// center and radius
			:r{rr}
		{
			add(Point{p.x - r, p.y - r});
		}

		void draw_lines() const;

		Point center() const { return {point(0).x + r, point(0).y + r}; }

		void set_radius(int rr) { r = rr; }
		int radius() const { return r; }
	private:
		int r;
	};


	struct Ellipse: Shape
	{
		Ellipse(Point p, int ww, int hh)	// center, min, and max distance from center
			:w{ww}, h{hh} {
			add(Point{p.x - ww, p.y - hh});
		}

		void draw_lines() const;

		Point center() const { return{point(0).x + w, point(0).y + h}; }
		Point focus1() const { return{center().x + int(sqrt(narrow_cast<double, int>(w * w - h * h))), center().y}; }
		Point focus2() const { return{center().x - int(sqrt(narrow_cast<double, int>(w * w - h * h))), center().y}; }

		void set_major(int ww) { w = ww; }
		int major() const { return w; }
		void set_minor(int hh) { h = hh; }
		int minor() const { return h; }
	private:
		int w;
		int h;
	};
	/*
	struct Mark : Text {
		static const int dw = 4;
		static const int dh = 4;
		Mark(Point xy, char c) : Text(Point(xy.x-dw, xy.y+dh),string(1,c)) {}
	};
	*/

	struct Marked_polyline: Open_polyline
	{
		Marked_polyline(const std::string& m) :mark(m) {}
		void draw_lines() const;
	private:
		std::string mark;
	};

	struct Marks: Marked_polyline
	{
		Marks(const std::string& m) :Marked_polyline(m)
		{
			set_color(Color(Color::Transparency::invisible));
		}
	};

	struct Mark: Marks
	{
		Mark(Point xy, char c) : Marks(std::string(1, c)) { add(xy); }
	};

	/*

	struct Marks : Shape {
		Marks(char m) : mark(string(1,m)) { }
		void add(Point p) { Shape::add(p); }
		void draw_lines() const;
	private:
		string mark;
	};
	*/

	struct Bad_image: Fl_Image
	{
		Bad_image(int h, int w) : Fl_Image(h, w, 0) {}
		void draw(int x, int y, int, int, int, int) { draw_empty(x, y); }
	};

	struct Suffix
	{
		enum Encoding { none, jpg, gif, bmp };
	};

	Suffix::Encoding get_encoding(const std::string& s);

	struct Image: Shape
	{
		Image(Point xy, std::string s, Suffix::Encoding e = Suffix::none);
		~Image() { delete p; }
		void draw_lines() const;
		void set_mask(Point xy, int ww, int hh) { w = ww; h = hh; cx = xy.x; cy = xy.y; }
		void move(int dx, int dy) { Shape::move(dx, dy); p->draw(point(0).x, point(0).y); }
	private:
		int w, h, cx, cy; // define "masking box" within image relative to position (cx,cy)
		Fl_Image* p;
		Text fn;
	};

} // Graph_lib
#endif //GRAPH_GUARD

