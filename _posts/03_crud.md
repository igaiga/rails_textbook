# CRUDの基礎とindexアクション

Webアプリには基本となる4つの機能があります。ページの新規作成（Create）、表示（Read）、更新（Update）、削除（Destroy）です。それぞれの頭文字を取ってCRUDと呼ばれています。大きなWebアプリも、このCRUDを基礎として作られます。

ここではCRUD機能を持ったRailsアプリを作り、その動作について解説します。

## CRUD基礎

### アプリの作成

今回も最初にアプリを作ります。本のタイトルとメモを管理する簡易なアプリです。以前の章で作成した ```my_web_apps``` フォルダの下に新しいアプリを作ります。ターミナルを起動して以下のコマンドを打ちます。

```bash
$ cd my_web_apps
$ rails new books_app
```

```console
$ rails new books_app
      create
... （略）
      create  db/cable_schema.rb
       force  config/cable.yml
```

次に、以下のコマンドを実行します（メッセージ中 "20220120025416"、"0.xxxxs" などの数字は実行するごとに異なります）。

```bash
$ cd books_app
$ rails g scaffold book title:string memo:text
$ rails db:migrate
$ rails s
```

```console
$ rails g scaffold book title:string memo:text
      invoke  active_record
      create    db/migrate/20220120025416_create_books.rb
... （略）
      create      app/views/books/_book.json.jbuilder

$ rails db:migrate
== 20220120025416 CreateBooks: migrating ======================================
-- create_table(:books)
   -> 0.0010s
== 20220120025416 CreateBooks: migrated (0.0011s) =============================

$ rails s
=> Booting Puma
...（略）
* Listening on http://127.0.0.1:3000
* Listening on http://[::1]:3000
Use Ctrl-C to stop
```

ブラウザを起動して以下のURLを入力してアクセスしてみます。

* http://localhost:3000/books

![起動した画面](assets/crud/books_index_blank.png)

こんな画面が表示されましたでしょうか。ここから、New Bookリンクをクリックして先へ進み、title欄とmemo欄を記入しCreate Bookボタンを押してみてください。

![データを入力してCreate Bookボタン](assets/crud/books_created_data_1.png)

ここからBack to booksリンクを押すと最初の`/books`のページに戻りますが、先ほど入力したデータが表示されていることがわかります。

![入力したデータが表示される](assets/crud/books_index_data_1.png)

さらにデータを追加したり、他のリンクも操作してみてください。

ここで作成したアプリはCRUDの各機能、すなわち、新規作成、表示、更新、削除を持っています。以降で、1つずつその動作を説明していきます。

### scaffoldコマンド

rails g scaffoldコマンドは新規作成、表示、更新、削除、各機能を一度に作る機能です。つまり、scaffoldを使うとCRUD機能を持ったページを作成することができます。

scaffoldは英語で「（建築現場などの）足場」という意味です。工事中の建物のまわりに組まれた足場の上で大工さんが作業している、あの足場です。scaffoldコマンドはWebアプリを作り易くするための足場です。CRUD機能はWebアプリでよく使う機能なので、「CRUDのこの部分にこの機能を足したらできるな」という場合に、scaffoldで生成したファイル群を編集して自分のアプリを作っていくと効率良く作れます。

作成されるファイルは以下の通りです。

```console
$ rails g scaffold book title:string memo:text
invoke  active_record
create    db/migrate/20220120025416_create_books.rb
create    app/models/book.rb
invoke    test_unit
create      test/models/book_test.rb
create      test/fixtures/books.yml
invoke  resource_route
 route    resources :books
invoke  scaffold_controller
create    app/controllers/books_controller.rb
invoke    erb
create      app/views/books
create      app/views/books/index.html.erb
create      app/views/books/edit.html.erb
create      app/views/books/show.html.erb
create      app/views/books/new.html.erb
create      app/views/books/_form.html.erb
create      app/views/books/_book.html.erb
invoke    resource_route
invoke    test_unit
create      test/controllers/books_controller_test.rb
create      test/system/books_test.rb
invoke    helper
create      app/helpers/books_helper.rb
invoke      test_unit
invoke    jbuilder
create      app/views/books/index.json.jbuilder
create      app/views/books/show.json.jbuilder
create      app/views/books/_book.json.jbuilder
```

この中のroute（`invoke resource_route`）, controller（`invoke scaffold_controller`）やview（`invoke erb`）は前の章で説明したrailsの各役割を担うファイルです。

一方、ページの観点から見ると、scaffoldは次に示す新規作成、表示、更新、削除のための4つの画面と、画面のない3つの機能を生成します。

![CRUD 4つの画面](assets/crud/crud_4_pages.png)

それぞれの機能と対応するアクションを示したものが次の図です。前の章でも説明されたアクションは、コントローラに書かれたpublicなメソッドのことです。基本となるケースでは、1つの画面を表示するときに1つのアクションが実行されています。

![CRUD 7つのアクション](assets/crud/crud_7_actions.png)

