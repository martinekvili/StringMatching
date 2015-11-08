package matchablestring.suffixarray;

import java.util.Arrays;
import java.util.Comparator;
import java.util.stream.IntStream;

public class MergeSort {
    static public class Comparer implements Comparator<Integer> {
        private String str;

        public Comparer(String s) {
            str = s;
        }

        @Override
        public int compare(Integer o1, Integer o2) {
            return StringHelper.compare(str, o1.intValue(), str, o2.intValue(), str.length());
        }
    }

    private static final int mergeTreshold = 8192;
    private static final int sortTreshold = 1024;

    private static void sequentialMerge(Integer[] arr1, int start1, int end1, Integer[] arr2, int start2, int end2,
                                        Integer[] dst, int start_dst, Comparator<Integer> comp) {
        while (start1 != end1 && start2 != end2) {
            if (comp.compare(arr1[start1], arr2[start2]) < 0) {
                dst[start_dst] = arr1[start1];
                start1++;
            } else {
                dst[start_dst] = arr2[start2];
                start2++;
            }
            start_dst++;
        }

        while (start1 != end1) {
            dst[start_dst] = arr1[start1];
            start1++;
            start_dst++;
        }

        while (start2 != end2) {
            dst[start_dst] = arr2[start2];
            start2++;
            start_dst++;
        }
    }

    private static void parallelMerge(Integer[] arr, int start1, int end1, int start2, int end2, Integer[] dst, int pos,
                                      Comparator<Integer> comparer) {
        int length1 = end1 - start1;
        int length2 = end2 - start2;

        if (length1 < length2) {
            int tmp;

            tmp = start1;
            start1 = start2;
            start2 = tmp;

            tmp = end1;
            end1 = end2;
            end2 = tmp;

            tmp = length1;
            length1 = length2;
            length2 = tmp;
        }

        if (length1 == 0) {
            return;
        }

        if ((length1 + length2) < mergeTreshold) {
            sequentialMerge(arr, start1, end1, arr, start2, end2, dst, pos, comparer);
        } else {
            int xpos1 = (start1 + end1) / 2;

            int xpos2 = Arrays.binarySearch(arr, start2, end2, arr[xpos1], comparer);
            xpos2 = xpos2 < 0 ? -(xpos2 + 1) : xpos2; // A dokument�ci� szerint
            // �gy kapjuk meg az
            // els� nem kisebb elem
            // index�t.

            int xpos_dst = pos + (xpos1 - start1) + (xpos2 - start2);

            dst[xpos_dst] = arr[xpos1];

            final int start1_f = start1;
            final int start2_f = start2;
            final int end1_f = end1;
            final int end2_f = end2;
            final int xpos2_f = xpos2; // Csak hogy haszn�lhassuk enclosing
            // scope-on bel�l

            IntStream.range(0, 2).parallel().forEach(i -> {
                if (i == 0) {
                    parallelMerge(arr, start1_f, xpos1, start2_f, xpos2_f, dst, pos, comparer);
                } else {
                    parallelMerge(arr, xpos1 + 1, end1_f, xpos2_f, end2_f, dst, xpos_dst + 1, comparer);
                }
            });
        }
    }

    private static void parallelSort(Integer[] src, int start, int end, Integer[] dest, Comparator<Integer> comparer,
                                     boolean srcToDest) {
        if (start == end) {
            return;
        }

        if ((end - start) < sortTreshold) {
            Arrays.sort(src, start, end, comparer);

            if (srcToDest) {
                for (int i = start; i < end; i++) {
                    dest[i] = src[i];
                }
            }

            return;
        }

        int middle = (start + end) / 2;

        IntStream.range(0, 2).parallel().forEach(i -> {
            if (i == 0) {
                parallelSort(src, start, middle, dest, comparer, !srcToDest);
            } else {
                parallelSort(src, middle, end, dest, comparer, !srcToDest);
            }
        });

        if (srcToDest) {
            parallelMerge(src, start, middle, middle, end, dest, start, comparer);
        } else {
            parallelMerge(dest, start, middle, middle, end, src, start, comparer);
        }
    }

    public static void parallelSort(Integer[] arr, Comparator<Integer> comparer) {
        Integer[] acc = new Integer[arr.length];

        parallelSort(arr, 0, arr.length, acc, comparer, false);
    }

}
