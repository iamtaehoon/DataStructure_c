#include <stdio.h>

const int number = 8;
int sorted[8];

void merge(int a[], int m, int middle, int n){
    int i = m;
    int j = middle +1;
    int k = m;

    while ((i<=middle) && (j<=n)) {
        if (a[i] < a[j]){
            sorted[k++]=a[i++];
        }
        else{
            sorted[k++] = a[j++];
        }
    }
    if (i <= middle){
        for(int t = i; t <= middle; t++){
            sorted[k++] = a[t++];
        }
    }
    else if(j<=n){//else로도 구현 가능하지만 그냥 더 가독성을 높이기 위해서
        for(int t =j; t<= n;t++){
            sorted[k++] = a[t++];
        }
    }
    for(int i = m; i<= n ;i++){
        a[i] =sorted[i];
    }
}

void merge_sort(int a[],start,end){
    if(start<end){
        int middle = (start+end)/2;
        merge_sort(a, start, middle);
        merge_sort(a,middle+1,end);
        merge(a, start, middle, end);
    }
}

int main(void){
    int array[number] = {2,5,4,6,3,8,1,7};
    for(int i = 0; i<number;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
    merge_sort(array, 0, number-1);
    for(int i = 0; i<number;i++){
        printf("%d ",array[i]);
    }
    
    return 0;
}
