////class Leetcode872 {
////    /**
////     * K Closest Points to Origin -- 堆排序，建堆过程太耗时
////     * @param points
////     * @param K
////     * @return
////     */
////    public int[][] kClosest(int[][] points, int K) {
////        int[][] result = new int[K][];
////        if (null == points || 0 == points.length || K < 0) {
////            return result;
////        }
////        Point[] pointArray = new Point[points.length];
////        for (int i = 0; i < points.length; i++) {
////            double distance = Math.pow(points[i][0], 2) + Math.pow(points[i][1], 2);
////            pointArray[i] = new Point(i, distance);
////        }
////        Heap pointHeap = new Heap(pointArray);
////        for (int i = 0; i < K; i++) {
////            Point point = pointHeap.popTopElement();
////            result[i] = points[point.index];
////            System.out.println(result[i][0] + "," + result[i][1] + ", distance:" + point.distance);
////        }
////        return result;
////    }
////
////    private class Point {
////        /**
////         * points[index]
////         */
////        int index;
////        double distance;
////
////        public Point(int index, double distance) {
////            this.index = index;
////            this.distance = distance;
////        }
////    }
////
////    /**
////     * 小顶推
////     */
////    private class Heap {
////        int size;
////        Point[] points;
////
////        public Heap(Point[] points) {
////            this.size = 0;
////            this.points = points;
////            this.buildHeap();
////        }
////
////        /**
////         * Move one element to right place
////         */
////        public void adjustDown(int index) {
////            while (index * 2 + 1 < size) {
////                int leftChildId = (index << 1) + 1;
////                int rightChildId = leftChildId + 1;
////                int minChildId = (rightChildId < size) ? (points[leftChildId].distance <= points[rightChildId].distance ?
////                        leftChildId : rightChildId) : leftChildId;
////                if (points[index].distance <= points[minChildId].distance) {
////                    break;
////                } else {
////                    swap(points, index, minChildId);
////                }
////                index = minChildId;
////            }
////        }
////
////        /**
////         * Move one element to right place
////         */
////        public void adjustUp(int index) {
////            int parentId = (index - 1) >> 1;
////            while (parentId >= 0) {
////                if (points[index].distance >= points[parentId].distance) {
////                    break;
////                }
////                swap(points, index, parentId);
////                index = parentId;
////                parentId = (index - 1) >> 1;
////            }
////        }
////
////        public void addElement(Point point) {
////            points[size] = point;
////            size++;
////            adjustUp(size - 1);
////        }
////
////        public Point popTopElement() {
////            Point elementRemoved = points[0];
////            swap(points, 0, size - 1);
////            // last element must be larger than index, so it can't be less than index's parent
////            size--;
////            adjustDown(0);
////            return elementRemoved;
////        }
////
////        private void buildHeap() {
////            for (int i = 0; i < points.length; i++) {
////                this.addElement(points[i]);
////            }
////        }
////
////        private void swap(Object[] array, int i, int j) {
////            Object temp = array[i];
////            array[i] = array[j];
////            array[j] = temp;
////        }
////    }
////
////    public static void main(String[] args) {
////        int[][] points = {{-41,72},{53,83},{-95,-31},{-61,68},{32,-56},{16,88},{-81,-48},{-31,56},{-57,-74},{24,-42},{-59,72},{-86,40},{34,-85},{-45,22},{-35,-95}};
////        int k = points.length;
////        Leetcode872 solution = new Leetcode872();
////        int[][] result = solution.kClosest(points, k);
////    }
////}
//
//public class Leetcode872 {
//    /**
//     * K Closest Points to Origin -- 小顶堆
//     * @param points
//     * @param K
//     * @return
//     */
//    public int[][] kClosest(int[][] points, int K) {
//        int[][] result = new int[K][];
//        if (null == points || 0 == points.length || K < 0) {
//            return result;
//        }
//        Point[] pointArray = new Point[points.length];
//        for (int i = 0; i < points.length; i++) {
//            double distance = Math.pow(points[i][0], 2) + Math.pow(points[i][1], 2);
//            pointArray[i] = new Point(i, distance);
//        }
//        Point[] sorted = HeapSort.getTopKElement(pointArray, K);
//        for (int i = 0; i < K; i++) {
//            result[i] = points[sorted[i].index];
////            System.out.println(result[i][0] + "," + result[i][1] + ", distance:" + sorted[i].distance);
//        }
//        return result;
//    }
//
//    private class Point {
//        /**
//         * points[index]
//         */
//        int index;
//        double distance;
//
//        public Point(int index, double distance) {
//            this.index = index;
//            this.distance = distance;
//        }
//    }
//
//    public static class HeapSort {
//        public static Point[] getTopKElement(Point[] pointsArray, int k) {
//            Point[] sortedPoints = new Point[pointsArray.length];
//            buildHeap(pointsArray);
//            int heapSize = pointsArray.length;
//            for (int i = 0; i < k; i++) {
//                sortedPoints[i] = pointsArray[0];
//                swap(pointsArray, 0, heapSize - 1);
//                adjustDown(pointsArray, 0,  --heapSize);
//            }
//            return sortedPoints;
//        }
//
//        public static void buildHeap(Point[] points) {
//            int heapSize = points.length;
//            for (int i = heapSize - 1; i >= 0; i--) {
//                adjustDown(points, i, heapSize);
//            }
//        }
//
//        public static void adjustDown(Point[] points, int index, int heapSize) {
//            while ((index << 1) + 1 < heapSize) {
//                int leftChildId = (index << 1) + 1;
//                int rightChildId = leftChildId + 1;
//                int minChildId = (rightChildId < heapSize) ? (points[leftChildId].distance <= points[rightChildId].distance ?
//                        leftChildId : rightChildId) : leftChildId;
//                if (points[index].distance > points[minChildId].distance) {
//                    swap(points, index, minChildId);
//                    index = minChildId;
//                } else {
//                    break;
//                }
//            }
//        }
//
//        /**
//         * Move one element up to right place
//         */
//        public void adjustUp(Point[] points, int index) {
//            int parentId = (index - 1) >> 1;
//            while (parentId >= 0) {
//                if (points[index].distance >= points[parentId].distance) {
//                    break;
//                }
//                swap(points, index, parentId);
//                index = parentId;
//                parentId = (index - 1) >> 1;
//            }
//        }
//
//        private static void swap(Object[] array, int i, int j) {
//            Object temp = array[i];
//            array[i] = array[j];
//            array[j] = temp;
//        }
//    }
//
//    public static void main(String[] args) {
//        int[][] points = {{-41,72},{53,83},{-95,-31},{-61,68},{32,-56},{16,88},{-81,-48},{-31,56},{-57,-74},{24,-42},{-59,72},{-86,40},{34,-85},{-45,22},{-35,-95}};
//        int k = points.length;
//        Leetcode872 solution = new Leetcode872();
//        int[][] result = solution.kClosest(points, k);
//    }
//}