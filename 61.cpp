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
    ListNode* rotateRight(ListNode* head, int k) {//当k>size时，k=k%size后rotate
        int size;
        ListNode *pre,*last;
        
        if(head==NULL || head->next==NULL || k==0){//size==0 or size==1 or k==0 时，直接返回head即可
        	return head;
        }
        size=1;
        pre=last=head;
        while(last->next){//last始终为最后一个元素
        	if(size<=k){//last首先向右移动k次，使得pre为倒数第k+1个节点
        		last=last->next;
        	}
        	else{
        		pre=pre->next;
        		last=last->next;
        		// cout<<pre->val<<",,,"<<last->val<<endl;
        	}
    		size++;
        }
        if(size!=k){
            if(size<k){//此时size<k，需要k%=size
                k=k%size;
                if(k>0){
                    for(int i=0;i<size-k-1;i++){
                        pre=pre->next;
                    }
                }
                else{
                    return head;
                }
            }//倒数第k个节点，即正数第size-k+1个节点，从head右移size-k-1次即到达pre(即第size-k个节点)           
            last->next=head;
            head=pre->next;
            pre->next=NULL;
        }
        else{//此时size==k，不需要移动任何元素
            return head;
        }
        return head;
    }
};

//与本人思想相比的优化：我首先为size>=k的情况找了pre；然后对size<k的情况计算 k%=size，再找到其pre。太过冗余
//实际上可以直接计算 k%=size，然后从head右移size-k次寻找到两种情况下共同的pre
思路如下：将链表首尾相连成环。寻找尾节点的同时可以计算链表长度。

记链表长度为n，则实际移位次数为k=k%n。记len=n-k。

也就是说链表的后k个节点成为新链表的前半部分，链表的前len个节点为新链表的后半部分。

因此head往右第len的节点为新链表的尾，第len+1为新链表的头

两端相连即可，尾部下一个设为NULL即可。

class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if(head == NULL)
            return head;
            
        ListNode* tail = head;
        int n = 1;
        while(tail->next != NULL)
        {
            n ++;
            tail = tail->next;
        }
        k %= n;
        if(k == 0)
            return head;
            
        int len = n-k;
        ListNode* cur = head;
        while(--len)
        {
            cur = cur->next;
        }
        ListNode* post = cur->next;
        cur->next = NULL;
        tail->next = head;
        return post;
    }
};