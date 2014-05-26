---
layout: post
unique_identifier:
 - 'http:/example.jp/bookid_in_url'
 - 'BookID'
 - 'URL'
title: '一番小さなRailsアプリづくり'
creator: 'igaiga'
date: '2014-04-01'
categories:
---

# 一番小さなRailsアプリづくり

ここではできるだけ小さい構成のRailsアプリを作ってみます。Railsアプリがどのように動作するのかの説明と、Railsが作るファイルがどのような役割なのか、機能と関連づけて説明していきます。

## 一番小さなRailsアプリをつくる

### アプリの作成

今回も最初にアプリを作ります。ブラウザに"Hello world!"と表示させるアプリです。前の章で作成した ```my_web_apps``` の下に新しいアプリを作ってみましょう。ターミナルを起動して以下のコマンドを打ちます。

{% highlight bash %}
cd my_web_apps
rails new helloworld
{% endhighlight %}

{% highlight console %}
$ rails new helloworld
      create
... (略)
Your bundle is complete!
Use `bundle show [gemname]` to see where a bundled gem is installed.
         run  bundle exec spring binstub --all
* bin/rake: spring inserted
* bin/rails: spring inserted
{% endhighlight %}

次に、前の章と同じように以下のコマンドを実行してみましょう。

{% highlight bash %}
cd helloworld
rails s
{% endhighlight %}
{% highlight console %}
$ rails s
=> Booting WEBrick
=> Rails 4.1.0 application starting in development on http://0.0.0.0:3000
=> Run `rails server -h` for more startup options
=> Notice: server is listening on all interfaces (0.0.0.0). Consider using 127.0.0.1 (--binding option)
=> Ctrl-C to shutdown server
[2014-05-05 10:22:56] INFO  WEBrick 1.3.1
[2014-05-05 10:22:56] INFO  ruby 2.1.1 (2014-02-24) [x86_64-darwin13.0]
[2014-05-05 10:22:56] INFO  WEBrick::HTTPServer#start: pid=30940 port=3000
{% endhighlight %}

ブラウザを起動して以下のURLを入力してアクセスしてみます。

* http://localhost:3000

![Welcome rails]({{ site.url }}/assets/my-first-web-app/welcome_rails.png)

図 : Welcome rails

前の章と同じように動作しています。ここで実行したコマンド ```rails s``` の s は server の略で、省略した s でも、省略せずに server でも、同じように動作します。

TODO: コラム：rails s を停止した場合のアクセス。ポート重複時のアクセス。

### rails g コマンドでページを作る

ひきつづき、以下のコマンドを入力してみましょう。rails server が起動している場合は、Ctrl-c (controlキーを押しながらcキー)で終了してからコマンドを打ってください。

{% highlight bash %}
rails g controller hello index
{% endhighlight %}
{% highlight console %}
$ rails g controller hello index
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
      create      test/helpers/hello_helper_test.rb
      invoke  assets
      invoke    coffee
      create      app/assets/javascripts/hello.js.coffee
      invoke    scss
      create      app/assets/stylesheets/hello.css.scss
{% endhighlight %}

もしもrails g コマンドを打ち間違えて違うファイルを作ってしまった場合は、打ち間違えたコマンドの g の部分を d にして再実行すると、rails g コマンドで作成したファイルをまとめて削除してくれます。たとえば、``` rails g controller hell index``` とhelloをhellと打ち間違えた場合は、``` rails d controller hell index``` コマンドを実行することで間違えて作ったファイル群を削除することができます。（ターミナルでカーソルキーの↑キーを押すと、さきほど入力した内容が出てくるので、それを利用して g を d に直すと楽に実行できます。）

