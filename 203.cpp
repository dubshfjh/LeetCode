/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
设置一个新头pre_head指向head，初始化指向head前方节点的指针pre 为 pre_head，使用head遍历整个链表。1.若 head->val == val，则pre->next = head，head右移一次  2.pre右移至head,head右移一次
踩到的坑：
    当不需要移除节点时，pre应该保持在原地不动!!!
    只有当不移除节点时pre才随着head右移，否则在遇到[1,1]时，在移除first 1节点后,pre右移到了second 1，于是second 1没被移除
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *pre_head = new ListNode(0);
        pre_head->next = head;
        ListNode *pre = pre_head;
        while(head){
            if(head->val == val){
                pre->next = head->next;
            }
            else{//Attention!!!当需要移除节点时，pre应该保持在原地不动!!!只有当不移除节点时pre才随着head右移
                pre = head;
            }
            head = head->next;
        }
        return pre_head->next;
    }
};