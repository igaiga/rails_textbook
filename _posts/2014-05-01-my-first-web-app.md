---
layout: post
unique_identifier:
 - 'http:/example.jp/bookid_in_url'
 - 'BookID'
 - 'URL'
title: 'Webアプリをまずはつくってみよう'
creator: '五十嵐邦明'
date: '2014-05-01'
categories:
---

# Webアプリをまずはつくってみよう

それでは、早速Webアプリをつくってみましょう。作るのは、タイトルなどの情報と画像が投稿できる簡易な書籍管理アプリです。まずはWebアプリでどんなことができるのか、その作り方はどのようなものかを体験してもらうのがこの章の目的です。それぞれのコマンドやコードの意味は、本書の中で追って説明していきます。

## Webアプリをつくる

### アプリの作成とWelcome画面

まずはターミナルを起動して以下のコマンドを打ってみましょう。

```bash
mkdir my_web_apps
cd my_web_apps
```

mkdirはフォルダを作成するコマンド、cdはターミナル内で現在のフォルダを移動するコマンドです（Winで普段使いなれている「コンピューター（エクスプローラー）」を起動するには、ターミナルで`explorer .`と打つと現在のフォルダを開くことができます。MacでFinderを開くにはターミナルから`open .`と打ちます。これらからフォルダを作るのと同じ働きをするコマンドがmkdirです）。

続けて以下のコマンドを実行します。

```bash
rails new first_books_app
```

以下のような結果が表示されるでしょうか（実行には少し時間がかかります）。

```console
$ rails new first_books_app
      create
      create  README.rdoc
      create  Rakefile
... (略)
Bundle complete! 16 Gemfile dependencies, 70 gems now installed.
Use `bundle show [gemname]` to see where a bundled gem is installed.
         run  bundle exec spring binstub --all
* bin/rake: spring inserted
* bin/rails: spring inserted
```

ターミナルの画面にこのように"Bundle complete!"と表示されれば成功です（メッセージ中"16 Gemfile dependencies, 70 gems now installed."の16や70という数字は異なる場合があります）。railsコマンドはたくさんのフォルダとファイルを自動で作ります。

次は以下のコマンドを実行してみてください。`rails s`コマンドはwebサーバを起動するコマンドで、sはserverの略です。

```bash
cd books_app
rails s
```

うまく動作している場合は、以下のような表示になります（メッセージ中"Version 3.8.2"の数字は異なる場合があります）。

```console
$ rails s
=> Booting Puma
=> Rails 5.1.2 application starting in development on http://localhost:3000
=> Run `rails server -h` for more startup options
Puma starting in single mode...
* Version 3.9.1 (ruby 2.4.1-p111), codename: Private Caller
* Min threads: 5, max threads: 5
* Environment: development
* Listening on tcp://0.0.0.0:3000
Use Ctrl-C to stop
```

では、ブラウザを起動して以下のURLを入力してアクセスしてみましょう。

* http://localhost:3000

![welcome rails](assets/my-first-web-app/welcome_rails.png)

これは、Railsが起動し、あなたのブラウザからのリクエストを受け付けて、表示している画面です。ここまでのわずかの手順で、Webアプリをつくり、画面を表示しているのです。

### ページの作成

ひきつづき、以下のコマンドを入力してください（メッセージ中"process 45698"、"20170108042052"、"0.0008s"らの数字は実行するごとに異なります）。rails serverが起動している場合は、Ctrl-c（controlキーを押しながらcキー）で終了してからコマンドを打ちます。

```bash
rails g scaffold book title memo:text author picture
rails db:migrate
rails s
```

```console
$ rails g scaffold book title memo:text author picture
Running via Spring preloader in process 45698
      invoke  active_record
      create    db/migrate/20170629002457_create_books.rb
...(略)

$ rails db:migrate
== 20170629002457 CreateBooks: migrating ======================================
-- create_table(:books)
   -> 0.0006s
== 20170629002457 CreateBooks: migrated (0.0007s) =============================

$ rails s
=> Booting Puma
=> Rails 5.1.2 application starting in development on http://localhost:3000
=> Run `rails server -h` for more startup options
Puma starting in single mode...
* Version 3.9.1 (ruby 2.4.1-p111), codename: Private Caller
* Min threads: 5, max threads: 5
* Environment: development
* Listening on tcp://0.0.0.0:3000
Use Ctrl-C to stop
```

