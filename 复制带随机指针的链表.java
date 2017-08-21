/**
 * Definition for singly-linked list with a random pointer.
 * class RandomListNode {
 *     int label;
 *     RandomListNode next, random;
 *     RandomListNode(int x) { this.label = x; }
 * };
 */
1. 首先忽略随机指针，直接复制每个节点，构建出只有next节点的链表；
2. 并且使用个Map记录<原始Node, 复制Node>的对应关系，为之后复制"random指针"做准备
3. 等到next节点复制完毕后，再将 每个复制Node 的random指向 clone(原始Node->random)：即record[原始Node->random]
public class Solution {
    /**
     * @param head: The head of linked list with a random pointer.
     * @return: A new head of a deep copy of the list.
     */
    public RandomListNode copyRandomList(RandomListNode head) {
        // write your code here
        if (head == null) {
        	return head;
        }
        //首先忽略随机指针，直接复制每个节点，构建出只有next节点的链表
        //并且使用个Map记录<原始Node, 复制Node>的对应关系，为之后复制"random指针"做准备
        Map<RandomListNode, RandomListNode> record = new HashMap<>();
        RandomListNode origin = head;
        RandomListNode preClone = null;
        while (origin != null) {
        	RandomListNode curClone = new RandomListNode(origin.label);
        	record.put(origin, curClone);
        	if (preClone != null) {
        		preClone.next = curClone;
        	}
        	preClone = curClone;
        	origin = origin.next;
        }

        //等到next节点复制完毕后，再将 每个复制Node 的random指向 clone(原始Node->random)：即record[原始Node->random]
        origin = head;
        while(origin != null) {
        	RandomListNode curClone = record.get(origin);
        	curClone.random = record.get(origin.random);
        	origin = origin.next;
        }
        return record.get(head);
    }
}