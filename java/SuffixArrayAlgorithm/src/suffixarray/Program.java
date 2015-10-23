package suffixarray;

import java.util.Random;

public class Program {

	public static void main(String[] args) {
		Integer[] t1 = new Integer[20];
		Random r = new Random();
		
		for (int i = 0; i < 20; i++) {
			t1[i] = r.nextInt(1000);
		}
		
		for (Integer i : t1) {
			System.out.print(i + " ");
		}
		System.out.println();
		
//		int n = Arrays.binarySearch(t1, 10, 20, 10);
//		int m = -(n+1);
//		
//		System.out.println(m + " : " + t1[m]);
		
		//MergeSort.sequentialMerge(t1, 0, 10, t1, 10, 20, t3, 0, new MergeSort.Comparer(""));
		//MergeSort.parallelMerge(t1, 0, 10, 10, 20, t3, 0, new MergeSort.Comparer(""), Executors.newWorkStealingPool());
		MergeSort.parallelSort(t1, new MergeSort.Comparer(""));
		
		for (Integer i : t1) {
			System.out.print(i + " ");
		}
	}

}
