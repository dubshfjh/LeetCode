/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *temp,*pre;
        if(head==NULL || head->next==NULL){
            return head;
        }  
        pre=temp=head;//pre为取值为当前元素序列的first元素,
        while(temp){
            while(temp->next && temp->val == temp->next->val){//temp将向右推进至取值为当前元素的last元素
                temp=temp->next;
            }
            if(temp != pre){
                pre->next=temp->next;
                temp=temp->next;
                pre=temp;
            }
            else{
                temp=temp->next;
                pre=temp;
            }
        }
        return head;
    }
};