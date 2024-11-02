buffer_size = 5
# buffer = [0 for i in range(buffer_size)]

class Freeze():
    def __init__(self, value):
        self.value = value
        self.is_freeze = False

# get index of minimum element in list
# TO-DO : buffer중에서 freeze된 것 빼고 최소값 찾기
def find_min(buffer : list):
    if len(buffer) == 0:
        return

write_file = open("G:/다른 컴퓨터/내 컴퓨터/2학년 2학기/파일처리론/파일처리론 과제/replacement_output.txt", "w")

with open("G:/다른 컴퓨터/내 컴퓨터/2학년 2학기/파일처리론/파일처리론 과제/replacement_input.txt", "r") as read_file:
    cases_num = int(read_file.readline()) # 4

    for i in range(cases_num):
        buffer = []
        runs = []
        runs_num = -1
        freeze_cnt = 0
        
        element_num = read_file.readline() # 원소 개수
        elements = list(map(int, read_file.readline().strip().split())) # 입력 값을 읽음

        # 레코드의 수가 버퍼 크기보다 작거나 같을 경우
        # 그냥 sort하고 파일 write
        if len(elements) <= buffer_size:
            runs_num += 1
            elements.sort()
            write_file.write(runs_num)
            write_file.write(" ".join(map(str, elements)))

        else:
            # 버퍼 채우기
            for i in range(buffer_size):
                buffer[i] = Freeze(elements.pop(0))
            
            # 입력 레코드가 남아 있을경우
            while(len(elements) > 0):
                # 최초 실행이거나 버퍼가 완전히 동결된 경우
                if(runs_num == -1 or freeze_cnt == 5):
                    runs.append([])
                    runs_num += 1
                
                # 버퍼에서 최소값 인덱스 찾기
                min_idx = find_min(buffer)

                # 버퍼 최소값을 runs에 추가 하고 current_num 갱신
                current_num = buffer.pop(min_idx)
                runs[runs_num].append(current_num)

                # 버퍼에 레코드 1개 채우기
                buffer.append(Freeze(elements.pop(0)))

                # 버퍼에 읽은 값이 가장 마지막에 넣은 값보다 작은 경우
                if buffer[len(buffer) - 1].value < current_num:
                    buffer[len(buffer) - 1].is_freeze = True
                    freeze_cnt += 1
                
                




            
            

write_file.close()