再びrails server を起動させましょう。
{% highlight bash %}
rails s
{% endhighlight %}
{% highlight console %}
$ rails s
=> Booting WEBrick
=> Rails 4.1.0 application starting in development on http://0.0.0.0:3000
=> Run `rails server -h` for more startup options
=> Notice: server is listening on all interfaces (0.0.0.0). Consider using 127.0.0.1 (--binding option)
=> Ctrl-C to shutdown server
[2014-05-05 10:22:56] INFO  WEBrick 1.3.1
[2014-05-05 10:22:56] INFO  ruby 2.1.1 (2014-02-24) [x86_64-darwin13.0]
[2014-05-05 10:22:56] INFO  WEBrick::HTTPServer#start: pid=30940 port=3000
{% endhighlight %}

ブラウザを使い、以下のURLへアクセスします。

* http://localhost:3000/hello/index

![hello/index]({{site_url}}/assets/smallest-app/hello_index.png)

図 : hello/index

この画面が出れば、ここまで意図通りに動作しています。さきほど実行した rails g コマンドはこのページ、/hello/index を作るものでした。どのような仕組みで動作しているかは後ほどまた説明しますので、今は先にこのページに"Hello world!"と表示させてみることにします。

```app/views/hello/index.html.erb``` ファイルをエディタで開いてみてください。以下のような内容になっています。

{% highlight erb %}
<h1>Hello#index</h1>
<p>Find me in app/views/hello/index.html.erb</p>
{% endhighlight %}

これを以下のように変更して、ブラウザで同じURLへアクセスしてみてください。(rails s は起動したままで大丈夫です。もしも rails s を一度終了していた場合は、rails s コマンドでもう一度起動してからアクセスしてください。)

{% highlight erb %}
<p>Hello world!</p>
{% endhighlight %}

![Hello world]({{site_url}}/assets/smallest-app/helloworld.png)

図 : Hello world

"Hello world!"の文字が表示されましたか？これで一番小さなRailsアプリができあがりました。ここへ、少しだけRubyのコードを書いて、現在時刻を表示する機能を追加してみましょう。

{% highlight erb %}
<p>Hello world!</p>
+ <p>現在時刻: <%= Time.now %></p>
{% endhighlight %}

![現在時刻表示]({{site_url}}/assets/smallest-app/time_now.png)

表示されましたか？ブラウザをリロードすると、現在時刻が更新されます。アクセスしたそのときの時刻が表示されるアプリになりました。最後に、このままでもいいのですが、コードのロジックの部分をビューに書くのではなく、コントローラで書くことにしましょう。動作は同じまま、コードを書き換えます。

コントローラを次のように変更します。

`app/controllers/hello_controller.rb`
{% highlight ruby %}
class HelloController < ApplicationController
  def index
+   @time = Time.now
  end
end
{% endhighlight %}

そして、ビューを変更します。

`app/views/hello/index.html.erb`
{% highlight erb %}
- <p>現在時刻: <%= Time.now %></p>
+ <p>現在時刻: <%= @time %></p>
{% endhighlight %}

これでブラウザからアクセスすると、先ほどと同じように現在時刻が表示されているかと思います。

次の節から、このアプリがどのように動作しているのかを説明していきます。

## Webアプリはどのように動作しているか

ここで、みなさんが普段ブラウザからつかっているWebアプリがどのように動作しているかを見てみましょう。アドレス入力欄にURLを入力してエンターキーを押すと、「リクエスト」がURL先のサーバへ向けて飛んでいきます。たとえば ```http://cookpad.com/``` と入力した場合は、クックパッドのサーバへ向けてリクエストが飛んでいきます。リクエストは追って説明していきますが、ざっくりと「そのページを見たいという要求（リクエスト）」とイメージしてもらえばOKです。

![リクエスト]({{site_url}}/assets/smallest-app/request.png)

図 : リクエスト

Webサーバ上で動作しているWebアプリはリクエストを受け取ると、「レスポンス」としてHTMLで書かれたテキストを作ってブラウザへ返します。レスポンスは「Webアプリが返してきた情報群（HTMLで書かれた表示するの情報を含む）」とイメージできます。HTMLは HyperText Markup Language のことで、Webページを記述するための言語です。ブラウザはHTMLを解釈して、私たちの見易い、いつも見慣れたWebページを表示します。

