public class Solution {
    /**
      * @param start, a string
      * @param end, a string
      * @param dict, a set of string
      * @return an integer
      */
    private Map<String, Integer> memory;

    public int ladderLength(String start, String end, Set<String> dict) {
        // write your code here
    	memory = new HashMap<>();
    	for (String s : dict) {
    		memory.put(s, -1);
    	}
    	int wordIndex = 0;
    	int minNum = Integer.MAX_VALUE;
    	Set<String> path = new HashSet<String>();
    	for (String s : dict) {
    		if (editDistance(start, s) == 1) {
    			minNum = Math.min(minNum, 1 + search(s, end, dict, path));
    		}
    	}
    	return minNum;
    }

    private int editDistance(String from, String to) {
    	if (from.length() != to.length()) {
    		return -1;
    	}
    	int dis = 0;
    	for (int i = 0; i < from.length(); i++) {
    		if (from.charAt(i) != to.charAt(i)) {
    			dis++;
    		}
    	}
    	return dis;
    }

    private int search(String from, String to, Set<String> dict, Set<String> path) {
        System.out.println(from + ",,," + path);
    	if (memory.get(from) != -1) {
    		return memory.get(from);
    	}

    	if (editDistance(from, to) == 1) {
    	    System.out.println(from + "===" +  path);
    		memory.put(from, 1);
    		return 1;
    	}

    	path.add(from);
    	int minNum = Integer.MAX_VALUE;
    	for (int i = 0; i < from.length(); i++) {
    		for (char j = 'a'; j <= 'z'; j++) {
    			StringBuilder temp = new StringBuilder(from);
    			temp.setCharAt(i, j);
    			String nextWord = temp.toString();
    			if (dict.contains(nextWord) && !path.contains(nextWord)) {
    				minNum = Math.min(minNum, search(nextWord, to, dict, path));
    			}
    		}
    	}
    	path.remove(from);
    	memory.put(from, minNum);
    	return minNum;
    }
}