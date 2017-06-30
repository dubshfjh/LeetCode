/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
给定阈值，将链表分割为左侧和右侧两部分。
    如果是分割数组，则只需记录右侧链表的头节点下标为index：1.如果节点[i] > target，则不需要处理 2.如果[i]<=target，则swap([i], [index])
    但本题为分割链表，所以swap节点代价较高，所以为左侧链表 和 右侧链表分别设置dummy head，对于节点[i] 按照其大小尾插到 左侧/右侧子链表
    ps：1. 只需要在整体链表建立后，再使 左链表尾节点.next = 右链表头节点，右链表尾节点.next=null；而不需要使每个节点[i]分析完后将Next=null
    2. 由于当前节点[i]只是按照尾插法 成为 左侧/右侧链表的新尾节点，节点[i].next并没有发生变化，所以不需要提前备份节点[i].next
public class Solution {
    public ListNode partition(ListNode head, int x) {
         if(head==null || head.next==null){
            return head;
         }       
         ListNode dummmyA = new ListNode(0);
         dummmyA.next = head;

         ListNode dummmyB = new ListNode(0);
         dummmyB.next = head;

         ListNode nodeA = dummmyA;
         ListNode nodeB = dummmyB;
         while(head != null){
            // ListNode temp = head.next;
            if(head.val < x){
                nodeA.next = head;
                nodeA = head;
            }
            else{
                //nodeA.next = temp; 因为nodeA下一次遇到<x的节点就修改了自己的next，所以不需要每次都设置为temp
                nodeB.next = head;
                nodeB = head;
            }
            head = head.next;
            // head = temp;由于head只是按照尾插法 成为 A/B链表的新尾节点，head.next并没有发生变化，所以不需要提前备份head.next
         }
         nodeB.next = null;//最后的nodeB必须指向空！！！否则假设：倒数第2个节点为last >=x的数(即最后的nodeB)，最后一个节点则为最后的nodeA，则nodeB将指向nodeA，导致死循环
         nodeA.next = dummmyB.next;
         return dummmyA.next;
    }
}