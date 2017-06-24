12345 -> 14235反转一半链表问题：首先将链表中分为left和right(中分时需要断开left尾节点与right头节点的链接)，
然后使用头插法reverse right，最后将right以交叉的方式合并到left中
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public void reorderList(ListNode head) {
        if(head==null || head.next==null){
            return;
        }
        ListNode slow = head;
        ListNode fast = head.next;
        while(fast!=null && fast.next!=null){
            slow = slow.next;
            fast = fast.next.next;
        }
        ListNode rightHead = reverse(slow.next);
        ListNode leftHead = head;
        slow.next = null;//断开左右链表，避免左链表 和  reverse的右链表合并时 产生循环链表
        while(leftHead!=null && rightHead != null){
            ListNode tempRight = rightHead.next;
            rightHead.next = leftHead.next;
            leftHead.next = rightHead;

            leftHead = rightHead.next;
            rightHead = tempRight;
        }
        // return head;
    }

    ListNode reverse(ListNode head){
        if(head==null || head.next==null){
            return head;
        }
        //只维护头节点的链表头插法，从head 开始 头插，直到尾节点时跳出循环(这只是为了保证head为右链表的头节点)
        ListNode headNode = null;
        while(head!=null && head.next!=null){
            ListNode temp = head.next;
            head.next = headNode;
            headNode = head;
            head = temp;
        }
        head.next = headNode;//
        return head;
        /* 维护头、尾两个指针的链表头插法，从head.next开始头插 直到 NULL时跳出循环
        ListNode rearNode = head;
        head = head.next;
        while(head!=null){
            ListNode temp = head.next;
            head.next = headNode;
            headNode = head;
            head = temp;
        }
        rearNode.next = null;
        */
        // return headNode;
    }
}