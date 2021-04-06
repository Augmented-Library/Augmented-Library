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

    bool Library::isEmpty(int floor = 0){
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


    double Library::pythagDist(double srcX, double srcY, double dstX, double dstY){ //TODO: fix pythag dist?
        return pow((srcX - dstX), 2) + pow((srcY - dstY), 2); //note sure what this is pow'ing
    }
    double Library::getEstimatedDist(Node* src, Node* dst){
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
        stairID = to_string(floor); //TODO: incorperate floor with this
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
        
    void run_test() {
        //init
        Library* tandon = new Library("Tandon Library", 2);
        
        //imports
        ifstream ifs;
        string fileName = "test-data.txt";//""
        bool hasImport = true;
        do{ //open file
            cout << "Import File Name: " << endl;
            cin >> fileName;
            if (fileName == "" || fileName == "no file"){
                hasImport = false;
            }
            ifs.open(fileName);
        }while(!ifs && hasImport);
        
        //import data
        string line;
        string[] components;
        Node* start;
        const int[][] boundaries;
        int autoID = 1;
        while (getline(ifs, line)){ //adds the file contents line by line
            cout << "Testing Input: " << line << endl;
            //TypeInput, Name, Floor, X_Location, Y_Location
            //string, string, int, float, float
            //TYPE-key {"N":node, "C":comment, "B":boundary, "I":IDstart}
            components = line.trim().split(","); //unsure if trim and split exist in c++ TODO: check
            cout << "Components: " << components << endl;
            //isValid, name, id, floor, x, y
            isValid = components[0]; //basically checks what kind of input we're looking at, if its an input at all
            if (isValid == "N"){
                Node newNode(autoID, components[1], float(components[3]), float(components[4]));
                if (autoID == 1){
                    start = &newNode; //keeping track of node change
                }
                autoID++; //just a msc identifier to help with handling places with the same string name
                tandon.addNode(newNode, int(components[2]));
                cout << "Imported Node: " << newNode << endl;
            }
            else if (isValid == "B"){ //helps with mapping and visualizing
                xstart = int(components[1]);
                xend = int(components[2]);
                ystart = int(components[3]);
                yend = int(components[4]);
                to_print = ""
                for(int x = xstart; x < xend; x++){
                    for(int y = ystart; y < yend; y++){
                        boundaries.push([x,y]);
                        to_print += "(" + x + ", " + y + "), ";
                    }
                }
                cout << "Imported Boundaries: " << to_print << endl;
            }
            else if (isValid == "I"){ //so no ID's repeat, we check current node number in database and start file with that number+1
                autoID = int(components[1]);
            }
            else if (isValid == "C"){
                //comment line
            }
            else{
                cout << "Invalid Line Read: " + name + id << endl;
            }
        }
        ifs.close();
        
        
        //init hardcoded nodes
        Node entrance("3_entrance", "Entrance");
        Node front_desk("3_frontdesk", "Front Desk");
        Node intersection1("3_intersection_1", "Intersection 1");
        Node sofa("3_sofa", "Sofa");
        Node computer("3_computer_1", "Computers 1");
        Node fourth_floor("4_test", "Test");

        entrance.addNode(front_desk); //linking
        intersection1.addNode(sofa);
        intersection1.addNode(computer);

        tandon.addNode(entrance); //adding to struct for future ref
        tandon.addNode(front_desk);
        tandon.addNode(intersection1);
        tandon.addNode(sofa);
        tandon.addNode(computer);

        entrance.location_x = 18;
        entrance.location_y = 9;
        fourth_floor.location_x = 18;
        fourth_floor.location_y = 9;
        getEstimatedDist(&entrance, &front_desk);

        entrance.displayNode(); //test
        front_desk.displayNode();
        intersection1.displayNode();
        sofa.displayNode();
        computer.displayNode();
    }

}
