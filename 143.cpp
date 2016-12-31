/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
算法思想：僵硬地通过数组中的序号对应关系进行交换，时间O(n),空间O(n)，不可取
reordered list中节点依次为L0->Ln->L1->Ln-1->...->Ln/2->Ln/2+1。因为单向链表较难反向分析一个元素的pre，所以事先将链表的所有元素存储到vector中
for i=0,1,...,n/2-1 循环地对除了中间元素对(即Ln/2和Ln/2+1)之外的每一对元素Li(记为left)和Ln-i(记为right)执行元素置换，PS：中间元素对保持原序即可
循环置换过程直到中间元素对(left->next==right)为止 1. right->next = left->next  2. left->next = right 3. left通过下标++右移一次，right通过下标--左移一次，然后对于左移过一次的right(即right的前一元素pre)设置pre->next=NULL
class Solution {
public:
    void reorderList(ListNode* head) {
        vector<ListNode*> nodes;
        ListNode *temp = head;
        while(temp){
            nodes.push_back(temp);
            temp=temp->next;
        }
        int size = nodes.size();
        if(size <= 2){
            return;
        }
        int left_index = 0;
        int right_index = size-1;

        while(left_index+1 < right_index){//调整后链表L0->Ln->L1->Ln-1->...->Ln/2->Ln/2+1 的最后2个元素不需要移动(即调整前链表的中间2个元素)，由于中间那对元素的left->next就是right，如果仍然用right->next = left->next则会导致right指向自身
            nodes[right_index]->next = nodes[left_index]->next;
            nodes[left_index]->next = nodes[right_index];
            left_index++;
            right_index--;//right左移到pre_right
            nodes[right_index]->next = NULL;//将pre_right指向空。避免类似只有3个节点时，第一次循环后left_index==right_index，于是循环结束，此时L0,L1都指向L2
        }
    }
};


算法思想：首先通过步长为1和步长为2的两个节点遍历，来找到链表的中间节点，将链表分为left和right，然后将right完全设置逆向后，将left和逆向right中通过left[i]->right[i]->left[i+1]连接到一起


在"分割链表"时不妨使得left的长度 >= right的长度。设链表元素下标为 1,2,3,...,n。让步长为1的元素p1从下标"1"开始遍历；让步长为2的元素p2从下标"2"开始遍历，直到 (!p2 || !p2->next)时跳出循环。
设此时p1和p2移动了i次，则p1跳出循环时的位置为 1+i，p2跳出循环时的位置为 2+2i。分析p2跳出循环的真实位置，如果n为偶数，则p2在位置"n"处(p2->next为NULL)跳出循环；如果n为奇数，则p2在位置"n+1"处(p2为NULL)跳出循环。
因此n为偶数时，1+i=n/2；n为奇数时，1+i=(n+1)/2。从而p1所处位置 1+i = [n/2]+1。{head...p1}组成的left长度 >= {p1->next,...}组成的right长度

在"逆向颠倒right"时，使用两个指针head2和p2(p2为head2的后一个元素)，初始化p2=head2->next，head2->next=NULL。while(p2){使用变量temp记录p2->next；p2指向head2；head2右移到p2；p2通过赋值为temp右移}

在"merge left和right时"，每次都只将p1指向p2。使用指针p1来回切换为left和right的当前元素；使用指针p2来回切换为right和left的当前元素。初始化p1为left的头，p2为right的头
    1. 用变量temp记录p1->next (PS:之后传递给p2)；
    2. p1指向p2; 
    3. p1=p1->next (ps:p1切换到p2上，因为下一步为：本层的p2指向本层p1->next。于是只需要将本层p2作为下层的p1，本层的temp作为下层的p2即可)
    4. p2=temp;

class Solution {
public:
    void reorderList(ListNode* head) {
        if(!head || !head->next){
            return;
        }
        ListNode *p1,*p2;
        p1 = head;
        p2 = head->next;
        // find the middle node which splits the longer left half 
        while(p2 && p2->next){
            p1 = p1->next;
            p2 = p2->next->next;
        }

        ListNode *head2 = p1->next;
        //cut from the middle and reverse the right half:O(n)
        p2 = head2->next;
        head2->next = NULL;
        while(p2){//循环结束时head2为初始right half 的最后一个元素，也就是reverse right的第一个元素
            ListNode *temp = p2->next;
            p2->next = head2;
            head2 = p2;
            p2 = temp;
        }

        // merge the shorter right into left，每次循环都只将p1指向p2
        for(p1=head,p2=head2;p1;){
            ListNode *temp = p1->next;//记录p1的初始next
            p1->next = p2;//p1指向p2
            p1 = p1->next;//p1切换到p2
            //前两句可以汇总为 p1 = p1->next = p2;//c++中 a=b=c表示首先执行b=c，再执行a=b。
            p2 = temp;//p2切换到初始p1的next
        }
    }
};