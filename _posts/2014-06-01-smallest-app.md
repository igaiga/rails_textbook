---
layout: post
unique_identifier:
 - 'http:/example.jp/bookid_in_url'
 - 'BookID'
 - 'URL'
title: '一番小さなRailsアプリづくり'
creator: '五十嵐邦明'
date: '2014-06-01'
categories:
--- 

# 一番小さなRailsアプリづくり

ここではできるだけ小さい構成のRailsアプリを作ってみます。Railsアプリがどのように動作するのかの説明と、Railsによって作られたファイルがどのような役割なのか、機能と関連づけて説明していきます。

## 一番小さなRailsアプリをつくる

### アプリの作成とWelcome画面

まずはターミナルを起動して、以下のコマンドを打ってみましょう。

```bash
mkdir my_web_apps
cd my_web_apps
```

mkdirはフォルダを作成するコマンド、cdはターミナル内で現在のフォルダを移動するコマンドです。Windowsで普段使いなれている「コンピューター（エクスプローラー）」を起動するには、ターミナルで`explorer .`と打つと現在のフォルダを開くことができます。MacでFinderを開くにはターミナルから`open .`と打ちます。mkdirコマンドで作成したフォルダが存在することが確認できます。フォルダはどちらから作成しても同じようにつくることができます。

それでは、アプリを作てみましょう。最初に作るのは、ブラウザに"Hello world!"と表示させるアプリです。先ほど作成したフォルダ ```my_web_apps``` の下に新しいアプリを作ってみましょう。ターミナルを起動して以下のコマンドを打ちます。

```bash
rails new helloworld
```

実行には少し時間がかかります。たくさんのメッセージが表示されます。

```console
$ rails new helloworld
      create
      create  README.md
      create  Rakefile
 ...（略）
✨  Done in 3.83s.
Webpacker successfully installed 🎉 🍰
```

ターミナルの画面にこのように"Webpacker successfully installed"と表示されれば成功です。メッセージ中"Done in 3.83s."の3.83sは所用時間なので、実行するごとに変化します。rails newコマンドはたくさんのフォルダとファイルを自動で作ります。rails newコマンドでやっていることはこの後のコラムで説明します。

次は以下のコマンドを実行してみてください。`rails s`コマンドはwebサーバを起動するコマンドで、sはserverの略です。

```bash
cd helloworld
rails s
```

うまく動作している場合は、以下のような表示になります（メッセージ中"Version 3.12.1"の数字は異なる場合があります）。

```console
$ rails s
=> Booting Puma
=> Rails 6.0.0 application starting in development
=> Run `rails server --help` for more startup options
Puma starting in single mode...
* Version 3.12.1 (ruby 2.6.5-p114), codename: Llamas in Pajamas
* Min threads: 5, max threads: 5
* Environment: development
* Listening on tcp://localhost:3000
Use Ctrl-C to stop
```

では、ブラウザを起動して以下のURLを入力してアクセスしてみましょう。

* http://localhost:3000

![welcome rails](assets/smallest-app/app_ss/welcome_rails.png)

これは、Railsが起動し、あなたのブラウザからのリクエストを受け付けて、表示している画面です。ここまでのわずかな手順で、ブラウザでページを表示する機能を持つWebアプリをつくることができました。

ここで実行したコマンド ```rails s``` のsはserverの略です。省略したsでも、省略せずにserverでも、同じように動作します。

コラム： ```rails new``` コマンドでやっていること

rails newコマンドを実行すると、たくさんのメッセージが表示されました。このとき、何が行われているのでしょうか。最初に、Railsアプリとして動作するのに必要なファイルとフォルダを作成します。次に、利用するGemライブラリ（Rubyの便利なプログラム集）をダウンロードして利用可能にします。つづいて、rails webpacker:install, yarn installが実行されて、JavaScriptのライブラリをダウンロードして利用可能にします。

### rails gコマンドでページを作る

ひきつづき、以下のコマンドを入力してみましょう（メッセージ中"in process 9959"の数字は実行するごとに異なります）。rails serverが起動している場合は、Ctrl-c（controlキーを押しながらcキー）で終了してからコマンドを打ってください。

```bash
rails g controller hello index
```

