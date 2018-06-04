#pragma once


class Summit;
class Face;

#include <vector>



class Edge
{
private:
	std::vector<Summit*> *summitsConnected = new std::vector<Summit*>();
	std::vector<Face*> * facesConnected = new std::vector<Face*>();
	Colore color;
	std::vector<Point> points;

public:
	Edge() {
	
	}
	Edge(Colore c, std::vector<Face*> *f)
	{
		color = c;
		facesConnected = f;
	}
	Edge(std::vector<Face*> *f, std::vector<Point> p)
	{
		facesConnected = f;
		points = p;
	}
	Edge(std::vector<Point> p)
	{
		facesConnected = new std::vector<Face*>();
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
		facesConnected = f;
	}
	std::vector<Face*> * getFacesConnected()
	{
		return facesConnected;
	}
	std::vector<Summit*> * getSummitsConnected()
	{
		return summitsConnected;
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