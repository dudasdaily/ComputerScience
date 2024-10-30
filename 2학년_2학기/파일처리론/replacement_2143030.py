from asyncio.windows_events import NULL


buffer_size = 5
buffer = [0 for i in range(buffer_size)]

sorted_list = []

class Freeze:
    value = NULL
    is_freeze = False

    def __init__(self, value):
        self.value = value
        self.is_freeze = False

write_file = open("G:/다른 컴퓨터/내 컴퓨터/2학년 2학기/파일처리론/파일처리론 과제/replacement_output.txt", "w")

with open("G:/다른 컴퓨터/내 컴퓨터/2학년 2학기/파일처리론/파일처리론 과제/replacement_input.txt", "r") as read_file:
    cases_num = int(read_file.readline()) # 4

    for i in range(cases_num):
        element_num = read_file.readline() # 원소 개수
        elements = list(map(int, read_file.readline().strip().split())) # 입력 값을 읽음

        # 버퍼 크기만큼 넣기
        for i in range(buffer_size):
            buffer[i] = Freeze(elements.pop(0))
        
        sorted_list += min(buffer)
        
        while(len(elements) > 0):
            record = elements.pop(0)

            
            

            

        

        
        
        


        
        

        

        
    


write_file.close()