```console
$ rails g controller hello index
Running via Spring preloader in process 9959
      create  app/controllers/hello_controller.rb
       route  get 'hello/index'
      invoke  erb
      create    app/views/hello
      create    app/views/hello/index.html.erb
      invoke  test_unit
      create    test/controllers/hello_controller_test.rb
      invoke  helper
      create    app/helpers/hello_helper.rb
      invoke    test_unit
      invoke  assets
      invoke    scss
      create      app/assets/stylesheets/hello.scss
```

もしもrails gコマンドを打ち間違えて違うファイルを作ってしまった場合は、打ち間違えたコマンドのgの部分をdにして再実行すると、rails gコマンドで作成したファイルをまとめて削除してくれます。たとえば、``` rails g controller hell index``` とhelloをhellと打ち間違えた場合は、``` rails d controller hell index``` コマンドを実行することで間違えて作ったファイル群を削除することができます（ターミナルでカーソルキーの↑キーを押すと、さきほど入力した内容が出てくるので、それを利用してgをdに直すと楽に実行できます）。

再びrails serverを起動させましょう。

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

ブラウザを使い、以下のURLへアクセスします。

* http://localhost:3000/hello/index

![hello/index](assets/smallest-app/app_ss/hello_index.png)


この画面が出れば、ここまで意図通りに動作しています。さきほど実行したrails gコマンドはこのページ、/hello/indexを作るものでした。どのような仕組みで動作しているかは後ほどまた説明しますので、今はこのページに"Hello world!"と表示させてみることにしましょう。

```app/views/hello/index.html.erb``` ファイルをエディタで開いてみてください。以下のような内容になっています。

```erb
<h1>Hello#index</h1>
<p>Find me in app/views/hello/index.html.erb</p>
```

これを以下のように変更して、ブラウザで同じURLへアクセスしてみてください。-の行を削除して、+の行を追加してください。先頭の-や+は入力しません。（rails sは起動したままで大丈夫です。もしもrails sを一度終了していた場合は、rails sコマンドでもう一度起動してからアクセスしてください）。

```diff
- <h1>Hello#index</h1>
- <p>Find me in app/views/hello/index.html.erb</p>
+ <p>Hello world!</p>
```

![Hello world](assets/smallest-app/app_ss/hello_world.png)

"Hello world!"の文字が表示されましたか？これで一番小さなRailsアプリができあがりました。ここへ、少しだけRubyのコードを書いて、現在時刻を表示する機能を追加してみましょう。以下のように、+の行を追加してください。

```diff
<p>Hello world!</p>
+ <p>現在時刻: <%= Time.current %></p>
```

![現在時刻表示](assets/smallest-app/app_ss/time_utc.png)

表示されましたか？ブラウザをリロードすると、現在時刻が更新される、アクセスしたそのときの時刻が表示されるアプリになりました。

ところで、現在時刻が9時間ずれていると思われた方もいるかと思います。これは異なるタイムゾーンで表示されているためです。この時刻はUTCタイムゾーンでの時刻です。UTCは協定世界時と呼ばれ、基準となるタイムゾーンとして使われています。日本での時刻はUTCよりも9時間早い時刻になります。プログラムを書き換えて、日本時間での現在時刻を表示させてみましょう[^1]。

```diff
- <p>現在時刻: <%= Time.current %></p>
+ <p>現在時刻: <%= Time.current.in_time_zone('Asia/Tokyo') %></p>
```

![現在時刻表示](assets/smallest-app/app_ss/time_jst.png)

コラム：今回の方法のほかに、アプリ全体でタイムゾーンを日本時間に設定してしまう方法もあります。その場合はconfig/application.rbファイル中に `config.time_zone = 'Asia/Tokyo'` と設定します。この方法の利点は、プログラムの中のあちこちで `in_time_zone('Asia/Tokyo')` を書かずに済み、config/application.rbファイルの1カ所にまとめることができることです。

最後に、このままでもいいのですが、コードのロジックの部分をビューに書くのではなく、コントローラで書くことにしましょう。動作は同じまま、コードを書き換えます。

コントローラを次のように変更します。

`app/controllers/hello_controller.rb`

```diff
class HelloController < ApplicationController
  def index
+   @time = Time.current.in_time_zone('Asia/Tokyo')
  end
end
```

そして、ビューを変更します。

`app/views/hello/index.html.erb`

```diff
- <p>現在時刻: <%= Time.current.in_time_zone('Asia/Tokyo') %></p>
+ <p>現在時刻: <%= @time %></p>
```

