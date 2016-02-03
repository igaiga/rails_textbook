---
layout: post
unique_identifier:
 - 'http:/example.jp/bookid_in_url'
 - 'BookID'
 - 'URL'
title: 'new, create アクション'
creator: '五十嵐邦明'
date: '2014-08-01'
categories:
---

# new, create アクション

この章ではCRUDのCにあたる新規登録を行うための2つのアクション、new と create について説明していきます。

説明に使うアプリは前の章でつくったものを引き続き使います。

## 概略

前の章での「CRUD遷移図」において、new とcreate はこの部分になります。

{% image path: assets/new-create/kn/crud-transition-diagram-new-create.png, description: CRUD画面遷移図(newとcreate) %}

おおまかな流れは以下のようになります。

{% image path: assets/new-create/kn/new-create-overview.png, description: おおまかな流れ %}

まず、newアクションが実行され新規入力画面が表示されます。ここで本のタイトルとメモを入力します。Create Book ボタンを押すと、次に画面のない create アクションが実行されます。createアクションで、前のステップで入力されたタイトルとメモで本のデータを新規登録します。

この流れを詳しく説明していきます。最初に、newアクションの新規入力画面の処理を見てみましょう。

## new アクション

新規入力画面が表示されるまでの処理の流れを見ていきましょう。

{% image path: assets/new-create/kn/new-page.png, description: 新規入力画面 %}

新規入力画面は new アクションで表示されます。Railsアプリは前章で説明した通り、Routes、コントローラ、ビューの各処理を経て画面が表示されます。

{% image path: assets/new-create/kn/new-flow.png, description: new(新規入力)画面が表示されるまで %}

最初はRoutesで処理が行われます。

### Routes

{% image path: assets/new-create/kn/new-flow-routes.png, description: 新規入力画面の処理の流れ - Routes %}


最初はRoutesにて、リクエストに対して処理されるコントローラとアクションが決まります。`http://localhost:3000/rails/info/routes`へアクセスしてRoutesの対応表を見てみましょう。今回のリクエストはパスが /books/new 、HTTPメソッドが GET なので、BooksController の new アクションへ処理が進みます。（図の下線部に該当します。）

{% image path: assets/new-create/kn/new-routes.png, description: Routes %}

### コントローラ

{% image path: assets/new-create/kn/new-flow-controller.png, description: 新規入力画面の処理の流れ - コントローラ %}

BooksControllerのnewアクションのコードを見てみましょう。ファイルは `app/controllers/books_controller.rb` です。

{% highlight ruby %}
def new
  @book = Book.new
end
{% endhighlight %}


newアクションは `@books = Book.new` の1行です。Book.new でBookクラスのインスタンス（データは空っぽ）を作り、@bookインスタンス変数へ代入し、ビューへ渡します。Book.new でつくった Bookクラスのインスタンスはタイトルとメモを格納できるようになっています。

インスタンスとはクラスという設計図からつくる実際に仕事をするオブジェクトです。「たい焼き」に例えると、クラスは「たい焼きの型」、インスタンスは「焼いた鯛焼き」です。Bookクラスには色々と便利な機能があるのですが、それは後ほど説明します。ここでは、Bookに関するビューで使う情報をつくり、インスタンス変数へ代入してビューへ送る、と考えると良いでしょう。

コントローラの処理が終わると次はビューです。ここでは進むビューの指示がないため、デフォルトの `views/books/new.html.erb` へ処理が進みます。

### ビュー

{% image path: assets/new-create/kn/new-flow-view.png, description: 新規入力画面の処理の流れ - ビュー %}

ビューのコード `views/books/new.html.erb` を見てみましょう。

{% highlight erb %}
<h1>New Book</h1>

<%= render 'form', book: @book %>

<%= link_to 'Back', books_path %>
{% endhighlight %}


これだけしかありません。随分とあっさりしています。実は、下の図中の枠線部分は別のファイルに書いてあり、 `<%= render 'form', book: @book %>` で埋め込まれるようになっています。