最初は、indexアクションのページについて見ていきましょう。

## indexアクション

indexアクションについて見ていきましょう。さきほどの7つのアクションの図で示されたこの部分です。

![indexアクション](assets/crud/index_7_actions.png)

indexアクションで表示されるページ（次の図）は登録されているデータの一覧です。ここでは登録されているBookの一覧表示画面になります。この画面が表示されるまでの処理を追いかけてみましょう。

![index - 一覧画面](assets/crud/books_index_data_2.png)

今回も処理の流れを図でみてみましょう。

![Railsアプリがリクエストを受けてレスポンスを返すまで（indexアクション）](assets/crud/index_flow.png)

Routesから順番に処理を追っていきます。

### Routes

Routesはリクエストから処理を行うコントローラとアクションを決めるための対応表です。

![Routes](assets/crud/index_flow_routes.png)

Routes表から、リクエストごとに次に処理するコントローラとアクションが決まります。Routes表を表示するために、rails serverを起動して、`http://localhost:3000/rails/info/routes` へアクセスしてみましょう。

![Routes表](assets/crud/index_routes.png)

今回はURLが"/books"、HTTPメソッドが "GET" なので、下線部が該当行です。「/booksにGETでアクセスされたとき、BooksControllerのindexアクションへ処理を渡す」という意味になります。次に進むべきコントローラはbooks#index（BooksControllerのindexアクション）となることが分かります。

コントローラの処理を見る前に、Routesのコードを見てみましょう。Routesのコードは `config/routes.rb` にあります。コードは以下のようになっています。

```ruby
Rails.application.routes.draw do
  resources :books
# ...（略）
end
```

Routes表を作るコードは `Rails.application.routes.draw do` から `end` の間に書きます。#記号ではじまる行はわかりやすさのためのコメントで、動作には影響がありません。 `http://localhost:3000/rails/info/routes`のページで表示された8行の対応表は、`resources :books` の1行によって作られます。CRUDはよく利用されるため、かんたんに書けるようになっているのです。

それでは次の処理、コントローラへ進みましょう。

### コントローラ

Routesではリクエストから処理されるコントローラとアクションが決まると、次はコントローラへ移動します。今回はBooksControllerのindexアクションです。

![コントローラ](assets/crud/index_flow_controller.png)

コントローラのコードを見てみましょう。ファイルは `app/controllers/books_controller.rb` です。

```ruby
class BooksController < ApplicationController
# ...（略）
  def index
    @books = Book.all
  end
# ...（略）
```

`class BooksController < ApplicationController`から最後の行の`end`までがBooksControllerのコードです。この中のindexメソッド、つまり`def index`から次の`end`までがindexアクションになります。

ここでやっていることは1行、`@books = Book.all` です。Book.allでBookの全データを取得して、@booksインスタンス変数へ代入します。@booksからはBookモデルの全てのオブジェクトが格納された配列を取得できます。Book.allでBookの全データがとれる仕組みとモデルオブジェクトについては、「モデル」の章で説明します。

@booksは@から始まる変数、インスタンス変数です。「一番小さなRailsアプリつくり」でも説明したように、インスタンス変数@booksを使っているのは、このあとviewで利用するためです。もしも、ここで変数をローカル変数booksにしてしまうと、コントローラの処理が終わったところでなくなってしまいます。

もうひとつ大切なことがあります。@booksと複数形になっています。これは、Book.allで取得するデータが複数の本のデータを格納していることを示すためです。場合によっては、本のデータが1個、あるいは0個である、という状況もあります。そのときも1個、あるいは0個のデータが入った配列相当のものが得られるため、どのパターンでも変数名を複数形の@booksにするのが慣習です。細かいことのようですが、RailsやRubyでのプログラミングでは変数の名前を複数形と単数形を意識して命名することが大切です。

コントローラのアクションでの処理が終わると、次はビューで処理が移ります。特に指定がないときは、`app/views/コントローラ名/アクション名`のviewファイルへ処理が移ります。ここでは`app/views/books/index.html.erb`です。

### ビュー

最後はビューでレスポンスとして返されるHTMLがつくられます。

![ビュー](assets/crud/index_flow_view.png)

今回は、このような画面のHTMLがつくられます。

![index画面](assets/crud/books_index_data_2.png)

ビューのコードを見てみましょう。ファイルは `app/views/books/index.html.erb` です。抜粋して、コントローラで取得した@booksを表示させるところを見てみましょう。

```erb
<p style="color: green"><%= notice %></p>

<% content_for :title, "Books" %>

<h1>Books</h1>

<div id="books">
  <% @books.each do |book| %>
    <%= render book %>
    <p>
      <%= link_to "Show this book", book %>
    </p>
  <% end %>
</div>

<%= link_to "New book", new_book_path %>
```

