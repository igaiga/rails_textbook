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

# new, createアクション

この章ではCRUDのC（Create）にあたる新規登録を行うための2つのアクション、newとcreateについて説明していきます。

説明に使うアプリは前の章でつくったものを引き続き使います。

## 概略

前の章での「CRUD遷移図」において、newとcreateはこの部分になります。

![CRUD画面遷移図(newとcreate)](assets/new-create/figures/crud_transition_diagram_new_create.png)

新規登録は2つのアクションで構成されます。処理の流れは以下のようになります。

### ステップ1: newアクション（新規作成画面）

![newアクション](assets/new-create/figures/new_create_overview_item_new.png)

newアクションが実行され新規入力画面を表示します。ここで本のタイトルとメモを入力します。Create Bookボタンを押すと、次に画面のないcreateアクションが実行されます。

### ステップ2: createアクション（画面なし）

![createアクション](assets/new-create/figures/new_create_overview_item_create.png)

つづくcreateアクションで、前のステップで入力されたタイトルとメモで本のデータを新規登録します。

この流れを詳しく説明していきます。最初に、newアクションの新規入力画面の処理を見てみましょう。

## newアクション

新規入力画面が表示されるまでの処理の流れを見ていきましょう。

![newアクション](assets/new-create/figures/new_create_overview_item_new.png)

![新規入力画面](assets/new-create/app_ss/books_new_data_1.png)

新規入力画面はnewアクションで表示されます。Railsアプリはこれまでに説明した通り、Routes、コントローラ、ビューの各処理を経て画面が表示されます。

![new(新規入力)画面の処理の流れ](assets/new-create/figures/new_flow.png)

最初はRoutesで処理が行われます。

### Routes

![新規入力画面の処理の流れ - Routes](assets/new-create/figures/new_flow_routes.png)

Routesの対応表をつかって、リクエストに対して処理されるコントローラとアクションが決まります。`http://localhost:3000/rails/info/routes`へアクセスしてRoutes表を見てみましょう。今回のリクエストはパスが /books/new 、HTTPメソッドがGETなので、BooksControllerのnewアクションへ処理が進みます。Routes表の下線部に該当します。

![Routes表](assets/new-create/figures/new_routes.png)

### コントローラ

![新規入力画面の処理の流れ - コントローラ](assets/new-create/figures/new_flow_controller.png)

BooksControllerのnewアクションのコードを見てみましょう。ファイルは `app/controllers/books_controller.rb` です。

```ruby
def new
  @book = Book.new
end
```

newアクションは `@book = Book.new` の1行です。Book.newでBookクラスのインスタンスを作り、@bookインスタンス変数へ代入し、ビューへ渡します。Book.newでつくったBookクラスのインスタンスはタイトルとメモを格納できるようになっていますが、タイトルとメモのデータは空っぽです。

インスタンスとはクラスから作られたオブジェクトのことです。オブジェクトとほぼ同じ意味で使われますが、「クラスから作ったオブジェクトである」「そのクラスに属する」ということを強調したいときに使います。クラスはその種族に属するオブジェクト（インスタンス）を作ることができる工場のようなものです。そのクラス自身が仕事をすることもあれば、そのクラスから作ったオブジェクトが仕事をすることもあります。

Bookクラスには色々と便利な機能があるのですが、それは後ほど説明します。ここでは、Bookに関するビューで使う情報をつくり、インスタンス変数へ代入し、ビューへ送る、と考えると良いでしょう。

コントローラの処理が終わると次はビューです。ここでは進むビューの指示がないため、デフォルトである `views/books/new.html.erb` へ処理が進みます。

### ビュー

![新規入力画面の処理の流れ - ビュー](assets/new-create/figures/new_flow_view.png)

ビューのコード `views/books/new.html.erb` を見てみましょう。

```erb
<h1>New Book</h1>

<%= render 'form', book: @book %>

<%= link_to 'Back', books_path %>
```


これだけしかありません。随分とあっさりしています。実は、下の図中の枠線部分は別のファイルに書いてあり、 `<%= render 'form', book: @book %>` で埋め込まれるようになっています。

![renderの説明](assets/new-create/figures/new_view_form_screenshot.png)

renderメソッドは別のビューファイルを埋め込みます。わざわざ別のファイルに書く理由は、他の画面でもそのファイルを利用することで、同じ部品を共用したいからです。埋め込む用のビューファイルをパーシャルと言います。書式は以下の通りです。

