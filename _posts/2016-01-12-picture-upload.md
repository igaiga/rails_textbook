---
layout: post
unique_identifier:
 - 'http:/example.jp/bookid_in_url'
 - 'BookID'
 - 'URL'
title: '画像アップロード機能の追加'
creator: '五十嵐邦明'
date: '2016-01-12'
categories:
---

# 画像アップロード機能の追加

アプリに画像アップロード機能を追加します。画像情報を格納するためのDBカラムを追加し、carrierwave gemを利用して画像アップロード機能を実装します。

この章では「CRUDの基礎とindexアクション」で作ったbooks_appを引き続き題材に使っていきます。モデルの章の後半で行ったbooksテーブルにauthorカラムを追加した後の状態を想定していますが、authorカラムの追加作業は行わなくてもこの章の内容は実行可能です。

## 画像情報を格納するためのDBカラムを追加

最初に、既存のbooksテーブルにstring型のpictureカラムを増やします。モデルの章でやったように、前に作ったmigrationファイルを編集するのではなく、新しいmigrationファイルを作ります。rails g migrationコマンドを実行し、migrationファイルを作成します。rails g migrationコマンドの基本形を再掲します。

```bash
rails g migration Addカラム名Toテーブル名 カラム名:型名
```

今回はbooksテーブルにpictureカラムをstring型で追加するので、実行するコマンドは以下になります。ターミナルで実行してみましょう。

```bash
rails g migration AddPictureToBooks picture:string
```

```console
$ rails g migration AddPictureToBooks picture:string
Running via Spring preloader in process 3249
      invoke  active_record
      create    db/migrate/20191020225655_add_picture_to_books.rb
```

作成されたmigrationファイルは以下のようになっています。

```
db/migrate/20191020225655_add_picture_to_books.rb
```

```ruby
class AddPictureToBooks < ActiveRecord::Migration[6.0]
  def change
    add_column :books, :picture, :string
  end
end
```

生成されたmigrationファイルには、booksテーブルへauthorカラムをstring型で追加する指示が書かれています。

migrationファイルを作成したら、`rails db:migrate`コマンドでDBへ内容を反映します。

```console
$ rails db:migrate
== 20191020225655 AddPictureToBooks: migrating ================================
-- add_column(:books, :picture, :string)
   -> 0.0027s
== 20191020225655 AddPictureToBooks: migrated (0.0028s) =======================
```

## carrierwave gemを追加

次は画像upload機能を持つライブラリcarrierwave gemを追加します。gemを追加する場合はGemfileへ追記します。記述する場所はどこでも良いのですが、今回は一番最後の行へ追記することにします。Gemfileへ次の一行を追加して保存します。

```ruby
gem 'carrierwave'
```

Gemfileの内容でgemを利用できるようにbundleコマンドをターミナルで実行します（メッセージ中"Installing carrierwave 1.0.0"の数字は異なる場合があります）。

```bash
bundle
```

```console
$ bundle
Using rake 13.0.0
...
Installing carrierwave 1.3.1
Bundle complete! 19 Gemfile dependencies, 79 gems now installed.
Use `bundle info [gemname]` to see where a bundled gem is installed.
```

bundleコマンドを実行すると、Gemfileに書かれたgemがまだなければインストールし利用可能にします。また、Gemfile.lockに利用するバージョンが書き込まれます。

続いて、carrierwaveを利用可能にするために、carrierwaveが提供する`rails g uploader Picture`コマンドを実行して必要なファイルを作成します。その前に、`bin/spring stop`コマンドを実行し、springというキャッシュの仕組みを再起動ておきます。このコマンドは環境によって実行不要な場合もありますが、確実に成功するように実行しています。

```bash
$ bin/spring stop
$ rails g uploader Picture
```

```console
$ bin/spring stop
Spring stopped.

$ rails g uploader Picture
Running via Spring preloader in process 4097
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
<%= form_with(model: book, local: true) do |form| %>
...
  <div class="field">
    <%= form.label :title %>
    <%= form.text_field :title %>
  </div>

  <div class="field">
    <%= form.label :memo %>
    <%= form.text_area :memo %>
  </div>

  <div class="field">
    <%= form.label :author %>
    <%= form.text_field :author %>
  </div>

+  <div class="field">
+    <%= form.label :picture %>
+    <%= form.file_field :picture %>
+  </div>

  <div class="actions">
    <%= form.submit %>
  </div>
<% end %>
```

次に詳細表示画面を修正します。

`app/views/books/show.html.erb`

```diff
<p id="notice"><%= notice %></p>

<p>
  <strong>Title:</strong>
  <%= @book.title %>
</p>

<p>
  <strong>Memo:</strong>
  <%= @book.memo %>
</p>

<p>
  <strong>Author:</strong>
  <%= @book.author %>
</p>

+<p>
+  <strong>Picture:</strong>
+  <%= image_tag(@book.picture_url) if @book.picture.present? %>
+</p>

<%= link_to 'Edit', edit_book_path(@book) %> |
<%= link_to 'Back', books_path %>
```

一覧表示画面も変更します。一覧表示画面では画像は表示させず、ファイル名だけを表示することにします。

`app/views/books/index.html.erb`

```diff
<p id="notice"><%= notice %></p>

<h1>Books</h1>

<table>
  <thead>
    <tr>
      <th>Title</th>
      <th>Memo</th>
      <th>Author</th>
+     <th>Picture</th>
      <th colspan="3"></th>
    </tr>
  </thead>

  <tbody>
    <% @books.each do |book| %>
      <tr>
        <td><%= book.title %></td>
        <td><%= book.memo %></td>
        <td><%= book.author %></td>
+       <td><%= book.picture %></td>
        <td><%= link_to 'Show', book %></td>
        <td><%= link_to 'Edit', edit_book_path(book) %></td>
        <td><%= link_to 'Destroy', book, method: :delete, data: { confirm: 'Are you sure?' } %></td>
      </tr>
    <% end %>
  </tbody>
</table>

<br>

<%= link_to 'New Book', new_book_path %>
```

これで画像アップロード機能が追加されました。

## 動作確認

rails serverを起動して、ブラウザから http://localhost:3000/books へアクセスしてみましょう[^2]。

[^2]: PictureUploaderが見つからない旨のエラー（"Unable to autoload constant PictureUploader"など）が発生した場合は、rails serverを一度止め、 `bin/spring stop` コマンドを実行してからrails serverをもう一度起動して、再アクセスしてみてください。また、 `app/uploaders/picture_uploader.rb` ファイルが存在するかも確認してみてください。存在しない場合は `rails g uploader Picture` コマンドが実行されていないケースが考えられます。


```bash
rails s
```

```console
$ rails s
=> Booting Puma
...（略）
* Listening on tcp://localhost:3000
Use Ctrl-C to stop
```

New Bookリンクをクリックすると、「ファイルを選択」ボタンが増えているかと思います。ボタンを押して画像ファイルを選び、アップロードしてみましょう。

![new](assets/picture-upload/books_new.png)

![show](assets/picture-upload/books_show.png)

uploadした画像ファイルがブラウザに表示されているのを確認してみてください。

## まとめ

ポイントをまとめます。

- carrierwave gemを使うと画像アップロード機能を追加できる
- Gemfileに新しいgemを追加した後、bundleコマンドでインストールする
- マイグレーションファイルの生成はrails g migration Addカラム名Toテーブル名 カラム名:型名
