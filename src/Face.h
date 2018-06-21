#pragma once
#include "Point.h"
#include "Colore.h"
#include <vector>
#include <iostream>


class Summit;
class Edge;
class Face {


private:
	Colore color;
	std::vector<Point> points;

	std::vector<Summit*> *summitsConnected;
	std::vector<Edge*> *edgesConnected;

public:
	Face() {
		summitsConnected = new std::vector<Summit*>();
		edgesConnected = new std::vector<Edge*>();

	}
	Face(Colore c, std::vector<Point> p)
	{
		summitsConnected = new std::vector<Summit*>();
		edgesConnected = new std::vector<Edge*>();
		color = c;

		points = p;
	}
	Face(std::vector<Point> p)
	{
		summitsConnected = new std::vector<Summit*>();
		edgesConnected = new std::vector<Edge*>();
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

	std::vector<Summit *> * getSummitsConnected()
	{
		return summitsConnected;
	}
	std::vector<Edge *> * getEdgesConnected()
	{
		return edgesConnected;
	}



	void setPointInd(int ind,Point p)
	{
		points[ind] = p;
	}




};