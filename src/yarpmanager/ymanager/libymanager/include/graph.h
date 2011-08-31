// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 *  Yarp Modules Manager
 *  Copyright: Robotics, Brain and Cognitive Sciences - Italian Institute of Technology (IIT)
 *  Authors: Ali Paikan <ali.paikan@iit.it>
 * 
 *  Copy Policy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#ifndef __GRAPH__
#define __GRAPH__

#include <map>
#include <string>
#include <iterator>

#include "ymm-types.h" 
#include "node.h"

using namespace std; 

//namespace ymm {

typedef map<string, Node*> NodePContainer;
typedef map<string, Node*>::iterator NodePIterator;

//typedef vector<Node>::iterator NodeIterator;
//typedef vector<Node> NodeContainer;

class GraphIterator;

/**
 * Class Graph  
 */
class Graph {

public: 
	Graph(void);
	~Graph();

	int getSize(void) { return nodes.size(); }
	Node* getNodeAt(int index);
	
	Node* addNode(Node* node);
	bool removeNode(Node* node);
	bool removeNode(const char* szLabel);
	bool addLink(Node* first, Node* second, 
				float weight, bool _virtual=false);
	bool addLink(const char* szFirst, const char* szSecond, 
				float weight, bool _virtual=false);
	bool removeLink(Node* first, Node* second);
	bool removeLink(const char* szFirst, const char* szSecond);
	void clear(void);	
	void setSatisfied(bool sat);
	void setVisited(bool vis);
	bool hasNode(Node* node);
	bool hasNode(const char* szLabel);	
	Node* getNode( const char* szLabel);
	GraphIterator begin(void);
	GraphIterator end(void);
	// it is better we put them as part of KnowlegeBase class
//	bool storeGraph(const char* szFileName);
//	bool loadGraph(const char* szFileName);
//	bool exportDotGraph(const char* szFileName);
	

protected:

private:
	NodePContainer nodes;
	NodePIterator findNode(Node* node);
};


/**
 *  Class GraphIterator
 */
class GraphIterator: public iterator<input_iterator_tag, Node*>
{
public:
	GraphIterator(void){}
	~GraphIterator(){}
	GraphIterator(const GraphIterator& mit) : itr(mit.itr) {}
	GraphIterator& operator++() {++itr;return *this;}
	GraphIterator operator++(int) {GraphIterator tmp(*this); operator++(); return tmp;}
	bool operator==(const GraphIterator& rhs) {return itr==rhs.itr;}
	bool operator!=(const GraphIterator& rhs) {return itr!=rhs.itr;}
	Node*& operator*() {return (*itr).second;}
	friend class Graph;
  
private:
	NodePIterator itr;
};

 
#define PRINT_GRAPH(g)\
		cout<<"Graph "<<#g<<" with "<<g.getSize()<<" nodes:"<<endl;\
		cout<<"{"<<endl;\
        for(GraphIterator itr=g.begin(); itr!=g.end(); itr++)\
        {\
			Node* n = (*itr);\
			cout<<" "<<n->getLabel()<<": [";\
			for(int j=0; j<n->sucCount(); j++)\
			{\
				Link l = n->getLinkAt(j);\
				cout<<l.to()->getLabel()<<"("<<l.weight()<<"), ";\
			}\
			cout<<"]"<<endl;\
		}\
        cout<<"}"<<endl;


/*                if( ! *((bool*)list_get_at(&l.marks, i)) )\
			printf("\033[31m%s\033[0m, ", ((vertex*)list_get_at(&l.nodes, i))->lable);\
	else\
			printf("%s, ", ((vertex*)list_get_at(&l.nodes, i))->lable);\
*/
//}

#endif //__GRAPH__
