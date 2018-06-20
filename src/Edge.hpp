#pragma once


class Summit;
class Face;

#include <vector>



class Edge
{
private:
	Summit * EdgePoint;
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
	void pushSummit(Summit * s)
	{
		std::vector<Summit *>::iterator iterSummit = std::find(summitsConnected->begin(), summitsConnected->end(), s);
		if (iterSummit == summitsConnected->end())
		{
			summitsConnected->push_back(s);
		}

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
	
	Summit* getEdgePoint()
	{
		return EdgePoint;
	}
	void setEdgePoint(Summit *s)
	{
		EdgePoint = s;
	}

	void setPoints(const std::vector<Point> & p)
	{
		points = p;
	}

	static std::vector<Edge *> * searchAdjacentEdges(std::vector<Edge *> *edges, Summit * s)
	{

		std::vector<Edge *> * tmpEdges = new std::vector<Edge*>();
		for (unsigned i = 0; i < edges->size(); ++i)
		{
			if (edges->at(i)->getSummitsConnected()->at(0) == s || edges->at(i)->getSummitsConnected()->at(1) == s)
			{
				tmpEdges->push_back(edges->at(i));
			}
		}

		return tmpEdges;
	}
	static Edge* FindEdgeFromSummits(Summit* s1, Summit* s2, std::vector<Edge*>* edges)
	{
		for (int i = 0; i < edges->size(); ++i)
		{
			if ((edges->at(i)->getSummitsConnected()->at(0) == s1 && edges->at(i)->getSummitsConnected()->at(1) == s2)
				|| (edges->at(i)->getSummitsConnected()->at(1) == s1 && edges->at(i)->getSummitsConnected()->at(0) == s2))
			{
				return edges->at(i);
			}
		}

		return nullptr;
	}
};