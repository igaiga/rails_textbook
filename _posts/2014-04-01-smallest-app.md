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

今回も最初にアプリを作ります。前の章で作成した my_web_apps の下に新しいアプリを作ってみましょう。ターミナルを起動して以下のコマンドを打ちます。

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

次に前の章と同じように以下のコマンドを実行してみましょう。

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

![welcome rails]({{ site.url }}/assets/my-first-web-app/welcome_rails.png)

前の章と同じように動作しています。ここで実行した ```rails s``` コマンドの s は server の略で、s でも server でも同じように動作します。

TODO: rails s を停止した場合のアクセス。ポート重複時のアクセス。

### rails g コマンドでページを作る

ひきつづき、以下のコマンドを入力してください。rails server が起動している場合は、Ctrl-c (controlキーを押しながらcキー)で終了してからコマンドを打ってください。

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

![entries]({{site_url}}/assets/smallest-app/hello_index.png)

この画面が出れば、ここまで意図通りに動作しています。



## TODO？:コラム bin/rails