![レスポンス]({{site_url}}/assets/smallest-app/response.png)

図 : レスポンス

コラム：Webサーバ
Webサーバとはなにものなのでしょうか？Webサーバは「Webサービスを提供する場合に必要な共通の機能を提供するもの」と言えます。Webアプリはブラウザとのやりとりで必要な機能のうち、どのサービスでも使う機能はWebサーバに仕事をまかせ、自分のサービスで必要なオリジナルな機能を提供することになります。Rubyには標準でWEBrick というWebサーバが用意されていて、rails s をしたときに起動するようになっています。実際のWebサービスを運用して提供する場合は、EnginxやApacheといったWebサーバが使われることが多いです。

HTMLはブラウザからも見ることができます。Chromeの場合は、どこかのサイト(たとえば ```http://cookpad.com/``` ) へアクセスしたあと、右クリックメニューから「ページのソースを表示」を選ぶとHTMLで書かれたそのページを閲覧することができます。

![右クリック]({{site_url}}/assets/smallest-app/right_click.png)

図 : 右クリックしてHTMLを表示する

![HTML]({{site_url}}/assets/smallest-app/html.png)

図 : HTML(抜粋)

ここまで説明してきた以下の2つが、ブラウザの主な仕事です。

* リクエストをWebサーバへ投げる
* レスポンスで返ってきたHTMLを解釈して表示する

## インターネットの向こう側とこちら側

ブラウザからWebサービスにアクセスする場合、通常はWebアプリはインターネット上にあります。ブラウザだけが自分のPCにあります。

![インターネット上のサービスにアクセス]({{site_url}}/assets/smallest-app/internet_and_local.png)

図 : インターネット上のサービスにアクセス

しかし、開発中は自分が作っているアプリをわざわざインターネット上へ置く必要はなく、自分のPCでWebアプリを動作させ、同じく自分のPCにあるブラウザからアクセス可能です。

![開発中のアプリにアクセス]({{site_url}}/assets/smallest-app/local.png)

図 : 開発中は自分のPCでつくることができる

## 今回つくったRailsアプリの動作まとめ

今回つくったRailsアプリの動作を図に描いてみました。

![今回つくったRailsアプリの動作]({{site_url}}/assets/smallest-app/smallest_app.png)

ブラウザのURL欄にアドレスを入力してEnterを押すとリクエストが飛びます。リクエストを受け取ったRailsアプリはHTMLをつくり、レスポンスとして返します。レスポンスを受け取ったブラウザはHTMLを解釈し、画面に表示します。

## Railsでの開発の進め方

Railsでの基本的な開発の進め方は以下の2つを繰り返すサイクルになります。

* ひな形になるファイル（ソースコードや設定ファイル）の生成
* つくっているアプリ用にファイルを変更、追記

実は、さきほどつくったアプリもこの手順で進めていました。

{% highlight bash %}
rails new helloworld
rails g controller hello index
{% endhighlight %}

これらのコマンドは「ひな形になるファイルの生成」を行っていました。そのあと、```app/views/hello/index.html.erb``` を編集して、

{% highlight erb %}
<p>Hello world!</p>
{% endhighlight %}

という内容に変更しました。このように、rails g コマンドなどでひな形となるファイルを生成し、それをそのアプリで使いたい形へ変えていく、Railsアプリ開発ではこれを繰り返してつくっていきます。

rails g コマンドはひな形を作成しますが、場合によってはこの手順を飛ばして、ゼロから手で書いても構いません。どちらの手順をつかっても、アプリをつくることが可能です。多くの場合、rails g コマンドを使った方が、楽につくれたり、ミスをしづらくなるので便利です。

## Railsが生成するファイル

### rails new コマンド

