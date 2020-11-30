import java.io.File;
import java.io.FileReader;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;


public class Solution {
    /**
     * Алгоритм Левенштейна для поиска редакторского расстояния
     */
    public static int Levenstain(String str1, String str2) {
        int[] Di_1 = new int[str2.length() + 1];
        int[] Di = new int[str2.length() + 1];

        for (int j = 0; j <= str2.length(); j++) {
            Di[j] = j; // (i == 0)
        }

        for (int i = 1; i <= str1.length(); i++) {
            System.arraycopy(Di, 0, Di_1, 0, Di_1.length);

            Di[0] = i; // (j == 0)
            for (int j = 1; j <= str2.length(); j++) {
                int cost = (str1.charAt(i - 1) != str2.charAt(j - 1)) ? 1 : 0;
                Di[j] = min(
                        Di_1[j] + 1,
                        Di[j - 1] + 1,
                        Di_1[j - 1] + cost
                );
            }
        }

        return Di[Di.length - 1];
    }

    private static int min(int n1, int n2, int n3) {
        return Math.min(Math.min(n1, n2), n3);
    }

    public static void main(String[] args) throws Exception {
        Scanner in = new Scanner(new FileReader("input.txt"));
        PrintStream out = new PrintStream(new File("output.txt"));
        Scanner indic = new Scanner(new FileReader("dict.txt"));
        ArrayList<String> words = new ArrayList<>(); // массив для хранения наших слов из текста
        char[] rubbish = new char[]{'!', '?', ',', ';', '.', ':', '«', '(', ')', '»'};
        while (in.hasNextLine()) {
            String s = in.nextLine(); // считываем текст
            String[] cur = s.split(" "); // разделяем на пробелы
            for (String x : cur) {
                if (!x.equals("—")) {
                    words.add(x); // добавляем в массив слова из текста, если это не тире
                }
            }
        }
        for (int i = 0; i < words.size(); i++) {
            // убираем знаки препинания
            String x = words.get(i);
            StringBuilder now = new StringBuilder();
            for (int j = 0; j < x.length(); j++) {
                boolean ok = true;
                for (char c : rubbish) {
                    if (x.charAt(j) == c) {
                        ok = false;
                        break;
                    }
                }
                if (ok) now.append(x.charAt(j));
            }
            // перевод всех символов в нижний регистр
            String f = now.toString();
            f = f.toLowerCase();
            words.set(i, f);
        }
        out.println("Number of words: " + words.size()); // кол-во слов
        HashSet<String> set = new HashSet<>(words); // структура для хранения кол-ва уникальных слов
        out.println("Number of different words: " + set.size()); // кол-во уникальных слов
        HashMap<String, Integer> map = new HashMap<>(); // структура для хранения словаря
        ArrayList<String> dict = new ArrayList<>();
        while (indic.hasNextLine()) {
            String word = indic.next();
            int value = indic.nextInt();
            map.put(word, value); // добавление элементов в словарь
            dict.add(word);
        }
        int k = 0;
        ArrayList<String> potentialMistakes = new ArrayList<>();
        for (String x : set) {
            if (map.containsKey(x)) k++; // проверка нахождения слова в словаре
            else {
                out.println(x); // вывод потенциальных ошибок
                potentialMistakes.add(x);
            }
        }
        out.println("Number of dic words: " + k); // кол-во слов из словаря
        HashMap<String, String> correctWord = new HashMap<>();
        for (String x : potentialMistakes) {
            /*
             * Нахождение редакторского расстояния
             */
            String ans = "none";
            int best = 3;
            for (String h : dict) {
                if (Levenstain(x, h) <= best) {
                    if (Levenstain(x, h) < best) {
                        best = Levenstain(x, h);
                        ans = h;
                    } else if (best < 3) {
                        if (map.get(h) > map.get(ans)) {
                            ans = h;
                        }
                    }
                }

            }
            if (x.contains("-")) {
                int index = x.indexOf('-');
                if (map.containsKey(x.substring(0, index)) && map.containsKey(x.substring(index + 1)) && best > 2) {
                    best = 2;
                    ans = x.substring(0, index) + " " + x.substring(index + 1);
                }
            }
            if (!ans.equals("none")) correctWord.put(x, ans);
            out.println(x + " - " + ans + " - " + best);
        }
        for (int i = 0; i < words.size(); i++) {
            if (!map.containsKey(words.get(i))) {
                words.set(i, correctWord.get(words.get(i)));
            }
        }
        set.addAll(words);
        out.println("Number of different words " + set.size());
    }
}
