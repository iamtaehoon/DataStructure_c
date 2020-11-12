#include <stdio.h>
#include <stdlib.h>  // malloc

#define DATATYPE char

#include "tree.h"


//전위
void ppreorder(TreeNode* bt) {
    if (bt == NULL) // 이진트리bt가 비어있으면
        return;
    else { // 아니면
        printf("%c ", bt->data); // 현재 노드 출력
        ppreorder( bt->left );    // 왼쪽 서브트리를 전위 순회
        ppreorder( bt->right );   // 오른쪽 서브트리를 전위 순회
        
    }
}

//중위
void iinorder(TreeNode* bt) {
    if (bt == NULL)
        return;
    else{
        iinorder(bt->left);
        printf("%c ", bt->data);
        iinorder(bt->right);
        
    }
    
}


//후위
void ppostorder(TreeNode* bt) {
    if (bt == NULL)
        return;
    else{
        ppostorder(bt->left);
        ppostorder(bt->right);
        printf("%c ", bt->data);
    }
}


int main() {
    TreeNode a, b, c, d, e, f;
    TreeNode* root;

    root = &a;

    a.data  = 'A';
    a.left  = &b;
    a.right = &c;

    b.data  = 'B';
    b.left  = &d;
    b.right = &e;

    c.data  = 'C';
    c.left  = &f;
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

    // preorder traversal : A B D E C F
    ppreorder( root );
    printf("\n");

    // inorder traversal : D, B, E, A, F, C
    iinorder( root );
    printf("\n");

    // postorder traversal : D, E, B, F, C, A
    ppostorder( root );
  
    printf("\n");
  
  return 0;
}
