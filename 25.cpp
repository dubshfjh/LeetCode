#include <iostream>
using namespace std;

typedef struct ListNode{
	int val;
	ListNode *next;
}ListNode;

#include <iostream>
using namespace std;

typedef struct ListNode{
	int val;
	ListNode *next;
}ListNode;

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k){
        int i;
        ListNode *newhead,*nexthead,*temp;
        newhead=head;
        if(k<=1||head==NULL){//此时无需reverse，递归在第一层就可以终结了
        	return head;
        }
        for(i=1;i<k;i++){//newhead尝试从head开始右移k-1次，只有从head到newhead的节点数为k时，才继续递归
        	if(newhead->next){//只有newhead的下一个节点不为NULL时，统计节点的数i才++
        		newhead=newhead->next;
        	}
        	else{
        		break;
        	}
        }
        if(i<k){//剩余未reverse的节点数<k，直接返回head
        	return head;
        }
        else{//头插法建立临时链表
        	nexthead=newhead->next;//头插法会消除原链表之间的连接关系，需要额外用个变量记录下次的head

        	ListNode *temphead=(ListNode*)malloc(sizeof(ListNode));
        	temphead->next=NULL;
        	newhead=head;
        	for(i=0;i<k;i++){
        		temp=newhead->next;//必须提前记录插头node的下一个节点

        		newhead->next=temphead->next;//头插法
        		temphead->next=newhead;

        		newhead=temp;//newhead移到之前记录的原链表的下一个节点
        	}
        	temphead=temphead->next;
			newhead=temphead;//记录本层的新头节点
        	head->next=reverseKGroup(nexthead,k);//传入下次需要reverse的k个节点的头节点，递归！
        	return newhead;
        }
    }
};

int main(){
	    ListNode *head1,*temp,*node,*res;
	    Solution sol=Solution();

        head1=(ListNode*)malloc(sizeof(ListNode));
        head1->val=0;
        head1->next=NULL;
        temp=head1;
		
        node=(ListNode*)malloc(sizeof(ListNode));
        node->val=1;
        node->next=NULL;
        temp->next=node;
        temp=node;
		
        node=(ListNode*)malloc(sizeof(ListNode));
        node->val=2;
        node->next=NULL;
        temp->next=node;
        temp=node;
		
        node=(ListNode*)malloc(sizeof(ListNode));
        node->val=3;
        node->next=NULL;
        temp->next=node;
		
        res=sol.reverseKGroup(head1,1);
		while(res){
			cout<<res->val<<endl;
			res=res->next;
		}
        return 0;
}


int main(){
	    ListNode *head1,*temp,*node,*res;
	    Solution sol=Solution();

        head1=(ListNode*)malloc(sizeof(ListNode));
        head1->val=0;
        head1->next=NULL;
        temp=head1;
		
        node=(ListNode*)malloc(sizeof(ListNode));
        node->val=1;
        node->next=NULL;
        temp->next=node;
        temp=node;
		
        node=(ListNode*)malloc(sizeof(ListNode));
        node->val=2;
        node->next=NULL;
        temp->next=node;
        temp=node;
		
        node=(ListNode*)malloc(sizeof(ListNode));
        node->val=3;
        node->next=NULL;
        temp->next=node;
		
        res=sol.reverseKGroup(head1,1);
		while(res){
			cout<<res->val<<endl;
			res=res->next;
		}
        return 0;
}
