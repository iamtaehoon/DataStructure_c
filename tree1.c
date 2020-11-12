#include <stdio.h>
#include <stdlib.h>  // malloc

#define DATATYPE char

#include "tree.h"

int main() {
  TreeNode a, b, c, d, e, f;
  TreeNode* root;
  TreeNode* p;

  // malloc사용 안함, 개수가 정해져 있을때만 가능. 이건 자연스럽진 않지만 보기에 편함
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

  #malloc 사용
  p = (TreeNode*)malloc(sizeof(TreeNode));

  root = p;
  
  p->data  = 'A';
  p->left  = (TreeNode*) malloc(sizeof(TreeNode));
  p->right = (TreeNode*) malloc(sizeof(TreeNode));
  
  p->left->data  = 'B';
  p->left->left  = (TreeNode*) malloc(sizeof(TreeNode));
  p->left->right = NULL;

  p->right->data  = 'C'; 
  p->right->left  = NULL;
  p->right->right = NULL;

  p->left->left->data  = 'D'; 
  p->left->left->left  = NULL;
  p->left->left->right = NULL;


  
  return 0;
}
