#include <iostream>
using namespace std;

typedef struct ListNode{
	int val;
	ListNode *next;
}ListNode;

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *pre,*node,*after;
        pre=NULL;
        node=head;
		if(node==NULL){//0个节点则返回NULL
			return NULL;
		}
        after=node->next;
        if(after==NULL){//1个节点则返回链表本身
        	return head;
        }
        while(after){
        	if(pre){//分析第3,4个节点对，(5,6)，(7,8)....
        		node->next=after->next;
        		after->next=node;
        		pre->next=after;
				//cout<<node->val<<",,,"<<after->val<<",,,"<<pre->val<<endl;
        	}
        	else{//只有分析前2个节点时，会进入本层，此时node节点无pre,head应该更新为第2个节点
        		node->next=after->next;
        		after->next=node;
        		head=after;//当节点数>=2时，头指针只改变一次，即变为最先的第2个节点
        	}

			if(node->next){//node->next!=NULL意味着还有1个以上的节点尚未swap，如果只剩1个节点，则导致after更新为NULL跳出循环；如果剩2个，则下次循环将进入else段
        		pre=node;
				node=node->next;//当node->next==NULL时,node此时移到NULL
        		after=node->next;//after=NULL->next，会报错
			}
			else{//当链表剩余节点数为0时，必须加入break语句跳出循环。否则after不会右移到NULL，死循环将产生!
				break;
			}
        }	
        return head;
    }
};

int main(){
	    ListNode *head1,*temp,*node;
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
		
        sol.swapPairs(head1);
        return 0;
}

递归方法！！！
class Solution {
public:
    ListNode* swapPairs(ListNode* head){//每层都swap head和head->next这两个节点
    	ListNode* newhead;
    	if(head==NULL||head->next==NULL){//如果本层swap的节点数<=1，则返回head
    		return head;
    	}
    	newhead=head->next;//head->next不为空时，才可用变量记录它
    	head->next=newhead->next;//head指向newhead的下一个节点
    	newhead->next=head;//newhead指向head
    	head->next=swapPairs(head->next);//head指向之后(两个节点经过交换后的前节点)
		return newhead;
    }
};
