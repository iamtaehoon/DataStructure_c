//우선순위 큐를 만들어봤다. adt는 create, init, insert_max_heap, delete_max_heap
//더 가독성이 뛰어나고 메모리를 덜 쓰는 코드로 만들 수도 있다. 내 생각대로 만들었지만, 더 효율적인 코드는 강의자료에 나와있음.
//나는 그냥 수도코드를 짠대로 하나하나 구현해봄
//create,init, 밑에 히프를 만드는 과정들은 강의자료 

#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200
typedef struct {
    int key;
}element; //왜 굳이 구조체로 만든거지? 내가 구조체 이해가 ㅇ아직 덜된건가?

typedef struct{
    element heap[MAX_ELEMENT];
    int heap_size;
}HeapType;

HeapType* create(){
    return (HeapType*)malloc(sizeof(HeapType));
}
void init(HeapType* h){
    h->heap_size = 0;
}

void insert_max_heap(HeapType* heap, element item){ // item을 heap에 넣어줄거임.
    int i;
    heap->heap_size += 1;
    i = heap->heap_size;
    heap->heap[i]= item;//item은 int 가 아니라 element임
    
    while((i != 1) && (heap->heap[i].key > heap->heap[i/2].key)){
        int temp;
        temp = heap->heap[i].key;
        heap->heap[i].key = heap->heap[i/2].key;
        heap -> heap[i/2].key = temp;
        i/=2;
    }
}
element delete_max_heap(HeapType* heap){
    int parent = 1;
    int child = 2;
    int temp;
    element item;
    item = heap->heap[1];
    heap->heap[parent].key = heap->heap[heap->heap_size].key;
    while(child <= heap->heap_size){
        if(heap->heap[child].key < heap->heap[child+1].key)
            child+=1;//else면 차일드 그대로 둘거니까 else 굳이 안써도 됨.
        if(heap->heap[child].key <= heap->heap[parent].key)
            break;//위에 있는 값이 더 크면 그냥 거기서 끝내면 됨.
        temp = heap->heap[parent].key;//바꼈지? child였던 값이 위로 올라가고 parent는 밑으로 내려옴. 그러면 이제 parent는 child가 되고 child는 다시 2를 곱해야지. 밑에 단계로 내려가~
        heap->heap[parent].key = heap->heap[child].key;
        heap->heap[child].key = temp;
        parent = child;
        child = 2*child;
    }
    
    return item;
}



int main(){
    element e1 = {10}, e2 ={5}, e3 ={30};
    element e4,e5,e6;
    HeapType* heap;
    
    heap = create();//힙을 생성해주고, 초기화 시켜줘야함
    init(heap);
    
    insert_max_heap(heap, e1);//삽입
    insert_max_heap(heap, e2);
    insert_max_heap(heap, e3);
    
    e4 = delete_max_heap(heap);//삭제
    printf("< %d > ", e4.key);
    e5 = delete_max_heap(heap);
    printf("< %d > ", e5.key);
    e6 = delete_max_heap(heap);
    printf("< %d > ", e6.key);
    
    free(heap);
    return 0;
}
