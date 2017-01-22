/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <iostream>
#include <unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
 };
/*这段代码只能判断A,B两个链表是否intersect，无法准确地找出first intersect节点
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *tailA,*tailB; //如果A,B链表intersect，则2个单向链表的尾节点必然相同
        tailA = findTail(headA);
        tailB = findTail(headB);
        if(tailA == tailB){
            return tailA;
        }
        else{
            return NULL;
        }
    }

    ListNode *findTail(ListNode *head){
        ListNode *fast,*pre,*tail;
        fast = head;//fast：步长为2的节点，用来寻找A,B链表的尾节点
        while(fast && fast->next){
            pre = fast;
            fast = fast->next->next;
        }
        if(fast){
            tail = fast;
        }
        else{
            tail = pre->next;
        }
        return tail;
    }
};
*///本算法异常辣鸡
首先用蛮力法：使用map记录A,B链表中每个访问过的节点,然后使用tempA,tempB遍历两个链表，如果tempA==tempB 或者 tempA,tempB在visit中出现过，则该节点为first 交叉节点
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(!headA || !headB){
            return NULL;
        }
        unordered_map<ListNode*,bool> visited;
        ListNode *tempA,*tempB;
        tempA = headA;
        tempB = headB;
        while(tempA && tempB){
            cout<<tempA->val<<",,,"<<tempB->val<<endl;
            if(tempA == tempB){
                return tempA;
            }
            if(visited.find(tempA)!=visited.end()){
                return tempA;
            }
            if(visited.find(tempB)!=visited.end()){
                return tempB;
            }
            visited[tempA] = true;
            tempA = tempA->next;
            visited[tempB] = true;
            tempB = tempB->next;
        }

        while(tempA && visited.find(tempA)==visited.end()){
            tempA = tempA->next;
        }
        while(tempB && visited.find(tempB)==visited.end()){
            tempB = tempB->next;
        }
        
        if(tempA || tempB){
            return tempA?tempA:tempB;
        }
        else{
            return NULL;
        }
    }
};

int main(){
    Solution s = Solution();
    ListNode *a = new ListNode(1);
    ListNode *temp = new ListNode(2);
    ListNode *b = new ListNode(3);
    ListNode *c = new ListNode(4);
    a->next = b;
    b->next = c;
    temp->next = c;
    ListNode *res = s.getIntersectionNode(a,temp);
    if(res){
        cout<<res->val<<endl;
    }
    else{
        cout<<"NULL"<<endl;
    }
    return 0;
}

//正常的思路：实际上就是分析两个链表是否有公共sublink段，设min,max分别为较短，较长链表的长度，则二者的公共链表段长度取值范围为{0,1...,min}
//因此A,B有公共链表段  等价于  templong从较长链表的第max-min个元素开始，tempshort从较短链表的head开始，
//  在遍历较长链表的后min个元素以及较短链表的全部元素的过程中，发现templong == tempshort(即较长链表的后min个元素与较短链表的元素intersects!)
如果A链表length == B链表length，则分别使用tempA,tempB从头部开始遍历两个链表，遇到的第一次tempA == tempB(即两个链表的first公共元素)，即为first交叉节点
    如果遍历完毕仍没有找到公共节点，说明不交叉
如果A链表length != B链表length，设min,max分别为较短，较长链表的长度，使用templong从较长链表的第max-min+1个元素开始，tempshort从较短链表的head开始，
    遇到的第一次templong == tempshort(即较长链表的后min个元素与较短链表的元素intersects!)，即为first交叉节点。
    如果遍历完毕仍没有找到公共节点，说明不交叉

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *tempA,*tempB,*templong,*tempshort,*temp;
        tempA = headA;
        tempB = headB;
        while(tempA && tempB){
            if(tempA == tempB){//如果遇到公共元素，则直接返回
                return tempA;
            }
            tempA = tempA->next;
            tempB = tempB->next;
        }
        if(!tempA && !tempB){//说明A,B长度相等，而且两个链表无公共元素
            return NULL;
        }
        else{//tempA，tempB中有一个不为空，此时它处于较长链表的第min+1个元素
            tempshort = tempA?headB:headA;//记录较短链表的头部
            temp = tempA?tempA:tempB;//temp记录较长链表的第min+1个元素
            templong = tempA?headA:headB;//templong从较长链表的头部开始，当temp遍历到较长链表的NULL(第max+1个元素)，templong移动了max-min次，为第max-min+1个元素
            while(temp){
                temp = temp->next;
                templong = templong->next;
            }

            while(templong && tempshort){//分析较长链表的后min个元素，与较短链表的全部元素之间是否存在公共元素
                if(templong == tempshort){
                    return templong;
                }
                templong = templong->next;
                tempshort = tempshort->next;
            }
            //较长元素的后min个元素与较短链表没有交叉!
            return NULL;
        }
    }
};
