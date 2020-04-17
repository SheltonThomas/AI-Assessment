#pragma once
#include "raylib.h"
#include <vector>
#include <algorithm>

namespace pathfinding
{
	struct Node;

	struct Edge
	{
		Node* target;
		float cost;
	};

	struct Node
	{
		Vector2 position;

		float gScore = 0.0f;
		//## Add hScore ##//
		float hScore = 0.0f;
		//## Add fScore ##//
		float fScore = 0.0f;
		Node* previous = nullptr;

		std::vector<Edge> connections;
	};

	int findManhattan(Node * currentNode, Node * goal)
	{
		return abs(currentNode->position.x - goal->position.x) + abs(currentNode->position.y - goal->position.y);
	}

	std::vector<Node*> pathFinding(Node* startNode, Node* endNode)
	{
		//Validate the input
		if (startNode == nullptr || endNode == nullptr) {
			return std::vector<Node*>();
		}

		if (startNode == endNode) {
			std::vector<Node*> singleNodePath;
			singleNodePath.push_back(startNode);
			return singleNodePath;
		}

		//Initialize the starting node
		startNode->gScore = 0;
		startNode->previous = nullptr;

		//Create our temporary lists for storing nodes
		std::vector<Node*> openList;
		std::vector<Node*> closedList;

		//Add the starting node to openList
		openList.push_back(startNode);

		while (!openList.empty()) {
			//Set the current node to the first node in the openList
			Node* currentNode = openList.front();
			//Remove currentNode from openList
			openList.erase(openList.begin());
			//Add currentNode to closedList
			closedList.push_back(currentNode);

			//If the destination node was added to the closed list,
			//the shortest path has been found
			if (currentNode == endNode) {
				break;
			}

			//For each Edge e in currentNode's connections
			for (Edge e : currentNode->connections) {
				//If the target node is in the closedList, ignore it
				if (std::find(closedList.begin(), closedList.end(), e.target) != closedList.end()) {
					continue;
				}
				//Temporarily calculate the target node's G Score
				float gScore = currentNode->gScore + e.cost;
				//## Temporarily calculate the target node's H Score ##//
				float hScore = findManhattan(e.target, endNode);
				//## Temporarily calculate the target node's F Score ##//
				float fScore = gScore + hScore;
				//If the target node is not in the openList, update it
				if (std::find(openList.begin(), openList.end(), e.target) == openList.end()) {
					//Update the target node's G Score from the temporary value
					e.target->gScore = gScore;
					//## Update the target node's H Score from the temporary value ##//
					//## Update the target node's F Score from the temporary value ##//
					e.target->fScore = fScore;
					//Set the target node's previous to currentNode
					e.target->previous = currentNode;
					//Find the earliest point we should insert the node to the list to keep it sorted
					//## Change this to use F Score instead of G Score ##//
					auto insertionPos = openList.end();
					for (auto i = openList.begin(); i != openList.end(); i++) {
						if (e.target->fScore < (*i)->fScore) {
							insertionPos = i;
							break;
						}
					}
					//Insert the node at the appropriate position
					openList.insert(insertionPos, e.target);
				}
				//Otherwise the target node IS in the open list
				else {
					//Compare the new G Score to the old one before updating
					//## Change this to use F Score instead of G Score ##//
					if (fScore < e.target->fScore) {
						//Update the target node's G Score from the temporary value
						e.target->gScore = gScore;
						//## Update the target node's H Score from the temporary value ##//
						//## Update the target node's F Score from the temporary value ##//
						e.target->fScore = fScore;
						//Set the target node's previous to currentNode
						e.target->previous = currentNode;
					}
				}
			}
		}

		//Create path in reverse from endNode to startNode
		std::vector<Node*> path;
		Node* currentNode = endNode;

		while (currentNode != nullptr) {
			//Add the current node to the beginning of the path
			path.insert(path.begin(), currentNode);
			//Go to the previous node
			currentNode = currentNode->previous;
		}

		return path;
	}

	void drawNode(Node* node, Vector2 scale, bool selected = false)
	{
		if (node == nullptr) {
			return;
		}

		static char buffer[10];
		sprintf_s(buffer, "%.0f", node->gScore);

		int x = (int)node->position.x * scale.x + scale.x / 2;
		int y = (int)node->position.y * scale.y + scale.y / 2;

		//Draw the circle for the outline
		DrawCircle(x, y, (scale.x + scale.y) * 0.125, YELLOW);

		//Draw the inner circle
		float radius = (scale.x + scale.y) * 0.1125f;
		if (selected)
			DrawCircle(x, y, radius, BROWN);
		else
			DrawCircle(x, y, radius, BLACK);

		//Draw the text
		int textX = x - scale.x * 0.1f;
		int textY = y - scale.y * 0.1f;
		int fontSize = (scale.x + scale.y) * 0.1f;
		DrawText(buffer, textX, textY, fontSize, WHITE);
	}

	void drawGraph(Node* node, Vector2 scale, std::vector<Node*>* drawnList = new std::vector<Node*>())
	{
		if (node == nullptr) {
			return;
		}

		drawNode(node, scale);
		drawnList->push_back(node);

		float x = node->position.x * scale.x + scale.x / 2;
		float y = node->position.y * scale.y + scale.y / 2;

		//For each Edge in this node's connections
		for (Edge e : node->connections) {
			//Get target position
			float tx = e.target->position.x * scale.x + scale.x / 2;
			float ty = e.target->position.y * scale.y + scale.y / 2;
			//Draw the Edge
			DrawLineEx({ x, y }, { tx, ty }, (scale.x + scale.y) * 0.01f, WHITE);
			//Draw the cost
			static char buffer[10];
			sprintf_s(buffer, "%.0f", e.cost);
			int fontSize = (scale.x + scale.y) * 0.1f;
			DrawText(buffer, (int)((x + tx) / 2), (int)((y + ty) / 2), fontSize, WHITE);
			//Draw the target node
			if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
				drawGraph(e.target, scale, drawnList);
			}
		}
	}
}