/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
传统插入排序算法，时间复杂度太高
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(head == NULL || head->next == NULL){
            return head;
        }
        int min;
        ListNode *node,*temp;
        ListNode *min_node;
        node = head;//node记录每次被插入最小值的指针位置.node依次取值为head,head->next,head->next->next...倒数第二个元素
        while(node->next){
            min = node->val;//min和min_node初始化为node本身
            min_node = node;
            temp = node->next;//temp从node->next开始寻找比min_node取更小值的节点
            while(temp){
                if(temp->val < min){
                    min_node = temp;
                    min = temp->val;
                }
                temp = temp->next;
            }
            swap(node,min_node);//将从当前node开始的最小节点放到node处
            node = node->next;
        }
        return head;
    }

private:
    void swap(ListNode *a,ListNode *b){
        int temp = a->val;
        a->val = b->val;
        b->val = temp;
    }
};


改进的插入排序：设置新指向NULL的链表头pre_head，并始终保证pre_head->...->NULL这个"新链表的升序排列"。依次对"旧链表"的第i(0,1...,size)个元素进行分析。每次都在"pre_head开始的新链表"中扫描找到first >= [i]的元素node，然后将[i]插入到node之前
时间复杂度仍然为O(n^2)
算法正确性：如果当前元素 cur 移动到最左侧的>=cur的元素前方后，仍未到达最终正确位置。
    if( cur 的左侧存在>cur的元素i,"实际上不可能" )，当遍历到i时，在"新链表"中"旧链表"的{[0],[1],...[i-1]}这些元素已经按升序排列了，因此"新链表"中fitst >=cur 的元素就是min{ >=cur元素 }
    if( cur 的右侧存在<cur的元素j)，则继续向右分析到元素j时，自然会把j插入到"新链表"中first >= [j]的元素前方("实际上就是min{>=j的元素}")
因此能实现最终的正确排序


class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(head == NULL){
            return head;
        }
        ListNode *help_head = new ListNode(0);//new starter of the sorted list
        //help_head->next = head;加上这句逻辑会错误，导致超时！！！必须初始化pre_head->next = NULL！！！
        //原因：对于第一个cur，它遇到的第一个>=cur的元素就是它自己，如果pre_head一开始就指向了head，则在执行"cur->next=pre->next"语句后head会指向自身，虽然backnext成功备份为head->next，但是从pre_head开始的链表变成了"pre_head->head->head->head...."。
        //正确的做法是让pre_head开始的链表始终保持升序。{pre_head->a1->a2->..->NULL}，a1<=a2<=a3<...
        
        ListNode *pre = help_head;//insert cur between pre and pre->next
        ListNode *cur = head;//被修改位置的节点cur
        ListNode *backup_next = NULL;//由于cur->next会指向pre->next，需要提前备份下一个修改位置的元素
        
        while(cur){
            ListNode *test = pre;
            // while(test){
            //     cout<<test->val<<"...";
            //     test=test->next;
            // }
            // cout<<endl;
            while(pre->next!=NULL && pre->next->val < cur->val){//从左到右找到第1个>=cur的元素(pre->next)，然后将cur插入pre和pre->next之间
                pre = pre->next;
            }
            
            backup_next = cur->next;
            cur->next = pre->next;
            pre->next = cur;

            cur = backup_next;
            pre = help_head;
        }
        return help_head->next;
    }
};