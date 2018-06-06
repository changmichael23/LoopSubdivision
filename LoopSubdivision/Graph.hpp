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


	std::vector<float> vectorialProduct(std::vector<float> f1, std::vector<float> f2)
	{
		if (f1.size() != 3 || f2.size() != 3)
		{
			std::cout << "Erreur taille produit vectoriel" << std::endl;
			return f1;
		}
		else
		{
			std::vector<float> tmp;
			tmp.push_back(f1[1] * f2[2] - f1[2] * f2[1]);
			tmp.push_back(f1[2] * f2[0] - f1[0] * f2[2]);
			tmp.push_back(f1[0] * f2[1] - f1[1] * f2[0]);
			return tmp;
		}
	}

	float scalarProduct(std::vector<float> f1, std::vector<float> f2)
	{
		float tmp = 0.0f;
		for (int i = 0; i < f1.size(); i++)
		{
			tmp += f1[i] * f2[i];
		}
		return tmp;
	}

	Point getRandomInsidePoint(Face f)
	{
		for (int i = 0; i < getSummitList()->size(); i++)
		{
			bool isSame = false;
			for (int j = 0; j < 3; j++)
			{
				if (getSummitList()->at(i)->getPoint().x == f.getPoints()[j].x && getSummitList()->at(i)->getPoint().y == f.getPoints()[j].y
					&& getSummitList()->at(i)->getPoint().z == f.getPoints()[j].z)
				{
					isSame = true;
				}
			}
			if (!isSame)
			{
				return getSummitList()->at(i)->getPoint();
			}
		}
	}

	static void updateNormals(Graph * graph)
	{

		for (unsigned i = 0; i < graph->getFaceList()->size(); ++i)
		{
			Face * tmpFace = graph->getFaceList()->at(i);
			tmpFace->getPoints().clear();
			std::vector<Point> tmpPoint = std::vector<Point>();
			for (unsigned j = 0; j < 3; ++j)
			{

				
				tmpPoint.push_back(tmpFace->getSummitsConnected()->at(j)->getPoint());
					
			}

			tmpFace->setPoints(tmpPoint);
		}

		for (int i = 0; i < graph->getFaceList()->size(); i++)
		{
			for (int j = 0; j < 3; j++)
			{

				std::vector<float> ab;
				std::vector<float> ac;

				ab.push_back(graph->getFaceList()->at(i)->getPoints()[(j + 1) % 3].x - graph->getFaceList()->at(i)->getPoints()[j].x);
				ab.push_back(graph->getFaceList()->at(i)->getPoints()[(j + 1) % 3].y - graph->getFaceList()->at(i)->getPoints()[j].y);
				ab.push_back(graph->getFaceList()->at(i)->getPoints()[(j + 1) % 3].z - graph->getFaceList()->at(i)->getPoints()[j].z);

				ac.push_back(graph->getFaceList()->at(i)->getPoints()[(j + 2) % 3].x - graph->getFaceList()->at(i)->getPoints()[j].x);
				ac.push_back(graph->getFaceList()->at(i)->getPoints()[(j + 2) % 3].y - graph->getFaceList()->at(i)->getPoints()[j].y);
				ac.push_back(graph->getFaceList()->at(i)->getPoints()[(j + 2) % 3].z - graph->getFaceList()->at(i)->getPoints()[j].z);
				std::vector<float> vectNormal = graph->vectorialProduct(ab, ac);


				Point tmp = graph->getRandomInsidePoint(*graph->getFaceList()->at(i));
				std::vector<float> f0;
				f0.push_back(tmp.x - graph->getFaceList()->at(i)->getPoints()[j].x);
				f0.push_back(tmp.y - graph->getFaceList()->at(i)->getPoints()[j].y);
				f0.push_back(tmp.z - graph->getFaceList()->at(i)->getPoints()[j].z);

				if (graph->scalarProduct(vectNormal, f0) > 0.0f)
				{
					vectNormal[0] = -vectNormal[0];
					vectNormal[1] = -vectNormal[1];
					vectNormal[2] = -vectNormal[2];
				}


				Point tmpP = Point(graph->getFaceList()->at(i)->getPoints()[j].x,
					graph->getFaceList()->at(i)->getPoints()[j].y,
					graph->getFaceList()->at(i)->getPoints()[j].z, vectNormal[0], vectNormal[1], vectNormal[2]);

				graph->getFaceList()->at(i)->setPointInd(j, tmpP);

			}
		}


	}
};