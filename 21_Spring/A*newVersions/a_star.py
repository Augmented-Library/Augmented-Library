import copy
# an individual state possible in the puzzle 

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

    def append_child(self, other, dist):
        # tuple so you have the child node and the distance to the child node 
        self.child_array.append((other,dist))
    
    
        


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
        '''
        temp = "Exit,Front Hallway,Front Desk,Front Bathroom,Front Hallway Pt 1,Main Hallway of Floor 3,Room 327,Room 328 and 335,Bottom Chunck,Rooms IDK since I can't read the name,Room 339 to 341,Room 333 to 335,Back Hallway,Computer Lab,Stairs,Stairs Hallway,Upper Chunck"
        axis = temp.split(",")
        distances = []
        distances.append([0,2,2.23,2.23,4,6.5,7.51,7.57,8.08,5,3.16,9.49,10.44,11.4,8.7,9.7,7.63])
        distances.append([2,0,1,1,2,4,7.02,7.07,6.7,3.61,3,7.62,9.22,13.148,6.7,7.7,5.83])
        distances.append([2.23,1,0,2,2.234,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14])
        distances.append([2.23,1,3.14,0,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14])
        distances.append([4,2,3.14,3.14,0,2.5,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14])
        distances.append([6.5,3.14,3.14,3.14,2.5,0,2,23,2.5,2.25,3.14,3.14,3.14,3.14,3.14,2.2,3.14,3])
        distances.append([7.51,3.14,3.14,3.14,3.14,3.14,0,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14])
        distances.append([7.57,3.14,3.14,3.14,3.14,3.14,3.14,0,2.23,3.14,3.14,2.23,3.14,3.14,3.14,3.14,3.14])
        distances.append([8.08,3.14,3.14,3.14,3.14,3.14,3.14,3.14,0,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14])
        distances.append([5,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,0,3.14,3.14,3.14,3.14,3.14,3.14,3.14])
        distances.append([3.16,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,0,3.14,3.14,3.14,3.14,3.14,3.14])
        distances.append([9.49,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,0,2.8,3.14,3.14,3.14,3.14])
        distances.append([10.44,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,0,2.23,3.14,3.14,4])
        distances.append([11.4,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,0,3.14,3.14,3.14])
        distances.append([8.7,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,0,1,3.14])
        distances.append([9.7,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,0,3.14])
        distances.append([7.63,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,3.14,0])
        '''
        #find the correct heuristic value
        '''
        row = 0
        col = 0
        for i in range(len(axis)):
            
            if axis[i] == curr_node.get_name():
                row = i
            elif axis[i] == goal.get_name():
                col = i
        print(row,col)
        return distances[row][col]
        '''
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
        
    # expand the the state to find possible moves of swapping the blank space
    # return a list of all these valid possible states, valid meaning it does not go out of bounds from the board
    def expand_node(self):
        # this will continue a list of states that are potential candidates for expansion from A* search 
        children = []          

        # potential spots that the blank space can swap to/move to
        potential_neighbors = []
        potential_neighbors.extend(self.curr_node.get_children())

        # now create those states and append it to the children class
        for ptn_child in potential_neighbors:

            #print(self.curr_node.get_name(), ptn_child[0].get_name())

            # create a deep-copy of the current state's configuration so you do not modify the current-state's configuration
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
            #child.set_d(temp_d)
            child.calculate_f() # fix the f_value of this new child then add that f_value into f_value_ls
            # child is completed with necessary information. now add this to the children list 
            children.append(child)
        return children
    
# solves the puzzle using the A* algorithmn
class Library: 
    def __init__(self, initial_state = [[]], goal_state = [[]], row = 3, col = 4):
        self.row = row
        self.col = col
        self.open = []                  # open queue are the states to be expanded
        self.close = []                 # close queue are the states that have been expanded. used to track repeating states
        self.is_state = initial_state   # the initial state
        self.gl_state = goal_state      # the goal state

        self.processor = State(None, None)

        self.output_file = ""
        self.input_file = ""

    def pathfind(self,curr,goal):
        self.is_state = curr
        self.gl_state = goal
        self.processor = State(curr, goal)
        self.a_star()

    # the actual a* search
    def a_star(self):
        # Put the initial state into the open list
        self.open.append(self.processor)
        # now iterate through this list until it is empty
        while self.open:
            # take the first state in the open list 
            curr_state = self.open[0]
            
            #curr_state.print_res()
            #print(curr_state.configuration)

            # check if matches the goal state and exit if necessary
            if curr_state.reached_goal():
                #curr_state.f_value_ls.append('0')
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
            #del self.open[0]
            self.close.append(temp_curr_state)
            # this part requires you to sort through the open list so the smallest f_value is the first element
            # so sort all of the states in the the open list by the state's f_value
            self.open.sort(key=lambda state:state.f_value)

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
exitNode.append_child(frontHallway, 2)

frontHallway.append_child(exitNode, 2)
frontHallway.append_child(frontBathroom, 1.1)
frontHallway.append_child(room323_324, 2)
frontHallway.append_child(frontDesk,1 )

