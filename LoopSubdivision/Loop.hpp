#pragma once
#include "Graph.hpp"



class Loop
{

public:
	static Graph LoopSubdivision(const Graph & graph)
	{
		Graph loopGraph = graph;

		// update vertices
		std::vector<Point> tmpPointList = std::vector<Point>();
		for (unsigned i = 0; i < loopGraph.getSummitList()->size(); ++i)
		{
			Summit *  tempSummit = loopGraph.getSummitList()->at(i);
			Point newPoint = Point();

			Point sumPoint = Point();

			float n = tempSummit->getEdgesConnected()->size();
			float alpha = 0;
			if (n == 3)
			{
				alpha = 3 / 16.0f;
				
			}
			else
			{
				alpha = 1.0f / n*(5 / 8.0f - std::pow(3 / 8.0f + (0.25f)*cos(2.0f*3.14159 / n), 2));
			}

			for (unsigned j = 0; j < n; ++j)
			{
				sumPoint = sumPoint + Summit::GetOppositeSummit(tempSummit, tempSummit->getEdgesConnected()->at(j))->getPoint();
			}


			newPoint = ((1 - n*alpha)*tempSummit->getPoint()) + (alpha* sumPoint);
			tmpPointList.push_back(newPoint);


		}
		

		std::vector<Edge *> tmpLoopEdgeList = std::vector<Edge *>();
		for (unsigned i = 0; i < loopGraph.getEdgeList()->size(); ++i)
		{
			Edge * currentEdge = loopGraph.getEdgeList()->at(i);

			Point p1 = currentEdge->getSummitsConnected()->at(0)->getPoint();
			Point p2 = currentEdge->getSummitsConnected()->at(1)->getPoint();

			Point p3 = Summit::GetOppositeSummit(currentEdge, currentEdge->getFacesConnected()->at(0))->getPoint();
			Point p4 = Summit::GetOppositeSummit(currentEdge, currentEdge->getFacesConnected()->at(1))->getPoint();

			Point p = Point(3 / 8.0f * (p1 + p2) + 1 / 8.0f*(p3 + p4));
			std::cout << p.x << " " << p.y << " " << p.z << std::endl;
			currentEdge->setEdgePoint(new Summit(p));
			
			loopGraph.getSummitList()->push_back(currentEdge->getEdgePoint());

			// new edges
			Edge * tmpEdge1 = new Edge();
				
			Edge * tmpEdge2 = new Edge();
			tmpEdge1->getSummitsConnected()->push_back(currentEdge->getSummitsConnected()->at(0));
			tmpEdge1->getSummitsConnected()->push_back(currentEdge->getEdgePoint());


			tmpEdge2->getSummitsConnected()->push_back(currentEdge->getSummitsConnected()->at(1));
			tmpEdge2->getSummitsConnected()->push_back(currentEdge->getEdgePoint());

			

			tmpLoopEdgeList.push_back(tmpEdge1);
			tmpLoopEdgeList.push_back(tmpEdge2);

			// Connect to new Edge Point
			currentEdge->getEdgePoint()->getEdgesConnected()->push_back(tmpEdge1);
			currentEdge->getEdgePoint()->getEdgesConnected()->push_back(tmpEdge2);


			Summit * summit1 = currentEdge->getSummitsConnected()->at(0);
			Summit * summit2 = currentEdge->getSummitsConnected()->at(1);
			
			summit1->getEdgesConnected()->push_back(tmpEdge1);
			summit2->getEdgesConnected()->push_back(tmpEdge2);

			// Remove old edge 2 points
			std::vector<Edge *>::iterator iteEdge =
				std::find(summit1->getEdgesConnected()->begin(),
					summit1->getEdgesConnected()->end(),
					currentEdge);
			summit1->getEdgesConnected()->erase(iteEdge);

			std::vector<Edge *>::iterator iteEdge1 =
				std::find(summit2->getEdgesConnected()->begin(),
					summit2->getEdgesConnected()->end(),
					currentEdge);
			summit2->getEdgesConnected()->erase(iteEdge1);


		}

		loopGraph.getEdgeList()->clear();
		for (unsigned i = 0; i < tmpLoopEdgeList.size(); ++i)
		{
			loopGraph.getEdgeList()->push_back(tmpLoopEdgeList[i]);
		}
		std::vector<Face *> tmpLoopFaceList = std::vector<Face*>();
		for (unsigned i = 0; i < loopGraph.getFaceList()->size(); ++i)
		{
			Face * tmpFace = loopGraph.getFaceList()->at(i);

			Summit * s1 = tmpFace->getEdgesConnected()->at(0)->getEdgePoint();
			Summit * s2 = tmpFace->getEdgesConnected()->at(1)->getEdgePoint();
			Summit * s3 = tmpFace->getEdgesConnected()->at(2)->getEdgePoint();

			// Create last edges
			Edge * e1 = new Edge();
			Edge * e2 = new Edge();
			Edge * e3 = new Edge();
			
			e1->getSummitsConnected()->push_back(s1);
			e1->getSummitsConnected()->push_back(s2);

			e2->getSummitsConnected()->push_back(s2);
			e2->getSummitsConnected()->push_back(s3);

			e3->getSummitsConnected()->push_back(s1);
			e3->getSummitsConnected()->push_back(s3);


			s1->getEdgesConnected()->push_back(e1);
			s1->getEdgesConnected()->push_back(e3);

			s2->getEdgesConnected()->push_back(e1);
			s2->getEdgesConnected()->push_back(e2);

			s3->getEdgesConnected()->push_back(e2);
			s3->getEdgesConnected()->push_back(e3);

			loopGraph.getEdgeList()->push_back(e1);
			loopGraph.getEdgeList()->push_back(e2);
			loopGraph.getEdgeList()->push_back(e3);
		}

		// for each face, compute new faces and link edges
		for (unsigned i = 0; i < loopGraph.getFaceList()->size(); ++i)
		{
			Face * tmpFace = loopGraph.getFaceList()->at(i);

			// Create 3 exterior Face
			for (unsigned j = 0; j < tmpFace->getSummitsConnected()->size(); ++j)
			{
				Summit * tmpSummit = tmpFace->getSummitsConnected()->at(j);

				// search for all connected edges to this vertex
				
				std::vector<Edge *> *allEdges = Edge::searchAdjacentEdges(loopGraph.getEdgeList(), tmpSummit);
				std::vector<Edge *> *foundEdges = new std::vector<Edge *>();
				Face * newFace = new Face();

				
				for (int k = 0; k < tmpFace->getEdgesConnected()->size(); ++k)
				{
					Summit * tmpSum = tmpFace->getEdgesConnected()->at(k)->getEdgePoint();
					

					for (int l = 0; l < allEdges->size(); ++l)
					{
						if (tmpSum == allEdges->at(l)->getSummitsConnected()->at(0) ||
							tmpSum == allEdges->at(l)->getSummitsConnected()->at(1))
						{
							foundEdges->push_back(allEdges->at(l));

						}
					}
				}

				// Connect in Faces

				Summit * summit1 = Summit::GetOppositeSummit(tmpSummit, foundEdges->at(0));
				Summit * summit2 = Summit::GetOppositeSummit(tmpSummit, foundEdges->at(1));

				newFace->getSummitsConnected()->push_back(tmpSummit);

				newFace->getSummitsConnected()->push_back(summit1);
				newFace->getSummitsConnected()->push_back(summit2);

				newFace->getEdgesConnected()->push_back(foundEdges->at(0));
				newFace->getEdgesConnected()->push_back(foundEdges->at(1));

				Edge* newEdge = Edge::FindEdgeFromSummits(summit1, summit2, loopGraph.getEdgeList());

				//Edge * newEdge = new Edge();
				/*newEdge->getSummitsConnected()->push_back(summit1);
				newEdge->getSummitsConnected()->push_back(summit2);*/
				//newEdge->getFacesConnected()->push_back(newFace);

				/*summit1->getEdgesConnected()->push_back(newEdge);
				summit2->getEdgesConnected()->push_back(newEdge);*/

				newFace->getEdgesConnected()->push_back(newEdge);

				// Connect to Faces
				summit1->getFacesConnected()->push_back(newFace);
				summit2->getFacesConnected()->push_back(newFace);
				tmpSummit->getFacesConnected()->push_back(newFace);


				foundEdges->at(0)->getFacesConnected()->push_back(newFace);
				foundEdges->at(1)->getFacesConnected()->push_back(newFace);
				newEdge->getFacesConnected()->push_back(newFace);


				
				tmpLoopFaceList.push_back(newFace);
				
				// remove

				std::vector<Face *>::iterator iteFace = 
					std::find(tmpSummit->getFacesConnected()->begin(), 
						tmpSummit->getFacesConnected()->end(),
						tmpFace);
				tmpSummit->getFacesConnected()->erase(iteFace);

			}

			// Create Last interior Face

			Summit * s1 = tmpFace->getEdgesConnected()->at(0)->getEdgePoint();
			Summit * s2 = tmpFace->getEdgesConnected()->at(1)->getEdgePoint();
			Summit * s3 = tmpFace->getEdgesConnected()->at(2)->getEdgePoint();

			//// Create last edges
			//Edge * e1 = new Edge();
			//Edge * e2 = new Edge();
			//Edge * e3 = new Edge();

			 Edge * e1 = Edge::FindEdgeFromSummits(s1, s2, loopGraph.getEdgeList());
			 Edge * e2 = Edge::FindEdgeFromSummits(s2, s3, loopGraph.getEdgeList());
			 Edge * e3 = Edge::FindEdgeFromSummits(s1, s3, loopGraph.getEdgeList());

			/*e1->getSummitsConnected()->push_back(s1);
			e1->getSummitsConnected()->push_back(s2);

			e2->getSummitsConnected()->push_back(s2);
			e2->getSummitsConnected()->push_back(s3);

			e3->getSummitsConnected()->push_back(s1);
			e3->getSummitsConnected()->push_back(s3);
*/

			//s1->getEdgesConnected()->push_back(e1);
			//s1->getEdgesConnected()->push_back(e3);

			//s2->getEdgesConnected()->push_back(e1);
			//s2->getEdgesConnected()->push_back(e2);

			//s3->getEdgesConnected()->push_back(e2);
			//s3->getEdgesConnected()->push_back(e3);
			
			Face * lastFace = new Face();

			lastFace->getEdgesConnected()->push_back(e1);
			lastFace->getEdgesConnected()->push_back(e2);
			lastFace->getEdgesConnected()->push_back(e3);

			lastFace->getSummitsConnected()->push_back(s1);
			lastFace->getSummitsConnected()->push_back(s2);
			lastFace->getSummitsConnected()->push_back(s3);

			e1->getFacesConnected()->push_back(lastFace);
			e2->getFacesConnected()->push_back(lastFace);
			e3->getFacesConnected()->push_back(lastFace);
			s1->getFacesConnected()->push_back(lastFace);
			s2->getFacesConnected()->push_back(lastFace);
			s3->getFacesConnected()->push_back(lastFace);
			

			tmpLoopFaceList.push_back(lastFace);

			/*loopGraph.getEdgeList()->push_back(e1);
			loopGraph.getEdgeList()->push_back(e2);
			loopGraph.getEdgeList()->push_back(e3);*/

			// remove currentFace

			
		}

		loopGraph.getFaceList()->clear();
		for (unsigned i = 0; i < tmpLoopFaceList.size(); ++i)
		{
			loopGraph.getFaceList()->push_back(tmpLoopFaceList[i]);
		}


		

		for (unsigned i = 0; i < tmpPointList.size(); ++i)
		{
			Summit *  tempSummit = loopGraph.getSummitList()->at(i);
			tempSummit->setPoint(tmpPointList[i]);
		}


		return loopGraph;
	}
};