#include "Graph.h"
#include <fstream>
#include <map>

namespace Graph_lib
{

	void Shape::draw_lines() const
	{
		if(color().visibility() == Color::Transparency::visible && 1 < points.size())	// draw sole pixel?
			for(size_t i{1}; i < points.size(); ++i)
				fl_line(points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
	}

	void Shape::draw() const
	{
		Fl_Color old_color{fl_color()};
		// there is no good portable way of retrieving the current style
		fl_color(lcolor.as_int());
		fl_line_style(static_cast<int>(ls.style()), ls.width());
		draw_lines();
		fl_color(old_color);	// reset color (to previous) and style (to default)
		fl_line_style(0);
	}


	// does two lines (p1,p2) and (p3,p4) intersect?
	// if false return the distance of the intersect point as distances from p1
	inline std::pair<double, double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel)
	{
		auto x1{narrow_cast<double, decltype(Point::x)>(p1.x)};
		auto x2{narrow_cast<double, decltype(Point::x)>(p2.x)};
		auto x3{narrow_cast<double, decltype(Point::x)>(p3.x)};
		auto x4{narrow_cast<double, decltype(Point::x)>(p4.x)};
		auto y1{narrow_cast<double, decltype(Point::y)>(p1.y)};
		auto y2{narrow_cast<double, decltype(Point::y)>(p2.y)};
		auto y3{narrow_cast<double, decltype(Point::y)>(p3.y)};
		auto y4{narrow_cast<double, decltype(Point::y)>(p4.y)};

		auto denom{(y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1)};
		if(denom == 0){
			parallel = true;
			return std::pair<double, double>(0.0, 0.0);
		}
		parallel = false;
		return std::pair<double, double>
			{((x4 - x3)* (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom,
			((x2 - x1)* (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom};
	}


	//intersection between two line segments
	//Returns true if the two segments intersect,
	//in which case intersection is set to the point of intersection
	bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection)
	{
		bool parallel;
		std::pair<double, double> u{line_intersect(p1, p2, p3, p4, parallel)};
		if(parallel || u.first < 0 || u.first > 1 || u.second < 0 || u.second > 1){ return false; }
		intersection.x = p1.x + u.first * narrow_cast<double, decltype(Point::x)>(p2.x - p1.x);
		intersection.y = p1.y + u.first * narrow_cast<double, decltype(Point::y)>(p2.y - p1.y);
		return true;
	}

	void Polygon::add(Point p)
	{
		int np{number_of_points()};

		if(1 < np){	// check that the new line isn't parallel to the previous one
			if(p == point(np - 1)){ throw std::runtime_error("polygon point equal to previous point"); }
			bool parallel{};
			line_intersect(point(np - 1), p, point(np - 2), point(np - 1), parallel);
			if(parallel){ throw std::runtime_error("two polygon points lie in a straight line"); }
		}

		for(int i{1}; i < np - 1; ++i){	// check that new segment doesn't intersect and old point
			Point ignore(0, 0);
			if(line_segment_intersect(point(np - 1), p, point(i - 1), point(i), ignore)){
				throw std::runtime_error("intersect in polygon");
			}
		}

		Closed_polyline::add(p);
	}

	void Polygon::draw_lines() const
	{
		if(number_of_points() < 3){ throw std::runtime_error("less than 3 points in a Polygon"); }
		Closed_polyline::draw_lines();
	}

	void Open_polyline::draw_lines() const
	{
		if(fill_color().visibility() == Color::Transparency::visible){
			fl_color(fill_color().as_int());
			fl_begin_complex_polygon();
			for(int i{}; i < number_of_points(); ++i){
				fl_vertex(point(i).x, point(i).y);
			}
			fl_end_complex_polygon();
			fl_color(color().as_int());	// reset color
		}

		if(color().visibility() == Color::Transparency::visible)
			Shape::draw_lines();
	}

	void Closed_polyline::draw_lines() const
	{
		Open_polyline::draw_lines();

		if(color().visibility() == Color::Transparency::visible)	// draw closing line:
			fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y, point(0).x, point(0).y);
	}

	void Shape::move(int dx, int dy)
	{
		for(size_t i{}; i < points.size(); ++i){
			points[i].x += dx;
			points[i].y += dy;
		}
	}

	void Lines::draw_lines() const
	{
	//	if (number_of_points()%2==1) error("odd number of points in set of lines");
		if(color().visibility() == Color::Transparency::visible)
			for(int i{1}; i < number_of_points(); i += 2)
				fl_line(point(i - 1).x, point(i - 1).y, point(i).x, point(i).y);
	}

	void Text::draw_lines() const
	{
		auto ofnt{fl_font()};
		auto osz{fl_size()};
		fl_font(fnt.as_int(), fnt_sz);
		fl_draw(lab.c_str(), point(0).x, point(0).y);
		fl_font(ofnt, osz);
	}

	Function::Function(Fct funct, double r1, double r2, Point xy, int count, double xscale, double yscale)
	// graph f(x) for x in [r1:r2) using count line segments with (0,0) displayed at xy
	// x coordinates are scaled by xscale and y coordinates scaled by yscale
	{
		if(r2 - r1 <= 0){ throw std::runtime_error("bad graphing range"); }
		if(count <= 0){ throw std::runtime_error("non-positive graphing count"); }
		auto dist{(r2 - r1) / count};
		auto r{r1};
		for(int i{}; i < count; ++i){
			add(Point(xy.x + static_cast<int>(r * xscale), xy.y - static_cast<int>(funct(r) * yscale)));
			r += dist;
		}
	}

	void Rectangle::draw_lines() const
	{
		if(fill_color().visibility() == Color::Transparency::visible){	// fill
			fl_color(fill_color().as_int());
			fl_rectf(point(0).x, point(0).y, w, h);
			fl_color(color().as_int());	// reset color
		}

		if(color().visibility() == Color::Transparency::visible){	// edge on top of fill
			fl_color(color().as_int());
			fl_rect(point(0).x, point(0).y, w, h);
		}
	}

	Axis::Axis(Orientation d, Point xy, int length, int n, std::string lab)
		:label{Point(0, 0), lab}
	{
		if(length < 0) throw std::runtime_error("bad axis length");
		switch(d){
			case Axis::Orientation::x:
				{
					Shape::add(xy);	// axis line
					Shape::add(Point(xy.x + length, xy.y));	// axis line
					if(1 < n){
						int dist = length / n;
						int x = xy.x + dist;
						for(int i = 0; i < n; ++i){
							notches.add(Point(x, xy.y), Point(x, xy.y - 5));
							x += dist;
						}
					}
					// label under the line
					label.move(length / 3, xy.y + 20);
					break;
				}
			case Axis::Orientation::y:
				{
					Shape::add(xy);	// a y-axis goes up
					Shape::add(Point(xy.x, xy.y - length));
					if(1 < n){
						int dist = length / n;
						int y = xy.y - dist;
						for(int i = 0; i < n; ++i){
							notches.add(Point(xy.x, y), Point(xy.x + 5, y));
							y -= dist;
						}
					}
					// label at top
					label.move(xy.x - 10, xy.y - length - 10);
					break;
				}
			case Axis::Orientation::z:
				throw std::runtime_error("z axis not implemented");
		}
	}

	void Axis::draw_lines() const
	{
		Shape::draw_lines();	// the line
		notches.draw();	// the notches may have a different color from the line
		label.draw();	// the label may have a different color from the line
	}


	void Axis::set_color(Color c)
	{
		Shape::set_color(c);
		notches.set_color(c);
		label.set_color(c);
	}

	void Axis::move(int dx, int dy)
	{
		Shape::move(dx, dy);
		notches.move(dx, dy);
		label.move(dx, dy);
	}

	void Circle::draw_lines() const
	{
		if(fill_color().visibility() == Color::Transparency::visible){	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);
			fl_color(color().as_int());	// reset color
		}

		if(color().visibility() == Color::Transparency::visible){
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, r + r, r + r, 0, 360);
		}
	}


