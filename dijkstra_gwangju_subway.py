#광주 지하철 노선표를 다익스트라를 사용해서
#지점 두곳을 입력하면 최단거리를 계싼해주는 알고리즘
#중간저장. 최단거리는 구함. 이제 최단경로만 표시해주면

import xlrd

INF = int(1e9)
cnt = 0 #64개 있음. 이 정류장이 몇 개 있는지 기록하려고. 노드의 개수

workbook = xlrd.open_workbook('gwangju_subway_full.xlsx')
worksheet = workbook.sheet_by_name('gwangju_subway')
info_list = worksheet._cell_values

for row in info_list[4:]:
    row[1] = int(row[1])
    row[7] = int(row[7])
    cnt += 1
    #row[0], row[2], row[9], row[10] 필요없는 값
    #row[1]은 인덱스(노드들의 번호), row[3]row[4]는 입력값과 결과값. row[5]row[6]은 좌표 거리계산할때 사용, row[7]은 몇개의 노드가 연결되었는지, row[8]row[9]row[10]은 연결되어 있는 값
# 엑셀에 있는 값이 잘 들어갔나 확인용
#    print(row)

graph = [[] for i in range(cnt+1)]
visited = [False]*(cnt+1)
distance = [INF]*(cnt+1)
parents = [0]*(cnt+1)
trace = []

for row in info_list[4:]:
    for x in range(row[7]):
        root = round(( (info_list[row[1]+3][5]-info_list[int(row[x+8])+3][5])**2 + (info_list[row[1]+3][6]-info_list[int(row[x+8])+3][6])**2 ) ** 0.5)
        #노드 간 거리를 계산해서 반올림해줌
        graph[row[1]].append((int(row[x+8]),root))

# 그래프 안에 노드 연결된 애들 잘 들어갔나 확인용
for i in range(cnt+1):
    print(graph[i])

departure_name, departure_line = input().split()
arrival_name, arrival_line = input().split()

for row in info_list[4:]:
    if (row[3] == departure_name) and (row[4] == departure_line):
        start = row[1]
        #여기가 출발점이다라는 뜻 나머지는 다 continue~ 노드번호를 따오면 될듯.
        break
for row in info_list[4:]:
    if (row[3] == arrival_name) and (row[4] == arrival_line):
        end = row[1] #도착 노드번호
        break


def get_smallest_node():
    min_value = INF
    index = 0
    for i in range(1,cnt+1):
        if distance[i] < min_value and not visited[i]:
            min_value = distance[i]
            index = i
    return index

def dijkstra(start,end):
    distance[start] = 0
    visited[start] = True
    for j in graph[start]:
        distance[j[0]] = j[1]#j[0]은 노드 j[1]은 거리 distance[노드번호] = 거리 입력 #무한대를 입력값으로 바꿔줌
        parents[j[0]] = start
    for i in range(cnt-1):#시작노드 빼고 총 n-1번 돌거다.
        now = get_smallest_node()
        visited[now] = True
        for j in graph[now]:
            cost = j[1] + distance[now]
            if cost < distance[j[0]]:
                parents[j[0]] = now
                distance[j[0]] = cost

    current = end
    while current != start:
        trace.append(current)
        current = parents[current]
    trace.append(start)
    trace.reverse()


dijkstra(start,end)

print("{0}({1})에서 {2}({3})까지 가는 최단거리는 ".format(info_list[start+3][3],info_list[start+3][4],info_list[end+3][3],info_list[end+3][4]),end='')
print(distance[end],end='')
#print(parents)
print("이고,\n최단경로는 ")
#print(trace)
for i in trace:
    print("{0}({1})->".format(info_list[i + 3][3], info_list[i + 3][4]),end ='')
print("하차한다.")
#for i in range(1,cnt+1):
#    if distance[i] == INF:
#        print('INFINITY')
#    else:
#        print(distance[i])
