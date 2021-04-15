//
//  a_star.swift
//  ARKitImageDetection
//
//  Created by Gordon Lei on 3/31/21.
//  Copyright © 2021 Apple. All rights reserved.
//

import Foundation

class Node: NSCopying{
    var name: String
    var x: Double
    var y: Double
    var child_array: [(Node,Double)]
    
    init(name: String, x: Double, y:Double){
        self.name = name
        self.x = x
        self.y = y
        self.child_array = []
    }
    
    func get_coord() -> (Double, Double) {
        return (self.x, self.y)
    }
    
    func get_children() -> [(Node,Double)] {
        return self.child_array
    }
    
    func get_name() -> String {
        return self.name
    }
    
    func manhattan_distance(other: Node) -> Double {
        return abs(self.x - other.x) + abs(self.y - other.y)
    }
    
    func append_child(otherNode: Node){
        self.child_array.append( (otherNode, self.manhattan_distance(other: otherNode)) )
    }
    
    func copy(with zone: NSZone? = nil) -> Any {
        let copy = Node(name: name, x: x, y: y)
        return copy
    }
}

extension Node: Equatable{
    static func == (lhs: Node, rhs: Node) -> Bool {
        return rhs.name == lhs.name
    }
}

class State: NSCopying{
    var curr_node: Node
    var goal: Node
    var depth: Int
    var f_value: Double
    var action_ls: [String]
    var d: Double
    
    init(curr_node: Node, goal: Node, depth: Int, f_value: Double, action_ls: [String], d: Double){
        self.curr_node = curr_node
        self.goal = goal
        self.depth = depth
        self.f_value = f_value
        self.action_ls = action_ls
        self.d = d
    }
    
    func reached_goal() -> Bool{
        return self.curr_node == self.goal
    }
    
    func print_res(){
       print(self.action_ls)
    }
    
    func print_f(){
        print(self.f_value)
    }
    
    func set_d(num : Double){
        self.d = num
    }
    
    func heuristic(currNode: Node, goalNode: Node) -> Double {
        return self.manhattan_distance(currNode: currNode, goalNode: goalNode)
    }
    
    func manhattan_distance(currNode: Node, goalNode: Node) -> Double {
        return abs(currNode.get_coord().0 - goalNode.get_coord().0) + abs(currNode.get_coord().1 - goalNode.get_coord().1)
    }
    
    func calculate_f() {
        self.f_value = (self.d) + self.heuristic(currNode: self.curr_node, goalNode: self.goal)
    }
    
    func expand_node() -> [State]{
        var children: [State]
        children = []
        
        var potential_neighbors: [(Node, Double)]
        potential_neighbors = []
        potential_neighbors.append(contentsOf: self.curr_node.get_children())
        
        for ptn_child in potential_neighbors{
            let temp_node = ((ptn_child).0).copy()
            
            let temp_depth = self.depth + 1
            
            let temp_f_value = self.f_value
            
            var temp_action_ls = self.action_ls
            temp_action_ls.append(ptn_child.0.get_name())

            let temp_d = self.d + ptn_child.1
            
            let child = State(curr_node: temp_node as! Node, goal: self.goal, depth: temp_depth, f_value: temp_f_value, action_ls: temp_action_ls, d: temp_d)
            child.calculate_f()
            children.append(child)
        }
        
        return children
    }
    
    func copy(with zone: NSZone? = nil) -> Any {
        let copy = State(curr_node: curr_node, goal: goal, depth: depth, f_value: f_value, action_ls: action_ls, d: d)
        return copy
    }
}

extension State: Equatable{
    static func == (lhs: State, rhs: State) -> Bool {
        return (
            lhs.curr_node == rhs.curr_node &&
                lhs.goal == rhs.goal &&
                lhs.depth == rhs.depth &&
                lhs.f_value == rhs.f_value &&
                lhs.action_ls == rhs.action_ls &&
                lhs.d == rhs.d
        )
    }
}

class Library{
    var open:[State]
    var close:[State]
    var curr: Node
    var goal:Node
    var processor:State
    var firstFloor:[String:Node]
    var secondFloor:[String:Node]
    
    init(open:[State], close:[State], curr: Node, goal:Node, processor:State, firstFloor:[String:Node], secondFloor:[String:Node]){
        self.open = []
        self.close = []
        self.curr = curr
        self.goal = goal
        self.processor = State(curr_node: curr, goal: goal, depth: 0, f_value: 0, action_ls: [], d: 0)
        self.firstFloor = [String: Node]()
        self.secondFloor = [String: Node]()
        
    }
    
    func reset(){
        self.open = []
        self.close = []
        self.curr = Node(name: "", x: 0.0, y: 0.0)
        self.goal = Node(name: "", x: 0.0, y: 0.0)
        self.processor = State(curr_node: curr, goal: goal, depth: 0, f_value: 0.0, action_ls: [], d: 0.0)
    }
    
    func search(curr: Node, goal: Node){
        self.reset()
        self.curr = curr
        self.goal = goal
        self.processor = State(curr_node: curr, goal: goal, depth: 0, f_value: 0.0, action_ls: [], d: 0.0)
        self.a_star()
    }
    