frontDesk.append_child(frontHallway,1 )

frontBathroom.append_child(frontHallway, 1.1)

room323_324.append_child(frontHallway, 2)
room323_324.append_child(mainHallway, 2.5)

mainHallway.append_child(room323_324, 2.5)
mainHallway.append_child(room327, 2.23)
mainHallway.append_child(room328_335, 2.5)
mainHallway.append_child(upperChunck, 3)
mainHallway.append_child(bottomChunck, 2.25)
mainHallway.append_child(stairs, 2.2)

stairs.append_child(mainHallway, 2.2)
stairs.append_child(stairsHallway, 1)

stairsHallway.append_child(stairs, 1)
stairsHallway.append_child(backHallway, 2.23)

backHallway.append_child(stairsHallway, 2.23)
backHallway.append_child(upperChunck, 4)
backHallway.append_child(computerLab, 2.23)
backHallway.append_child(room333_335, 2.8)

computerLab.append_child(backHallway, 2.23)

room333_335.append_child(backHallway, 2.8)
room333_335.append_child(bottomChunck, 3)
room333_335.append_child(room328_335, 2.23)

room328_335.append_child(room333_335, 2.23)
room328_335.append_child(bottomChunck, 2.23)
room328_335.append_child(mainHallway, 2.5)

bottomChunck.append_child(room333_335, 3)
bottomChunck.append_child(room328_335, 2.23)
bottomChunck.append_child(mainHallway, 2.25)
bottomChunck.append_child(room_IDK, 2.5)

room_IDK.append_child(bottomChunck, 2.5)
room_IDK.append_child(room339_341, 3)

room339_341.append_child(room_IDK, 3)

#===========================
stairs2 = Node("Stairs", 11,5.5)
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
'''
stairs2.append_child(hallwayFront, .5)

stairsBottom.append_child(hallwayFront, 1.58)
stairsBottom.append_child(backHallway2, 2.23)

backHallway2.append_child(stairsBottom, )
backHallway2.append_child(bottomRightSection, )

bottomRightSection.append_child(backHallway2, )
bottomRightSection.append_child(inBetweenHallway, )

inBetweenHallway.append_child(bottomRightSection, ) 
inBetweenHallway.append_child(hallwayFront, ) 
inBetweenHallway.append_child(printer, ) 

hallwayFront.append_child(upperChunk2, )
hallwayFront.append_child(inBetweenHallway, )
hallwayFront.append_child(topLong, )
hallwayFront.append_child(printer, )
hallwayFront.append_child(stairs2, )
hallwayFront.append_child(stairsBottom, )

topLong.append_child(upperChunck2, ) 
topLong.append_child(roomBigStudy, )
topLong.append_child(gap, )
topLong.append_child(bathroomSection) 
topLong.append_child(hallwayFront)   

gap.append_child(topLong, )
gap.append_child(printer, )
gap.append_child(hallwayGap, )

printer.append_child(hallwayGap, )
printer.append_child(gap, )
printer.append_child(gap2, )
printer.append_child(hallwayFront, )
printer.append_child(inBetweenHallway, )

gap2.append_child(printer, )
gap2.append_child(bottomStudy, )

bottomStudy.append_child(gap2, ) 
bottomStudy.append_child(hallwaySnack, )

hallwaySnack.append_child(bottomStudy, ) 
hallwaySnack.append_child(bathroomSection, )
hallwaySnack.append_child(hallwayGap, )

hallwayGap.append_child(hallwaySnack, )
hallwayGap.append_child(gap, )
hallwayGap.append_child(printer, )

roomBigStudy.append_child(topLong, )
roomBigStudy.append_child(upperChunck2, )

upperChunk2.append_child(roomBigStudy, )
upperChunk2.append_child(topLong, )
upperChunk2.append_child(hallwayFront, )
upperChunk2.append_child(backHallway2, )
'''
#================
first_floor = []
first_floor.extend([exitNode,frontHallway,frontDesk,frontBathroom,room323_324,mainHallway,stairs,stairsHallway,backHallway,computerLab,room333_335,room328_335,bottomChunck,room_IDK,room339_341])

second_floor = []
second_floor.extend([stairs2 ,stairsBottom ,backHallway2,bottomRightSection ,inBetweenHallway ,hallwayFront ,topLong ,gap ,printer ,gap2 ,bottomStudy ,hallwaySnack ,hallwayGap, roomBigStudy, upperChunk2])

#================
temp_lib = Library()

testTuples = [(exitNode,computerLab),(exitNode, hallwaySnack)]
for each in testTuples:
    start = each[0]
    end = each[1]

    print("=============================")
    
    print(start.get_name, " ---> ", end.get_name)

    print("\n")

    if(end in first_floor):
        temp_lib.pathfind(start, stairs)
        temp_lib.pathfind(stairs2, end)

    else:
        temp_lib.pathfind(start,end)

    
    print("=============================")

