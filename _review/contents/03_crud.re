
= CRUDの基礎とindexアクション


Webアプリには基本となる4つの機能があります。ページの新規作成（Create）、表示（Read）、更新（Update）、削除（Destroy）です。それぞれの頭文字を取ってCRUDと呼ばれています。大きなWebアプリも、このCRUDを基礎として作られます。



ここではCRUD機能を持ったRailsアプリを作り、その動作について解説します。


== CRUD基礎

=== アプリの作成


今回も最初にアプリを作ります。本のタイトルとメモを管理する簡易なアプリです。以前の章で作成した @<tt>{my_web_apps} フォルダの下に新しいアプリを作ります。ターミナルを起動して以下のコマンドを打ちます（メッセージ中の"Done in 3.61s."の数字は所用時間なので、毎回異なります）。


//emlist[][bash]{
cd my_web_apps
rails new books_app
//}

//emlist[][console]{
$ rails new books_app
      create
... （略）
   Done in 3.61s.
Webpacker successfully installed 🎉 🍰
//}


次に、以下のコマンドを実行します（メッセージ中"in process 52142"、"20160702024137"、"-> 0.0013s"などの数字は実行するごとに異なります）。


//emlist[][bash]{
cd books_app
rails g scaffold book title:string memo:text
rails db:migrate
rails s
//}

//emlist[][console]{
$ rails g scaffold book title:string memo:text
Running via Spring preloader in process 20280
      invoke  active_record
      create    db/migrate/20191012005727_create_books.rb
...
      invoke  scss
      create    app/assets/stylesheets/scaffolds.scss

$ rails db:migrate
== 20191012005727 CreateBooks: migrating ======================================
-- create_table(:books)
   -> 0.0034s
== 20191012005727 CreateBooks: migrated (0.0035s) =============================

$ rails s
=> Booting Puma
...（略）
* Listening on tcp://localhost:3000
Use Ctrl-C to stop
//}


ブラウザを起動して以下のURLを入力してアクセスしてみます。

 * http://localhost:3000/books



//image[books_index_blank][起動した画面]{
//}




こんな画面が表示されましたでしょうか。ここから、New Bookリンクをクリックして先へ進み、title欄とmemo欄を記入しCreate Bookボタンを押してみてください。



//image[books_created_data_1][データを入力してCreate Bookボタン]{
//}




ここからBackボタンを押すと最初の@<tt>{/books}のページに戻りますが、先ほど入力したデータが表示されていることが分かるかと思います。



//image[books_index_data_1][入力したデータが表示される]{
//}




さらにデータを追加したり、他のリンクも操作してみてください。



ここで作成したアプリはCRUDの各機能、すなわち、新規作成、表示、更新、削除を持っています。以降で、1つずつその動作を説明していきます。


=== scaffoldコマンド


rails g scaffoldコマンドは新規作成、表示、更新、削除、各機能を一度に作る機能です。つまり、scaffoldを使うとCRUD機能を持ったページを作成することができます。



scaffoldは英語で「（建築現場などの）足場」という意味です。工事中の建物のまわりに組まれた足場の上で大工さんが作業している、あの足場です。scaffoldコマンドはWebアプリを作り易くするための足場です。CRUD機能はWebアプリでよく使う機能なので、「CRUDのこの部分にこの機能を足したらできるな」という場合に、scaffoldで生成したファイル群を編集して自分のアプリを作っていくと効率良く作れます。



作成されるファイルは以下の通りです。


//emlist[][console]{
$ rails g scaffold book title:string memo:text
Running via Spring preloader in process 20280
  invoke  active_record
  create    db/migrate/20191012005727_create_books.rb
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
  invoke  assets
  invoke    scss
  create      app/assets/stylesheets/books.scss
  invoke  scss
  create    app/assets/stylesheets/scaffolds.scss
//}


この中のroute（@<tt>{invoke resource_route}）, controller（@<tt>{invoke scaffold_controller}）やview（@<tt>{invoke erb}）は前の章で説明したrailsの各役割を担うファイルです。



一方、ページの観点から見ると、scaffoldは次に示す新規作成、表示、更新、削除のための4つの画面と、画面のない3つの機能を生成します。



