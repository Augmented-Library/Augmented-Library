import copy
# Nodes represent a location
class Node:
    def __init__(self, name,x,y):
        self.name = name
        self.child_array = []
        self.x = x
        self.y = y
    
    def __eq__(self, other):
        return self.name == other.get_name()

    def get_coord(self):
        return (self.x , self.y)

    def get_children(self):
        return self.child_array
    
    def get_name(self):
        return self.name

    # calculate the manhattan distance between two coordinates 
    def manhattan_distance(self, other):
        return abs(self.x - other.x) + abs(self.y - other.y)


    def append_child(self, other):
        # tuple so you have the child node and the distance to the child node 
        self.child_array.append((other,self.manhattan_distance(other)))
    
#State is the current node + goal combination 
class State:
    def __init__(self, curr_node, goal, temp_d = 0, outputObj = "", depth = 0, f_value = 0, action_ls = []): 
        # curr node is the current location
        self.curr_node = curr_node
        # goal is the goal location
        self.goal = goal
        # how deep the state is in the tree / how many steps to take 
        self.depth = depth
        # what is the f-value of the state 
        self.f_value = f_value
        # the actions needed to get to the current state
        self.action_ls = action_ls
        # the output file
        self.outputObj = outputObj
        # this is to track the total distance travelled. 
        # I don't think this is done accurately in calculate_f() or expand_node()
        #   have to double check since idk if it records 
        self.d = temp_d

    def reached_goal(self):
        return self.curr_node == self.goal

    def print_res(self):
        print(self.action_ls)

    def print_f(self):
        print(self.f_value)

    def set_d(self, num):
        self.d = num

    # determine the herusitic value of the state (in other words h(x))
    def heuristic(self, curr_node, goal):
        return self.manhattan_distance(curr_node, goal)

    # calculate the manhattan distance between two coordinates 
    def manhattan_distance(self, curr, goal):
        return abs(curr.get_coord()[0] - goal.get_coord()[0]) + abs(curr.get_coord()[1] - goal.get_coord()[1])
    
    # calculate the f-value and set it as f_value, then append this value to f_values_ls
    def calculate_f(self):
        # print("f(x) = g(x) + h(x)")

        # print(str(self.depth + self.heuristic()) + " = " + str(self.depth) + " + " + str(self.heuristic()))
        # print(self.curr_node.get_name(), self.goal.get_name())

        self.f_value = (self.d) + self.heuristic(self.curr_node, self.goal)
        
    # expand the state to show the next possible locations
    # return a list of all possible states
    def expand_node(self):
        # this will continue a list of states that are potential candidates for expansion from A* search 
        children = []          

        # potential next locations 
        potential_neighbors = []
        potential_neighbors.extend(self.curr_node.get_children())

        # now create those states and append it to the children class
        for ptn_child in potential_neighbors:
            # create a deep-copy of the next location so you do not modify the current-state
            temp_node = copy.deepcopy(ptn_child[0])
            
            # increase the depth by 1
            temp_depth = self.depth + 1
            # temporary f_value 
            temp_f_value = self.f_value

            # deep-copy the action_ls and then add what action the current child of the state will do
            temp_action_ls = copy.deepcopy(self.action_ls)
            # print(ptn_child[2])
            temp_action_ls.append(ptn_child[0].get_name())
            # print(temp_action_ls)

            temp_d = self.d + ptn_child[1]

            # create a temporary variable the represents a potential state to expand upon 
            child = State(temp_node, self.goal, temp_d, self.outputObj, temp_depth, temp_f_value, temp_action_ls)
            child.calculate_f() # fix the f_value of this new child then add that f_value into f_value_ls
            # child is completed with necessary information. now add this to the children list 
            children.append(child)
        return children
    
# solves the puzzle using the A* algorithmn
class Library: 
    def __init__(self, initial_state = None, goal_state = None):
        self.open = []                  # open queue are the states to be expanded
        self.close = []                 # close queue are the states that have been expanded. used to track repeating states
        self.curr = initial_state   # the current node 
        self.goal = goal_state      # the goal node
        self.processor = State(None, None)
        self.firstFloor = {}
        self.secondFloor = {}

    def reset(self):
        self.open = []                  # open queue are the states to be expanded
        self.close = []                 # close queue are the states that have been expanded. used to track repeating states
        self.curr = None   # the initial state
        self.goal = None      # the goal state
        self.processor = State(None, None)
 
    # does some prep work before doing a* search
    def search(self,curr,goal):
        self.reset()
        self.curr = curr
        self.goal = goal
        self.processor = State(curr, goal)
        self.a_star()

    # some prep work to make sure you can navigate through 2 floors
    def pathfind(self, curr, goal):
        print("=============================")
        print(curr.get_name(), " ---> ", goal.get_name())
        print("\n")
        if goal in self.secondFloor.values():
            self.search(curr, self.get_node("Stairs"))
            self.search(self.get_node("Stairs 2"), goal)
        else:
            self.search(curr, goal)
        print("=============================")

    # get a specific node depending on its name
    def get_node(self, name):
        if name in self.firstFloor.keys():
            return self.firstFloor[name]
        else:
            return self.secondFloor[name]

    # the actual a* search
    def a_star(self):
        # Put the initial state into the open list
        self.open.append(self.processor)
        # now iterate through this list until it is empty
        while self.open:
            # take the first state in the open list 
            curr_state = self.open[0]
            # check if matches the goal state and exit if necessary
            if curr_state.reached_goal():
                curr_state.print_res()
                break
            # expand the node and find the potential states to be expanded 
            pot_for_exp = curr_state.expand_node()
            # for every single possible node to be expanded in the next iteration of the while loop...
            for child_state in pot_for_exp:
                # remove it if it is a repeated state
                if(child_state in self.close):
                    pot_for_exp.remove(child_state)
                    continue
            # now add the not repeated states into the open list 
            for child_state in pot_for_exp:
                self.open.append(child_state)
            # remove the curr_state from open list and add it to close list
            temp_curr_state = curr_state
            self.open.remove(curr_state)
            self.close.append(temp_curr_state)
            # this part requires you to sort through the open list so the smallest f_value is the first element
            # so sort all of the states in the the open list by the state's f_value
            self.open.sort(key=lambda state:state.f_value)

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



#================
tempLib = Library()
tempLib.build_library()
testTuples = [("Exit", "Computer Lab"),("Exit", "hallway to snack lounge")]
for each in testTuples:
    start = tempLib.get_node(each[0])
    end = tempLib.get_node(each[1])
    tempLib.pathfind(start, end)