    func pathfind(curr: Node, goal: Node){
        print("================")
        print(curr.get_name(), " --> ", goal.get_name())
        
        print("\n")
        
        let valExists = self.secondFloor.values.contains(goal)
        if valExists{
            self.search(curr: curr, goal: self.get_node(name: "Stairs"))
            self.search(curr: self.get_node(name: "Stairs"), goal: goal)
        }
        else{
            self.search(curr: curr, goal: goal)
        }
        print("================")
    }
    
    func get_node(name: String) -> Node{
        let valExists = self.firstFloor.keys.contains(name)
        if valExists{
            return self.firstFloor[name]!
        }
        else{
            return self.secondFloor[name]!
        }
    }
    
    func a_star(){
        self.open.append(self.processor)
        while(self.open.isEmpty == false){
            let curr_state = self.open[0]
            
            if curr_state.reached_goal(){
                curr_state.print_res()
                break
            }
            
            
            let pot_for_exp = curr_state.expand_node()
            
            for child_state in pot_for_exp{
                if self.close.contains(child_state){
                    if let index = self.close.firstIndex(of: child_state) {
                        self.close.remove(at: index)
                        continue
                    }
                }
            }
            
            for child_state in pot_for_exp{
                self.open.append(child_state)
            }
            
            let temp_curr_state = curr_state
            if let index = self.open.firstIndex(of: curr_state) {
                self.open.remove(at: index)
            }
            self.close.append(temp_curr_state)
            self.open.sort{$0.f_value < $1.f_value}
        }
    }
    