//image[crud_4_pages][CRUD 4つの画面]{
//}




それぞれの機能と対応するアクションを示したものが次の図です。前の章でも説明されたアクションは、コントローラに書かれたpublicなメソッドのことです。1つの画面を表示するとき、1つのアクションが実行されているのが基本形です。



//image[crud_7_actions][CRUD 7つのアクション]{
//}




最初は、indexアクションのページについて見ていきましょう。


== indexアクション


indexアクションについて見ていきましょう。さきほどの7つのアクションの図で示されたこの部分です。



//image[index_7_actions][indexアクション]{
//}




indexアクションで表示されるページ（次の図）は登録されているデータの一覧です。ここでは登録されているBookの一覧表示画面になります。この画面が表示されるまでの処理を追いかけてみましょう。



//image[books_index_data_2][index - 一覧画面]{
//}




今回も処理の流れを図でみてみましょう。



//image[index_flow][Railsアプリがリクエストを受けてレスポンスを返すまで（indexアクション）]{
//}




Routesから順番に処理を追っていきます。


=== Routes


Routesはリクエストから処理を行うコントローラとアクションを決めるための対応表です。



//image[index_flow_routes][Routes]{
//}




Routes表から、リクエストごとに次に処理するコントローラとアクションが決まります。Routes表を表示するために、rails serverを起動して、@<tt>{http://localhost:3000/rails/info/routes} へアクセスしてみましょう。



//image[index_routes][Routes表]{
//}




今回はURLが"/books"、HTTPメソッドが "GET" なので、下線部が該当行です。「/booksにGETでアクセスされたとき、BooksControllerのindexアクションへ処理を渡す」という意味になります。次に進むべきコントローラはbooks#index（BooksControllerのindexアクション）となることが分かります。



コントローラの処理を見る前に、Routesのコードを見てみましょう。Routesのコードは @<tt>{config/routes.rb} にあります。コードは以下のようになっています。


//emlist[][ruby]{
Rails.application.routes.draw do
  resources :books
  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
end
//}


Routes表を作るコードは @<tt>{Rails.application.routes.draw do} から @<tt>{end} の間に書きます。#記号ではじまる行はわかりやすさのためのコメントで、動作には影響がありません。 @<tt>{http://localhost:3000/rails/info/routes}のページで表示された8行の対応表は、@<tt>{resources :books} の1行によって作られます。CRUDはよく利用されるため、かんたんに書けるようになっているのです。



それでは次の処理、コントローラへ進みましょう。


=== コントローラ


Routesではリクエストから処理されるコントローラとアクションが決まると、次はコントローラへ移動します。今回はBooksControllerのindexアクションです。



//image[index_flow_controller][コントローラ]{
//}




コントローラのコードを見てみましょう。ファイルは @<tt>{app/controllers/books_controller.rb} です。


//emlist[][ruby]{
class BooksController < ApplicationController
  ...
  def index
    @books = Book.all
  end
  ...
//}


@<tt>{class BooksController < ApplicationController}から最後の行の@<tt>{end}までがBooksControllerのコードです。この中のindexメソッド、つまり@<tt>{def index}から次の@<tt>{end}までがindexアクションになります。



ここでやっていることは1行、@<tt>{@books = Book.all} です。Book.allでBookの全データがつまった配列を取得して、@booksインスタンス変数へ代入します。Book.allでBookの全データがとれる仕組みについては、「モデル」の章で説明します。



@booksは@から始まる変数、インスタンス変数です。「一番小さなRailsアプリつくり」でも説明したように、インスタンス変数@booksを使っているのは、このあとviewで利用するためです。もしも、ここで変数をローカル変数booksにしてしまうと、コントローラの処理が終わったところでなくなってしまいます。



もうひとつ大切なことがあります。@booksと複数形になっています。これは、Book.allで取得するデータが複数の本のデータを格納した配列であることを示すためです。場合によっては、本のデータが1個、あるいは0個である、という状況もあります。そのときも1個、あるいは0個のデータが入った配列が取得されます。どのパターンも@booksへは配列を代入するため、変数名を複数形の@booksにするのが慣習です。細かいことのようですが、RailsやRubyでのプログラミングでは変数の名前を複数形と単数形を意識して命名することが大切です。



コントローラのアクションでの処理が終わると、次はビューで処理が移ります。特に指定がないときは、@<tt>{app/views/コントローラ名/アクション名}のviewファイルへ処理が移ります。ここでは@<tt>{app/views/books/index.html.erb}です。


=== ビュー


最後はビューでレスポンスとして返されるHTMLがつくられます。



//image[index_flow_view][ビュー]{
//}




今回は、このような画面のHTMLがつくられます。



//image[books_index_data_2][index画面]{
//}




ビューのコードを見てみましょう。ファイルは @<tt>{app/views/books/index.html.erb} です。抜粋して、コントローラで取得した@booksを表示させるところを見てみましょう。


//emlist[][erb]{
<% @books.each do |book| %> ⬅️ @booksはbookがいくつか入った配列
  <tr>
    <td><%= book.title %></td> ⬅️初回のbook.title "RubyとRailsの学習ガイド" 
    <td><%= book.memo %></td> ⬅️初回のbook.memo "Rails関連技術地図とそれらの学習資料の紹介"
    <td><%= link_to 'Show', book %></td>
    <td><%= link_to 'Edit', edit_book_path(book) %></td>
    <td><%= link_to 'Destroy', book, method: :delete, data: { confirm: 'Are you sure?' } %></td>
  </tr>
<% end %>
//}


表示は@<tt>{<% @books.each do |book| %>}から@<tt>{<% end %>} で行っています。@booksに代入された全データ（"RubyとRailsの学習ガイド"、"Ruby超入門"）でブロックを繰り返し実行し、titleやmemoを表示したり、Show（詳細画面）、Edit（編集画面）、削除ボタンのリンクを生成します。



今回のケースでは、@booksに2つのデータが入っています。@books.each文は全データで繰り返し処理を行う文です。1回目の実行では変数book（2つの@<tt>{|}記号で囲まれているところ）に「RubyとRailsの学習ガイド」のデータが入った状態となり、そのtitleやmemoが表示されます。2回目の実行では「Ruby超入門」のデータが格納されて同様の処理が実行されます。



index.html.erbはHTMLのテンプレートファイルで、HTMLの中にRubyコードを埋め込むことができます。@<tt>{<%= %>}で囲まれたコードは実行結果がHTMLとして出力されます。@<tt>{<% %>} で囲まれたコードは実行されますが、結果を埋め込みません。今回は@books.eachの繰り返しで @<tt>{<% %>} が使われています。



RailsアプリはつくられたHTMLをレスポンスとしてブラウザに返します。ブラウザは受け取ったHTMLを私たちが見れる形で表示します。


== まとめ


この章ではCRUDの1つ、一覧表示（index画面）の基礎的な内容について説明しました。



リクエストを受けてレスポンスを返すまでの流れをまとめると以下のようになります。Railsアプリはリクエストを受けると、 Routes、コントローラ、ビューの処理を経てレスポンス（HTML）を返します。



//image[index_flow][Railsアプリがリクエストを受けてレスポンスを返すまで（indexアクション）]{
//}




今回のリクエストはindex（一覧）画面を表示するものです。上記の処理の後、ブラウザは受け取ったHTMLを私たちが見れる形で表示します。



//image[books_index_data_2][index画面]{
//}




ポイントをまとめると以下のようになります。

 * CRUDはWebアプリの基本となる4つの機能、新規作成（Create）、表示（Read）、更新（Update）、削除（Destroy）
 * rails g scaffoldはCRUDをつくる機能
 * パスが/books、HTTPメソッドがGETのリクエストは一覧画面を表示する



次の章ではCRUDのCreate（新規作成）について説明します。


== さらに学びたい場合は
 * @<href>{https://railsguides.jp/routing.html,Rails ガイド: Rails のルーティング}
 ** routesについての詳しい解説です。
 * @<href>{https://railsguides.jp/action_controller_overview.html,Rails ガイド: Action Controller の概要}
 ** コントローラについての詳しい解説です。

