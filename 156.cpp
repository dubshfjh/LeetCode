Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node)
     or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root.

For example:
Given a binary tree {1,2,3,4,5},
   1
 /  \
 2   3
/ \
4 5

return the root of the binary tree [4,5,2,#,#,3,1].
 4
/ \
5 2
 / \
 3 1

这题有一个重要的限制就是，整棵树的任何一个右孩子要么为拥有left兄弟的叶子节点，要么为空，所以右子都不会再生枝节
    因此上下颠倒递归的主体就是：对于每层存在left child的节点node，首先接收对(node->left)递归产生的下层子树的new root用于直接返回给上一层，
    然后将原来node->left的右孩子指针指向node，左孩子指针指向以及原来的右兄弟节点(即node->child)。最后将从最底层1路接收并保持不变的new root返回给上一层
    对于不存在left child的节点node(必然也不存在right child的leaf节点)，直接返回自己作为本层子树的new root

public:
TreeNode UpsideDownBinaryTree(TreeNode *root) {
    if(root == NULL){
        return root;
    }
    if(root->left){
        TreeNode *parent,*left,*right;
        parent = root;
        left = root->left;
        right = root->right;

        TreeNode *newroot = UpsideDownBinaryTree(root->left);
        left->left = right;
        left->right = node;
        return newroot;
    }
    else{
        return root;
    }
}



第二个思路是直接用迭代 代替 递归
把左子树继续颠倒，颠倒完后，原来的那个左孩子的左右孩子指针分别指向原来的根节点以及原来的右兄弟节点即可

TreeNode UpsideDownBinaryTree(TreeNode *root) {
    if(root == NULL){
        return root;
    }
    TreeNode *node = root;
    TreeNode *parent,*right_sib;//parent为node的父节点，right_sib为上一层的右子节点，即本层node的右兄弟节点
    parent = right = NULL;
    while(node){
        left = node->left;
        node->left = right_sib;

        right_sib = node->right;//right_sib更新为本层node的右子节点，即下层节点node->left的右兄弟节点
        node->right = parent;

        parent = node;
        node = left;
    }
    return parent;
}
