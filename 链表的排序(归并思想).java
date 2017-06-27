/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    public ListNode sortList(ListNode head) {
        if(head==null || head.next==null){
            return head;
        }
        ListNode slow = head;
        ListNode fast = head.next;//当链表长度<=3时，可以免去fast的右移(毕竟尾节点就至少得是head.next)
        while(fast!=null && fast.next!=null){
            slow = slow.next;
            fast = fast.next.next;
        }
        // ListNode leftHead = sortList(head);//获取排好序的左半链表，和右半链表，然后merge
        ListNode rightHead = sortList(slow.next);
        //注意在分析下一层的左子链表的middle节点(快慢指针法) 和 合并链表时,左半链表与右半链表必须断开！！！！
        //否则后果：左子链表的长度会与父链表一致；
        //合并链表时，如果左子链表的尾节点 就是 整体merge链表的尾节点，尾节点将指向 右子链表的头节点
        slow.next = null;
        ListNode leftHead = sortList(head);
        return merge(leftHead,rightHead); 
    }

    public ListNode merge(ListNode left,ListNode right){
        ListNode preHead = new ListNode(0);
        ListNode rear = preHead;
        while(left!=null && right!=null){
            if(left.val < right.val){
                rear.next = left;
                // rear = left;
                left = left.next;
            }
            else{
                rear.next = right;
                // rear = right;
                right = right.next;
            }
            rear = rear.next;
        }
        if(left != null){//左半链表与右半链表必须断开！！！！否则在这种情况下，左半链表的last节点作为整体链表的尾节点，就会与右半链表的头节点相连
            rear.next = left;
        }
        if(right != null){
            rear.next = right;
        }
        return preHead.next;
    }
}