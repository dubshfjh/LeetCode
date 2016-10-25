/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
//1->1->2->2->3: 3
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
        ListNode *newhead = new ListNode(0);//手动设置一个空头指向head，可以避免对本身链表的head各种右移。
        newhead->next=head;//此时把head本身也视作一个普通元素即可

        pre=newhead;
        temp=head;
        while(temp){//temp是遍历到的当前元素，pre为前一个未删除元素
            while(temp->next && temp->val == temp->next->val){
                temp=temp->next;
            }
            if(temp != pre->next){//temp发生了移动,此时的temp为最后一个取相同值的元素，pre应该指向它的next
                pre->next=temp->next; //temp最多到最后一个元素，所以temp必然存在，不需要再判断temp是否为NULL了
                temp=temp->next;
            }
            else{//此时不需要删除本元素，pre右移到temp。temp分析下一个元素即可
                pre=temp;
                temp=temp->next;
            }
        }
        return newhead->next;
    }
};