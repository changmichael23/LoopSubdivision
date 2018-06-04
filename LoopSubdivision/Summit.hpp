

#include "Edge.hpp"
class Summit {
	// each point connected to edges
private:
	Point point;

	std::vector<Edge*> * edgesConnected;
	Colore color;

public:
	Summit() {
		edgesConnected = new std::vector<Edge*>();
	}
	Summit(Point p)
	{
		point = p;
		edgesConnected = new std::vector<Edge*>();
	}
	Summit(Colore c, Point p)
	{
		color = c;
		point = p;
	}

	Summit(Colore c, std::vector<Edge*> *e, Point p)
	{
		color = c;

		edgesConnected = e;
		point = p;
	}

	void setPoint(const Point & p)
	{
		point = p;
	}

	Point getPoint()
	{
		return point;
	}

	void setColor(const Colore & c)
	{
		color = c;
	}

	const Colore & getColor() const
	{
		return color;
	}

	void setEdgesConnected(std::vector<Edge*> * f)
	{
		edgesConnected = f;
	}

	std::vector<Edge*> * getEdgesConnected()
	{
		return edgesConnected;
	}

};