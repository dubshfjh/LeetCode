public class Solution {
    /**
     * @param A: Given an integer array
     * @return: void
     */
    public void heapify(int[] A) {
        // write your code here
    	if (A.length == 0) {
    		return;
    	}
    	buildHeap(A);
    }

    private void buildHeap(int[] A) {
    	int i = A.length >> 1;
    	for (; i >= 0; i--) {
    		minHeapAdjust(A, i);
    	}
    }

    private void minHeapAdjust(int[] A, int index) {
    	int lChild = index * 2 + 1;
    	int rChild = lChild + 1;
    	while (lChild < A.length && rChild < A.length) {
    		if (A[lChild] >= A[index] && A[rChild] >= A[index]) {
    			break;
    		}
    		int minChild = (A[lChild] < A[rChild]) ? lChild : rChild;
    		swap(A, index, minChild);
    		index = minChild;

    		lChild = 2 * index + 1;
    		rChild = lChild + 1;
    	}
    	if (rChild < A.length && A[rChild] < A[index]) {
    		swap(A, index, rChild);
    	}
    	if (lChild < A.length && A[lChild] < A[index]) {
    		swap(A, index, lChild);
    	}
    }

    private void swap(int[] A, int i, int j) {
    	int temp = A[i];
    	A[i] = A[j];
    	A[j] = temp;
    }
}