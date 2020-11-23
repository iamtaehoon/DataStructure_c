#광주 지하철 노선표를 다익스트라를 사용해서
#지점 두곳을 입력하면 최단거리를 계싼해주는 알고리즘
#중간저장. 엑셀파일을 가지고 그래프, 그리고 연결 노드와 거리까지 데이터로 만들어냄

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

for row in info_list[4:]:
    for x in range(row[7]):
        root = round(( (info_list[row[1]+3][5]-info_list[int(row[x+8])+3][5])**2 + (info_list[row[1]+3][6]-info_list[int(row[x+8])+3][6])**2 ) ** 0.5)
        #노드 간 거리를 계산해서 반올림해줌
        graph[row[1]].append((int(row[x+8]),root))

# 그래프 안에 노드 연결된 애들 잘 들어갔나 확인용
for i in range(cnt+1):
    print(graph[i])
