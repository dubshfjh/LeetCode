#include <iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
};
 
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *temp,*del_pre;//不能声明为 ListNode* temp,del_pre!!!!!
        temp=head;
        for(int i=0;i<n;i++){
        	temp=temp->next;
        }
        if(temp==NULL){//若删除倒数第len个，e.g.:1->2->3，要求删除倒数第3个节点，则temp移动3次后为NULL
        	head=head->next;//，此时删除1节点，head=head->next即可
        	return head;
        }

       	del_pre=head;
       	while(temp->next!=NULL){
       		temp=temp->next;
       		del_pre=del_pre->next;
       	}
       	//循环结束后del_pre和末尾节点之间还有n-2个节点，因此del_pre->next就是倒数第n个节点，移除它即可
       	del_pre->next=del_pre->next->next;
       	return head;
    }
};