/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
头插法，新建一个pre_head指向head，使用指针temp1从head->next开始遍历每个节点，让每个temp1指向pre_head->next，然后pre_head指向temp1。reverse完毕后head为最后一个节点，设置head->next为NULL

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next){
            return head;
        }
        ListNode *pre_head = new ListNode(0);
        pre_head->next = head;
        ListNode *temp1,*temp2;
        temp1 = head->next;
        while(temp1){//temp1应该从head1->next开始头插，因为当temp1==head时，头插法会使得temp1指向自身
            temp2 = temp1->next;
            temp1->next = pre_head->next;
            pre_head->next = temp1;
            temp1 = temp2; 
        }
        head->next = NULL;//head此时为最后一个node，但它指向了链表的第2个Node，所以需要断开
        return pre_head->next;
    }
};