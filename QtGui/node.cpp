#include <iostream>
#include "graph.h"

using namespace graph;

Node::Node(){}

Node::Node(string _Id, string _IP, string _Location, vector<ExitPoint> _exitPoints)
{
	Id = _Id;
	IP = _IP;
	Location = _Location;
	exitPoints = _exitPoints;
}

Node::~Node(){}