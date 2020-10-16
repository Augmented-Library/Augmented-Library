#include <iostream>
#include <list>
using namespace std;

//node class to indicate points of interest in library and main intersections
//wip: showing the actual path between two nodes, since they won't all be straight lines
class Node{
public:
  //should work like a doubly linked list
  struct NodeConnect(Node* node1, Node* node2, float dist){
    Node* node1; //original
    Node* node2;
    float dist;
  }
  
  string id;
  string displayName;
  
  List<NodeConnect> adjacentNodes;
  
  //int location_x; //I think locations are unneccessary unless we're plotting the floor-plan by a grid-system
  //int location_y;

  Node(string idname, string dispname){
    id = idname;
    displayName = dispname;
  }
  
  void addConnect(Node* addNode, float newDist){
    NodeConnect newConnect;
    newConnect.node1 = this;
    newConnect.node2 = addNode;
    newConnect.dist = newDist;
    adjacentNodes.push_back(newConnect);
  }
  
  float getDistTo(Node* destination){ //only works for straight shots atm
    float totalDist = 0
      //fancy a* stuff
    Node n = *this;
    while (&n != destination){
      totalDist += adjacentNodes[0].dist;
      n = *adjacentNodes[0].node2;
    }
    return totalDist;
  }
  
  string displayNode(){ //idk if we wana use fancy ostream stuff for toString but this works
    return displayName + "\n";
  }
  
  bool organize(){
    //order adjacentNodes by distance, returns true if already ordered
    return false;
  }
};

int main() {
  Node entrance("3_entrance", "Entrance");
  Node front_desk("3_frontdesk", "Front Desk");
  entrence.addConnect(*front_desk, 10);
  cout << entrance.displayNode();
  return 0;
}
