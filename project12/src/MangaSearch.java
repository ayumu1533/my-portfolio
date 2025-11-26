/**
 * 漫画の検索に責任を持つクラス
 * 漫画の詳細検索とレビュー検索を行う
 * @author 本多 若菜
 */

import java.util.*;


public class MangaSearch {

    public void queryAndShow() {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("漫画名を入力してください:");
        String title = scanner.nextLine();

        MangaDetailSearch s1 = new MangaDetailSearch(title);
        MangaReviewSearch s2 = new MangaReviewSearch(title);

        s1.queryAndShow();
        s2.queryAndShow();
    }
}