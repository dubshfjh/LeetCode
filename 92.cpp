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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *newhead,*temphead,*pre,*temp;
        int i=1;
        newhead = new ListNode(0);
        newhead->next=head;
        pre=newhead;
        temp=head;
        while(i<m){
            pre=temp;
            temp=temp->next;
            i++;
        }

        temphead=pre;//固定住reversed部分链表的头部
        while(i<=n){//pre始终是第m-1个元素，temp会从第m个元素遍历到第n个元素，依次使用头插法
            if(temp!=temphead->next){
                pre->next=temp->next;
                temp->next=temphead->next;
                temphead->next=temp;
                temp=pre->next;
            }
            else{
                pre=temp;
                temp=temp->next;
            }
            i++;
        }

        return newhead->next;
    }
};