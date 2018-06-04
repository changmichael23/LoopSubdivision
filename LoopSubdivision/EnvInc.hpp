#pragma once
#include "Graph.hpp"
class EnvInc
{
private:
	Graph *graph;
	std::vector<Point> pointsLeft;
public:
	EnvInc()
	{
		graph = nullptr;
	}
	EnvInc(Graph *g, std::vector<Point> p)
	{
		graph = g;
		pointsLeft = p;
	}
	Graph *getGraph()
	{
		return graph;
	}
	void setGraph(Graph * g)
	{
		graph = g;
	}

	void initializeGraph()
	{
		for (int i = 0; i < 4; i++)
		{
			graph->getSummitList()->push_back(new Summit(pointsLeft.back()));
			pointsLeft.pop_back();
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = i + 1; j < 4; j++)
			{
				std::vector<Point> tmp;
				tmp.push_back(graph->getSummitList()->at(i)->getPoint());
				tmp.push_back(graph->getSummitList()->at(j)->getPoint());


				Edge *tmpEdge = new Edge(tmp);
				graph->getSummitList()->at(i)->getEdgesConnected()->push_back(tmpEdge);
				graph->getSummitList()->at(j)->getEdgesConnected()->push_back(tmpEdge);
				graph->getEdgeList()->push_back(tmpEdge);

			}
		}

		std::vector<Point> tmp;
		tmp.push_back(graph->getSummitList()->at(0)->getPoint());
		tmp.push_back(graph->getSummitList()->at(1)->getPoint());
		tmp.push_back(graph->getSummitList()->at(2)->getPoint());

		Face *tmpFace = new Face(tmp);


		graph->getEdgeList()->at(0)->getFacesConnected()->push_back(tmpFace);
		graph->getEdgeList()->at(1)->getFacesConnected()->push_back(tmpFace);
		graph->getEdgeList()->at(3)->getFacesConnected()->push_back(tmpFace);
		graph->getFaceList()->push_back(tmpFace);
		tmp.clear();

		tmp.push_back(graph->getSummitList()->at(0)->getPoint());
		tmp.push_back(graph->getSummitList()->at(1)->getPoint());
		tmp.push_back(graph->getSummitList()->at(3)->getPoint());

		tmpFace = new Face(tmp);


		graph->getEdgeList()->at(0)->getFacesConnected()->push_back(tmpFace);
		graph->getEdgeList()->at(2)->getFacesConnected()->push_back(tmpFace);
		graph->getEdgeList()->at(4)->getFacesConnected()->push_back(tmpFace);
		graph->getFaceList()->push_back(tmpFace);
		tmp.clear();

		tmp.push_back(graph->getSummitList()->at(0)->getPoint());
		tmp.push_back(graph->getSummitList()->at(2)->getPoint());
		tmp.push_back(graph->getSummitList()->at(3)->getPoint());

		tmpFace = new Face(tmp);

		graph->getEdgeList()->at(1)->getFacesConnected()->push_back(tmpFace);
		graph->getEdgeList()->at(2)->getFacesConnected()->push_back(tmpFace);
		graph->getEdgeList()->at(5)->getFacesConnected()->push_back(tmpFace);
		graph->getFaceList()->push_back(tmpFace);
		tmp.clear();

		tmp.push_back(graph->getSummitList()->at(1)->getPoint());
		tmp.push_back(graph->getSummitList()->at(2)->getPoint());
		tmp.push_back(graph->getSummitList()->at(3)->getPoint());

		tmpFace = new Face(tmp);


		graph->getEdgeList()->at(3)->getFacesConnected()->push_back(tmpFace);
		graph->getEdgeList()->at(4)->getFacesConnected()->push_back(tmpFace);
		graph->getEdgeList()->at(5)->getFacesConnected()->push_back(tmpFace);

