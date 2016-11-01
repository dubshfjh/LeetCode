/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
算法思想：手动插入一个空头newhead，规定子树在链表中头节点的前一个节点pre，以及该子树的节点个数size。对每一棵子树选择其中间节点(即第(size+1)/2个节点)，
作为其根节点node并构建，其左子树区间的下边界与size为[pre,(size+1)/2-1],node->left赋值为左子树根节点；其右子树区间的下边界与size为[node,size-leftsize]，
node->right赋值为右子树根节点。如果size==0，说明当前子树的根节点为NULL。
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        int i=0;
        ListNode *temp;
        ListNode *newhead = new ListNode(0);
        newhead->next=head;
        temp=head;
        while(temp){
            i++;
            temp=temp->next;
        }
        return construcNode(newhead,i);
    }

    TreeNode* construcNode(ListNode* pre,int size){//pre是当前子树链表的前一个节点
        if(size<=0){
            return NULL;
        }
        int i;
        ListNode *mid;
        mid = pre;
        for(i=1;i<=(size+1)/2;i++){//mid为链表的第(1+size)/2个元素，从pre移动(1+size)/2次即可到达
            mid = mid->next;
        }
        if(i>1){//其实size>=1时，i遍历完后就>=2了
            TreeNode *node = new TreeNode(mid->val);
            int leftsize = i-2;//i遍历完后变成了(size+1)/2+1
            int rightsize = size-1-leftsize;
            node->left = construcNode(pre,leftsize);
            node->right = construcNode(mid,rightsize);
            return node;
        }
        else{//这里应该不用进入
            return NULL;
        }
    }
};