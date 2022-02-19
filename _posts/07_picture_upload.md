# 画像アップロード機能の追加

アプリに画像アップロード機能を追加します。画像情報を格納するためのDBカラムを追加し、carrierwave gemを利用して画像アップロード機能を実装します。

この章では「CRUDの基礎とindexアクション」でつくったbooks_appを引き続き題材に使っていきます。モデルの章の後半で行ったbooksテーブルにauthorカラムを追加した後の状態を想定していますが、authorカラムの追加作業は行わなくてもこの章の内容は実行可能です。

## 画像情報を格納するためのDBカラムを追加

最初に、既存のbooksテーブルにstring型のpictureカラムを増やします。モデルの章でやったように、前に作ったmigrationファイルを編集するのではなく、新しいmigrationファイルをつくります。rails g migrationコマンドを実行し、migrationファイルを作成します。rails g migrationコマンドの基本形を再掲します。

```bash
$ rails g migration Addカラム名Toテーブル名 カラム名:型名
```

今回はbooksテーブルにpictureカラムをstring型で追加するので、実行するコマンドは以下になります。ターミナルで実行してみましょう。

```bash
$ rails g migration AddPictureToBooks picture:string
```

```console
$ rails g migration AddPictureToBooks picture:string
invoke  active_record
create    db/migrate/20220109012706_add_picture_to_books.rb
```

作成されたmigrationファイルは以下のようになっています。

```
db/migrate/20220109012706_add_picture_to_books.rb
```

```ruby
class AddPictureToBooks < ActiveRecord::Migration[7.0]
  def change
    add_column :books, :picture, :string
  end
end
```

生成されたmigrationファイルには、booksテーブルへpictureカラムをstring型で追加する指示が書かれています。

migrationファイルを作成したら、`rails db:migrate`コマンドでDBへ内容を反映します。

```console
$ rails db:migrate
== 20220109012706 AddPictureToBooks: migrating ================================
-- add_column(:books, :picture, :string)
   -> 0.0007s
== 20220109012706 AddPictureToBooks: migrated (0.0008s) =======================
```

## carrierwave gemを追加

次は画像upload機能を持つライブラリcarrierwave gemを追加します。gemを追加する場合はGemfileへ追記します。記述する場所はどこでも良いのですが、今回は一番最後の行へ追記することにします。Gemfileへ次の一行を追加して保存します。

```ruby
gem "carrierwave"
```

Gemfileの内容でgemを利用できるようにbundle installコマンドをターミナルで実行します（メッセージ中"Installing carrierwave 2.2.2"や"17 Gemfile dependencies, 81 gems now installed."の数字は異なる場合があります）。

```bash
$ bundle install
```

```console
$ bundle install
...
Installing carrierwave 2.2.2
...
Bundle complete! 17 Gemfile dependencies, 81 gems now installed.
Use `bundle info [gemname]` to see where a bundled gem is installed.
```

bundle installコマンドを実行すると、Gemfileに書かれたgemがまだなければインストールし利用可能にします。また、Gemfile.lockに利用するバージョンが書き込まれます。

続いて、carrierwaveを利用可能にするために、carrierwaveが提供する`rails g uploader Picture`コマンドを実行して必要なファイルを作成します。Rails6.1以前の環境では、事前に`bin/spring stop`コマンドを実行し、springというキャッシュの仕組みを再起動しておきます。Rails7.0以降ではspringがデフォルトでインストールされなくなったので、`bin/spring stop`コマンドは不要です。

```bash
$ rails g uploader Picture
```

```console
$ rails g uploader Picture
create  app/uploaders/picture_uploader.rb
```

## モデルの変更

次にモデルからcarrierwaveを利用して画像を扱えるように編集します。`app/models/book.rb`を開いて、次の行、

```ruby
class Book < ApplicationRecord
```

の直後に、以下を追加します。

```ruby
  mount_uploader :picture, PictureUploader
```

## コントローラの変更


コントローラのStrong Parameterの部分にpictureも追加します。`app/controllers/books_controller.rb`を開いて、以下を変更します。

```diff
class BooksController < ApplicationController
...
    def book_params
-      params.require(:book).permit(:title, :memo, :author)
+      params.require(:book).permit(:title, :memo, :author, :picture)
    end
end
```

## ビューの修正

続いて、ビューファイルを変更していきます。フォームのパーシャルファイルを変更し、pictureの欄を追加します。`text_field`ではなく、`file_field`を使っていることに注意してください。

`app/views/books/_form.html.erb`

```diff
<%= form_with(model: book) do |form| %>
...
  <div>
    <%= form.label :title, style: "display: block" %>
    <%= form.text_field :title %>
  </div>

  <div>
    <%= form.label :memo, style: "display: block" %>
    <%= form.text_area :memo %>
  </div>

  <div>
    <%= form.label :author, style: "display: block" %>
    <%= form.text_field :author %>
  </div>

+  <div>
+    <%= form.label :picture, style: "display: block" %>
+    <%= form.file_field :picture %>
+  </div>

  <div>
    <%= form.submit %>
  </div>
<% end %>
```

次に詳細表示画面を修正します。

`app/views/books/_book.html.erb`

```diff
<div id="<%= dom_id book %>">
  <p>
    <strong>Title:</strong>
    <%= book.title %>
  </p>

  <p>
    <strong>Memo:</strong>
    <%= book.memo %>
  </p>

  <p>
    <strong>Author:</strong>
    <%= book.author %>
  </p>
  
+  <p>
+    <strong>Picture:</strong>
+    <%= image_tag(book.picture_url) if book.picture.present? %>
+  </p>

</div>
```

これで画像アップロード機能が追加されました。

## 動作確認

rails serverを起動して、ブラウザから http://localhost:3000/books へアクセスしてみましょう。

```bash
$ rails s
```

```console
$ rails s
=> Booting Puma
...（略）
* Listening on http://127.0.0.1:3000
* Listening on http://[::1]:3000
Use Ctrl-C to stop
```

もしもPictureUploaderが見つからない旨のエラー（"Unable to autoload constant PictureUploader"など）が発生した場合は、rails serverを一度止めてからもう一度起動して、再アクセスしてみてください。また、 `app/uploaders/picture_uploader.rb` ファイルが存在するかも確認してみてください。存在しない場合は `rails g uploader Picture` コマンドが実行されていないケースが考えられます。

New Bookリンクをクリックすると、「ファイルを選択」ボタンが増えているかと思います。ボタンを押して画像ファイルを選び、アップロードしてみましょう。

![new](assets/picture-upload/books_with_upload_new.png)

![show](assets/picture-upload/books_with_upload_created.png)

uploadした画像ファイルがブラウザに表示されているのを確認してみてください。

## まとめ

ポイントをまとめます。

- carrierwave gemを使うと画像アップロード機能を追加できる
- Gemfileに新しいgemを追加した後、bundle installコマンドでインストールする
- マイグレーションファイルの生成はrails g migration Addカラム名Toテーブル名 カラム名:型名
