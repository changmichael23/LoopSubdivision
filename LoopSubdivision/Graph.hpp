#pragma once
#include "Summit.hpp"

class Graph {
private:
	std::vector<Summit*> *summitList;
	std::vector<Edge*> *edgeList;
	std::vector<Face*> *faceList;


public:
	Graph() {
		summitList = new std::vector<Summit*>;
		edgeList = new std::vector<Edge*>;
		faceList = new std::vector<Face*>;
	}
	Graph(std::vector<Summit*> *s, std::vector<Face*>* f, std::vector<Edge*>* e)
	{
		summitList = s;
		faceList = f;
		edgeList = e;
	}
	void setSummitList(std::vector<Summit*>* s)
	{
		summitList = s;
	}
	std::vector<Summit*> * getSummitList()
	{
		return summitList;
	}
	void setFaceList(std::vector<Face*> * f)
	{
		faceList = f;
	}
	std::vector<Face*> * getFaceList()
	{
		return faceList;
	}
	void setEdgeList(std::vector<Edge*>* e)
	{
		edgeList = e;
	}
	std::vector<Edge*> * getEdgeList()
	{
		return edgeList;
	}


	void visualiseGraph()
	{
		for (int i = 0; i < summitList->size(); i++)
		{
			std::cout << "Summit : " << std::endl;
			std::cout << summitList->at(i)->getPoint().toString() << std::endl;
			std::cout << summitList->at(i)->getColor() << std::endl;
			for (int j = 0; j < summitList->at(i)->getEdgesConnected()->size(); j++)
			{
				std::cout << "Edges : " << std::endl;
				std::cout << summitList->at(i)->getEdgesConnected()->at(j)->getPoints()[0].toString() << std::endl;
				std::cout << summitList->at(i)->getEdgesConnected()->at(j)->getPoints()[1].toString() << std::endl;
				std::cout << "Faces : " << std::endl;
				for (int k = 0; k < 3; k++)
				{
					std::cout << summitList->at(i)->getEdgesConnected()->at(j)->getFacesConnected()->at(0)->getPoints()[k].toString() << " ";
				}
				std::cout << "" << std::endl;
				std::cout << "Faces 1: " << std::endl;
				for (int k = 0; k < 3; k++)
				{
					std::cout << summitList->at(i)->getEdgesConnected()->at(j)->getFacesConnected()->at(1)->getPoints()[k].toString() << " ";
				}
				std::cout << "" << std::endl;

			}
		}
	}
};