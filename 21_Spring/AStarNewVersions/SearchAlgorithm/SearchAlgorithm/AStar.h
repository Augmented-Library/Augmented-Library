//
//  AStar.h
//  
//
//  Created by Kora Hughes on 4/6/21.
//

#ifndef AStar_h
#define AStar_h
#include <string>
#include <iostream>
//using namespace std;

namespace SearchAlgorithms{
    class Node{
        //friends?
    private:
        std::string id = "";
        
        float getDist(Node* toFind);
        
    public:
        std::string displayName = "";

        int location_x = 0;
        int location_y = 0;

        Node* adjacentNodes[5]; //Question: How do we define these @Dorthy?
        //Node: Can add dll functionality for search so user has to search once instead of twice to get to and from a given location
        //Node* previous_search;

        Node(const int idname, const std::string& dispname, const int x_loc, const int y_loc) {
            id = idname;
            displayName = dispname;
            location_x = x_loc;
            location_y = y_loc;
            for(int i = 0; i<5; i++){ //default size
                adjacentNodes[i] = nullptr;
            }
        }
        
        
        void addNode(Node adjacent);
        void addNode(Node* adjacent);

        void displayNode();
        
        std::string getID();
    };

    class Library{
    private:
        double pythagDist(double srcX, double srcY, double dstX, double dstY);
    public:
        //overarching struct
        struct Floor{
            Node* fNodes[1]; //aka nodes on the floor
            Node* entrence;
            Node* exit;
        };
        Floor levels[1];
        std::string name;
        
        Library(std::string new_name, int num_floors = 2){
            name = new_name;
            if (num_floors < 0){
                std::cout << "Error on Library declaration: num_floors < 0: " << num_floors << std::endl;
                num_floors = 1;
            }
            while (num_floors > 0){
                Floor templateFloor; //to prevent shallow-copy issues
                levels.push_back(templateFloor);
                num_floors--;
            }
        }
        
        void addNode(Node new_node, int floor);
        bool isEmpty(int floor);
        
        double getEstimatedDist(Node* src, Node* dst);
    };


    class Path{
    public:
        std::string node1ID;
        std::string node2ID;

        long actDist;

        Path(std::string id1, std::string id2, long distance){
            if (id1.compare(id2) == -1){
                node1ID = id1;
                node2ID = id2;
            }
            else {
                node1ID = id2;
                node2ID = id1;
            }
            actDist = distance;
        }
    };

    struct AStarNode{
    public:
        Node* location;
        std::string path;
        AStarNode(Node loc, std::string new_path){
            location = &loc;
            path = new_path;
        }
    };
}

#endif /* AStar_h */
