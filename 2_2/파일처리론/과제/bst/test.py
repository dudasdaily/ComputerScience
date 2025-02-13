<<<<<<< HEAD
=======
from pathlib import Path
input_path = Path(__file__).parent / 'bst_input.txt'
output_path = Path(__file__).parent / 'bst_output.txt'


class Node:
    def __init__(self, key=None):
        self.key = key
        self.left = None
        self.right = None

class Bst:
    def __init__(self, output_path):
        self.root = None
        self.output_file = open(output_path, 'w')
    
    def __del__(self):
        self.output_file.write("\n")
        self.output_file.close()

    def search(self, key):
        if self.root is None:
            return False
        
        cmpNode = self.root
        self.output_file.write("R")

        while cmpNode:
            if key == cmpNode.key:
                return True
            
            if key < cmpNode.key:
                self.output_file.write("0")
                cmpNode = cmpNode.left
            
            elif key > cmpNode.key:
                self.output_file.write("1")
                cmpNode = cmpNode.right
        
        return False
    
    def insert(self, key):
        if self.root is None:
            self.root = Node(key)
        
        cmpNode = self.root

        while True:
            if key < cmpNode.key:
                if cmpNode.left is None:
                    cmpNode.left = Node(key)
                    return
                
                cmpNode = cmpNode.left
            
            elif key > cmpNode.key:
                if cmpNode.right is None:
                    cmpNode.right = Node(key)
                    return
                
                cmpNode = cmpNode.right
            
            else:
                # 삽입 실패
                return False
    
    def delete(self, key):
        parent = None
        cmpNode = self.root

        # 삭제할 노드 찾기
        while cmpNode and cmpNode.key != key:
            parent = cmpNode

            if key < cmpNode.key:
                cmpNode = cmpNode.left
            
            elif key > cmpNode.key:
                cmpNode = cmpNode.right

        if cmpNode is None:
            return False
        
        # 삭제할 노드가 자식이 없는 경우
        if cmpNode.left is None and cmpNode.right is None:
            if cmpNode is self.root:
                self.root = None
            
            elif cmpNode == parent.left:
                parent.left = None
            
            elif cmpNode == parent.right:
                parent.right = None
        
        # 삭제할 노드가 오른쪽 자식만 있는 경우
        elif cmpNode.left is None:
            if cmpNode == self.root:
                self.root = cmpNode.right
            
            elif cmpNode == parent.left:
                parent.left = cmpNode.right
            
            elif cmpNode == parent.right:
                parent.right = cmpNode.right
        
        # 삭제할 노드가 왼쪽 자식만 있는 경우
        elif cmpNode.right is None:
            if cmpNode == self.root:
                self.root = cmpNode.left
            
            elif cmpNode == parent.left:
                parent.left = cmpNode.left
            
            elif cmpNode == parent.right:
                parent.right = cmpNode.left
        
        # 삭제할 노드가 두 개의 서브트리를 가지는 경우
        else:
            successorParent = cmpNode
            successor = cmpNode.right

            while successor.left:
                successorParent = successor
                successor = successor.left
            
            if successorParent == cmpNode:
                successorParent.right = successor.right

            else:
                successorParent.left = successor.right
        
            cmpNode.key = successor.key



input_file = open(input_path, 'r')

caseNum = int(input_file.readline())

for n in range(caseNum):
    # 트리 객체 생성
    tree = Bst(output_path)

    # insert할 노드 수
    nodeNum = int(input_file.readline())

    


>>>>>>> d43a0f184a790fc6e8be0be95e7ea59ceea6cf59
