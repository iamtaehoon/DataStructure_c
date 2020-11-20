//이진트리 연산 3가지 함수를 구현해보았다.
// 노드개수를 반환, 입력한 노드의 높이를 반환, leafnode의 개수를 반환
// get_node_count, get_height, leaf_node_count

#include <stdio.h>
#include <stdlib.h>
#define DATATYPE char

#include "tree.h"

int max(int x, int y){
    return x>y?x:y;
}

int get_node_count(TreeNode* bt){//인자로 주어진 binary tree
    int count = 0;
    if (bt != NULL)
        count = get_node_count(bt->left) + get_node_count(bt->right)+1;

    return count;
}
int get_height(TreeNode* bt){
    int height= 0;
    if(bt != NULL)
        height = max(get_height(bt->left),get_height(bt->right)) + 1;
        
    return height;
}
int leaf_node_count(TreeNode* bt){
    int cnt = 1;
    if (bt->left == NULL && bt->right == NULL)
        return cnt;
    else if (bt->right == NULL)
        return leaf_node_count(bt->left);
    else if (bt->left == NULL)
        return leaf_node_count(bt->right);
    else
        return leaf_node_count(bt->left) + leaf_node_count(bt->right);
}


int main() {
    TreeNode a, b, c, d, e, f;
    TreeNode* root;
    TreeNode* p;

    root = & a;

    // 그림 8-19 예제 (1) - malloc을 사용하지 않는 버전
    a.data  = 'A';
    a.left  = & b;
    a.right = & c;

    b.data  = 'B';
    b.left  = & d;
    b.right = & e;

    c.data  = 'C';
    c.left  = & f;
    c.right = NULL;

    d.data  = 'D';
    d.left  = NULL;
    d.right = NULL;

    e.data  = 'E';
    e.left  = NULL;
    e.right = NULL;

    f.data  = 'F';
    f.left  = NULL;
    f.right = NULL;

    printf("%d\n",get_node_count(root));
    printf("%d\n",get_height(root));
    printf("%d\n",get_height(&c));
    printf("%d\n",get_height(&f));
    printf("%d\n",leaf_node_count(root));

    printf("\n");
  
    return 0;
}
