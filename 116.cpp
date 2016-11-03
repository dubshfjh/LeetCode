#include <iostream>
using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(root==NULL){
            return;
        }
        TreeLinkNode *lev_head,*temp,*pre;//lev_head记录每一层的头节点，temp从每一层的头节点开始遍历至NULL，pre记录节点的前一个节点的右子节点
        lev_head=root;
        while(lev_head->left || lev_head->right){//头节点遍历到最后一层就可以停止了。从第1层至第n-1层节点，将每个节点的左子节点->next=右子节点；将前一个节点右子节点->next=当前节点的左子节点
            temp = lev_head;
            pre = NULL;//本层前一个节点的右子节点
            while(temp){
                if(pre){
                    pre->next = temp->left;
                }
                temp->left->next = temp->right;
                pre = temp->right;
                temp = temp->next;
            }
            lev_head = lev_head->left;
        }
    }
};

int main(){
    Solution sol = Solution();
    TreeLinkNode *root = new TreeLinkNode(1);
    TreeLinkNode *left1 = new TreeLinkNode(2);
    TreeLinkNode *right1 = new TreeLinkNode(3);
    TreeLinkNode *left11 = new TreeLinkNode(4);
    TreeLinkNode *left12 = new TreeLinkNode(5);
    TreeLinkNode *right11 = new TreeLinkNode(6);
    TreeLinkNode *right12 = new TreeLinkNode(7);

    root->left = left1;
    root->right = right1;
    left1->left = left11;
    left1->right = left12;
    right1->left = right11;
    right1->right = right12;

    sol.connect(root);
    return 0;
}