	void Ellipse::draw_lines() const
	{
		if(fill_color().visibility() == Color::Transparency::visible){	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, w + w - 1, h + h - 1, 0, 360);
			fl_color(color().as_int());	// reset color
		}

		if(color().visibility() == Color::Transparency::visible){
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, w + w, h + h, 0, 360);
		}
	}

	void draw_mark(Point xy, char c)
	{
		static const int dx = 4;
		static const int dy = 4;
		std::string m(1, c);
		fl_draw(m.c_str(), xy.x - dx, xy.y + dy);
	}

	void Marked_polyline::draw_lines() const
	{
		Open_polyline::draw_lines();
		for(int i = 0; i < number_of_points(); ++i)
			draw_mark(point(i), mark[i % mark.size()]);
	}
	/*
	void Marks::draw_lines() const
	{
		for (int i=0; i<number_of_points(); ++i)
			fl_draw(mark.c_str(),point(i).x-4,point(i).y+4);
	}
	*/


	std::map<std::string, Suffix::Encoding> suffix_map;

	int init_suffix_map()
	{
		suffix_map["jpg"] = Suffix::jpg;
		suffix_map["JPG"] = Suffix::jpg;
		suffix_map["jpeg"] = Suffix::jpg;
		suffix_map["JPEG"] = Suffix::jpg;
		suffix_map["gif"] = Suffix::gif;
		suffix_map["GIF"] = Suffix::gif;
		suffix_map["bmp"] = Suffix::bmp;
		suffix_map["BMP"] = Suffix::bmp;
		return 0;
	}

	Suffix::Encoding get_encoding(const std::string& s)
			// try to deduce type from file name using a lookup table
	{
		static int x = init_suffix_map();

		std::string::const_iterator p = find(s.begin(), s.end(), '.');
		if(p == s.end()) return Suffix::none;	// no suffix

		std::string suf(p + 1, s.end());
		return suffix_map[suf];
	}

	bool can_open(const std::string& s)
				// check if a file named s exists and can be opened for reading
	{
		std::ifstream ff{s.c_str()};
		return ff.is_open();
	}


	// somewhat over elaborate constructor
	// because errors related to image files can be such a pain to debug
	Image::Image(Point xy, std::string s, Suffix::Encoding e)
		:w{}, h{}, cx{}, cy{}, fn(xy, "")
	{
		add(xy);

		if(!can_open(s)){
			fn.set_label("cannot open \"" + s + '\"');
			p = new Bad_image(30, 20);	// the "error image"
			return;
		}

		if(e == Suffix::none) e = get_encoding(s);

		switch(e){
			case Suffix::jpg:
				p = new Fl_JPEG_Image(s.c_str());
				break;
			case Suffix::gif:
				p = new Fl_GIF_Image(s.c_str());
				break;
		//	case Suffix::bmp:
		//		p = new Fl_BMP_Image(s.c_str());
		//		break;
			default:	// Unsupported image encoding
				fn.set_label("unsupported file type \"" + s + '\"');
				p = new Bad_image(30, 20);	// the "error image"
		}
	}

	void Image::draw_lines() const
	{
		if(fn.label() != "") fn.draw_lines();

		if(w && h)
			p->draw(point(0).x, point(0).y, w, h, cx, cy);
		else
			p->draw(point(0).x, point(0).y);
	}

} // Graph