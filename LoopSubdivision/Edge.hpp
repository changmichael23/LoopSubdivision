#pragma once
#include "Face.hpp"
#include <vector>
class Edge
{
private:

	std::vector<Face*> * faceConnected = new std::vector<Face*>();
	Colore color;
	std::vector<Point> points;

public:
	Edge() {
	
		faceConnected = new std::vector<Face*>();
	}
	Edge(Colore c, std::vector<Face*> *f)
	{
		color = c;
		faceConnected = f;
	}
	Edge(std::vector<Face*> *f, std::vector<Point> p)
	{
		faceConnected = f;
		points = p;
	}
	Edge(std::vector<Point> p)
	{
		faceConnected = new std::vector<Face*>();
		points = p;
	}
	void setColor(const Colore & c)
	{
		color = c;
	}
	const Colore & getColor() const
	{
		return color;
	}
	void setFacesConnected(std::vector<Face*> * f)
	{
		faceConnected = f;
	}
	std::vector<Face*> * getFacesConnected()
	{
		return faceConnected;
	}
	std::vector<Point>& getPoints()
	{
		return points;
	}
	void setPoints(const std::vector<Point> & p)
	{
		points = p;
	}

};