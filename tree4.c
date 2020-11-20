#이진탐색트리의 탐색, 삽입, 삭제를 구현함
#malloc, free가 되지 않아 삭제는 반쪽자리 구현.
#데이터타입을 만들어서 했더니 삭제할 방법이 마땅히 떠오르지 않음.
#함수를 통해서 밖에 값을 없앨 수가 있나? free 대신 해당 data,left,right에 NULL을 넣어주면 되려나? 다음번에 한 번 더 생각해보기
#그래도 i 값이 남아있긴 하지만 연결고리는 지워버려서 tree 내에서 접근할 수 있는 방법은 없음!

#include <stdio.h>
#include <stdlib.h>
#define DATATYPE int

#include "tree.h"

//탐색, 삽입, 삭제를 구현할 거
TreeNode* search(TreeNode* node, int key){//재귀함수 뿐 아니라 while을 이용해서 작성할 수 있음. 근데 굳이?
    if(node == NULL){
        TreeNode null_data;
        null_data.data = -1;
        null_data.left = NULL;
        null_data.right = NULL;
        return &null_data;
        
    }
    if(key == node->data)
        return node;
    else if (key < node->data)
        return search(node->left, key);
    else//찾으려는 값이 더 큰 경우. 기준이 된 노드값보다-->오른쪽으로 이동해야지
        return search(node->right, key);

}

TreeNode * new_node(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = key;
    temp->left = NULL;
    temp->right = NULL;
    
    return temp;
}

TreeNode* insert_node(TreeNode* node, int key){
    if (node == NULL)//트리가 공백이면 새로운 노드를 반환한다.
        return new_node(key);
    else if (key < node->data)//찾는 값이 더 작으면 왼쪽으로 보내준다.
        node->left = insert_node(node->left, key);
    else if (key>node->data)
        node->right = insert_node(node->right, key);
    return node;
}

TreeNode* min_value_node(TreeNode* node){
    if (node->left == NULL){
        return node;
    }
    else
        return min_value_node(node->left);
}

TreeNode* delete_node(TreeNode* node, int key){
    //세가지 케이스가 존재. 단말노드, 자식이 1개만 있는경우, 자식이 2개 다 있는 경우
    if(node == NULL) return node;
    
    else{
        if(key < node->data)
            node->left = delete_node(node->left, key);
        else if(key > node->data)
            node->right = delete_node(node->right, key);
        else{//지울거를 만난 경우!
            //근데 그 지우는게 단말노드나 자식이 1개인 경우! 이건 상대적으로 쉬움
            if(node->left == NULL){
                TreeNode* temp = node->right;
                //free(node);//삭제 여기서 하는거
                return temp;
            }
            else if(node->right == NULL){
                TreeNode* temp = node->left;
                //free(node);//삭제 여기서 하는거
                //왜 에러가 발생하냐 하면, malloc으로 자리를 만들어 준게 아니라 treenode자료형을 만들어서 해줬기 때문에 free를 할 게 없음.
                return temp;
            }
            else{//자식노드가 두개 다 있는 경우
                TreeNode* temp = min_value_node(node->right);//무조건 오른쪽 서브노드의 가장 작은 값을 삭제할 노드 위치로 올려보낼거임
                node->data = temp->data;
                node->right = delete_node(node->right,temp->data);
                
            }
        }
    }
    
    return node;
    
}
    


int main() {
    TreeNode a, b, c, d, e, f, g, h, i;
    TreeNode* root;
    TreeNode* p;

    root = & a;

    // 그림 8-19 예제 (1) - malloc을 사용하지 않는 버전
    a.data  = 18;
    a.left  = & b;
    a.right = & c;

    b.data  = 7;
    b.left  = & d;
    b.right = & e;

    c.data  = 26;
    c.left  = NULL;
    c.right = & f;

    d.data  = 3;
    d.left  = NULL;
    d.right = NULL;

    e.data  = 12;
    e.left  = & h;
    e.right = NULL;

    f.data  = 31;
    f.left  = NULL;
    f.right = NULL;

    g.data = 27;
    g.left = NULL;
    g.right = NULL;
    
    h.data = 11;
    h.left = &i;
    h.right = NULL;
    
    i.data = 9;
    i.left = NULL;
    i.right = NULL;
    
    printf("%d\n",search(root, 18)->data);
    printf("%d\n",search(root, 3)->data);
    printf("%d\n",search(root, 300)->data);//-1이 나오는건 에러코드임. 내가 그렇게 코드를 작성.
    
    insert_node(root, 300);
    printf("%d\n",search(root, 300)->data);//앞에서 300이 없었는데 새로 300이 생겼지.
    delete_node(root, 300); // 단말노드 300 삭제
    printf("%d\n",search(root, 300)->data);//-1 나와야 함

    delete_node(root, 9); // b를 삭제해보자, 그러면 i 사라지고 9가 올라와서 그 자리를 차지했겠지
    printf("%d, %d, %d\n",b.data,b.left->data, b.right->data);
    //밑에거는 delete통해서 사라져버림. b값인 9를 delete해서 i 값이 올라갔기 때문에 없는 값임!
    //printf("%d",h.left->data); //원래 삭제가 되있어야 하는데 삭제가 안되어 있는 이유. free가 안되가지고 저기 있는 저 변수들을 없애 줄 방법이 따로 없음 ㅋ
    printf("%d",c.right->data); //원래 삭제가 되있어야 하는데 삭제가 안되어 있는 이유. free가 안되가지고 저기 있는 저 변수들을 없애 줄 방법이 따로 없음 ㅋㅋ

    
    printf("\n");
  
    return 0;
}
