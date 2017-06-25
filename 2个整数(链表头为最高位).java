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
错误思想：因为"1->2->3 + 4->5" 这类加法必须从低位加到高位，为了代码优雅性采用递归思想： 
对于l1和l2，首先获取l1右侧 和 l2右侧链表的相加结果 rightResNode，记temp = l1+l2+flag(右侧链表相加所得整体进位)，然后再将temp%10作为curNode，flag=temp/10，并将curNode指向rightResNode
"错误原因：这种递归并没有使得最低位对齐，而是似的最高位对齐，因此结果会变成 "1+4 -> 2+5 ->3"，但正确结果为"1 -> 2+4 ->3+5""
// private ListNode helpAddList(ListNode l1, ListNode l2) {
    // 	if (l1 == null || l2 == null) {
    // 		return l1 == null ? l2 : l1;
    // 	}
    // 	ListNode rightRes = helpAddList(l1.next, l2.next);
    // 	int temp = l1.val + l2.val + flag
    // 	flag = temp % 10;
    // 	ListNode newNode = new ListNode(temp % 10);
    // 	newNode.next = rightRes;
    // 	return newNode;
    // }

算法思想：1. 抽象出反转链表的方法reverse()，以及基于dummy执行“头插节点”的方法headInsert()
2. 首先反转链表l1 和 l2，然后从低位到高位累加每一位直到某个链表为null：temp = l1+l2+flag（低位相加所得整体进位），将temp%10作为curNode，flag=temp/10
3. 对剩下的链表remainLink 进行计算：temp = remainLink +flag（低位相加所得整体进位），将temp%10作为curNode，flag=temp/10
PS：在reverse链表 以及 中分链表操作时，必须将新链表的尾节点指向null! 否则会导致循环链表的出现，以致TLE或内存溢出
public class Solution {
    /**
     * @param l1: the first list
     * @param l2: the second list
     * @return: the sum list of l1 and l2
     */
    public ListNode addLists2(ListNode l1, ListNode l2) {
        // write your code here
        if (l1 == null || l2 == null) {
            return l1 == null ? l2 : l1;
        } else {
            int	flag = 0;
            ListNode dummy = new ListNode(0);
            ListNode reverseL1 = reverse(l1);
            ListNode reverseL2 = reverse(l2);
            while (reverseL1 != null && reverseL2 != null) {
                int temp = reverseL1.val + reverseL2.val + flag;
                flag = temp / 10;
                headInsert(temp % 10, dummy);
                reverseL1 = reverseL1.next;
                reverseL2 = reverseL2.next;
            }
            ListNode remainLink = (reverseL1 == null) ? reverseL2 : reverseL1;
            while (remainLink != null) {
                int temp = remainLink.val + flag;
                flag = temp / 10;
                headInsert(temp % 10, dummy);
                remainLink = remainLink.next;
            }
            ListNode head = dummy.next;
            if (flag != 0) {
                head = new ListNode(flag);
                head.next = dummy.next;
            }
            return head;
        }
    }

    private ListNode reverse(ListNode oldhead) {
        ListNode dummy = new ListNode(0);
        dummy.next = oldhead;
        ListNode head = oldhead.next;
        while (head != null) {
            ListNode temp = head.next;
            head.next = dummy.next;
            dummy.next = head;
            head = temp;
        }
        //最后必须将新尾节点(之前的head)指向null，否则链表会变成首尾相连的循环链表
        oldhead.next = null;
        return dummy.next;
    }

    private void headInsert(int value, ListNode dummy) {
        ListNode newNode = new ListNode(value);
        newNode.next = dummy.next;
        dummy.next = newNode;
    }

    // public static void main(String[] args) {
    //     Scanner sc = new Scanner(System.in);
    //     while (sc.hasNext()) {
    //         int m = 3;
    //         int n = 2;
    //         int[] num1 = new int[m];
    //         int[] num2 = new int[n];
    //         for (int i = 0 ; i < m; i++) {
    //             num1[i] = sc.nextInt();
    //         }

    //         for (int i = 0; i < n; i++) {
    //             num2[i] = sc.nextInt();
    //         }
    //         Solution obj = new Solution();
    //         ListNode l1 = new ListNode(0);
    //         ListNode l2 = new ListNode(0);
    //         for (int i : num1) {
    //             obj.headInsert(i, l1);
    //         }

    //         for (int j : num2) {
    //             obj.headInsert(j, l2);
    //         }
    //         obj.addLists2(l1.next, l2.next);
    //     }
    // }
}