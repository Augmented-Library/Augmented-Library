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
  list<Node*> adjacentNodes;

  Node(string idname, string dispname, int x, int y){
    id = idname;
    displayName = dispname;
    location_x = x;
    location_y = y;
  }

  string displayNode(){
    return displayName + "\n";
  }
};

int main() {
  Node entrance("3_entrance", "Entrance", 0, 0);
  Node front_desk("3_frontdesk", "Front Desk", 0, 10);
  cout << entrance.displayNode();
  return 0;
}