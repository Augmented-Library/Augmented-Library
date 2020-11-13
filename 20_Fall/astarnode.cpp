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
};

int main() {
  Node entrance("3_entrance", "Entrance");
  Node front_desk("3_frontdesk", "Front Desk");
  Node intersection1("3_intersection_1", "Intersection 1");
  Node sofa("3_sofa", "Sofa");
  Node computer("3_computer_1", "Computers 1");

  entrance.addNode(front_desk);
  intersection1.addNode(sofa);
  intersection1.addNode(computer);

  entrance.displayNode();
  front_desk.displayNode();
  intersection1.displayNode();
  sofa.displayNode();
  computer.displayNode();

  return 0;
}