では、Railsはどのようなファイルを生成するのでしょうか。最初の rails new コマンドを実行したとき、以下のように create ... という表示がずらっとされたと思います。railsが生成したファイルとフォルダの名前を表示していたのです。

{% highlight console %}
$ rails new helloworld
create
create  README.rdoc
create  Rakefile
create  config.ru
create  .gitignore
create  Gemfile
create  app
create  app/assets/javascripts/application.js
create  app/assets/stylesheets/application.css
create  app/controllers/application_controller.rb
create  app/helpers/application_helper.rb
create  app/views/layouts/application.html.erb
create  app/assets/images/.keep
create  app/mailers/.keep
create  app/models/.keep
... (略)
{% endhighlight %}

これらのファイル群によって、rails new をしただけで（何もコードを書かなくても）webアプリとして動作します。たくさんのファイルがつくられていますね。Railsアプリの基本的なフォルダとファイル群は以下の図のものです。いきなり全てを説明するのは難しいので、順番に説明していきます。役割ごとにフォルダが分かれています。それぞれの役割についてはこの後説明していきます。

![Railsアプリの基本的なフォルダ・ファイル群]({{site_url}}/assets/smallest-app/rails_files.png)


図 : Railsアプリの基本的なフォルダ・ファイル群

### rails g コマンド

次に実行した rails g コマンドで作られたファイルを見てみましょう。

{% highlight bash %}
rails g controller hello index
{% endhighlight %}

{% highlight console %}
$ rails g controller hello index
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
create      test/helpers/hello_helper_test.rb
invoke  assets
invoke    coffee
create      app/assets/javascripts/hello.js.coffee
invoke    scss
create      app/assets/stylesheets/hello.css.scss
{% endhighlight %}

ここで実行した rails g controller コマンドは、URLのパスが /hello/index であるページを表示するためのファイル群を生成します。g は generate の略です。rails g controller の後ろの hello と index が、生成するページのパスを指定していることが分かります。

ちなみに、前にやった rails g scaffold もgenerateの種類の1つです。scaffold は編集、更新、削除といったたくさんの機能を一度につくりますが、rails g controller の場合は生成するページをつくるシンプルなものです。そのほかにもいくつかの generate コマンドが用意されています。もしも、コマンドを間違えて生成したファイルをまとめて削除したい場合は、 g を d に替えたコマンドを実行すると、まとめて削除することができます。d は destroy の略です。

ここで生成されたファイルのうち、特に重要なのは以下の3つのファイルです。

* app/controllers/hello_controller.rb
* app/views/hello/index.html.erb
* config/routes.rb

![rails g controller]({{site_url}}/assets/smallest-app/rails_g_controller.png)

図 : rails g controller hello index コマンドで生成されるファイル

これらのファイルがどのような働きをしているのかを、次の節でRailsがリクエストを受けてからレスポンスを返すまでの基本的な処理の順序を追いかけながら説明していきます。

## Rails がリクエストを受けてからレスポンスを返すまでの流れ

ブラウザからアクセスしたときに、Railsアプリはどのように動作しているのでしょうか？以下の図は、今回つくったRailsアプリの動作を示したものです。前に出てきた動作の図から少しだけ詳しく書き加えてあります。

![Railsアプリの動作]({{site_url}}/assets/smallest-app/rails_app_semantics.png)

図 : Railsアプリの動作

ここでは、この図のRailsAppの部分について詳しく説明していきます。ここから、対象箇所を抜き出したのが次の図です。

![リクエストを受けてレスポンスを返すまで]({{site_url}}/assets/smallest-app/rails_app_request_to_response.png)

図 : リクエストを受けてレスポンスを返すまで

リクエストを受けたRailsアプリは、Routes, Controller, View の各所で処理を行い、レスポンスとしてHTMLを生成して返します。各所ではそれぞれ仕事の分担が決まっていて、自分の担当の処理を行います。Routes, Controller, View でそれぞれどのような処理が行われているのか、順に見ていきましょう。

