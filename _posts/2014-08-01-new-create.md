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

{% image path: assets/new-create/crud-transition-diagram-new-create.png, description: CRUD画面遷移図(newとcreate) %}

おおまかな流れは以下のようになります。

{% image path: assets/new-create/new-create-overview.png, description: おおまかな流れ %}

まず、newアクションが実行され新規入力画面が表示されます。ここで本のタイトルとメモを入力します。Create Book ボタンを押すと、次に画面のない create アクションが実行されます。createアクションで、前のステップで入力されたタイトルとメモで本のデータを新規登録します。

この流れを詳しく説明していきます。最初に、newアクションの新規入力画面の処理を見てみましょう。

## new アクション

新規入力画面が表示されるまでの処理の流れを見ていきましょう。

{% image path: assets/new-create/new-page.png, description: 新規入力画面 %}

新規入力画面は new アクションで表示されます。Railsアプリは前章で説明した通り、Routes、コントローラ、ビューの各処理を経て画面が表示されます。

{% image path: assets/new-create/new-flow.png, description: new(新規入力)画面が表示されるまで %}

### Routes

{% image path: assets/new-create/new-flow-routes.png, description: Routes %}


最初はRoutesにて、リクエストに対して処理されるコントローラとアクションが決まります。`http://localhost:3000/rails/info/routes`へアクセスしてRoutesの対応表を見てみましょう。今回のリクエストはパスが /books/new 、HTTPメソッドが GET なので、BooksController の new アクションへ処理が進みます。（図の下線部に該当します。）

{% image path: assets/new-create/new-routes.png, description: Routes %}

### コントローラ

{% image path: assets/new-create/new-flow-controller.png, description: コントローラ %}

BooksControllerのnewアクションのコードを見てみましょう。ファイルは `app/controllers/books_controller.rb` です。

{% image path: assets/new-create/new-controller.png, description: コントローラ %}

newアクションは `@books = Book.new` の1行です。Book.new でBookクラスのインスタンス（データは空っぽ）を作り、@bookインスタンス変数へ代入します。Bookクラスのインスタンスはタイトルとメモを格納できるようになっています。

インスタンスとはクラスという設計図からつくる実際に仕事をするオブジェクトです。「たい焼き」に例えると、クラスは「たい焼きの型」、インスタンスは「焼いた鯛焼き」です。Bookクラスには色々と便利な機能があるのですが、それは後ほど説明します。ここでは、Bookに関してビューで使う情報をつくってインスタンス変数へ代入してビューへ送る、と考えてください。

コントローラの処理が終わると次はビューです。ここでは進むビューの指示がないため、デフォルトの `views/books/new.html.erb` へ処理が進みます。

### ビュー

{% image path: assets/new-create/new-flow-view.png, description: ビュー %}

ビューのコード `views/books/new.html.erb` を見てみましょう。

{% image path: assets/new-create/new-view-1.png, description: ビュー %}

これだけしかありません。随分とあっさりしています。実は、下の図中の枠線部分は別のファイルに書いてあり、 `<%= render 'form' %>` で埋め込まれるようになっています。

{% image path: assets/new-create/new-view-render.png, description: render の説明 %}

render メソッドは別のビューファイルを埋め込みます。埋め込む用のビューファイルをパーシャルと言います。埋め込むファイル名には1つルールがあり、render で書いた文字列の先頭に _ を付けたファイル名にします。つまり、 `<%= render 'form' %>` で埋め込まれるファイルは `_form.html.erb` になります。(わざわざ別のファイルに書いてある理由は、他の画面でも同じ部品を共用したいからです。

{% image path: assets/new-create/new-view-2.png, description: 2つのビューファイルからページが作られている %}

このように、2つのビューファイルからページが作られています。

この中で、下図の枠線部分はエラー表示の部分です。

{% image path: assets/new-create/new-view-error.png, description: エラー表示の部分 %}

基本的な流れの部分について説明していきます。前のページの基本的な流れの部分を抜き出した下図を見てください。

{% image path: assets/new-create/new-view-form.png, description: コードとページの部品の対応 %}

それぞれ矢印の先の部品を作っています。また、全体としては form という名の部品になってます。formはHTMLでブラウザからサーバへ情報を送信する部品の1つです。

まずは部品の1つ、タイトルのところを見てみましょう。

{% image path: assets/new-create/new-view-form-title-html.png, description: タイトル(HTML) %}


枠線内がタイトルの部分です。白色の部分がHTML、<%= %> で囲まれた黄色の部分がRailsコードの部分です。

<div></div>は中のHTML要素をグルーピングするための要素です。それだけだと特に見た目を変えませんが、CSSで修飾する要素を指定するためによく使います。ここでは "field" というclass名をつけてCSSで修飾できるようにしています。<br /> は改行を入れるHTML要素です。

次はRailsコードの部分を見てみましょう。

{% image path: assets/new-create/new-view-form-title-rails.png, description: タイトル(Railsコード) %}

`f.label :title` で "Title"という文字列を表示しています。その名の通り、ラベルの部分です。`f.text_field :title` はその下にあるテキスト入力欄です。f はformブロック内の変数で、ここでは @book に関するformを記述するために使っています。(ここはそう書くものだと思ってもらえれば・・・)

{% image path: assets/new-create/new-view-form-memo.png, description: メモ %}

メモの部分も同様です。`f.label :memo` が "Memo" を表示する部分です。`f.text_area :memo` がその下のテキスト入力欄を作ります。`text_area` は先ほどの `text_field` よりも広くて改行を入力できるテキスト入力欄を作るメソッドです。

{% image path: assets/new-create/new-view-form-submit-1.png, description: submit %}

`f.submit` は投稿ボタン(Create Book ボタン)を作ります。このボタンを押すとform内の情報をまとめてサーバへ送信（リクエストを送信）します。つまり・・・

{% image path: assets/new-create/new-view-form-submit-2.png, description: submitボタンを押すとリクエストが飛ぶ %}

Create Book ボタンを押すと、form内の情報、ここでは Book に関する情報、入力したタイトルとメモを送信します。では、具体的にどんなリクエストが飛ぶのか試してみましょう。




