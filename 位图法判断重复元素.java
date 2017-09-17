1. 位图法解决空间不足问题，32-bit 的int整数最多有 2^32 = 4G 个，因为内存限定在 1 GB，所以应该采用 BitMap ，使每个整数占用 <=2 bit
2. 因为我们共要区分 3 种情况：未出现、出现 1 次、出现超过 1 次；所以 必须使用 2 bit 表示 1 个整数
3. num 在字节数组 byte[] 中的 index = (num / 4)，因为 2 bit 表示 1 个数字；在 byte[i] 中的 2 个bit下标定位，设 bitIndex = num % (8 / 2) = num & 3
	其下标分别为 {2 * bitIndex, 1 + 2 * bitIndex}
   初始化byte[i] = 00000000，如果 bitIndex = 1，则设置当前byte的 bit[2], bit[3] 为 01，即00010000
public class Solution {
	static byte[] bitMap;
	public static String getBit(int num) {
		int byteIndex = ((num >> 3) << 1);
		int bitIndex = (num & 3);
		bitIndex <<= 1;
		boolean firstZero = (bitMap[bitIndex] & (1 << bitIndex) == 0);
		boolean secondZero = (bitMap[bitMap[bitIndex]] & (1 << (bitIndex + 1)) == 0); 
		if (firstZero && secondZero) { //00代表元素未出现过
			return "notExist";
		} else if (secondZero) { //10代表多次出现过
			return "duplicate";
		} else { //01代表出现过1次
			return "single";
		}
	} 

	public static void setBit(int num) {
		int byteIndex = ((num >> 3) << 1);
		int bitIndex = (num & 3); //e.g. 初始化byte[i] = 00000000，如果 bitIndex = 1，则设置当前byte的 bit[2], bit[3] 为 01，即00010000
		bitIndex <<= 1;
		bitMap[byteIndex] &= (0 << bitIndex); //01代表第1次出现，10代表多次出现
		bitMap[byteIndex] |= (1 << (bitIndex + 1));
	}

	public static void setExistBit(int num) {
		int byteIndex = ((num >> 3) << 1);
		int bitIndex = (num & 3);
		bitIndex <<= 1;
		bitMap[byteIndex] |= (1 << bitIndex); //01代表第1次出现，10代表多次出现
		bitMap[byteIndex] &= (0 << (bitIndex + 1));
	}

	public static void excludeDuplicate(int[] nums) {
		int len = ((1 << 33) >> 3); //使用2bit表示1个整数，因此总bit数应该为 2 * 2^32，1 byte = 8 bit， 因此字节数组长度 = (2^33)/8
		bitMap = new byte[len];
		String exists = "";
		for (int num : nums) {
			exists = getBit(num);
			if (exists.equals("notExist")) {
				setBit(num);
			} else {
				setExistBit(num);
			}
		}

		for (int num : nums) {
			exists = getBit(num);
			if (exists.equals("single")) {
				System.out.println(num);
			} 
		}
	}
}