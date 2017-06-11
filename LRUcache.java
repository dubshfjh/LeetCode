public class LRUCache {
    private class Node {//模拟linkedHashMap jdk源码，没必要再单独引入一个链表，直接利用Node节点的pre,next属性构建双向链表
        int key;
        int value;
        Node pre;
        Node next;
        public Node(int key, int value) {
            this.key = key;
            this.value = value;
            this.pre = null;
            this.next = null;
        }
    }

    // List<Node> data;//记录{key-value}对象数据，以及对象的访问顺序。由于从map中移除"最近最少访问"元素时，需要访问顺序列表尾部元素的key，所以链表本身需要存储key
    private int capacity;
    private Map<Integer, Node> record;//记录key是否存在，以及存储每个key对应的{key-Node}对象(或许也可以存储在data列表中的下标)
    private Node dummyHead = new Node(-1, -1);
    private Node dummyTail = new Node(-1, -1);
    // @param capacity, an integer
    public LRUCache(int capacity) {
        // write your code here
        this.capacity = capacity;
        dummyHead.next = dummyTail;
        dummyTail.pre = dummyHead;
        record = new HashMap<Integer, Node>();
    }

    // @return an integer
    public int get(int key) {
        // write your code here
        if (!record.containsKey(key)) {
            return -1;
        }
        //将被访问的元素 移到 “访问顺序” 链表的头部
        Node curNode = record.get(key);
        //1. 从链表中移除旧的元素，但不需要从map中移除其记录
        curNode.next.pre = curNode.pre;
        curNode.pre.next = curNode.next;
        //2. 将该元素移到链表头部
        movetoHead(curNode);
        return curNode.value;
    }

    // @param key, an integer
    // @param value, an integer
    // @return nothing
    public void set(int key, int value) {
        // 内部的get()方法会将key对应的node移到头部
        if (this.get(key) != -1) {//已存在元素，则 1.更新当前Node对象为最新访问 2.更新该元素的value，即移到“访问顺序”链表头部
            record.get(key).value = value;
            return;
        }
        //新的元素
        if (record.size() == capacity) {//cache已满，需要移除处于链表尾部的“最近最久未访问”元素 1.链表中删除节点 2.map中删除节点记录
            record.remove(dummyTail.pre.key);
            dummyTail.pre = dummyTail.pre.pre;
            dummyTail.pre.next = dummyTail;
        }
        Node insertNode = new Node(key, value);
        record.put(key, insertNode);
        movetoHead(insertNode);
    }

    public void movetoHead(Node curNode) {
        curNode.next = dummyHead.next;
        curNode.pre = dummyHead;
        dummyHead.next.pre = curNode;
        dummyHead.next = curNode;
    }
}
