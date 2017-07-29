1->2->1->2不是回文链表；1->2->2->1才是！！！
思想：中分链表后，将右半链表reverse后与左半链表顺序比较，如果完全匹配 or 左半链表多了最后1个元素则 "为回文链表"
1. 中分链表：快慢指针法
	1.1 当fast初始化为slow.next时，如果链表长为偶数则slow停止于第[len/2]个元素，左半链表长度 == 右半链表长度
	1.2 如果链表长为奇数则slow停止于第[len/2+1]个元素，左半链表长度 == 右半链表长度 + 1
2. 反转链表：采用dummy节点&头插法，注意 必须将 旧Head 指向null，否则会出现循环链表

踩到的坑：1. 1->2->1->2不是回文链表；1->2->2->1才是！！！
2. 反转链表时，不要忘记 必须将 旧Head 指向null，否则会出现循环链表！！！
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
public class Solution {
    /**
     * @param head a ListNode
     * @return a boolean
     */
    public boolean isPalindrome(ListNode head) {
        // Write your code here
        if (head == null || head.next == null) {
            return true;
        }
        ListNode slow = head;
        ListNode fast = head.next; //当fast初始化为slow.next时，如果链表长为偶数则slow停止于第[len/2]个元素，
        // 左半链表长度 == 右半链表长度；如果链表长为奇数则slow停止于第[len/2+1]个元素，左半链表长度 == 右半链表长度 + 1
//        while(slow.next != null && fast.next != null) { slow的停止位置不可能为null（因为它停止于中间节点），fast应该停止于最后1个节点
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }

        ListNode rHead = slow.next;
        slow.next = null;
        rHead = reverseList(rHead);

        ListNode lHead = head;
        while(lHead != null && rHead != null) {
            if (lHead.val != rHead.val) {
                return false;
            } else {
                lHead = lHead.next;
                rHead = rHead.next;
            }
        }
        return lHead == null || lHead.next == null;
//        return lHead.next == null;
    }

    private ListNode reverseList(ListNode head) {
        if (head == null || head.next == null) {
            return head;
        }
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        ListNode newHead = head.next;
        while(newHead != null) {
            ListNode temp = newHead.next;
            newHead.next = dummy.next;
            dummy.next = newHead;
            newHead = temp;
        }
        //必须将旧头部节点断开，否则会导致循环链表
        head.next = null;
        return dummy.next;
    }

    // public static void main(String[] args) {
    //     Solution obj = new Solution();
    //     ListNode node1 = new ListNode(0);
    //     ListNode node2 = new ListNode(1);
    //     ListNode node3 = new ListNode(1);
    //     ListNode node4 = new ListNode(1);
    //     ListNode node5 = new ListNode(0);
    //     node1.next = node2;
    //     node2.next = node3;
    //     node3.next = node4;
    //     node4.next = node5;
    //     System.out.println(obj.isPalindrome(node1));
    // }
}