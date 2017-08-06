1. 两个链表若有公共节点，则二者从first 公共节点开始的所有节点 都会重合 
2。 设较长链表，较短链表的长度分别为 bigLen, smallLen
则 将较长链表的头节点先移动 bigLen - smallLen 次后，再将 两个链表的节点 依次向右比较，遇到的first公共节点必然为整体的 first 相交节点
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;      
 *     }
 * }
 */
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;      
 *     }
 * }
 */
public class Solution {
    /**
     * @param headA: the first list
     * @param headB: the second list
     * @return: a ListNode 
     */
    public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
        // Write your code here
        if (headA == null || headB == null) {
            return null;
        }
        int aLen = getListLength(headA);
        int bLen = getListLength(headB);
        if (aLen < bLen) {
            headB = moveHead(headB, bLen - aLen);
        } else {
            headA = moveHead(headA, aLen - bLen);
        }
        while(headA != null && headB != null) {
            if (headA == headB) {
                break;
            }
            headA = headA.next;
            headB = headB.next;
        }
        return headA;
    }

    private int getListLength(ListNode head) {
        int len = 0;
        while(head != null) {
            len++;
            head = head.next;
        }
        return len;
    }

    private ListNode moveHead(ListNode head, int num) {
        for (int i = 0; i < num; i++) {
            head = head.next;
        }
        return head;
    }
}