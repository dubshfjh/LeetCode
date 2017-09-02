双重检查 + volatile + synchronized
obj定义为volatile的原因：
1) 生成一个对象至少包括三步：1.申请堆空间；2.成员变量初始化；3.obj指向堆空间。其中JMM可能因为指令级重排序，而先执行第3步
2) 假定然后线程1获取了同步对象Solution.class的ObjectMonitor，执行完步骤1和步骤3，此时obj变量已经指向了尚未初始化的内存空间；
3) 线程2在经过第一层if (obj == null)检测到 obj != null，那么直接返回 obj 取值，此时单例对象尚未初始化
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
	    static Solution obj = new Solution(); //当调用 InnerClass.静态属性/静态方法时，出发getStatic字节码指令,InnerClass的类对象被加载到JVM中，默认获取了JVM的Lock
    }
    public static Solution getInstance() {
        // write your code here
        return InnerClass.obj;
    }
};