		graph->getFaceList()->push_back(tmpFace);
		setNormal();
	}

	void removeBlueFromGraph()
	{

		for (int i = 0; i < graph->getSummitList()->size(); i++)
		{
			if (graph->getSummitList()->at(i)->getColor() != Colore(red))
			{
				for (int j = 0; j < graph->getSummitList()->at(i)->getEdgesConnected()->size(); j++)
				{
					if (graph->getSummitList()->at(i)->getEdgesConnected()->at(j)->getColor() != Colore(red))
					{
						for (int k = 0; k < graph->getSummitList()->at(i)->getEdgesConnected()->at(j)->getFacesConnected()->size(); k++)
						{
							if (graph->getSummitList()->at(i)->getEdgesConnected()->at(j)->getFacesConnected()->at(k)->getColor() == Colore(blue))
							{
								//remove Face from edge
								std::vector<Face*>* tmpF = graph->getSummitList()->at(i)->getEdgesConnected()->at(j)->getFacesConnected();
								tmpF->erase(tmpF->begin() + k);
								k--;
							}

						}
					}
					if (graph->getSummitList()->at(i)->getEdgesConnected()->at(j)->getColor() == Colore(blue))
					{
						//remove Edge from summit
						std::vector<Edge*>* tmpE = graph->getSummitList()->at(i)->getEdgesConnected();
						tmpE->erase(tmpE->begin() + j);
						j--;
					}
				}
			}
			if (graph->getSummitList()->at(i)->getColor() == Colore(blue))
			{
				//remove summit from graph
				std::vector<Summit*>* tmpS = graph->getSummitList();
				tmpS->erase(tmpS->begin() + i);
				i--;


			}
		}

		for (int i = 0; i < graph->getFaceList()->size(); i++)
		{
			if (graph->getFaceList()->at(i)->getColor() == Colore(blue))
			{
				std::vector<Face*>* tmpF = graph->getFaceList();
				tmpF->erase(tmpF->begin() + i);
				i--;
			}
		}
		for (int i = 0; i < graph->getEdgeList()->size(); i++)
		{
			if (graph->getEdgeList()->at(i)->getColor() == Colore(blue))
			{
				std::vector<Edge*>* tmpE = graph->getEdgeList();
				tmpE->erase(tmpE->begin() + i);
				i--;
			}
		}

	}

	int returnIndexTmpEdge(std::vector<Edge*> tmpE, Edge * e)
	{
		for (int i = 0; i < tmpE.size(); i++)
		{
			if (tmpE[i] == e)
			{
				return i;
			}
		}
		return -1;
	}

	void connectNewPoint(Point p)
	{
		std::vector<Face*> tmpFacesData = *new std::vector<Face*>();
		std::vector<Edge*> tmpEdgesData = *new std::vector<Edge*>();

		Summit *newS = new Summit(p);
		bool allRed = true;
		for (int i = 0; i < graph->getSummitList()->size(); i++)
		{
			if (graph->getSummitList()->at(i)->getColor() == Colore(purple))
			{
				allRed = false;
				Summit *tmpS = graph->getSummitList()->at(i);
				Edge *tmpEdger = new Edge();
				tmpEdger->getPoints().push_back(tmpS->getPoint());
				tmpEdger->getPoints().push_back(p);


				for (int j = 0; j < tmpS->getEdgesConnected()->size(); j++)
				{

					Edge *tmpE = tmpS->getEdgesConnected()->at(j);
					Face *tmpF = new Face();
					if (tmpE->getColor() == Colore(purple))
					{
						// Create new Face and push in global graph if not existing
						int indTmp = returnIndexTmpEdge(tmpEdgesData, tmpE);
						if (indTmp > -1)
						{
							tmpEdger->getFacesConnected()->push_back(tmpFacesData[indTmp]);
							bool exist = false;
							for (int i = 0; i < 2; i++)
							{
								if (tmpEdger->getPoints()[i] == tmpFacesData[indTmp]->getPoints()[0] ||
									tmpEdger->getPoints()[i] == tmpFacesData[indTmp]->getPoints()[1])
								{
									exist = true;
								}
								if (!exist)
								{
									tmpFacesData[indTmp]->getPoints().push_back(tmpEdger->getPoints()[i]);
								}
							}

						}
						else
						{
							tmpEdgesData.push_back(tmpE);
							tmpFacesData.push_back(tmpF);
							tmpEdger->getFacesConnected()->push_back(tmpF);
							tmpE->getFacesConnected()->push_back(tmpF);
							tmpF->getPoints().push_back(tmpEdger->getPoints()[0]);
							tmpF->getPoints().push_back(tmpEdger->getPoints()[1]);
						}


					}
				}
				tmpS->getEdgesConnected()->push_back(tmpEdger);
				newS->getEdgesConnected()->push_back(tmpEdger);
				graph->getEdgeList()->push_back(tmpEdger);


			}

		}
		if (!allRed)
		{
			graph->getSummitList()->push_back(newS);
		}

		for (int i = 0; i < tmpFacesData.size(); i++)
		{
			graph->getFaceList()->push_back(tmpFacesData[i]);
		}

	}

	void algo()
	{

		while (pointsLeft.size() > 0)
		{

			setColorGraph(pointsLeft.back());
			removeBlueFromGraph();
			Point tmp = pointsLeft.back();
			connectNewPoint(tmp);

			pointsLeft.pop_back();
			
		}setNormal();
	}

	void setNormal()
	{
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
				std::vector<float> vectNormal = vectorialProduct(ab, ac);


				Point tmp = getRandomInsidePoint(*graph->getFaceList()->at(i));
				std::vector<float> f0;
				f0.push_back(tmp.x-	 graph->getFaceList()->at(i)->getPoints()[j].x);
				f0.push_back(tmp.y - graph->getFaceList()->at(i)->getPoints()[j].y);
				f0.push_back(tmp.z - graph->getFaceList()->at(i)->getPoints()[j].z);

				if (scalarProduct(vectNormal, f0) > 0.0f)
				{
					vectNormal[0] = - vectNormal[0];
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

	void setColorGraph(Point p)
	{
		//Faces
		for (int i = 0; i < graph->getFaceList()->size(); i++)
		{
			//set normal



			if (isVisible(*graph->getFaceList()->at(i), p))
			{
				graph->getFaceList()->at(i)->setColor(Colore(blue));
			}
			else
			{
				graph->getFaceList()->at(i)->setColor(Colore(red));
			}
		}

		// Edges

		for (int i = 0; i < graph->getEdgeList()->size(); i++)
		{
			if (graph->getEdgeList()->at(i)->getFacesConnected()->at(0)->getColor() == Colore(blue))
			{
				if (graph->getEdgeList()->at(i)->getFacesConnected()->at(1)->getColor() == Colore(blue))
				{
					graph->getEdgeList()->at(i)->setColor(Colore(blue));
				}
				else
				{
					graph->getEdgeList()->at(i)->setColor(Colore(purple));
				}
			}
			else
			{
				if (graph->getEdgeList()->at(i)->getFacesConnected()->at(1)->getColor() == Colore(blue))
				{
					graph->getEdgeList()->at(i)->setColor(Colore(purple));
				}
				else
				{
					graph->getEdgeList()->at(i)->setColor(Colore(red));
				}
			}
		}

		// Summit
		int  count;
		for (int i = 0; i < graph->getSummitList()->size(); i++)
		{
			count = 0;
			for (int j = 0; j < graph->getSummitList()->at(i)->getEdgesConnected()->size(); j++)
			{
				if (graph->getSummitList()->at(i)->getEdgesConnected()->at(j)->getColor() == Colore(purple))
				{
					count++;
				}
			}

			if (count > 0)
			{
				graph->getSummitList()->at(i)->setColor(Colore(purple));
			}
			else
			{
				if (graph->getSummitList()->at(i)->getEdgesConnected()->at(0)->getColor() == Colore(red))
				{
					graph->getSummitList()->at(i)->setColor(Colore(red));
				}
				else
				{
					graph->getSummitList()->at(i)->setColor(Colore(blue));
				}
			}


		}


	}

	bool isVisible(Face f, Point p)
	{
		Point tmp = getRandomInsidePoint(f);
		std::vector<float> v1;       // Vecteur (f0,pointInt)
		std::vector<float> v2;		 // Vecteur (f0,nouveauPoint)

		v1.push_back(tmp.x - f.getPoints()[0].x);
		v1.push_back(tmp.y - f.getPoints()[0].y);
		v1.push_back(tmp.z - f.getPoints()[0].z);

		v2.push_back(p.x - f.getPoints()[0].x);
		v2.push_back(p.y - f.getPoints()[0].y);
		v2.push_back(p.z - f.getPoints()[0].z);

		std::vector<float> ab;
		std::vector<float> ac;

		ab.push_back(f.getPoints()[1].x - f.getPoints()[0].x);
		ab.push_back(f.getPoints()[1].y - f.getPoints()[0].y);
		ab.push_back(f.getPoints()[1].z - f.getPoints()[0].z);

		ac.push_back(f.getPoints()[2].x - f.getPoints()[0].x);
		ac.push_back(f.getPoints()[2].y - f.getPoints()[0].y);
		ac.push_back(f.getPoints()[2].z - f.getPoints()[0].z);


		std::vector<float> normalExt = vectorialProduct(ab, ac);
		float sca0 = scalarProduct(normalExt, v1);
		float sca1 = scalarProduct(normalExt, v2);
		bool sign = scalarProduct(normalExt, v1) >= 0.0f ? true : false;
		bool sign1 = scalarProduct(normalExt, v2) >= 0.0f ? true : false;
		if (sign == sign1)
		{
			return false;
		}
		return true;

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
		for (int i = 0; i < graph->getSummitList()->size(); i++)
		{
			bool isSame = false;
			for (int j = 0; j < 3; j++)
			{
				if (graph->getSummitList()->at(i)->getPoint().x == f.getPoints()[j].x && graph->getSummitList()->at(i)->getPoint().y == f.getPoints()[j].y
					&& graph->getSummitList()->at(i)->getPoint().z == f.getPoints()[j].z)
				{
					isSame = true;
				}
			}
			if (!isSame)
			{
				return graph->getSummitList()->at(i)->getPoint();
			}
		}
	}
};