from pathlib import Path

buffer_size = 5

input_path = Path(__file__).parent / 'replacement_input.txt'
output_path = Path(__file__).parent / 'replacement_output.txt'

# 파일값의 최대값(나중에 버퍼에서 최솟값을 찾는 함수에서 최소값의 초기값을 정할때 씀)
max_value = 100

class Freeze:
    def __init__(self, value: int, freeze=False):
        self.value = value
        self.is_freeze = freeze

# 인자로 주어진 버퍼에서 freeze안된 요소들 중 최소값의 인덱스를 반환
def find_min(buffer: list):
    min_value = max_value + 1
    min_index = -1

    for i in range(len(buffer)):
        if not buffer[i].is_freeze and buffer[i].value < min_value:
            min_value = buffer[i].value
            min_index = i

    return min_index

write_file = open(output_path, "w")

with open(input_path, "r") as read_file:
    cases_num = int(read_file.readline())

    for n in range(cases_num):
        buffer = []
        runs = [[]]
        runs_idx = 0
        freeze_cnt = 0

        element_num = int(read_file.readline())  # 원소 개수
        line = read_file.readline()  # str 한줄 읽기

        pharse_num = ""
        current_num = None

        # 버퍼 생성 및 runs생성
        for i in range(len(line)):
               # 버퍼가 꽉 찬 경우
            if len(buffer) == buffer_size:
                # 버퍼가 다 동결 된 경우
                if freeze_cnt == buffer_size:
                    runs.append([])
                    runs_idx += 1

                    for j in range(len(buffer)):
                        buffer[j].is_freeze = False
                    freeze_cnt = 0

                    min_idx = find_min(buffer)
                    current_num = buffer.pop(min_idx).value
                    runs[runs_idx].append(current_num)

                else:
                    min_idx = find_min(buffer)
                    current_num = buffer.pop(min_idx).value
                    runs[runs_idx].append(current_num)

            # 버퍼 채우기
            if line[i] == " " or i == len(line) - 1:
                # 버퍼에 들어오는 값이 동결해야되는 값일 경우
                if pharse_num and (current_num != None) and (int(pharse_num) < current_num):
                    buffer.append(Freeze(int(pharse_num), True))
                    freeze_cnt += 1
                    pharse_num = ""
                
                elif pharse_num:
                    buffer.append(Freeze(int(pharse_num)))
                    pharse_num = ""

            else:
                pharse_num += line[i]
        
        # 입력파일을 다 읽고 버퍼가 남은 경우
        while buffer:
            # 버퍼에 남은 값이 다 동결되어있는 경우
            if freeze_cnt == len(buffer):
                runs.append([])
                runs_idx += 1

                for k in range(len(buffer)):
                    buffer[k].is_freeze = False
                freeze_cnt = 0
                
                min_idx = find_min(buffer)
                current_num = buffer.pop(min_idx).value
                runs[runs_idx].append(current_num)
            
            else:
                min_idx = find_min(buffer)
                current_num = buffer.pop(min_idx).value
                runs[runs_idx].append(current_num)
        
        # 생성된 Runs 숫자 쓰기
        write_file.write(str(len(runs)) + "\n")

        # runs[0], runs[1], ... 작성
        for i in range(len(runs)):
            for j in range(len(runs[i])):
                if j != (len(runs[i]) - 1):
                    write_file.write(str(runs[i][j]) + " ")
                
                elif j == (len(runs[i]) - 1) and i != len(runs):
                    write_file.write(str(runs[i][j]) + "\n")
                
                else:
                    write_file.write(str(runs[i][j]))
            
write_file.close()