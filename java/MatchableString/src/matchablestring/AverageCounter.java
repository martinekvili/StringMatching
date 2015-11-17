package matchablestring;

import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class AverageCounter {

    public static long countAverage(List<Long> data) {
        Collections.sort(data);

//        System.out.println("\nData is:");
//        for (Long l : data) {
//            System.out.println(l);
//        }

        long Q1 = data.get(0);
        long Q2 = data.get(data.size() / 2);
        long diff = (long) ((Q2 - Q1) * 1.5);

//        System.out.println("Q1: " + Q1 + ", Q2: " + Q2 + ", diff: " + diff);

        List<Long> filtered = data.stream().filter(d -> d <= Q2 + diff).collect(Collectors.toList());

        return filtered.stream().reduce(0L, (acc, d) -> acc + d) / filtered.size();
    }
}