```
<%= render 埋め込みたいファイル名, パーシャル内で使う変数名: 渡す変数 %>
```

埋め込むファイル名には1つルールがあり、renderで書いた文字列の先頭に_を付けたファイル名にします。つまり、`<%= render 'form', book: @book %>`で埋め込まれるファイルは ` _form.html.erb` になります。

また、`<%= render 'form', book: @book %>`の`book: @book`の部分は、`@book`変数を埋め込み先のパーシャル内で`book`変数として使うための指示です。パーシャル内でも@はじまりのインスタンス変数を利用することも可能です。それでもわざわざbook変数として渡しているのは、パーシャル内で利用する変数を明示すること、他のコントローラでパーシャルを流用する時にインスタンス変数名を揃える必要がないことなどのメリットがあります。

埋め込まれるパーシャルビュー `_form.html.erb` は以下のようになっています。
ファイルは`app/views/books/_form.html.erb`です。

```erb
<%= form_with(model: book, local: true) do |form| %>
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
    <%= form.label :title %>
    <%= form.text_field :title %>
  </div>

  <div class="field">
    <%= form.label :memo %>
    <%= form.text_area :memo %>
  </div>

  <div class="actions">
    <%= form.submit %>
  </div>
<% end %>
```

`new.html.erb` と `_form.html.erb` の2つのファイルでこの画面はつくられています。

では、`_form.html.erb` の中を解説していきます。この中で、2行目からの以下の部分はエラーを表示するコードです。ここでは説明を省略して、それ以外の基本となる部分を説明します。

```erb
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
```

残りの部分について説明していきます。次の図を見てください。

![コードとページの部品の対応](assets/new-create/figures/new_view_form.png)

それぞれ矢印の先の部品を作っています。また、全体としてはformという名の部品になってます。formはHTMLでブラウザからサーバへ情報を送信する仕組みです。

まずは部品の1つ、タイトルのところを見てみましょう。

![タイトル部品](assets/new-create/figures/new_view_form_title_html.png)

枠線内がタイトルの部分です。全体はHTMLですが、 `<%= %>`で囲まれた部分がその中に埋め込まれたRailsコードです。

`<div></div>`は中のHTML要素をグルーピングするための要素です。それだけだと特に見た目を変えませんが、CSSで修飾する要素を指定するためによく使います。ここでは "field" というHTMLでのclass名をつけてCSSで修飾できるようにしています。

Railsコードの部分をもう少し詳しく見てみましょう。`form.label :title` で "Title"という文字列を表示しています。その名の通り、ラベルの部分です。`form.text_field :title` はその下にあるテキスト入力欄です。`form` はformブロック内の変数で、ここではbookに関するformを記述するために使っています。見慣れない書き方かもしれませんが、ここはそう書くものだと思ってもらえれば大丈夫です。

![メモ部品](assets/new-create/figures/new_view_form_memo_html.png)

メモの部分も同様です。`form.label :memo` が "Memo" を表示する部分です。`form.text_area :memo` がその下のテキスト入力欄を作ります。`text_area` は先ほどの `text_field` よりも広くて改行を入力できるテキスト入力欄を作るメソッドです。

![投稿ボタン部品](assets/new-create/figures/new_view_form_submit_html.png)

最後は投稿するボタンの部分です。`form.submit` は投稿ボタン（Create Bookボタン）を作ります。このボタンを押すとform内の情報をまとめてサーバへ送信（リクエストを送信）します。ここでは、Bookに関する情報、入力したタイトルとメモをリクエストに含んで送信します。ここで送信されたタイトルとメモが後の行程で登録されます。

では、具体的にどんなリクエストが飛ぶのかを観察してみましょう。

### リクエストを観察する

Chromeのデベロッパーツールを使うと、どのようなリクエストがサーバへ送信されたかを見ることができます。

TODO: スクショ置き換え、データ置き換え

![Chromeでリクエストを観察する(準備)](assets/new-create/figures/create-request-1.png)

new画面を表示させ、タイトル欄とメモ欄にBookの情報を入力します。Chromeのメニューからデベロッパーツールを起動します。Networkと書かれたタブを選択します。CreateBookボタンを押し、リクエストを送信してみましょう。

TODO: スクショ置き換え、データ置き換え