これでブラウザからアクセスすると、先ほどと同じように現在時刻が表示されているかと思います。

次の節から、このアプリがどのように動作しているのかを説明していきます。

## Webアプリはどのように動作しているか

ここで、普段ブラウザからつかっているWebアプリがどのように動作しているかを見てみましょう。アドレス入力欄にURLを入力してエンターキーを押すと、「リクエスト」がURL先のサーバへ向けて飛んでいきます。たとえば ```http://cookpad.com/``` と入力した場合は、クックパッドのサーバへ向けてリクエストが飛んでいきます。リクエストは追って説明していきますが、ざっくりと「そのページを見たいという要求（リクエスト）」とイメージしてもらえばOKです。

![リクエスト](assets/smallest-app/figures/request.png)

Webサーバ上で動作しているWebアプリはリクエストを受け取ると、「レスポンス」としてHTMLで書かれたテキストを作ってブラウザへ返します。レスポンスは「Webアプリが返してきた情報群（HTMLで書かれた表示するための情報を含む）」とイメージできます。

![レスポンス](assets/smallest-app/figures/response.png)

ブラウザはHTMLを解釈して、私たちにとって見やすい、いつも見慣れたWebページを表示します。HTMLはHyperText Markup Languageのことで、Webページを記述するための言語です。

![HTMLを表示](assets/smallest-app/figures/result.png)

コラム：Webサーバ
Webサーバとはなにものなのでしょうか？Webサーバは「Webサービスを提供する場合に必要な共通の機能を提供するもの」と言えます。Webアプリはブラウザとのやりとりで必要な機能のうち、どのサービスでも使う機能はWebサーバに仕事をまかせ、自分のサービスで必要なオリジナルな機能を提供することに注力します。Railsで開発するときにはpumaというWebサーバを利用する設定になっていて、`rails s`を実行すると起動します。実際のWebサービスを運用する場合は、nginxやApacheといったWebサーバを組み合わせて使うことが多いです。

HTMLはブラウザからも見ることができます。Chromeの場合は、どこかのサイト（たとえば ```http://cookpad.com/```）へアクセスしたあと、右クリックメニューから「ページのソースを表示」を選ぶとHTMLで書かれたそのページを閲覧することができます。

![右クリック](assets/smallest-app/app_ss/right_click.png)

![HTML(抜粋)](assets/smallest-app/app_ss/html.png)

ここまでに説明してきた以下の2つが、ブラウザの主な仕事です。

* リクエストをWebサーバへ投げる
* レスポンスで返ってきたHTMLを解釈して表示する

## インターネットの向こう側とこちら側

ブラウザからWebサービスにアクセスするとき、通常、Webアプリはインターネット上にあります。ブラウザだけが自分のPCにあります。

![インターネット上のサービスにアクセス](assets/smallest-app/figures/internet_and_local.png)

しかし、開発中は自分が作っているアプリをわざわざインターネット上へ置く必要はなく、自分のPCでWebアプリを動作させ、同じく自分のPCにあるブラウザからアクセス可能です。

![開発中は自分のPCでつくることができる](assets/smallest-app/figures/local.png)

## 今回つくったRailsアプリの動作まとめ

今回つくったRailsアプリの動作を図にすると次のようになります。

![今回つくったRailsアプリの動作](assets/smallest-app/figures/smallest_app.png)

ブラウザのURL欄にアドレスを入力してEnterを押すとリクエストが飛びます。リクエストを受け取ったRailsアプリはHTMLをつくり、レスポンスとして返します。レスポンスを受け取ったブラウザはHTMLを解釈し、画面に表示します。

## Railsでの開発の進め方

Railsでの基本的な開発の進め方は以下の2つを繰り返すサイクルになります。

* ひな形になるファイル（ソースコードや設定ファイル）の生成
* つくっているアプリ用にファイルを変更、追記

実は、さきほどつくったアプリもこの手順で進めていました。

```bash
rails new helloworld
rails g controller hello index
```

これらのコマンドは「ひな形になるファイルの生成」を行っていました。そのあと、```app/views/hello/index.html.erb``` を編集して、

```erb
<p>Hello world!</p>
```

という内容に変更しました。このように、rails gコマンドなどでひな形となるファイルを生成し、それをそのアプリで使いたい形へ変えていく、Railsアプリ開発ではこれを繰り返してつくっていきます。

