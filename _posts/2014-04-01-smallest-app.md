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

"Hello world!"の文字が表示されましたか？これで一番小さなRailsアプリができあがりました。それでは次は、このアプリがどのように動作しているのかを見ていきましょう。

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

★ここから