    func build_library(){
        let exitNode = Node(name: "Exit", x: 3,y: 3.5)
        let frontHallway = Node(name: "Front Hallway",x: 5, y: 3.5)
        let frontDesk = Node(name: "Front Desk", x: 5,y: 4.5)
        let frontBathroom = Node(name: "Front Bathroom", x: 5,y: 2.5)
        
        let room323_324 = Node(name: "Front Hallway Pt 1", x: 6.5, y: 3.5)

        let mainHallway = Node(name: "Main Hallway of Floor 3", x: 9, y: 3.5)
        let room327 = Node(name: "Room 327", x: 10.25, y: 4.5)
        let room328_335 = Node(name: "Room 328 and 335", x: 12,y: 3.5)

        let bottomChunck = Node(name: "Bottom Chunck", x: 8.75, y: 1)

        let room_IDK = Node (name: "Rooms IDK since I can't read the name", x: 7, y: 1.25)
        let room339_341 = Node(name: "Room 339 to 341", x: 4, y: 1.25)

        let room333_335 = Node(name: "Room 333 to 335", x: 11.5, y: 1.25)
        let backHallway = Node(name: "Back Hallway", x: 12.75,y: 2)
        let computerLab = Node(name: "Computer Lab", x: 13.5, y: 1.25)

        let stairs = Node(name: "Stairs", x: 11, y: 3.75)
        let stairsHallway = Node(name: "Stairs Hallway", x: 11.5, y: 3.75)

        let upperChunck = Node(name: "Upper Chunck", x: 10, y: 7.5)

        
        
        
        
        
        exitNode.append_child(otherNode: frontHallway)

        frontHallway.append_child(otherNode: exitNode)
        frontHallway.append_child(otherNode: frontBathroom)
        frontHallway.append_child(otherNode: room323_324)
        frontHallway.append_child(otherNode: frontDesk)

        frontDesk.append_child(otherNode: frontHallway)

        frontBathroom.append_child(otherNode: frontHallway)

        room323_324.append_child(otherNode: frontHallway)
        room323_324.append_child(otherNode: mainHallway)

        mainHallway.append_child(otherNode: room323_324)
        mainHallway.append_child(otherNode: room327)
        mainHallway.append_child(otherNode: room328_335)
        mainHallway.append_child(otherNode: upperChunck)
        mainHallway.append_child(otherNode: bottomChunck)
        mainHallway.append_child(otherNode: stairs)

        stairs.append_child(otherNode: mainHallway)
        stairs.append_child(otherNode: stairsHallway)

        stairsHallway.append_child(otherNode: stairs)
        stairsHallway.append_child(otherNode: backHallway)

        backHallway.append_child(otherNode: stairsHallway)
        backHallway.append_child(otherNode: upperChunck)
        backHallway.append_child(otherNode: computerLab)
        backHallway.append_child(otherNode: room333_335)

        computerLab.append_child(otherNode: backHallway)

        room333_335.append_child(otherNode: backHallway)
        room333_335.append_child(otherNode: bottomChunck)
        room333_335.append_child(otherNode: room328_335)

        room328_335.append_child(otherNode: room333_335)
        room328_335.append_child(otherNode: bottomChunck)
        room328_335.append_child(otherNode: mainHallway)

        bottomChunck.append_child(otherNode: room333_335)
        bottomChunck.append_child(otherNode: room328_335)
        bottomChunck.append_child(otherNode: mainHallway)
        bottomChunck.append_child(otherNode: room_IDK)

        room_IDK.append_child(otherNode: bottomChunck)
        room_IDK.append_child(otherNode: room339_341)

        room339_341.append_child(otherNode: room_IDK)

        let stairs2 = Node(name: "Stairs 2", x: 11,y: 5.5)
        let stairsBottom = Node(name: "Hallway Space next to Stairs", x: 11.5, y: 4.5)
        let backHallway2 = Node(name: "Back Hallway",x: 12.5, y: 2)
        let bottomRightSection = Node(name: "bottom right section", x: 11, y: 1)
        let inBetweenHallway = Node(name: "In between hallway at the bottom right", x: 10.25, y: 3)
        let hallwayFront = Node(name: "Hallway portion in front of stairs", x: 10.25, y: 6)
        let topLong = Node(name: "hallway along the section with the gaps", x: 6.5, y: 6.5)
        let gap = Node(name: "gap between sections", x: 7.5, y: 5.5)
        let printer = Node(name: "printer area", x: 9, y: 4.5)
        let gap2 = Node(name: "gap between the printer and study rooms", x: 8, y: 2.5)
        let bottomStudy = Node(name: "bottom study area", x: 7, y: 1)
        let hallwaySnack = Node(name: "hallway to snack lounge", x: 6.25, y: 3)
        let bathroomSection = Node(name: "bathroom hallway", x: 4.5, y: 4.5)
        let hallwayGap = Node(name: "hallway between printer and hallway to snack", x: 7, y: 4.5)
        let roomBigStudy = Node(name: "hallway to big study rooms", x: 5.5,y: 9)
        let upperChunk2 = Node(name: "Upper Chunck", x: 9.5,y: 9.5)


        stairs2.append_child(otherNode: hallwayFront)

        stairsBottom.append_child(otherNode: hallwayFront)
        stairsBottom.append_child(otherNode: backHallway2)

        backHallway2.append_child(otherNode: stairsBottom)
        backHallway2.append_child(otherNode: bottomRightSection)

        bottomRightSection.append_child(otherNode: backHallway2)
        bottomRightSection.append_child(otherNode: inBetweenHallway)

        inBetweenHallway.append_child(otherNode: bottomRightSection)
        inBetweenHallway.append_child(otherNode: hallwayFront)
        inBetweenHallway.append_child(otherNode: printer)

        hallwayFront.append_child(otherNode: upperChunk2)
        hallwayFront.append_child(otherNode: inBetweenHallway)
        hallwayFront.append_child(otherNode: topLong)
        hallwayFront.append_child(otherNode: printer)
        hallwayFront.append_child(otherNode: stairs2)
        hallwayFront.append_child(otherNode: stairsBottom)

        topLong.append_child(otherNode: upperChunk2)
        topLong.append_child(otherNode: roomBigStudy)
        topLong.append_child(otherNode: gap)
        topLong.append_child(otherNode: bathroomSection)
        topLong.append_child(otherNode: hallwayFront)

        gap.append_child(otherNode: topLong)
        gap.append_child(otherNode: printer)
        gap.append_child(otherNode: hallwayGap)

        printer.append_child(otherNode: hallwayGap)
        printer.append_child(otherNode: gap)
        printer.append_child(otherNode: gap2)
        printer.append_child(otherNode: hallwayFront)
        printer.append_child(otherNode: inBetweenHallway)

        gap2.append_child(otherNode: printer)
        gap2.append_child(otherNode: bottomStudy)

        bottomStudy.append_child(otherNode: gap2)
        bottomStudy.append_child(otherNode: hallwaySnack)

        hallwaySnack.append_child(otherNode: bottomStudy)
        hallwaySnack.append_child(otherNode: bathroomSection)
        hallwaySnack.append_child(otherNode: hallwayGap)

        hallwayGap.append_child(otherNode: hallwaySnack)
        hallwayGap.append_child(otherNode: gap)
        hallwayGap.append_child(otherNode: printer)

        roomBigStudy.append_child(otherNode: topLong)
        roomBigStudy.append_child(otherNode: upperChunk2)

        upperChunk2.append_child(otherNode: roomBigStudy)
        upperChunk2.append_child(otherNode: topLong)
        upperChunk2.append_child(otherNode: hallwayFront)
        upperChunk2.append_child(otherNode: backHallway2)

        let floor1 = [exitNode,frontHallway,frontDesk,frontBathroom,room323_324,mainHallway,stairs,stairsHallway,backHallway,computerLab,room333_335,room328_335,bottomChunck,room_IDK,room339_341]
        for node in floor1{
            self.firstFloor[node.get_name()] = node
        }
        let floor2 = [stairs2,stairsBottom,backHallway2,bottomRightSection,inBetweenHallway,hallwayFront,topLong,gap,printer,gap2,bottomStudy,hallwaySnack,hallwayGap,roomBigStudy,upperChunk2]
        for node in floor2{
            self.secondFloor[node.get_name()] = node
        }
    }
    
}