![Chromeでリクエストを観察する(リクエスト送信)](assets/new-create/figures/create-request-2.png)

たくさん表示されました。一番最初のbooksと書かれた行が先ほどボタンを押して発行されたリクエストです。booksの行をクリックして詳細を見てみましょう。

TODO: スクショ置き換え、データ置き換え

![Chromeでリクエストを観察する(リクエストの中身)](assets/new-create/figures/create-request-3.png)

最初にURLとHTTPメソッドが書いてあります。Routesで使う情報がここに載っています。

下の方へスクロールすると、Form Dataという欄にbook[title]とbook[memo]の情報を見つけることができます。さきほどnew画面で入力した内容がここに表示されていることを確認してみてください。

次は、飛んだこのリクエストがどのように処理されるかを見ていきましょう。

## Createアクション
### 新たなリクエスト

new画面でCreate bookボタンを押すと新たなリクエストを飛ばすことが分かりました。ここからは、この2つ目のリクエストを追いかけます。リクエストの内容は、さきほどChromeで確認したように次の図のようになっています。

![新たなリクエスト](assets/new-create/figures/create_flow_routes.png)

### Routes

いつものように最初の処理はroutesです。

![routes](assets/new-create/figures/create_routes.png)

URLのパスは/books 、HTTPメソッドはPOSTなので対応するコントローラとアクションはbooks#create、つまりBooksControllerのcreateアクションが呼び出されます。

HTTPメソッドのPOSTは今回のようなデータの新規作成時に使います。そのほか、サーバの状態へ何らかの変更を与えるときにはこのPOSTを利用します。

一方で、indexやnewの時に利用したHTTPメソッドGETは、サーバの状態を変えない場合に使います。newアクションでは新規入力画面を表示するだけでまだデータを保存しないので、HTTPメソッドはGETを使うのです。

### コントローラ

![新たなリクエスト](assets/new-create/figures/create_flow_controller.png)

コントローラのソースファイルは `app/controllers/books_controller.rb` です。ここでやっていることは大きく3つです。

```ruby
def create
  @book = Book.new(book_params) # ⬅️1. リクエストのパラメータを使って本のデータを作る
  respond_to do |format|
    if @book.save # ⬅️2. 本のデータを保存する
      # ⬅️3a. 成功したらshow画面へ
      format.html { redirect_to @book, notice: 'Book was successfully created.' }
      format.json { render :show, status: :created, location: @book }
    else
      # ⬅️3b. 保存失敗したらnew画面へ（元の画面）
      format.html { render :new }
      format.json { render json: @book.errors, status: :unprocessable_entity }
    end
  end
end
```

3つの処理を順に見ていきます。最初は `@book = Book.new(book_params)` です。

```ruby
def create
  @book = Book.new(book_params)
  ...
```

`Book.new` メソッドの引数に渡している `book_params` はメソッドを呼び出しています。このメソッドはファイルの後半に定義されています。`book_params` の中を見てみましょう。

### パラメータ

`app/controllers/books_controller.rb`

```ruby
def book_params
  params.require(:book).permit(:title, :memo)
end
```

`book_params` メソッドはパラメータに関する処理を行っています。パラメータとはブラウザから飛んでくるリクエストの中に含まれる情報で、たとえばユーザーの入力した値が入っています。さきほどChromeデベロッパーツールを使って見たものが、Railsまで渡ってきています。

パラメータは `params` で取得できます。次は`params`にどんな情報が、どのように入っているかを見てみましょう。次のようにコードを変更してみてください。

`app/controllers/books_controller.rb`

```diff
def book_params
+ p "**********" # 見つけ易くするための目印。何でも良い。
+ p params # paramsの中身を表示
  params.require(:book).permit(:title, :memo)
end
```

コードを変更して、ブラウザから新規登録画面を表示し、テキストボックス欄に入力し、Create Bookボタンを押します。その後、rails serverのshellに流れた文字列から************を探してみてください。表示されていない場合は、rails serverを再起動してみてください。

TODO: スクショ新データで撮り直し

![パラメータの中身の表示 実行結果](assets/new-create/figures/create-controller-params.png)

実行結果を見ると、確かに `params` の中にブラウザにて入力した値がHashの形で入っていることが分かりました。

これを、少し前にブラウザのデベロッパーツールで表示させた内容と比較してみましょう。

TODO: スクショ撮り直し、つかいやすい形にする