rails gコマンドはひな形を作成しますが、場合によってはこの手順を飛ばして、ゼロから手で書いても構いません。どちらの手順をつかっても、アプリをつくることが可能です。多くの場合、rails gコマンドを使った方が、楽につくれたり、ミスをしづらくなるので便利です。

## Railsが生成するファイル

### rails newコマンド

では、Railsはどのようなファイルを生成するのでしょうか。最初のrails newコマンドを実行したとき、以下のようにcreate ...という表示がずらっとされたと思います。railsが生成したファイルとフォルダの名前を表示していたのです。

```console
$ rails new helloworld
create
create  README.md
create  Rakefile
create  config.ru
create  .gitignore
create  Gemfile
create  app
create  app/assets/config/manifest.js
create  app/assets/javascripts/application.js
create  app/assets/javascripts/cable.js
create  app/assets/stylesheets/application.css
create  app/channels/application_cable/channel.rb
create  app/channels/application_cable/connection.rb
create  app/controllers/application_controller.rb
create  app/helpers/application_helper.rb
... (略)
```

これらのファイル群によって、rails newをしただけで（何もコードを書かなくても）Webアプリとして動作します。たくさんのファイルがつくられていますね。Railsアプリの基本的なフォルダとファイル群は以下の図のものです。いきなりすべてを説明するのは難しいので、順番に説明していきます。役割ごとにフォルダが分かれています。それぞれの役割についてはこの後説明していきます。

![Railsアプリの基本的なフォルダ・ファイル群（一部抜粋）](assets/smallest-app/figures/rails_files.png)

### rails gコマンド

次に実行したrails gコマンドで作られたファイルを見てみましょう。

```bash
rails g controller hello index
```

```console
$ rails g controller hello index
Running via Spring preloader in process 50811
  create  app/controllers/hello_controller.rb
   route  get 'hello/index'
  invoke  erb
  create    app/views/hello
  create    app/views/hello/index.html.erb
  invoke  test_unit
  create    test/controllers/hello_controller_test.rb
  invoke  helper
  create    app/helpers/hello_helper.rb
  invoke    test_unit
  invoke  assets
  invoke    coffee
  create      app/assets/javascripts/hello.coffee
  invoke    scss
  create      app/assets/stylesheets/hello.scss
```

ここで実行したrails g controllerコマンドは、URLのパスが/hello/indexであるページを表示するためのファイル群を作ります。gはgenerateの略です。rails g controllerの後ろのhelloとindexが、生成するページのパスを指定していることが分かります。ほかにもいくつかのgenerateコマンドが用意されているので、またあとで説明します。

もしも、コマンドを間違えて生成したファイルをまとめて削除したい場合は、gをdに替えたコマンドを実行すると、まとめて削除することができます。dはdestroyの略です。

ここで生成、追記されたファイルのうち、特に重要なのは以下の3つのファイルです。

* app/controllers/hello_controller.rb
* app/views/hello/index.html.erb
* config/routes.rb

![rails g controller hello index コマンドで生成されるファイル](assets/smallest-app/figures/rails_g_controller.png)

これらのファイルがどのような働きをしているのかを、次の節でRailsがリクエストを受けてからレスポンスを返すまでの基本的な処理の順序を追いかけながら説明していきます。

## Railsアプリの処理の流れ

ブラウザからアクセスしたときに、Railsアプリはどのように動作しているのでしょうか？次の図は、今回つくったRailsアプリの動作を示したものです。前に出てきた動作の図から少し詳しくしています。

![Railsアプリの動作](assets/smallest-app/figures/rails_app_semantics.png)

ここでは、この図のRails Appの部分について詳しく説明していきます。ここから、対象箇所を抜き出したのが次の図です。

![Railsアプリがリクエストを受けてレスポンスを返すまで](assets/smallest-app/figures/rails_app_request_to_response.png)

リクエストを受けたRailsアプリは、Routes, Controller, Viewの3つのコードを通過します。それぞれの場所で処理を行い、レスポンスとしてHTMLを生成して返します。各所ではそれぞれ仕事の分担が決まっていて、自分の担当の処理を行います。Routes, Controller, Viewでそれぞれどのような処理が行われているのか、順に見ていきましょう。

### Routes

Routesは「リクエストのURLとHTTPメソッド」に応じて次に処理を行う先を決めるのが仕事です。URLは前に出てきましたが、HTTPメソッドとは何でしょうか？

