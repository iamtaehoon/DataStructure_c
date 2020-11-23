#다익스트라 알고리즘을 사용해 광주시내 지하철 최단경로, 최단거리를 보여주는 코드

import xlrd

INF = int(1e9)
cnt = 0  # 64개 있음. 정류장 노드의 개수

workbook = xlrd.open_workbook('gwangju_subway_full.xlsx')
worksheet = workbook.sheet_by_name('gwangju_subway')
info_list = worksheet._cell_values

for row in info_list[4:]:
    row[1] = int(row[1])
    row[7] = int(row[7])
    cnt += 1
    # row[0], row[2], row[9], row[10] 필요없는 값
    # row[1]은 인덱스(노드들의 번호), row[3]row[4]는 입력값과 결과값.
    # row[5]row[6]은 좌표 거리계산할때 사용, row[7]은 몇개의 노드가 연결되었는지,
    # row[8]row[9]row[10]은 연결되어 있는 값

graph = [[] for i in range(cnt + 1)]
visited = [False] * (cnt + 1)
distance = [INF] * (cnt + 1)
parents = [0] * (cnt + 1)
trace = []  # 경로 추적을 위해 parents, trace를 사용한다.

# 데이터를 전처리 해준다. int로 바꿀 값들을 바꿔준다.
# 왜 4부터 시작하는가? 4부터 데이터가 입력되어있다. 4가 인덱스 1, number 100, 이름 녹동이다. 이거 이제 인덱스를 number 바꿔주면 댈듯!로 99를 더해주면 돼
for row in info_list[4:]:
    for x in range(row[7]):
        # 아래 공식은 두 점 사이의 거리를 계산하는 공식이다. 거리는 편의를 위해 반올림 해준다.
        root = round(((info_list[row[1] + 3][5] - info_list[int(row[x + 8]) + 3][5]) ** 2 + (
                    info_list[row[1] + 3][6] - info_list[int(row[x + 8]) + 3][6]) ** 2) ** 0.5)
        graph[row[1]].append((int(row[x + 8]), root))

# 입력을 받는다.
print("우선 탑승하는 역의 이름과 호선을 공백으로 구분하여 입력하고 엔터를 누른 다음, 내리는 역의 이름과 호선을 공백으로 구분하여 입력하시오.")
print("입력 예시 :")
print("녹동 1호선")
print("효천 2호선(3단계)")
print("위의 양식처럼 하단에 작성하시오.")
departure_name, departure_line = input().split()
arrival_name, arrival_line = input().split()

# 출발, 도착하는 값을 한글로 입력했을 때 해당 number를 가져온다.(현재 인덱스로 작성되어 있음.)
for row in info_list[4:]:
    if (row[3] == departure_name) and (row[4] == departure_line):
        start = row[1]
        break
for row in info_list[4:]:
    if (row[3] == arrival_name) and (row[4] == arrival_line):
        end = row[1]
        break


# 방문하지 않은 노드 중 최단거리를 갖는 인덱스 값을 찾는다.
def get_smallest_node():
    min_value = INF
    index = 0
    for i in range(1, cnt + 1):
        if distance[i] < min_value and not visited[i]:
            min_value = distance[i]
            index = i
    return index


def dijkstra(start, end):
    distance[start] = 0
    visited[start] = True
    for j in graph[start]:
        distance[j[0]] = j[1]
        parents[j[0]] = start

    for i in range(cnt - 1):  # 시작노드 빼고 총 n-1번 돌거다.
        now = get_smallest_node()
        visited[now] = True
        for j in graph[now]:
            cost = j[1] + distance[now]
            # 새로 입력된 값이 기존 값보다 작으면, 작은 값으로 변경해준다.
            if cost < distance[j[0]]:
                # 값이 변경되었다는 건 해당 노드의 부모값은 그 전에 방문한 노드가 된다.(그림을 보면 이해가 빠르다.)
                parents[j[0]] = now
                distance[j[0]] = cost

    # end값부터 부모노드를 역순으로 찾아낸다. 이후 reverse를 통해 원래 방향으로 뒤집는다.
    current = end
    while current != start:
        trace.append(current)
        current = parents[current]
    trace.append(start)
    trace.reverse()


dijkstra(start, end)

print("{0}({1})에서 {2}({3})까지 가는 최단거리는 ".format(info_list[start + 3][3], info_list[start + 3][4], info_list[end + 3][3],
                                               info_list[end + 3][4]), end='')
print(distance[end], end='')
# print(parents)
print("이고,\n최단경로는 ")
# print(trace)
for i in trace:
    print("{0}({1})->".format(info_list[i + 3][3], info_list[i + 3][4]), end='')
print("하차한다.")

