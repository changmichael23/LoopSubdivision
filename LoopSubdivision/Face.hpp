#pragma once
#include "Point.hpp"
#include "Colore.hpp"
#include <vector>
#include <iostream>

class Face {


private:
	Colore color;
	std::vector<Point> points;

public:
	Face() {}
	Face(Colore c, std::vector<Point> p)
	{
		color = c;

		points = p;
	}
	Face(std::vector<Point> p)
	{
		points = p;
	}
	const Colore & getColor() const
	{
		return color;
	}
	void setColor(const Colore & c)
	{
		color = c;
	}
	std::vector<Point> & getPoints()
	{
		return points;
	}
	void setPoints(const std::vector<Point> & p)
	{
		points = p;
	}
	void setPointInd(int ind,Point p)
	{
		points[ind] = p;
	}




};