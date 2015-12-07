package matchablestring;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;

public class Program {
    private static String readAllText(String path) {
        try (BufferedReader reader = new BufferedReader(new FileReader(new File(path)))) {
            StringBuilder sb = new StringBuilder();
            while (reader.ready()) {
                sb.append(reader.readLine());
                sb.append('\n');
            }
            return sb.toString();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

    private static long measure(String orig, String pat, boolean parallel, int matchNum, Function<String, MatchableString> func) {
        List<Integer> l = null;

        List<Long> data = new ArrayList<>();

        for (int i = 0; i < 12; i++) {
            long start = System.nanoTime();     // mérés indul

            MatchableString str = func.apply(orig);
            str.preprocess(parallel);

            for (int j = 0; j < matchNum; j++) {
                Pattern p = new Pattern(pat);
                l = str.match(p, parallel);
            }

            data.add((System.nanoTime() - start) / 1000000);
        }

//        System.out.println((parallel ? "Parallel" : "Single thread") + " matching took " + (elapsed / 1000) + " s " + (elapsed % 1000) + " ms");
//        System.out.println("Found " + l.size() + " matches.");

        return AverageCounter.countAverage(data);
    }

    private static void measureReadFile(String[] args, boolean isWarmUp) {
        String path = "..\\resources\\" + args[1];

        int multiplier = Integer.parseInt(args[3]);
        int matchNum = Integer.parseInt(args[4]);

        String orig = readAllText(path);

        String str = orig;
        for (int i = 0; i < multiplier - 1; i++) {
            str += orig;
        }

        if (!isWarmUp) {
            System.out.print(str.length() + ";");
        }

        if (args[0].equals("both")) {
            if (!isWarmUp) {
                System.out.print(matchNum + ";");
            }

            long boyer = measure(str, args[2], true, matchNum, MatchableStrings::createBoyer);
            long suffixArray = measure(str, args[2], true, matchNum, MatchableStrings::createSuffixArray);

            if (!isWarmUp) {
                System.out.print(boyer + ";");
                System.out.println(suffixArray);
            }
        } else if(args[0].equals("both_helped")) {
            if (!isWarmUp) {
                System.out.print(matchNum + ";");
            }

            Function<String, MatchableString> func = s ->
                    MatchableStrings.create(s, matchNum >= 1000 ?
                            MatchableStrings.NumberOfMatches.MoreThan1000 :
                            MatchableStrings.NumberOfMatches.LessThan1000);
            long helped = measure(str, args[2], true, matchNum, func);

            if (!isWarmUp) {
                System.out.println(helped);
            }
        } else {
            Function<String, MatchableString> func = (args[0].equals("boyer")) ? MatchableStrings::createBoyer : MatchableStrings::createSuffixArray;

            long singleThread = measure(str, args[2], false, matchNum, func);
            long parallel = measure(str, args[2], true, matchNum, func);

            if (!isWarmUp) {
                System.out.print(singleThread + ";");
                System.out.println(parallel);
            }
        }
    }

    private static void measureSimple(Function<String, MatchableString> func) {
        String orig = "i had to, Hence, i peed the fence. i don't see the adHence";
        MatchableString sm = func.apply(orig);
        sm.preprocess(false);

        String pat = "ence";
        Pattern p = new Pattern(pat);
        List<Integer> h = sm.match(p, false);

        for (Integer i : h) {
            System.out.println(i + " : " + orig.substring(i, i + pat.length()));
        }
    }

    public static void main(String[] args) {
//        measureSimple(MatchableStrings::createBoyer);
//        measureSimple(MatchableStrings::createSuffixArray);

        String[] warmUpArgs = new String[]{args[0], "00_alice.txt", "CURTSEYING", "1", "1"};

        measureReadFile(warmUpArgs, true);
        measureReadFile(args, false);
    }
}