* リクエスト
 * URL : http://localhost:3000/hello/index
 * HTTPメソッド：GET

リクエストを構成する要素のうち、重要なものがURLとHTTPメソッドです。URLはインターネット上の住所を表し、アクセスする先を指定するものです。もう一方のHTTPメソッドは、そのURLに対して「何をするか」を指示するものです。ブラウザのアドレス欄へURLを入力しEnterを押すと、HTTPメソッド "GET" でリクエストが飛びます。GETは「ページを取得する」指示です。GETのほかにもHTTPメソッドはいくつかあり、Railsアプリでよく使うものは4つです。GET以外のHTTPメソッドは次の章以降で説明していきます。

まとめると、リクエストは「URL」でアクセス先を、「HTTPメソッド」でなにをするかを指示します。

![Routes](assets/smallest-app/figures/routes_mapping.png)

最初に、Routesは「リクエストのURLとHTTPメソッド」に応じて次に処理を行う先を決めるのが仕事だと書きました。RailsではRoutesの処理が終わると、次はコントローラのアクションへ処理が移ります。アクションとはコントローラに書かれているメソッドのうち、publicなメソッドのことです。「Routesから呼び出せるメソッド」と言っても良いでしょう。ここでのメソッドはRubyでのメソッドのことで、処理を集めて名前をつけたものです。HTTPメソッドとは別のものです。RoutesはリクエストのURLとHTTPメソッドから、処理の進み先であるコントローラのアクションを決定します。RoutesはリクエストとControllerのアクションとの対応表と言えます。

では、Routesの対応表を見て見ましょう。rails serverを起動させて `/rails/info/routes` へアクセスしてみてください。Routesの対応表の見方を説明したのが次の図です。

* http://localhost:3000/rails/info/routes

![Routes対応表](assets/smallest-app/figures/routes.png)

