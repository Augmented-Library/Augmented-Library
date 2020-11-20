#include <iostream>
#include <list>
using namespace std;

//node class to indicate points of interest in library and main intersections
//wip: showing the actual path between two nodes, since they won't all be straight lines
class Node{
public:

  string id;
  string displayName;

  int location_x;
  int location_y;

  Node* adjacentNodes[5];
  //Node: Can add dll functionality for search so user has to search once instead of twice to get to and from a given location
  //Node* previous_search;

  Node(string idname, string dispname){
    id = idname;
    displayName = dispname;
    for(int i = 0; i<5; i++){
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
  public addAStarNode(Node new_node, int floor = 0){
    levels[floor].nodesOnFloor.push_back(new_node);
  }

  Floor levels[];
  string name;
};

double getEstimatedDist(Node* src, Node* dst){
  int srcFl = stoi(src->id.substr(0,1));
  int dstFl = stoi(dst->id.substr(0,1));
  if (srcFl == dstFl){ //on same floor
    double srcX = src->location_x;
    double srcY = src->location_y;
    double dstX = dst->location_x;
    double dstY = dst->location_y;

    return sqrt(pow(srcX - dstX,2) + pow(srcY - dstY,2));
  }
  else { //on different floor
    // WIP
    //will only account for staircase nodes, since dibner only has stairs afaik
    string stairID(1,src->id[0]);
    stairID += "_staircase";
    return 0;
  }
}

int main() {
  Library tandon = new Library("Tandon Library", 2);

  Node entrance("3_entrance", "Entrance"); //init nodes
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
