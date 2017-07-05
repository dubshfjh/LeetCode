双重检查 + volatile + synchronized
class Solution {
    /**
     * @return: The same instance of this class every time
     */
  	private static volatile Solution obj = null;
  	private Solution() {}  
    public static Solution getInstance() {
        // write your code here
        if (obj == null) {
        	synchronized (Solution.class) {
	        	if (obj == null) {
	        		obj = new Solution();       		
	        	}
	        }
        }
        return obj;
    }
};

利用类加载时自动获取的JVM锁

class Solution {
    /**
     * @return: The same instance of this class every time
     */
    private Solution() {
    }
    // class InnerClass{ 内部类的地位等同于一个属性/方法，只有静态内部类才能在“Solution实例”尚未构建时，就进行调用
    static class InnerClass {
	    static Solution obj = new Solution(); //当调用 InnerClass.静态属性/静态方法时，InnerClass的类对象被加载到JVM中，默认获取了JVM的Lock
    }
    public static Solution getInstance() {
        // write your code here
        return InnerClass.obj;
    }
};