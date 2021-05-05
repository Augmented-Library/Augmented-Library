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

void import_nodes(){
    /*
     def build_library(self):
     #================
     #============= Before the lobby ======================
     exitNode = Node("Exit", 3,3.5)
     frontHallway = Node("Front Hallway",5, 3.5)
     frontDesk = Node("Front Desk", 5,4.5)
     frontBathroom = Node("Front Bathroom", 5,2.5)
     # this one is the small section in front of room 323 or 324
     room323_324 = Node("Front Hallway Pt 1", 6.5, 3.5)
     #================ Main lobby area =====================
     mainHallway = Node("Main Hallway of Floor 3", 9, 3.5)
     room327 = Node("Room 327", 10.25, 4.5)
     room328_335 = Node("Room 328 and 335", 12,3.5)
     #=============== Bottom left area =================
     bottomChunck = Node("Bottom Chunck", 8.75, 1)
     # this is the room before room339 to 341
     room_IDK = Node ("Rooms IDK since I can't read the name", 7, 1.25)
     room339_341 = Node("Room 339 to 341", 4, 1.25)
     #================ Bottom right area ==================
     room333_335 = Node("Room 333 to 335", 11.5, 1.25)
     backHallway = Node("Back Hallway", 12.75,2)
     computerLab = Node("Computer Lab", 13.5, 1.25)
     #================= Stairs area ========================
     stairs = Node("Stairs", 11, 3.75)
     stairsHallway = Node("Stairs Hallway", 11.5, 3.75)
     #=================== Upper chunck =====================
     upperChunck = Node("Upper Chunck", 10, 7.5)

     #add the child nodes
     exitNode.append_child(frontHallway)

     frontHallway.append_child(exitNode)
     frontHallway.append_child(frontBathroom)
     frontHallway.append_child(room323_324)
     frontHallway.append_child(frontDesk)

     frontDesk.append_child(frontHallway)

     frontBathroom.append_child(frontHallway)

     room323_324.append_child(frontHallway)
     room323_324.append_child(mainHallway)

     mainHallway.append_child(room323_324)
     mainHallway.append_child(room327)
     mainHallway.append_child(room328_335)
     mainHallway.append_child(upperChunck)
     mainHallway.append_child(bottomChunck)
     mainHallway.append_child(stairs)

     stairs.append_child(mainHallway)
     stairs.append_child(stairsHallway)

     stairsHallway.append_child(stairs)
     stairsHallway.append_child(backHallway)

     backHallway.append_child(stairsHallway)
     backHallway.append_child(upperChunck)
     backHallway.append_child(computerLab)
     backHallway.append_child(room333_335)

     computerLab.append_child(backHallway)

     room333_335.append_child(backHallway)
     room333_335.append_child(bottomChunck)
     room333_335.append_child(room328_335)

     room328_335.append_child(room333_335)
     room328_335.append_child(bottomChunck)
     room328_335.append_child(mainHallway)

     bottomChunck.append_child(room333_335)
     bottomChunck.append_child(room328_335)
     bottomChunck.append_child(mainHallway)
     bottomChunck.append_child(room_IDK)

     room_IDK.append_child(bottomChunck)
     room_IDK.append_child(room339_341)

     room339_341.append_child(room_IDK)

     #=========================== 2nd floor

     stairs2 = Node("Stairs 2", 11,5.5)
     stairsBottom = Node("Hallway Space next to Stairs", 11.5, 4.5)
     backHallway2 = Node("Back Hallway",12.5, 2)
     bottomRightSection = Node("bottom right section", 11, 1)
     inBetweenHallway = Node("In between hallway at the bottom right", 10.25, 3)
     hallwayFront = Node("Hallway portion in front of stairs", 10.25, 6)
     topLong = Node("hallway along the section with the gaps", 6.5, 6.5)
     gap = Node("gap between sections", 7.5, 5.5)
     printer = Node("printer area", 9, 4.5)
     gap2 = Node("gap between the printer and study rooms", 8, 2.5)
     bottomStudy = Node("bottom study area", 7, 1)
     hallwaySnack = Node("hallway to snack lounge", 6.25, 3)
     bathroomSection = Node("bathroom hallway", 4.5, 4.5)
     hallwayGap = Node("hallway between printer and hallway to snack", 7, 4.5)
     roomBigStudy = Node("hallway to big study rooms", 5.5,9)
     upperChunk2 = Node("Upper Chunck", 9.5,9.5)
     #==========================

     #Connect the Nodes for the 2nd floor

     stairs2.append_child(hallwayFront)

     stairsBottom.append_child(hallwayFront)
     stairsBottom.append_child(backHallway2)

     backHallway2.append_child(stairsBottom)
     backHallway2.append_child(bottomRightSection)

     bottomRightSection.append_child(backHallway2)
     bottomRightSection.append_child(inBetweenHallway)

     inBetweenHallway.append_child(bottomRightSection)
     inBetweenHallway.append_child(hallwayFront)
     inBetweenHallway.append_child(printer)

     hallwayFront.append_child(upperChunk2)
     hallwayFront.append_child(inBetweenHallway)
     hallwayFront.append_child(topLong)
     hallwayFront.append_child(printer)
     hallwayFront.append_child(stairs2)
     hallwayFront.append_child(stairsBottom)

     topLong.append_child(upperChunk2)
     topLong.append_child(roomBigStudy)
     topLong.append_child(gap)
     topLong.append_child(bathroomSection)
     topLong.append_child(hallwayFront)

     gap.append_child(topLong)
     gap.append_child(printer)
     gap.append_child(hallwayGap)

     printer.append_child(hallwayGap)
     printer.append_child(gap)
     printer.append_child(gap2)
     printer.append_child(hallwayFront)
     printer.append_child(inBetweenHallway)

     gap2.append_child(printer)
     gap2.append_child(bottomStudy)

     bottomStudy.append_child(gap2)
     bottomStudy.append_child(hallwaySnack)

     hallwaySnack.append_child(bottomStudy)
     hallwaySnack.append_child(bathroomSection)
     hallwaySnack.append_child(hallwayGap)

     hallwayGap.append_child(hallwaySnack)
     hallwayGap.append_child(gap)
     hallwayGap.append_child(printer)

     roomBigStudy.append_child(topLong)
     roomBigStudy.append_child(upperChunk2)

     upperChunk2.append_child(roomBigStudy)
     upperChunk2.append_child(topLong)
     upperChunk2.append_child(hallwayFront)
     upperChunk2.append_child(backHallway2)

     floor1 = [exitNode,frontHallway,frontDesk,frontBathroom,room323_324,mainHallway,stairs,stairsHallway,backHallway,computerLab,room333_335,room328_335,bottomChunck,room_IDK,room339_341]
     for node in floor1:
         self.firstFloor[node.get_name()] = node
     floor2 = [stairs2,stairsBottom,backHallway2,bottomRightSection,inBetweenHallway,hallwayFront,topLong,gap,printer,gap2,bottomStudy,hallwaySnack,hallwayGap,roomBigStudy,upperChunk2]
     for node in floor2:
         self.secondFloor[node.get_name()] = node
     */
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
