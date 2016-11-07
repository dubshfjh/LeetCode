/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
本题的解法完全可以用于Populating Next Right Pointers in Each Node。

本题的一个难点在于要求使用常数空间，这样的话普通的深度优先遍历由于需要递归压栈而无法使用，普通的广度优先搜索需要使用队列也无法使用，因此选择使用两层迭代，使用current指向当前结点的方法进行广度优先遍历。

同之前的简化版本不同，本题的区别在于二叉树并不完整，之前算法中可以将当前结点的右子结点与下一结点的左子结点相连的方法失效。因此这里选用广度优先遍历，引入“层”的概念，需要储存两个值：遍历的当前结点、本层上一个非空的结点(previous)。由于寻找遍历的下一个结点需要使用父层的next指针，因此算法设计为遍历当前结点时完成三件事：

1. 如果左子结点存在，则更新previous的next指向左子结点
2. 如果右子结点存在，则更新左子结点（或previous）的next指向右子结点
3. 分析完当前结点的孩子之后，current右推到其next
4. 分析完一整层节点后，current更新为child_head即可

class Solution {
public:
    void connect(TreeLinkNode *root) {
        TreeLinkNode *child_head,*pre,*current;//child_head为下一层头节点(即本层的第一个子节点)，pre为本层的前一个非空节点，current为当前节点
        current = root;
        pre = child_head = NULL;
        while(current){//依次分析第1层到第n-1层的节点，current从每层的头节点开始遍历，对其下一层的子节点进行连接
            while(current){//依次分析同一层的每个节点，对于左子为空 && 右子为空的节点，不需要对其子节点进行任何操作，因此直接右移到next即可
                if(current->left){
                    if(pre){
                        pre->next = current->left;
                    }
                    else{//pre为空，说明current为本层的第一个节点，而且此时currenr->left非空
                        child_head = current->left;
                    }
                    pre = current->left;

                }

                if(current->right){
                    if(pre){
                        pre->next = current->right;
                    }
                    else{//pre为空，说明current为本层的第一个节点
                        child_head = current->right;
                    }
                    pre = current->right;
                }
                current = current->next;//当前节点的子节点遍历完毕，右推一次
            }
            current = child_head;//当前层遍历完毕，转入下一层
            pre = child_head = NULL;
        }
    }
};

Wrong Answer，各种情况分析交叉在一起，过于混乱
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
        TreeLinkNode *lev_head,*temp,*pre,*child_head;//lev_head记录每一层中first拥有子节点的头节点，temp从每一层的头节点开始遍历至NULL，pre记录节点的前一个存在child的节点的最右侧子节点
        lev_head = root;
        while(temp){
            temp = lev_head;
            pre = NULL;
            child_head = NULL;
            while(temp){//pre实际上就是本层链表的前一个节点
                cout<<"temp: "<<temp->val<<endl;

                if(pre){//如果链表中存在前一个节点，而且temp存在子节点，则更新pre->next为最右侧的子节点
                    pre->next = (temp->left)?temp->left:pre->next;
                    pre->next = (temp->right)?temp->right:pre->next;
                    cout<<"pre: "<<pre->val<<" ,next: "<<pre->next->val<<endl;
                }
                else{//不存在pre，说明如果temp存在子节点，则其最左侧的子节点即为下一层的链表头
                    if(temp->left || temp->right){
                        child_head = (temp->left)?temp->left:temp->right;
                    }
                }

                if(temp->left && temp->right){//如果temp有子节点，则将pre更新到最右侧的子节点，如果双子都存在还需要左子->右子
                    pre = temp->right;
                    temp->left->next = temp->right;//双子都存在，左子指向右子
                }
                else if(temp->left || temp->right){
                    pre = (temp->left)?temp->left:temp->right;
                }//else{pre = pre}
                cout<<"New pre: "<<pre->val<<endl;
                temp = temp->next;
            }
            
            if(child_head==NULL){
                break;
            }
            temp = child_head;
            while(temp->left==NULL && temp->right==NULL && temp){//找到下一层节点中最靠前，而且本身拥有children节点的作为新的lev_head
                temp = temp->next;
            }
            if(temp){//temp存在，lev_head被赋值为下层的最靠前节点
                lev_head = temp;
            }
            
            cout<<"Next Layer: "<<lev_head->val<<endl;
        }
    }
};


int main(){
    Solution sol = Solution();
    TreeLinkNode *root = new TreeLinkNode(3);
    TreeLinkNode *left1 = new TreeLinkNode(9);
    TreeLinkNode *right1 = new TreeLinkNode(20);
    TreeLinkNode *left11 = new TreeLinkNode(4);
    TreeLinkNode *left12 = new TreeLinkNode(5);
    TreeLinkNode *right11 = new TreeLinkNode(15);
    TreeLinkNode *right12 = new TreeLinkNode(7);

    root->left = left1;
    root->right = right1;
    // left1->left = left11;
    // left1->right = left12;
    right1->left = right11;
    right1->right = right12;

    sol.connect(root);
    return 0;
}