表中の "HTTP Verb" がHTTPメソッドです。"Path"（パス）はURLの後半部分に相当します。URLが"http://localhost:3000/hello/index"である場合、パスは"/hello/index"になります。(表示されたパスの後半部分の`"(.:format)"は省略できる記述で、レスポンスで返すフォーマットを指定するための機能です。省略した場合はHTMLを返すのが普通です。)

右端の"Controller#Action"が処理の移るコントローラとアクションを示しています。ここでは "hello#index" と書かれていますが、#より左側がコントローラ名、右側がアクション名です。この場合は、「HelloControllerのindexアクション」を示しています。

この対応表を解釈すると、「リクエストのHTTPメソッドが"GET"、パスが"/hello/index"のとき、次の処理は"HelloController"の"index"アクションになる」となります。

ここで表示されたRoutesは`config/routes.rb`ファイルから生成されています。このファイルには次のような記述があります。

```ruby
get 'hello/index'
```

これがRoutesのコード部分で、この1行からさきほど説明した対応表が生成されています。「パス"hello/index"へのGETでのアクセスでHelloControllerのindexアクションが呼ばれる」という文です。Routesの書き方はまた追って説明していきます。

Routesについてまとめると、「RoutesはリクエストのパスとHTTPメソッドによって次の処理先であるコントローラとアクションを決める対応表」となります。

それでは、次の処理が行われるコントローラをみてみましょう。

### コントローラ

コントローラではさまざまな処理を行い、次のビューに処理を渡します。コントローラのファイルは`app/controllers/`へ置きます。さきほどのRoutesで次の処理先として指定されたHelloControllerは、`app/controller/hello_controller.rb` というファイルです。

```ruby
class HelloController < ApplicationController
  def index
    @time = Time.current.in_time_zone('Asia/Tokyo')
  end
end
```

HelloControllerのindexアクションが呼び出されます。`def index`から`end`までがindexアクションです。コントローラにあるpublicなメソッドをアクションと呼びます。アクションはRoutesから次の処理先として指示される可能性があります。

このindexアクションでは`@time`というインスタンス変数に現在時刻を代入しています。アクションの中のプログラム、ここでは `@time = Time.current.in_time_zone('Asia/Tokyo')` は、インデント（字下げ）されて書かれます。

変数は名札のようなもので、代入したものをあとから使えるように名前をつける仕組みです。変数のうち、@はじまりの変数のことをインスタンス変数といいます。インスタンス変数を使うと、コントローラから、このあとの処理先であるビューへ情報を伝えることができます。ちなみに、@はじまりではない変数はローカル変数と呼ばれ、このメソッド（アクション）を抜けると役目を終えて使えなくなります。つまり、ローカル変数へ代入してもビューから使うことはできません。ビューで使うためには、@はじまりのインスタンス変数を利用します。

![インスタンス変数を使うとビューへ情報を渡すことができる](assets/smallest-app/figures/instance_variable.png)

次にどのビューへ処理が進むかはコントローラで指定することができますが、今回は何も指定がありません。指定がないときは、コントローラおよびアクションと同名のビューを選択します。今回はHelloControllerのindexアクションなので、次の処理先であるビューのファイルはapp/views/hello/index.html.erbになります。

コントローラについてまとめてみましょう。コントローラではさまざまな処理を行い、次のビューに処理を渡します。ビューへ情報を伝えるためには@はじまりのインスタンス変数へ代入しておきます。次の処理先となるビューはコントローラで指定することができますが、指定していないときはコントローラおよびアクションと同名のビューを選択します。

それでは次の処理が行われるビューを見てみましょう。

### ビュー

ビューではHTMLなど、ユーザーの目に届く部分を作ります。作られたHTMLは、レスポンスとしてブラウザへ送られます。

ビューのファイルであるindex.html.erbは、HTMLのもとになるファイルです。ブラウザで表示させるための言語HTMLをそのまま書くことができます。さらに、普通のHTMLとの違いとして、Rubyのコードを実行した結果を埋め込むこともできます。このようなファイルをテンプレートと呼びます。ここではerbという種類のテンプレートが使われています。書かれているHTMLと、埋め込まれたRubyのコードを実行した結果をあわせてHTMLを作ります。では、ビューのファイルを見てみましょう。

`app/views/hello/index.html.erb`

```erb
<p>現在時刻: <%= @time %></p>
```

HTMLのpタグがあります。その中にHTMLではない `<%=` と `%>` というタグがあります。これがRubyのコードを実行するためのタグです。ここではその中にある `@time` が実行されます。@timeインスタンス変数にはコントローラで実行された現在時刻 `Time.current.in_time_zone('Asia/Tokyo')` の結果が代入されているので、これがHTMLへ埋め込まれます。

ビューで作られたHTMLは、Railsがその他の加工を加えてレスポンスとして送出され、ブラウザに表示されます。作られたHTMLはブラウザで「ページのソースを表示」機能をつかって確認することができます。

![ブラウザからビューがつくったHTMLを確認](assets/smallest-app/app_ss/time_jst.png)

ビューについての動作をまとめてみましょう。ビューはHTMLなど、ユーザーの目に届く部分をつくります。erbはテンプレートと呼ばれるHTMLのもとになるファイルで、Rubyのコードを実行した結果を埋め込むことができます。ビューで使う情報をコントローラから送ってもらうときは、インスタンス変数を使います。作られたHTMLは、Railsがその他の加工を加えてレスポンスとして送出します。

### まとめ

最小構成のRailsアプリをつくり、リクエストを受けてレスポンスを返すまでの動作について説明しました。ポイントをまとめると以下のようになります。

* Routes、コントローラ、ビューの順番で処理を行い、HTMLを作ってブラウザへレスポンスを返す
* RoutesはリクエストのURLとHTTPメソッドに応じて、処理をするコントローラとアクションを決める対応表
* コントローラはさまざまな処理を行い、ビューで使う情報を@はじまりのインスタンス変数を使って渡す
* ビューはテンプレート書かれたRubyのコードを実行して埋め込み、HTMLを作る

![Railsアプリがリクエストを受けてレスポンスを返すまで](assets/smallest-app/figures/rails_app_request_to_response.png)

## さらに学びたい場合は

- [Rails Guides : Rails のルーティング](https://railsguides.jp/routing.html)
  - Routesについての詳しい説明です。
- [Rails Guides : Action Controller の概要](https://railsguides.jp/action_controller_overview.html)
  - コントローラについての詳しい説明です。
- [Rails Guides : Action View の概要](http://railsguides.jp/action_view_overview.html)
  - ビューについての詳しい説明です。
- [Rails Guides : レイアウトとレンダリング](https://railsguides.jp/layouts_and_rendering.html)
  - コントローラから次のビューを指定する方法や、ビューを整理して書くための情報などが説明されています。
