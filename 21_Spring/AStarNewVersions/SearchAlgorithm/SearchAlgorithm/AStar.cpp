//
//  AStar.cpp
//  
//
//  Created by Kora Hughes on 4/6/21.
//

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include "AStar.h"

using namespace std;

//node class to indicate points of interest in library and main intersections
//wip: showing the actual path between two nodes, since they won't all be straight lines

namespace SearchAlgorithms{

    void Node::addNode(Node adjacent){
        this->addNode(&adjacent);
    }
    void Node::addNode(Node* adjacent){
        for(int i = 0; i < 5; i++){
            if (adjacentNodes[i] == nullptr){
                adjacentNodes[i] = adjacent;
                break;
            }
            if (adjacentNodes[i] == adjacent){
                return;
            }
        }
        adjacent->addNode(this);
    }

    void Node::displayNode(){
        string retStr = displayName + "\n";
        for (Node* node : adjacentNodes){
            if (node != nullptr){
                retStr += "\t" + node->displayName + "\n";
            }
        }
        cout << retStr;
    }

    string Node::getID(){
        return this->id;
    }

    //semi-copied from a_star.py
    vector<Node*> Node::expand(std::vector<Node*> fNodes) const {
        vector<Node*> closeNodes;
        vector<float> dist;
        for (Node* node : fNodes){
            //Goal: search nodes on this node's floor (fNodes input) and return all of the adjacent nodes?
            if (node->floor == this->floor){ //extra check
                dist.push_back(pythagDist(this->location_x, node->location_x, this->location_y, node->location_y))
            }
        }
        return closeNodes;
    }

    bool Library::isEmpty(int floor = 0) const{
        return this->levels[floor].fNodes.size() > 1;
    }

    void Library::addNode(Node new_node, int floor = 0){
        if (this->isEmpty(floor)){
            this->levels[floor].fNodes.push_back(&new_node);
            this->levels[floor].entrence = &new_node;
        }
        else{
            this->levels[floor].fNodes.push_back(&new_node);
        }
    }


    double pythagDist(double srcX, double srcY, double dstX, double dstY) { //TODO: fix pythag dist?
        return pow((srcX - dstX), 2) + pow((srcY - dstY), 2); //note sure what this is pow'ing
    }

    double Library::getEstimatedDist(Node* src, Node* dst) const{
        int srcFl = stoi(src->getID().substr(0,1));
        int dstFl = stoi(dst->getID().substr(0,1));

        double srcX = src->location_x;
        double srcY = src->location_y;
        double dstX = dst->location_x;
        double dstY = dst->location_y;

        if (srcFl == dstFl){ //on same floor
            return pythagDist(srcX, srcY, dstX, dstY);
        }
        // WIP - missing a lot do not use
        //will only account for staircase nodes, since dibner only has stairs afaik
        //will need to be updated in case of multiple staircases or accessibility
        string stairID;
        int currFl = srcFl;
        double dist = 0;

        double currX = srcX;
        double currY = srcY;
        double nextX;
        double nextY;

        while (currFl != dstFl){
            stairID = levels[0].entrance->id; //TODO: incorperate floor with this
        stairID += "_staircase";

        //assuming global nodes (in a dictionary potentially)
        //Node* stair = /global node collection/["stairID"]
        Node stair(0, "Test", 49, 9); //fill in for now
        nextX = stair.location_x;
        nextY = stair.location_y;

        //dist from current loc to next loc
        dist += pythagDist(currX, currY, nextX, nextY);

        currX = nextX;
        currY = nextY;
        currFl++;

        return 0;
    }
    
    ostream& operator <<(ostream& os, const Library& lib) {
      // just shows the number of nodes per level for now...
        os << "Library " << lib.name << ": {";
        for(int i; i < lib.levels.size(); i++){
            os << lib.levels[i].fNodes.size() << ", ";
        }
        os << "}" << endl;
      return os;
    }
}
