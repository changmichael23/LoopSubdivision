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
	std::vector<Summit*> * getSummitList() const
	{
		return summitList;
	}
	void setFaceList(std::vector<Face*> * f)
	{
		faceList = f;
	}
	std::vector<Face*> * getFaceList() const
	{
		return faceList;
	}
	void setEdgeList(std::vector<Edge*>* e)
	{
		edgeList = e;
	}
	std::vector<Edge*> * getEdgeList() const
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

	static Graph* duplicateGraph(const Graph & graph)
	{
		Graph* duplicatedGraph = new Graph();

		std::vector<Face *> *tmpFaceList = new std::vector<Face *>();
		std::vector<Edge *> *tmpEdgeList = new std::vector<Edge *>();
		std::vector<Summit *> *tmpSummitList = new std::vector<Summit *>();

		for (unsigned i = 0; i < graph.getSummitList()->size(); ++i)
		{
			
			Summit* summit = graph.getSummitList()->at(i);

			tmpSummitList->push_back(summit);


			for (unsigned j = 0; j < summit->getEdgesConnected()->size(); ++j)
			{
				Edge * edge = summit->getEdgesConnected()->at(j);

				std::vector<Edge *>::iterator iteEdge = (std::find(tmpEdgeList->begin(), tmpEdgeList->end(), edge));
				if (iteEdge != tmpEdgeList->end())  //if found
				{
					//tmpEdgeList->at(iteEdge - tmpEdgeList->begin())->getSummitConnected()->push_back(summit); //achtung
					edge = tmpEdgeList->at(iteEdge - tmpEdgeList->begin());
					for (unsigned k = 0; k < edge->getFacesConnected()->size(); k++)
					{
						Face * face = edge->getFacesConnected()->at(k);
						
						std::vector<Summit *>::iterator iteSummit = std::find(face->getSummitsConnected()->begin(), face->getSummitsConnected()->end(), summit);
						if (iteSummit == face->getSummitsConnected()->end())
						{
							summit->getFacesConnected()->push_back(face);
							face->getSummitsConnected()->push_back(summit);
						}
						
					}
				}
				else
				{
					tmpEdgeList->push_back(edge);

					for (unsigned k = 0; k < edge->getFacesConnected()->size(); k++)
					{
						Face * face = edge->getFacesConnected()->at(k);
						std::vector<Face *>::iterator iteFace = (std::find(tmpFaceList->begin(), tmpFaceList->end(), face));
						if (iteFace != tmpFaceList->end()) // if found
						{
							tmpFaceList->at(iteFace - tmpFaceList->begin())->getEdgesConnected()->push_back(edge);

						}
						else
						{
							face->getEdgesConnected()->push_back(edge);
							tmpFaceList->push_back(face);

						}
						 
						std::vector<Summit *>::iterator iteSummit = std::find(face->getSummitsConnected()->begin(), face->getSummitsConnected()->end(), summit);
						if (iteSummit == face->getSummitsConnected()->end())
						{
							summit->getFacesConnected()->push_back(face);
							face->getSummitsConnected()->push_back(summit);
						}
					}
					

				}
				edge->getSummitsConnected()->push_back(summit);
				

			}

		}


		duplicatedGraph->summitList = tmpSummitList;
		duplicatedGraph->edgeList = tmpEdgeList;
		duplicatedGraph->faceList = tmpFaceList;

		duplicatedGraph->summitList->at(0)->getFacesConnected()->at(0)->setColor(Colore::blue);


		return duplicatedGraph;
	}
};