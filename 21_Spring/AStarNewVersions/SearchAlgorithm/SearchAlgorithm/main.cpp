//
//  main.cpp
//  SearchAlgorithm
//
//  Created by Kora Hughes on 4/6/21.
//  Copyright © 2021 NYU Augmented Library VIP. All rights reserved.
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
using namespace SearchAlgorithms;

void run_test();

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Testing..." << endl;
    run_test();
    return 0;
}

//test code
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
