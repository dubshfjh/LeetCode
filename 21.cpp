#include <iostream>
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *head,*temp;
        head=(ListNode*)malloc(sizeof(ListNode));
        head->next=NULL;
        temp=head;
        while(l1&&l2){
        	if(l1->val<l2->val){
        		temp->next=l1;
        		temp=l1;
        		l1=l1->next;
        	}
        	else{
        		temp->next=l2;
        		temp=l2;
        		l2=l2->next;
        	}
        }
        if(l1){
        	temp->next=l1;
        }
        if(l2){
        	temp->next=l2;
        }
        head=head->next;//当l1和l2都为NULL时,head=head->next后，return NULL
        return head;
    }
};