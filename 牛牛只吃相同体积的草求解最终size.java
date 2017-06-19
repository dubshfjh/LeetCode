使用一个HashSet保存所有草料的体积，对于当前的牛size不断执行size<<=1操作，直到HashSet中找不到==size的草料，即HashSet.contains(size) == false
private int calFinalSize(int n, int a, int[] nums) { //n为草料堆数，a为初始size，nums存储每堆草的size
    if (n < 1) {
        return a;
    }
    Set<Integer> record = new HashSet<>();
    for (int num : nums) {
        record.add(num);
    }
    while (record.contains(a)) {
        a <<= 1;
    }
    return a;
}