![パラメータの送信側と受信側](assets/new-create/figures/create-controller-params-2.png)

ここで出力した `params` の値と、さきほどブラウザのデベロッパーツールで表示させたパラメータの値が同じになっていることが分かります。ブラウザのデベロッパーツールはパラメータを送信している部分です。一方でRailsのアプリ側はパラメータを受信している部分です。ブラウザがユーザーの入力データをパラメータとして送信し、私たちが作成しているアプリがそのデータを受け取っていることを確認できました。

TODO:「new/createのChrome Dev toolsとログの図（新規）」をここに挿入する

### Strong Parameters

`book_params`の説明に戻ります。`params`の後ろについている、requireとpermitとはなんでしょうか？

`app/controllers/books_controller.rb`

```ruby
def book_params
  params.require(:book).permit(:title, :memo)
end
```

params以降のrequire, permitメソッドは、パラメータの内容を制限します。意図していないデータが入ってくるのを防ぐための仕組みです。ここでは、bookのtitle, memoだけを受け取るようにしています。requireには対象となるモデル名（モデルについては次章で説明します）を、permitには更新を許可するカラム名を指定します。

このパラメータを制限する仕組みはStrong Parametersと呼ばれます。これが必要な理由は、攻撃に対する防御、つまりセキュリティ対策です。ブラウザから飛ばすパラメータは、ユーザーの手によって改ざんすることも可能です。つまり、任意のパラメータを飛ばして攻撃をすることもできます。そのため、1つ前のnew画面で用意したformに存在しないパラメータが飛んでくる可能性もあるので、ここで変更を許可するパラメータを絞っています。

たとえば、titleだけを更新したいケースがあり、titleだけを更新するformをつくったとします。`Book.new(book_params)`でnewメソッドは、引数で受け取った値を自分のカラムへ代入します。このとき、book_paramsにtitleの情報だけがやってくればいいのですが、攻撃者はmemoの情報もパラメータとして飛ばすこともあります。StrongParametersで受け取り可能なパラメータを絞っていないと、プログラマの意図しないカラムが更新されてしまうことになります。

## まとめ

createアクションでの処理について説明してきました。createアクション全体の中で、どこまで進んだかを確認してみましょう。

`app/controllers/books_controller.rb`

```ruby
def create
  @book = Book.new(book_params) # ⬅️1. リクエストのパラメータを使って本のデータを作る
  respond_to do |format|
    if @book.save # ⬅️2. 本のデータを保存する
      # ⬅️3a. 成功したらshow画面へ
      format.html { redirect_to @book, notice: 'Book was successfully created.' }
      format.json { render :show, status: :created, location: @book }
    else
      # ⬅️3b. 保存失敗したらnew画面へ（元の画面）
      format.html { render :new }
      format.json { render json: @book.errors, status: :unprocessable_entity }
    end
  end
end
def book_params
  params.require(:book).permit(:title, :memo)
end
```

この章では1.まで、createアクションにパラメータ（params）が届いたのを確認したところまで説明しました。`params`でパラメータの情報を取り、StrongParametersを使って必要なものだけに制限します。

Book.new(book_params)で本のデータを作ります。newはクラスのインスタンスを作るメソッドです。実はBookは「モデル」という種族に属する便利な機能を持ったクラスです。モデルについての説明は次の章で行います。

このあと、本の情報を保存し（2.の部分）、その結果により表示する画面を切り替えます（3.の部分）。続きは次の章で説明します。

この章のまとめです。

- 新規入力画面はnewアクション、新規登録はcreateアクション
- newアクションではまだデータを保存せず、サーバのデータ変更を伴わないためHTTPメソッドGETを使う
- createアクションではデータを保存し、サーバのデータ変更を伴うためHTTPメソッドPOSTを使う
- ユーザーがブラウザでformへ入力した内容はリクエスト内のパラメータとしてRailsアプリへ届き、 paramsで渡ってきたパラメータを取得できる
- セキュリティ問題対策のためStrongParameters（requireメソッド、permitメソッド）を利用してparamsに制限をかける

次の章ではモデルについて説明します。

## さらに学びたい場合は

- [Rails Guides : Action Controller の概要](http://railsguides.jp/action_controller_overview.html)
  - 前章でも紹介した、コントローラについての詳しい解説のページです。StrongParametersに関する説明もここに書いてあります。