{% image path: assets/new-create/kn/new-view-render.png, description: render の説明 %}

render メソッドは別のビューファイルを埋め込みます。埋め込む用のビューファイルをパーシャルと言います。埋め込むファイル名には1つルールがあり、render で書いた文字列の先頭に _ を付けたファイル名にします。つまり、 `<%= render 'form', book: @book %>` で埋め込まれるファイルは `_form.html.erb` になります。(わざわざ別のファイルに書いてある理由は、他の画面でも同じ部品を共用したいからです。

また、`<%= render 'form', book: @book %>` の `book: @book` の部分は、 `@book` 変数を埋め込み先のパーシャル内では `book` 変数として使うように渡す指示です。

埋め込まれるパーシャルビュー `_form.html.erb` は以下のようになっています。

{% highlight erb %}
<%= form_for(book) do |f| %>
  <% if book.errors.any? %>
    <div id="error_explanation">
      <h2><%= pluralize(book.errors.count, "error") %> prohibited this book from being saved:</h2>

      <ul>
      <% book.errors.full_messages.each do |message| %>
        <li><%= message %></li>
      <% end %>
      </ul>
    </div>
  <% end %>

  <div class="field">
    <%= f.label :title %>
    <%= f.text_field :title %>
  </div>

  <div class="field">
    <%= f.label :memo %>
    <%= f.text_area :memo %>
  </div>

  <div class="actions">
    <%= f.submit %>
  </div>
<% end %>
{% endhighlight %}

`new.html.erb` と `_form.html.erb` の2つのファイルでこの画面はつくられています。

では、`_form.html.erb` の中を解説していきます。この中で、前半2行目からのこの部分はエラーを表示するコードです。ここでは説明を省略して、それ以外の基本となる部分を説明します。

{% highlight erb %}
<% if book.errors.any? %>
  <div id="error_explanation">
    <h2><%= pluralize(book.errors.count, "error") %> prohibited this book from being saved:</h2>
   <ul>
    <% book.errors.full_messages.each do |message| %>
      <li><%= message %></li>
    <% end %>
    </ul>
  </div>
<% end %>
{% endhighlight %}

残りの部分について説明していきます。最初に下図を見てください。

{% image path: assets/new-create/kn/new-view-form.png, description: コードとページの部品の対応 %}

それぞれ矢印の先の部品を作っています。また、全体としては form という名の部品になってます。formはHTMLでブラウザからサーバへ情報を送信する仕組みの1つです。

まずは部品の1つ、タイトルのところを見てみましょう。

{% image path: assets/new-create/kn/new-view-form-title-html.png, description: タイトル部品 %}

枠線内がタイトルの部分です。全体はHTMLですが、 <%= %> で囲まれた黄色の部分がその中に埋め込まれたRailsコードです。

&lt;div&gt;&lt;/div&gt;は中のHTML要素をグルーピングするための要素です。それだけだと特に見た目を変えませんが、CSSで修飾する要素を指定するためによく使います。ここでは "field" というHTMLでのclass名をつけてCSSで修飾できるようにしています。

次はRailsコードの部分をもう少し詳しく見てみましょう。

{% image path: assets/new-create/kn/new-view-form-title-rails.png, description: タイトル(Railsコード) %}

`f.label :title` で "Title"という文字列を表示しています。その名の通り、ラベルの部分です。`f.text_field :title` はその下にあるテキスト入力欄です。f はformブロック内の変数で、ここでは book に関するformを記述するために使っています。(見慣れない書き方ですが、ここはそう書くものだと思ってもらえれば大丈夫です。)

次はその下のメモの部分を見てみましょう。

{% image path: assets/new-create/kn/new-view-form-memo.png, description: メモ %}

メモの部分も同様です。`f.label :memo` が "Memo" を表示する部分です。`f.text_area :memo` がその下のテキスト入力欄を作ります。`text_area` は先ほどの `text_field` よりも広くて改行を入力できるテキスト入力欄を作るメソッドです。

最後は投稿するボタンの部分です。

{% image path: assets/new-create/kn/new-view-form-submit-1.png, description: submit %}

`f.submit` は投稿ボタン(Create Book ボタン)を作ります。このボタンを押すとform内の情報をまとめてサーバへ送信（リクエストを送信）します。つまり・・・

{% image path: assets/new-create/kn/new-view-form-submit-2.png, description: submitボタンを押すとリクエストが飛ぶ %}

Create Book ボタンを押すと、form内の情報、ここでは Book に関する情報、入力したタイトルとメモをリクエストに含んで送信します。ここで送信されたタイトルとメモが後の行程で登録されるのです。では、具体的にどんなリクエストが飛ぶのかを観察してみましょう。

### リクエストを観察する

Chromeのデベロッパーツールを使うと、どのようなリクエストがサーバへ送信されたかを見ることができます。

{% image path: assets/new-create/create-request-1.png, description: Chromeでリクエストを観察する(準備) %}

new画面を表示させ、タイトル欄とメモ欄にBookの情報を入力します。Chromeのメニューからデベロッパーツールを起動します。Networkと書かれたタブを選択します。CreateBookボタンを押し、リクエストを送信してみましょう。

{% image path: assets/new-create/create-request-2.png, description: Chromeでリクエストを観察する(リクエスト送信) %}

たくさん表示されました。一番最初の books と書かれた行が先ほどボタンを押して発行されたリクエストです。books の行をクリックして詳細を見てみましょう。

{% image path: assets/new-create/create-request-3.png, description: Chromeでリクエストを観察する(リクエストの中身) %}

最初にURLとHTTPメソッドが書いてあります。いつもRoutesで使っている情報がここに載っています。

下の方へスクロールすると、Form Data という欄にbook[title]とbook[memo]の情報があることが分かります。さきほどnew画面で入力した内容がここに表示されていることを確認してみてください。次は、飛んだこのリクエストがどのように処理されるかを見ていきましょう。

## Create アクション
### 新たなリクエスト

new画面でCreate book ボタンを押すと新たなリクエストが飛ぶことが分かりました。次は、この2つ目のリクエストを追いかけます。リクエストの内容は、さきほどChromeで確認したように以下の図のようになっています。

{% image path: assets/new-create/create-flow-request.png, description: 新たなリクエスト %}

### Routes

いつものように最初の処理はroutesです。

{% image path: assets/new-create/create-routes.png, description: routes %}

URLのパスは /books 、HTTPメソッドは POST なので books#create 、つまりBooksControllerのcreateアクションが呼び出されます。

HTTPメソッドの POST は今回のようなデータの新規作成時に使います。そのほか、サーバの状態へ何らかの変更を与える場合にはこの POST を利用します。index や new の時に利用したHTTPメソッド GET は、サーバの状態に変更を与えない場合に使います。new アクションでは新規入力画面を表示するだけでまだデータを保存しないので、HTTPメソッドは GET を使うのです。

### コントローラ

コントローラのソースファイルは `app/controllers/books_controller.rb` です。

{% image path: assets/new-create/create-controller-1.png, description: コントローラ %}

ここでやっていることは大きく3つです。

{% image path: assets/new-create/create-controller-2.png, description: コントローラ - 3つの処理 %}

3つの処理を順に見ていきます。

{% image path: assets/new-create/create-controller-3.png, description: コントローラ - 処理1 %}

最初は `@book = Book.new(book_params)` です。

{% image path: assets/new-create/create-controller-4.png, description: コントローラ - book_params %}

`Book.new` メソッドの引数に渡している `book_params` はメソッドを呼び出しています。このメソッドはファイルの後半に定義されています。`book_params` の中を見てみましょう。

### パラメータ

{% image path: assets/new-create/create-controller-params-1.png, description: パラメータ %}

`book_params` メソッドはパラメータに関する処理を行っています。パラメータとは、ブラウザから飛んでくるリクエストの中に含まれる情報で、たとえばユーザーが入力した値が格納されています。前にChromeを使って見たものです。

パラメータは `params` で取得できます。次は`params`にどんな情報が、どのように入っているかを見てみましょう。

{% image path: assets/new-create/create-controller-params-2.png, description: パラメータの中身を表示するコード %}

コードを変更して、ブラウザから新規登録画面を表示し、テキストボックス欄に入力し、Create Book ボタンを押します。その後、rails s のshellを流れた文字列から ************ を探してみてください。

{% image path: assets/new-create/create-controller-params-3.png, description: パラメータの中身の表示結果 %}

実行結果を見ると、確かに `params` の中にHashの形式でブラウザで入力した値が入っていることが分かりました。

これを、少し前にブラウザのデベロッパーツールで表示させた内容と比較してみましょう。

{% image path: assets/new-create/create-controller-params-4.png, description: パラメータの送信側と受信側 %}

ここで出力した `params` の値と、さきほどブラウザのデベロッパーツールで表示させたパラメータの値が同じになっていることが分かります。ブラウザのでデベロッパーツールはパラメータを送信している部分です。一方でRailsのアプリ側はパラメータを受信している部分です。ブラウザがユーザーの入力データをパラメータとして送信し、私たちが作成しているアプリがそのデータを受け取っていることを確認できました。

`book_params`の説明に戻って、`params`の後ろについている、 require, permit とはなんでしょうか？

{% image path: assets/new-create/create-strong-parameters.png, description: Strong Parameters %}

params以降のrequire, permitメソッドは、パラメータの内容を制限しています。意図していないデータが入ってくるのを防ぐために使用します。ここでは、book の title, memo だけを受け取るようにしています。

このパラメータを制限する仕組みは Strong Parameters と呼ばれます。なぜこれが必要かと言うと、ブラウザから飛ばすパラメータはユーザーの手によって改ざんすることも可能だからです。つまり、任意のパラメータを飛ばす攻撃をすることができます。この1つ前のnewの画面にないパラメータが飛んでくる可能性があるので、ここで変更を許可するパラメータを絞っているのです。(もう少し説明すると、ここで使われている `Book.new(book_params)` に関係しています。newメソッドは、引数で受け取ったHashに応じて自分のカラムへ代入します。例えば、title だけを更新したいケースがあったとして、book_params に title の情報だけがやってくればいいのですが、攻撃者は memo の情報もパラメータとして飛ばすこともあります。StrongParameterで受け取り可能なパラメータを絞っていないと、プログラマの意図しないカラムが更新されてしまうことになります。)

## まとめ

{% image path: assets/new-create/create-model.png, description: create - 本のデータを作る %}

ここまでで見て来たように `book_params` でパラメータの情報を取れることが分かりました。これを使って本のデータを作ります。

本のデータは Book.new で作ります。newはクラスのインスタンスを作るメソッドです。実はBookは「モデル」という種族に属する便利な機能を持ったクラスです。モデルについての説明は次の章で行います。

{% image path: assets/new-create/create-summary.png, description: create - ここまでの流れ %}

このあと、本の情報を保存し(2.の部分)、その結果により表示する画面を切り替えます(3.の部分)。ここまでで 1.の途中まで、create アクションにパラメータ(params)が届いたのを確認したところまでやりました。

続きは次の章で説明します。

この章のまとめです。

- 新規入力画面は new アクション、新規登録は create アクション
- new アクションではまだデータを保存せず、サーバのデータ変更を伴わないため HTTPメソッド GET を使う
- create アクションではデータを保存し、サーバのデータ変更を伴うため HTTPメソッド POST を使う
- ユーザーがブラウザでフォームへ入力した内容はリクエスト内のパラメータとしてRailsアプリへ届く
- Railsアプリでは params 変数で渡ってきたパラメータを取得できる
- セキュリティ問題対策のためStrongParametersを利用してparamsに制限をかける

次の章ではモデルについて説明します。

## さらに学びたい場合は

- [Rails Guides : Action Controller の概要](http://railsguides.jp/action_controller_overview.html)
  - 前章でも紹介した、コントローラについての詳しい解説のページです。StrongParametersに関する説明もここに書いてあります。
