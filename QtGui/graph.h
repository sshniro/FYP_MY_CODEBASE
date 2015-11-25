#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <thread>
#include "QtCore\qdebug.h"

using namespace std;

namespace graph{
	class Graph;
	class Node;

	struct ExitPoint
	{
		int sector;
		pair<int, int> topLeftPoint;
		pair<int, int> bottomRightPoint;
	};

	class Graph
	{
	protected:
		//collection of nodes as <node_id, node_obj>
		map<string, Node> Nodes;

		//map < base-node-id, sector < list < pair < ajecent-node-id, weight > > > >
		map<string, vector<vector<pair<string, int>>>> Edges;

	public:
		Graph();
		~Graph();

		/*
		check whether graph is already configured
		returns : boolean
		*/
		bool isConfigured();

		/*
		initialte graph data structure by retreaving data from data source
		*/
		int initGraph();

		/*
		get all nodes in Graph space.
		returns	: vector<model::Node objects>
		*/
		vector<Node> getAllNodes();

		/*
		get keys of all nodes in Graph space.
		returns	: vector<string>
		*/
		vector<string> getKeysOfAllNodes();

		/*
		get Node from id.
		returns	: model::Node object - exception if not found
		params	: node id (integer)
		*/
		Node * getNode(string node_id);

		/*
		add Node to Graph::Nodes collection.
		returns	: boolian value (true if success, false if error in process) - exception if Node.Id already exist
		params	: model::Node object
		*/
		bool addNode(Node node);

		/*
		edit a Node in Graph::Nodes collection.
		returns	: boolian value (true if success, false if error in process) - exception if Node not found
		params	: model::Node object
		*/
		bool editNode(Node node);

		/*
		delete a Node from Graph::Nodes collection.
		returns	: boolian value (true if success, false if error in process) - exception if relevent Node not found
		params	: node id (integer)
		*/
		bool deleteNode(string node_id);

		/*
		get the adgecency list for the graph.
		returns	: map<base node id, vector<adgecent node id>> - NULL if not any
		*/
		map<string, vector<vector<pair<string, int>>>> getAdgecencyList();

		/*
		get all adgecent nodes' ids of a given node.
		returns	: vector<adgecent node id> - NULL if not any - exception if base node id not found
		params	: base node id (integer)
		*/
		vector<vector<pair<string, int>>> getNeighbours(string base_node_id);

		/*
		add new model::Node as an adgecent node to the given node.
		returns	: boolian (true if success, false otherwise) - exception if base node not found or new node id already exist in node space
		params	: base node id (integer), new node object(model::Node)
		*/
		bool addNeighbour(string base_node_id, Node new_node, int location_in_metrix, int weight);

		/*
		add existing model::Node as an adgecent node to the given node.
		returns	: boolian (true if success, false otherwise) - exception if base node or new node not found
		params	: base node id (integer), new node id(integer)
		*/
		bool addNeighbour(string base_node_id, string new_node_id, int location_in_metrix, int weight);

		/*
		remove a model::Node from the adgecent node list of the given node.
		returns	: boolian (true if success, false otherwise) - exception if base node or removing node not found
		params	: base node id (integer), removing node id(integer)
		*/
		bool removeNeighbour(string base_node_id, string removing_id);

		/*
		check if two model::Node s are adgecent.
		returns	: boolian (true if success, false otherwise) - exception if nodes not found
		params	: node_base id (integer), node2 id(integer)
		*/
		bool isNeighbour(string node1_id, string node2_id);

	};

	class Node
	{
	public:
		Node();
		Node(string _Id, string _IP, string _Location, vector<ExitPoint> _exitPoints);
		~Node();

		string Id;
		int ThreadId;
		string IP;
		string Location; //physical
		vector<ExitPoint> exitPoints;
	};

}
#endif // GRAPH_H
