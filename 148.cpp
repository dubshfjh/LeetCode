时间复杂度要求为O(nlogn)，可以考虑使用归并排序
数组的归并排序思想：

设归并排序的当前区间是R[low..high]，分治法的三个步骤是：
1.分解：将当前区间一分为二，即求分裂点
2.求解：递归地对两个子区间R[low..mid]和R[mid+1..high]进行归并排序；
3.组合：将已排序的两个子区间R[low..mid]和R[mid+1..high]归并为一个有序的区间R[low..high]。

第3步归并操作的基本步骤如下：
1.申请两个与已经排序序列R[low...mid],R[mid+1...high]相同大小的空间left和right，并将两个序列拷贝其中；
2.初始化下标i,j分别为两个(已经拷贝&&排序)序列left和right的起始位置(对应R中的low和mid+1)。在R[low...high]段插入排序后的元素，初始化下标k = low to high,然后在R[k]处依次插入min(left[i],right[j])

3.重复2直到某一拷贝序列全部放入原始序列，将另一个序列剩下的所有元素直接复制到原始序列尾。

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
[2,1,7,3,4,5,123,6,7,9]
class Solution {
public:
    逻辑出现了错误！！归并排序根本不需要起始节点和中止节点，只需要一个头节点，然后遍历头节点得到中间节点mid后，将mid->next设置为NULL来断开左右两段链表即可即可！
    /*
    ListNode* sortList(ListNode* head) {
        if(head==NULL || head->next==NULL){
            return head;
        }
        ListNode *node = head;
        while(node->next && node->next->next){
            node = node->next->next;
        }
        if(node->next){
            node = node->next;
        }
        return merge_sort(head,node);
    }

    ListNode* merge_sort(ListNode* head,ListNode* rear){
        if(head == rear){
            return head;
        }
        ListNode *left,*mid,*right;
        left = mid = right = head;
        while(right!=rear && right->next!=rear){//right要么到达最后一个元素(元素数目n为奇数)，要么到达倒数第2个元素(n为偶数)。当n为偶数时，mid为第n/2个元素；当n为奇数时，mid为第(n+1)/2个元素
            right = right->next->next;
            mid = mid->next;
        }

        if(right!=rear){
            right = right->next;
        }
        cout<<left->val<<",,,"<<mid->val<<",,,"<<mid->next->val<<",,,"<<right->val<<endl;
        merge_sort(left,mid);
        merge_sort(mid->next,right);
        return merge(left,mid,right);
    }
    
    
    ListNode* merge(ListNode* left,ListNode* mid,ListNode* right){
        ListNode* pre_head = new ListNode(0);
        ListNode *head1,*head2,*temp;
        head1 = left;
        head2 = mid->next;
        temp = pre_head;
        mid->next = NULL;
        while(head1 && head2){
            if(head1->val < head2->val){
                temp->next = head1;
                temp = head1;
                head1 = head1->next;
            }
            else{
                temp->next = head2;
                temp = head2;
                head2 = head2->next;
            }
        }

        if(head1){
            temp->next = head1;
        }
        if(head2){
            temp->next = head2;
        }
        return pre_head->next;
    }
    */
};

采用分治法实现递归的归并排序。递归地对从当前head开始的链表进行排序，并返回排序后链表的新头节点。如果head本段链表长度为 0/1 则直接返回头节点，否则通过步长为1的指针slow，步长为1用来记录slow前一个节点的指针pre，
以及步长为2的指针fast从head开始遍历直到(!fast || !fast->next)，在循环结束时fast将为NULL(元素数目n为偶数)/最后一个节点(n为奇数)；对应的slow将为第(n/2+1)个元素/第(n+1/2)个元素。
Attention!!!!将pre->next=NULL断开左，右两侧的子链表！！！之后，{head...pre}为较短的左半链表，{slow...}为较长的右半链表。递归地对以head开始的左子链表排序，更新head为排序后左子链表的新头部；
递归地对以slow开始的右子链表排序，更新slow为排序后右子链表的新头部。最后Merge(head为头部的左子链表，slow为头部的右子链表)，返回Merge生成链表的新头部
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(!head || !head->next){
            return head;
        }
        ListNode *pre_slow,*slow,*fast;
        slow = fast = head;
        while(fast && fast->next){//当元素数目n为偶数时，fast以NULL结束,slow以第 n/2+1 个元素结束；当n为奇数时，fast以最后一个元素结束，slow以第 n+1/2 个元素(实际上还是第n/2+1个)结束
            pre_slow = slow;
            slow = slow->next;
            fast = fast->next->next;
        }//此处选择让左侧元素数 <= 右侧元素数，所以{head...pre_slow}为左侧链表，{slow...最后一个元素}为右侧链表
        pre_slow->next = NULL;
        head = sortList(head);
        slow = sortList(slow);
        head = merge(head,slow);
        return head;
    }

    ListNode* merge(ListNode* head1,ListNode* head2){
        ListNode *pre_head = new ListNode(0);
        ListNode *rear = pre_head;
        while(head1 && head2){
            if(head1->val < head2->val){
                rear->next = head1;
                rear = head1;
                head1 = head1->next;
            }
            else{
                rear->next = head2;
                rear = head2;
                head2 = head2->next;
            }
        }

        if(head1){
            rear->next = head1;
        }
        if(head2){
            rear->next = head2;
        }
        return pre_head->next;
    }
};