#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

 typedef struct ListNode{
	int val;
	ListNode *next;
 }ListNode;
 
本段代码超时啦(尽管逻辑经过短的测试用例发现貌似正确)。缺陷在于每次必须遍历所有lists一次才能够选取出一个节点，必须改进
网上的方法建议基于heap/优先队列来优化，或者每次只取出前2个链表来进行组合，复用之前的代码
/*
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int i,j,len,flag,minindex,minval;//flag存储了尚未推至NULL的链表个数
        len=lists.size();
        flag=len;
        ListNode *head,*temp;
        head=(ListNode*)malloc(sizeof(ListNode));
        head->next=NULL;
        temp=head;

        while(flag>1){
   			flag=0;//在代码最开始处进行判断，避免[[],[]]这种输入导致的minindex保留初值-1
        	for(i=0;i<len;i++){
        		if(lists[i]){//统计尚未右移到NULL的链表个数
        			flag++;
					//cout<<flag<<endl;
        		}
        	}

        	if(flag>1){
	        	minindex=-1;
	        	minval=INT_MAX;
	        	for(i=0;i<len;i++){
	        		if(lists[i]){
	        			if(lists[i]->val<minval){
	        				minval=lists[i]->val;
	        				minindex=i;
				        	//cout<<lists[minindex]->val<<endl;

	        			}
	        		}
	        	}
	        	temp->next=lists[minindex];
	        	temp=lists[minindex];
	        	lists[minindex]=lists[minindex]->next;
				//cout<<lists[minindex]->val<<endl;
        	} 	        	
        }

        for(i=0;i<len;i++){
        	if(lists[i]){
        		temp->next=lists[i];
        		break;
        	}
        }
        
        head=head->next;
		
        temp=head;
        while(temp){
        	cout<<temp->val<<endl;
        	temp=temp->next;
        }
        if(head==NULL){
        	cout<<"NULL!"<<endl;
        }
		
		
        return head;
    }
};
*/

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

typedef struct ListNode{
	int val;
	ListNode *next;
}ListNode;
 
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int len;
        ListNode *tempmerge,*list1,*list2;
        if(lists.size()==0){
            return NULL;
        }
        while(lists.size()>1){
            list1=lists[0];
            lists.erase(lists.begin());

            list2=lists[0];
            lists.erase(lists.begin());

            tempmerge=mergetwolinks(list1,list2);
            lists.push_back(tempmerge);
        }
        /*
        tempmerge=lists[0];
        
        while(tempmerge){
            cout<<tempmerge->val;
            tempmerge=tempmerge->next;
        }
        */
        
        return lists[0];
    }

    ListNode* mergetwolinks(ListNode *l1,ListNode *l2){
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

        head=head->next;
        return head;
    }
};

int main(){
	    ListNode *head1,*head2,*temp,*node;
	    vector<ListNode*> lists;
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
        temp=node;

        lists.push_back(head1);

        head2=(ListNode*)malloc(sizeof(ListNode));
        head2->val=0;
        head2->next=NULL;
        temp=head2;

        node=(ListNode*)malloc(sizeof(ListNode));
        node->val=4;
        node->next=NULL;
        temp->next=node;
        temp=node;

 		node=(ListNode*)malloc(sizeof(ListNode));
        node->val=5;
        node->next=NULL;
        temp->next=node;
        temp=node;

        lists.push_back(head2);

        sol.mergeKLists(lists);
}