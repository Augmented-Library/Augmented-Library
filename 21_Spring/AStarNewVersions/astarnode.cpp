#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//node class to indicate points of interest in library and main intersections
//wip: showing the actual path between two nodes, since they won't all be straight lines

/*  Sample Nodelay: https://github.com/clementmihailescu/Pathfinding-Visualizer/blob/master/public/browser/node.js
 function Node(id, status) {
   this.id = id;
   this.status = status;
   this.previousNode = null;
   this.path = null;
   this.direction = null;
   this.storedDirection = null;
   this.distance = Infinity;
   this.totalDistance = Infinity;
   this.heuristicDistance = null;
   this.weight = 0;
   this.relatesToObject = false;
   this.overwriteObjectRelation = false;

   this.otherid = id;
   this.otherstatus = status;
   this.otherpreviousNode = null;
   this.otherpath = null;
   this.otherdirection = null;
   this.otherstoredDirection = null;
   this.otherdistance = Infinity;
   this.otherweight = 0;
   this.otherrelatesToObject = false;
   this.otheroverwriteObjectRelation = false;
 }
 */

class Node{
public:
    string id;
    string displayName;

    int location_x;
    int location_y;

    Node* adjacentNodes[5]; //Question: How do we define these @Dorthy?
    //Node: Can add dll functionality for search so user has to search once instead of twice to get to and from a given location
    //Node* previous_search;

    Node(string idname, string dispname, x_loc, y_loc){
        id = idname;
        displayName = dispname;
        location_x = x_loc;
        location_y = y_loc;
        for(int i = 0; i<5; i++){ //default size
            adjacentNodes[i] = nullptr;
        }
    }

    /*void addConnect(Node* addNode, float newDist){
    NodeConnect newConnect;
    newConnect.node1 = this;
    newConnect.node2 = addNode;
    newConnect.dist = newDist;
    adjacentNodes.push_back(newConnect);
    }*/

    void addNode(Node adjacent){
        this->addNode(&adjacent);
    }

    void addNode(Node* adjacent){
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

    void displayNode(){
        string retStr = displayName + "\n";
        for (Node* node : adjacentNodes){
            if (node != nullptr){
                retStr += "\t" + node->displayName + "\n";
            }
        }
        cout << retStr;
    }
};

class Path{
    public:
    //must be in alphabetical order (?)
    //to reduce no. of repeated paths
    string node1ID;
    string node2ID;

    long actDist;

    Path(string id1, string id2, long distance){
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
    Node* location;
    //each node id needed to get from starting to current node
    //will be separated by comma
    string path;
    public AStarNode(Node loc, string new_path){
        location = *loc;
        path = new_path;
    }
};

class Library{ //might be useful..?
//    friend ostream& operator<<(ostream& os, const Library& lib){
//        os << "[" << lib.join(",") << ": " << war.getStrength();
//        return os;
//    }
public:
    //overarching struct
    public struct Floor{
        Node* nodesOnFloor[5];
        Node* entrence;
        Node* exit;
    };

    public Library(string new_name, int num_floors){
        name = new_name;
        levels = new Floor[num_floors];
    }
    public addNode(Node new_node, int floor = 0){
        levels[floor].nodesOnFloor.push_back(new_node);
    }

    Floor levels[];
    string name;
    };

//test only with same floor nodes
/* Sample Search Structure: https://github.com/clementmihailescu/Pathfinding-Visualizer/blob/master/public/browser/pathfindingAlgorithms/astar.js
 function astar(nodes, start, target, nodesToAnimate, boardArray, name, heuristic) {
   if (!start || !target || start === target) {
     return false;
   }
   nodes[start].distance = 0;
   nodes[start].totalDistance = 0;
   nodes[start].direction = "up";
   let unvisitedNodes = Object.keys(nodes);
   while (unvisitedNodes.length) {
     let currentNode = closestNode(nodes, unvisitedNodes);
     while (currentNode.status === "wall" && unvisitedNodes.length) {
       currentNode = closestNode(nodes, unvisitedNodes)
     }
     if (currentNode.distance === Infinity) return false;
     nodesToAnimate.push(currentNode);
     currentNode.status = "visited";
     if (currentNode.id === target) {
       return "success!";
     }
     updateNeighbors(nodes, currentNode, boardArray, target, name, start, heuristic);
   }
 }
 */
double getEstimatedDist(Node* src, Node* dst){
    int srcFl = stoi(src->id.substr(0,1));
    int dstFl = stoi(dst->id.substr(0,1));

    double srcX = src->location_x;
    double srcY = src->location_y;
    double dstX = dst->location_x;
    double dstY = dst->location_y;

    if (srcFl == dstFl){ //on same floor
        return pythagDist(srcX, srcY, dstX, dstY);
    }
    else { //on different floor
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
        stairID = to_string(floor);
        stairID += "_staircase";

        //assuming global nodes (in a dictionary potentially)
        //Node* stair = /global node collection/["stairID"]
        Node stair("4_test", "Test"); //fill in for now
        stair.location_x = 49;
        stair.location_y = 9;

        nextX = stair.location_x;
        nextY = stair.location_y;

        //dist from current loc to next loc
        dist += pythagDist(currX, currY, nextX, nextY);

        currX = nextX;
        currY = nextY;
        currFl++;
    }
    return 0;
}

double pythagDist(double srcX, double srcY, double dstX, double dstY){
    (pow(srcX - dstX,2) + pow(srcY - dstY,2));
}

int main() {
    //init
    Library tandon = new Library("Tandon Library", 2);
    
    //imports
    ifstream ifs;
    string fileName = ""
    bool hasImport = true;
    do{ //open file
        cout << "Import File Name: " << endl;
        cin >> fileName;
        if (fileName == "" || fileName = "no file"){
            hasImport = false;
        }
        ifs.open(fileName);
    }while(!ifs && hasImport);
    
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

    
    
    Node entrance("3_entrance", "Entrance"); //init hardcode nodes
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

    return 0;
}