### Routes

Routesは「リクエストのURLとHTTPメソッド」に応じて次に処理を行う先を決めるのが仕事です。URLは前に出てきましたが、HTTPメソッドとは何でしょうか？

* リクエスト
 * URL : http://localhost:3000/hello/index
 * HTTPメソッド：GET

リクエストを構成する要素のうち、重要なものがURLとHTTPメソッドです。URLはアドレスということもあるように、インターネット上の住所を表します。URLでアクセスする先を指定するのです。もう一方のHTTPメソッドは、そのURLに対して「何をするか」を指示するものです。ブラウザのアドレス欄へURLを入力しEnterを押すと、HTTPメソッド "GET" でリクエストが飛びます。GETは「ページを取得する」の意です。GETのほかにも、HTTPメソッドはいくつかあり、Railsアプリでよく使うものは4つほどです。GET以外のHTTPメソッドは次の章以降で説明していきます。

まとめると、リクエストは「URL」でアクセス先を、「HTTPメソッド」で行うことを指定します。

Routesの処理を、HTTPメソッドを加えてもう少し詳しくみてみましょう。最初に説明した通り、Routesは「リクエストのURLとHTTPメソッド」に応じて次に処理を行う先を決めるのが仕事です。RailsではRoutesの処理が終わると、次はControllerのアクションへ処理が移ります。アクションとはControllerのメソッドのうち、Routesから呼び出されるもののことです。RoutesはリクエストのURLとHTTPメソッドから、処理の進み先であるContollerのアクションを決定します。RoutesはリクエストとController のアクションとの対応表と言えます。

では、Routesの対応表を見て見ましょう。rails server を起動させて以下へアクセスすると、Routesの対応表が表示されます。（図参照）

* http://localhost:3000/rails/info/routes

![Routes]({{site_url}}/assets/smallest-app/routes.png)

図 : Routes

"HTTP Verb" がHTTPメソッドです。"Path"はURLの後半部分に相当します。URLが"http://localhost:3000/hello/index"である場合、パスは"/hello/index"になります。(表示されたPathの後半部分の "(.:format)" は省略できる記述で、、レスポンスで返すフォーマットを指定するための機能です。多くのRailsアプリでは省略するとHTMLを返します。)

右端の"Controller#Action"が処理が移るコントローラとアクションを示しています。ここでは "hello#index" と書かれていますが、#より左側がコントローラ名、右側がアクション名です。この場合は、「HelloControllerのindexアクション」を示しています。

まとめると、この対応表は「リクエストのHTTPメソッドが"GET"、パスが"/hello/index"のとき、次の処理は"HelloController"の"index"アクションになる」という意味になります。

ここで表示されたRoutesは`config/routes.rb`ファイルから生成されます。このファイルを開くと以下のような記述があります。

{% highlight ruby %}
get 'hello/index'
{% endhighlight %}


これがRoutesのコード部分で、この1行からさきほど説明した対応表が生成されています。「パス"hello/index"へのGETでのアクセスでHelloControllerのindexアクションが呼ばれる」という文です。Routesの書き方はまた追って説明していきます。

それでは次に、処理が進む先となるコントローラをみてみましょう。

### コントローラ

コントローラはさまざまな処理を行い、次のビューに処理を渡します。コントローラのファイルは`app/controllers/`へ置きます。さきほどのRoutesで指定されたHelloControllerは`app/controller/hello_controller.rb` というファイルです。

{% highlight ruby %}
class HelloController < ApplicationController
  def index
    @time = Time.now
  end
end
{% endhighlight %}

`def index`から`end`までがindexアクションです。HelloControllerのindexアクションが呼び出されます。★TODO


どのビューへ処理が進むかはコントローラで指定可能ですが、今回のように何も指定が無い場合は、コントローラと同名のビューを選択します。今回はHelloControllerのindexアクションなので、対応するビューのファイルはapp/views/hello/index.html.erb になります。
