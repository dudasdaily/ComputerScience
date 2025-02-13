from io import TextIOWrapper
from pathlib import Path
input_path = Path(__file__).parent / 'bst_input.txt'
output_path = Path(__file__).parent / 'bst_output.txt'

def readKey(input_file: TextIOWrapper) -> list:
    # 한줄 읽기
    line = input_file.readline().strip()
    intList = list(map(int, line.split()))

    return intList

class Node:
    def __init__(self, key=None):
        self.key = key
        self.left = None
        self.right = None

class Bst:
    def __init__(self, output_path):
        self.root = None
        self.output_file = open(output_path, 'a')
    
    def __del__(self):
        self.output_file.close()

    def search(self, key):
        if self.root is None:
            return False
        
        cmpNode = self.root
        self.output_file.write("R")

        while cmpNode:
            if key == cmpNode.key:
                self.output_file.write("\n")
                return True
            
            if key < cmpNode.key:
                self.output_file.write("0")
                cmpNode = cmpNode.left
            
            elif key > cmpNode.key:
                self.output_file.write("1")
                cmpNode = cmpNode.right
        
        # 검색 실패시
        self.output_file.write("\n")
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
        # cmpNode = 삭제할 노드 | parent는 삭제할 노드의 부모노드
        while cmpNode and cmpNode.key != key:
            parent = cmpNode

            if key < cmpNode.key:
                cmpNode = cmpNode.left
            
            elif key > cmpNode.key:
                cmpNode = cmpNode.right

        # 삭제할 키가 트리에 없는 경우
        if cmpNode is None:
            return False
        
        # 여기서부터는 삭제할 노드가 트리에 있음
        # 삭제할 노드가 자식이 없는 경우
        if cmpNode.left is None and cmpNode.right is None:
            # 삭제할 노드가 루트인 경우
            # 이걸안하면 parent가 None이여서 오류가 남
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

            # successor를 오른쪽 서브트리의 제일 작은 노드로 바꿈.
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

# 이미 bst_output.txt가 있을 경우 그 파일 내용을 비움
file_clear = open(output_path, 'w')
file_clear.close()

for n in range(caseNum):
    # 트리 객체 생성
    tree = Bst(output_path)

    # 삽입할 키의 개수
    keyNum = int(input_file.readline())
    # 삽입할 키를 가진 리스트
    keyList = readKey(input_file)
    # 키 삽입
    for i in range(keyNum):
        tree.insert(keyList[i])

    # 검색할 키의 개수
    keyNum = int(input_file.readline())
    # 검색할 키를 가진 리스트
    keyList = readKey(input_file)
    # 키 검색
    for i in range(keyNum):
        tree.search(keyList[i])
    
    # 삭제할 키의 개수
    keyNum = int(input_file.readline())
    # 삭제할 키를 가진 리스트
    keyList = readKey(input_file)
    # 키 삭제
    for i in range(keyNum):
        tree.delete(keyList[i])
    
    # 검색할 키의 개수
    keyNum = int(input_file.readline())
    # 검색할 키를 가진 리스트
    keyList = readKey(input_file)
    # 키 검색
    for i in range(keyNum):
        tree.search(keyList[i])

input_file.close()