index.html.erbはHTMLのテンプレートファイルで、HTMLの中にRubyコードを埋め込むことができます。`<%= %>`で囲まれた部分は、Rubyコードの実行結果がHTMLとして埋め込まれます。類似の部品`<% %>`では、囲まれたRubyコードは実行されますが結果を埋め込みません。今回は@books.eachの繰り返しの指示で `<% %>` が使われています。

@booksに代入された全データ（"RubyとRailsの学習ガイド"、"Ruby超入門"）でブロックを繰り返し実行し、titleやmemoを表示したり、Show（詳細画面）へのリンクを生成しています。

@books.eachは全データで繰り返し処理を行います。より具体的には、ここで「データ」と呼んでいるものは「Bookモデルオブジェクト」です。今回のケースでは@booksに2つのデータ、つまり2つのBookモデルオブジェクトが入っているので、2回繰り返されます。モデルオブジェクトについて詳しくは「モデル」の章で説明しますので、ここでは「本のデータを持ったオブジェクト」といった理解で大丈夫です。

1回目の実行では変数book（2つの`|`記号で囲まれているところ）に「RubyとRailsの学習ガイド」のデータが入ったBookモデルオブジェクトが代入され、そのtitleやmemoが表示されます。2回目の実行では「Ruby超入門」のBookモデルオブジェクトが入って同様の処理が実行されます。

表示は `<% render book %>` で行っています。実は、表示部分は別のファイルに書いてあり、 `<%= render book %>` で埋め込まれるようになっています。次の図の囲み部分は別のファイルが埋め込まれています。

![renderの説明](assets/crud/index_view_partial_screenshot.png)

renderメソッドは別のビューファイルを埋め込みます。わざわざ別のファイルに書く理由は、他の画面でもそのファイルを利用することで、同じ部品を共用したいからです。埋め込む用のビューファイルをパーシャルと言います。書式は次のようになっています。

```
<%= render モデルオブジェクト %>
```

ここではrenderメソッドにBookモデルオブジェクトを渡しています。このとき、renderメソッドはパーシャルビューファイルとして `books/_book.html.erb` を埋め込む仕様になっています。パーシャルであるビューファイルの名前は、先頭を `_` で始めるルールになっています。また、データを表示するためにパーシャルの中ではbook変数へBookモデルオブジェクトが代入された状態になっています。

埋め込まれるパーシャルビュー `_book.html.erb` は次のようになっています。ファイルは`app/views/books/_book.html.erb`です。

```erb
<div id="<%= dom_id book %>">
  <p>
    <strong>Title:</strong>
    <%= book.title %> ⬅初回のbook.titleは "RubyとRailsの学習ガイド"
  </p>

  <p>
    <strong>Memo:</strong>
    <%= book.memo %> ⬅初回のbook.memoは "Rails関連技術地図とそれらの学習資料の紹介"
  </p>

</div>
```

1回目の実行では変数bookに「RubyとRailsの学習ガイド」のデータが入ったBookモデルオブジェクトが代入され、そのtitleやmemoが埋め込まれます。 `<%= book.title %>` の部分には `"RubyとRailsの学習ガイド"` が埋め込まれ、 `<%= book.memo %>` の部分には `"Rails関連技術地図とそれらの学習資料の紹介"` が埋め込まれたHTMLをつくります。

2回目の実行では「Ruby超入門」のBookモデルオブジェクトが入って同様の処理が実行され、HTMLがつくられます。パーシャルビュー `_book.html.erb` をそれぞれのデータで合計2回埋め込んだHTMLがつくられ、パーシャルビューからつくられたHTMLを埋め込んだ `index.html.erb` からHTMLがつくられます。

RailsアプリはつくられたHTMLをレスポンスとしてブラウザに返します。ブラウザは受け取ったHTMLを私たちが見れる形で表示します。

## まとめ

この章ではCRUDの1つ、一覧表示（index画面）の基礎的な内容について説明しました。

リクエストを受けてレスポンスを返すまでの流れをまとめると以下のようになります。Railsアプリはリクエストを受けると、 Routes、コントローラ、ビューの処理を経てレスポンス（HTML）を返します。

![Railsアプリがリクエストを受けてレスポンスを返すまで（indexアクション）](assets/crud/index_flow.png)

今回のリクエストはindex（一覧）画面を表示するものです。上記の処理の後、ブラウザは受け取ったHTMLを私たちが見れる形で表示します。

![index画面](assets/crud/books_index_data_2.png)

ポイントをまとめると以下のようになります。

* CRUDはWebアプリの基本となる4つの機能、新規作成（Create）、表示（Read）、更新（Update）、削除（Destroy）
* rails g scaffoldはCRUDをつくる機能
* パスが/books、HTTPメソッドがGETのリクエストは一覧画面を表示する

次の章ではCRUDのCreate（新規作成）について説明します。

## さらに学びたい場合は

- [Rails ガイド: Rails のルーティング](https://railsguides.jp/routing.html)
  - routesについての詳しい解説です。

- [Rails ガイド: Action Controller の概要](https://railsguides.jp/action_controller_overview.html)
  - コントローラについての詳しい解説です。

