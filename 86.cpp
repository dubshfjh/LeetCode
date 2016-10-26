/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

思想：首先加入一个空头new_head指向head，使用temp当遇到<x的节点时尝试左移，因为要保持原序列只能用尾插法(即使用temp_head记录左半链表的last元素)

对于<x的节点，需要左移
一、如果temp与temp_head之间有其他节点：
1. pre->next=temp->next
2. temp->next=temp_head->next
3. temp_head->next=temp
4. temp_head右移到temp
5. temp右移到pre->next
(pre不需要右移)

二、如果temp就是temp_head的next，那么不需要temp->next指向temp_head->next(自身指向自身的谬误)
1. temp_head右移到temp
2. pre右移到temp
3. temp右移

对于>=x的节点，直接分析next节点
1.pre右移到temp
2.temp右移

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode *new_head,*temp_head,*pre,*temp;
        if(head==NULL || head->next==NULL){
            return head;
        }
        new_head = new ListNode(0);
        new_head->next=head;
        pre=temp_head=new_head;//temp_head记录左半部分列表(即<x部分链表)的最后一个节点
        temp=head;//第一个节点如果<x，则保持不动即可
        while(temp){
            // cout<<"整体的第一个元素："<<new_head->next->val<<endl;
            if(temp->val < x){
                if(temp != temp_head->next){//如果temp不是temp_head的next，则temp->nect需要指向temp_head->next
                    pre->next=temp->next;
                    temp->next=temp_head->next;
                    temp_head->next=temp;//必须得将temp_head->next指向temp，否则每一个左移的节点都会丢失
                    temp_head=temp;
                    temp=pre->next;    
                }
                else{//如果temp就在temp_head后面，则temp不能用Next指向自身，temp_head右移一次到temp,pre和temp也右移一次
                    temp_head=temp;
                    pre=temp;
                    temp=temp->next;
                }
                // cout<<"左半链表的last元素："<<temp_head->val<<",,,"<<temp_head->next->val<<endl;
            }
            else{
                pre=temp;
                temp=temp->next;
                // cout<<"右半链表的元素："<<pre->val<<endl;
            }
        }
        
        return new_head->next;
    }
};