ここでまたブラウザを使い、以下のURLを表示させます。

* http://localhost:3000/books

![books](assets/my-first-web-app/scaffold_index.png)


画面が表示されたら、New Bookのリンクをたどってみましょう。Title, Memoなどを入力し、Create Bookボタンで保存してみてください。また、保存したデータを編集や削除をしてみてください。ここまでの作業で簡易なブログの基本機能ができました。

### 写真アップロード機能の追加

次は、写真をアップロードできるようにしてみましょう。Railsにファイルをアップロードする機能を追加するには、ライブラリをインストールする必要があります。Railsルートフォルダ（```my_web_apps/blog_app```）内のGemfileというファイルを開いてください。

```ruby
gem 'sqlite3'
```

という記述を探して、その下に次の一行を追加して保存します。

```ruby
gem 'carrierwave'
```

追加できたら、Terminalで、次のコマンドを実行してください（`rails s`はCtrl-cで終了させてください。また、メッセージ中"Installing carrierwave 1.0.0"、"Running via Spring preloader in process 67309"の数字は異なる場合があります。）。

```bash
bundle
bin/spring stop
rails g uploader Picture
```

```console
$ bundle
Fetching gem metadata from https://rubygems.org/...........
Fetching version metadata from https://rubygems.org/...
Fetching dependency metadata from https://rubygems.org/..
Resolving dependencies...
...
Installing carrierwave 1.0.0
Bundle complete! 17 Gemfile dependencies, 71 gems now installed.
Use `bundle show [gemname]` to see where a bundled gem is installed.

$ bin/spring stop
Spring stopped.

$ rails g uploader Picture
Running via Spring preloader in process 67309
      create  app/uploaders/picture_uploader.rb
```

次にファイルを編集します。`app/models/book.rb`を開いて、次の行、

```ruby
class Book < ApplicationRecord
```

の直後に、以下を追加します。

```ruby
  mount_uploader :picture, PictureUploader
```

さらに、`app/views/books/_form.html.erb`の以下の部分を編集します（- 記号の行を削除して、かわりに + 記号の行を追加してください）。

```diff
- <%= form.text_field :picture, id: :book_picture %>
+ <%= form.file_field :picture, id: :book_picture %>
```

あと少しです。最後に`app/views/books/show.html.erb`を開いて編集します。

```diff
- <%= @book.picture %>
+ <%= image_tag(@book.picture_url) if @book.picture.present? %>
```

rails serverを起動して、ブラウザから http://localhost:3000/books へアクセスしてみましょう[^2]。

[^2]: PictureUploaderが見つからない旨のエラー（"Unable to autoload constant PictureUploader"など）が発生した場合は、rails serverを一度止め、 `bin/spring stop` コマンドを実行してからrails serverをもう一度起動して、再アクセスしてみてください。また、 `app/uploaders/picture_uploader.rb` ファイルが存在するかも確認してみてください。存在しない場合は `rails g uploader Picture` コマンドが実行されていないケースが考えられます。

```bash
rails s
```

```console
$ rails s
=> Booting Puma
=> Rails 5.1.2 application starting in development on http://localhost:3000
=> Run `rails server -h` for more startup options
Puma starting in single mode...
* Version 3.9.1 (ruby 2.4.1-p111), codename: Private Caller
* Min threads: 5, max threads: 5
* Environment: development
* Listening on tcp://0.0.0.0:3000
Use Ctrl-C to stop
```

New Bookリンクをクリックすると、「ファイルを選択」ボタンが増えているかと思います。ボタンを押して画像ファイルを選び、アップロードしてみましょう。

* http://localhost:3000/books

![new](assets/my-first-web-app/new_page.png)

![show](assets/my-first-web-app/show_page.png)

画像をアップロードできる簡易ブログアプリができあがりました。初めてのWebアプリづくりはいかがでしたか？とてもシンプルなアプリですが、Webアプリの基本となるデータ作成、表示、更新、削除の機能や、写真投稿機能を付加するためのライブラリの使い方などがこの中につまっています。本書を読み終わる頃には、ここで書いたコードやコマンドの意味が分かるようになりますので、今はまだ分からなくて大丈夫です（まだ何も説明していないので当たり前ですね）。次の章から、Webアプリがどうような仕組みで動作するのかを説明していきます。
