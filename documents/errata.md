# 正誤表
## v2.1.0〜v.2.1.3 Rails7.0版
### Page.104 詳細表示画面のビューファイルを修正

- 誤: `@books.author`

```
+<p>
+  <strong>Author:</strong>
+  <%= @book.author %>
+</p>
```

- 正: `books.author`

```
+<p>
+  <strong>Author:</strong>
+  <%= book.author %>
+</p>
```

## 2020年2月29日 技術書典8 v2.0.0
### Page.100 7.1 画像情報を格納するための DB カラムを追加
後ろから2つ目の文「pictureカラム」であるところが「authorカラム」となっている。v2.0.1以降で修正済みです。
- 誤: books テーブルへ author カラムを string 型で追加する
- 正: books テーブルへ picture カラムを string 型で追加する
