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

コントローラの処理が終わると次はビューです。ここでは特に進むビューの指示がないため、デフォルトの `views/books/new.html.erb` へ処理が進みます。

### ビュー
