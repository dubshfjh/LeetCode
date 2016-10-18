错误答案！没考虑第一位>10时的情况;更没有考虑l1和l2不等长的情况
/*
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
        int temp,flag;
        ListNode *result,*node,*rear;
        flag=0;
        result=(struct ListNode*)malloc(sizeof(ListNode));
        result->next=NULL;
        rear=result;
        while(l1&&l2){
            temp=l1->val+l2->val+flag;
            if(temp>=10){
                flag=1;
                temp-=10;
            }
            node=(struct ListNode*)malloc(sizeof(ListNode));
            node->val=temp;
            node->next=rear->next;
            rear->next=node;
            rear=node;
            l1=l1->next;
            l2=l2->next;
        }
        result=result->next;
        return result;
    }
};
*/
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
        int temp,flag;
        ListNode *result,*node,*rear;
        flag=0;
        result=(struct ListNode*)malloc(sizeof(ListNode));
        result->next=NULL;
        rear=result;
        while(l1||l2){
            temp=flag;
            if(l1){
                temp+=l1->val;
            }
            if(l2){
                temp+=l2->val;
            }
            if(temp>=10){
                flag=1;
                temp-=10;
            }
            else{
                flag=0;
            }
            node=(struct ListNode*)malloc(sizeof(ListNode));
            node->val=temp;
            node->next=rear->next;
            rear->next=node;
            rear=node;
            if(l1){
                l1=l1->next;
            }
            if(l2){
                l2=l2->next;
            }
        }
        if(flag==1){
            node=(struct ListNode*)malloc(sizeof(ListNode));
            node->val=1;
            node->next=rear->next;
            rear->next=node;
            rear=node;
        }
        result=result->next;
        return result;
    }
};

int main(){
    ListNode *l1,*l2,*node;
    l1=(struct ListNode*)malloc(sizeof(ListNode));
    l1->val=5;
    l1->next=NULL;

    l2=(struct ListNode*)malloc(sizeof(ListNode));
    l2->val=7;
    node=(struct ListNode*)malloc(sizeof(ListNode));
    node-val=2;
    node->next=NULL;
    l2->next=node;

    Solution sol=Solution();
    sol.addTwoNumbers(l1,l2);
    return 0;
}