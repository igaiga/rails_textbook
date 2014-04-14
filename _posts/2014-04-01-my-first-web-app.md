---
layout: post
unique_identifier:
 - 'http:/example.jp/bookid_in_url'
 - 'BookID'
 - 'URL'
title: 'Webアプリをまずはつくってみよう'
subtitle: 'presented by igaiga'
creator: 'igaiga'
date: '2014-04-01'
categories:
---

# Webアプリをまずはつくってみよう

それでは、早速Webアプリをつくってみましょう。作るのは、記事と写真が投稿できる簡易なブログアプリです。まずはWebアプリづくりがどのようなものかを体験してもらうのがこの章の目的です。それぞれのコマンドやコードの意味は、本書の中で追って説明していきます。

## Webアプリをつくる

### アプリの作成とWelcome画面

まずはターミナルを起動して以下のコマンドを打ってみましょう。

{% highlight bash %}
mkdir my_web_apps
cd my_web_apps
{% endhighlight %}

mkdir はフォルダを作成するコマンド、cd はターミナル内で現在のフォルダを移動するコマンドです。(Winで普段使いなれている「コンピューター(エクスプローラー)」を起動するには、ターミナルで explorer . と打つと現在のフォルダを開くことができます。MacでFinderを開くにはターミナルから open . と打ちます。)

続けて以下のコマンドを実行します。

{% highlight bash %}
rails new blog_app
{% endhighlight %}

以下のような結果が表示されるでしょうか。(実行には少し時間がかかります)

{% highlight console %}
$ rails new blog_app
      create
      create  README.rdoc
      create  Rakefile
... (略)
Your bundle is complete!
Use `bundle show [gemname]` to see where a bundled gem is installed.
         run  bundle exec spring binstub --all
* bin/rake: spring inserted
* bin/rails: spring inserted
{% endhighlight %}

ターミナルの画面にこのように"Your bundle is complete!"と表示されれば成功です。railsコマンドはたくさんのフォルダとファイルを自動で作ります。

{% highlight console %}
$ rails new blog_app
       exist
   identical  README.rdoc
    conflict  Rakefile
Overwrite /Users/igarashi/work/blog_app/Rakefile? (enter "h" for help) [Ynaqdh] 
{% endhighlight %}

次は以下のコマンドを実行してみてください。

{% highlight bash %}
cd blog_app
rails server
{% endhighlight %}

うまく動作している場合は、以下のような表示になります。

{% highlight console %}
$ rails server
=> Booting WEBrick
=> Rails 4.1.0 application starting in development on http://0.0.0.0:3000
=> Run `rails server -h` for more startup options
=> Notice: server is listening on all interfaces (0.0.0.0). Consider using 127.0.0.1 (--binding option)
=> Ctrl-C to shutdown server
[2014-04-14 09:26:25] INFO  WEBrick 1.3.1
[2014-04-14 09:26:25] INFO  ruby 2.1.1 (2014-02-24) [x86_64-darwin13.0]
[2014-04-14 09:26:25] INFO  WEBrick::HTTPServer#start: pid=3855 port=3000
{% endhighlight %}

では、ブラウザを起動して以下のURLを入力してアクセスしてみましょう。

* localhost:3000

![welcome rails]({{ site.url }}/assets/welcome_rails.png)

これは、Railsが起動し、あなたのブラウザからのリクエストを受け付けて、表示している画面です。ここまでのわずかの手順で、Webアプリをつくり、画面を表示しているのです。

### ページの作成

ひきつづき、以下のコマンドを入力してください。rails server が起動している場合は、Ctrl + C ボタンで終了してからコマンドを打ちます。

{% highlight bash %}
rails generate scaffold entry title description:text picture
rake db:migrate
rails server
{% endhighlight %}

{% highlight console %}
$ rails generate scaffold entry title description:text picture
      invoke  active_record
      create    db/migrate/20140414232433_create_entries.rb
      create    app/models/entry.rb
...(略)

$ rake db:migrate
== 20140414232433 CreateEntries: migrating ====================================
-- create_table(:entries)
   -> 0.0009s
== 20140414232433 CreateEntries: migrated (0.0010s) ===========================

$ rails server
=> Booting WEBrick
=> Rails 4.1.0 application starting in development on http://0.0.0.0:3000
=> Run `rails server -h` for more startup options
=> Notice: server is listening on all interfaces (0.0.0.0). Consider using 127.0.0.1 (--binding option)
=> Ctrl-C to shutdown server
[2014-04-15 08:24:53] INFO  WEBrick 1.3.1
[2014-04-15 08:24:53] INFO  ruby 2.1.1 (2014-02-24) [x86_64-darwin13.0]
[2014-04-15 08:24:53] INFO  WEBrick::HTTPServer#start: pid=5929 port=3000
{% endhighlight %}

ここでまたブラウザを使い、以下のURLを表示させます。

* http://localhost:3000/entries

![entries]({{site_url}}/assets/scaffold_index.png)

画面が表示されたら、New Entry のリンクをたどってみましょう。Title, Description などを入力し、Create Entry ボタンで保存してみてください。また、保存したデータを編集や削除をしてみてください。ここまでの作業で簡易なブログの基本機能ができました。

★ここから

### 写真アップロード機能の追加

Rails にファイルをアップロードする機能を追加するには、ライブラリをインストールする必要があります。

プロジェクトディレクトリ内の Gemfile を開いて、この行

gem 'sqlite3'
の直後に、次の一行を追加します。

gem 'carrierwave'

Terminal で、次のコマンドを実行してください。 :

bundle
そうすると、次のコマンドでアップロードを実行するコードを生成できます。 :

rails generate uploader Picture
ここで、Terminal 上で Rails server プロセスをリスタート する必要があります。追加したライブラリをアプリにロードさせるためです。

app/models/idea.rb を開いて、次の行

class Idea < ActiveRecord::Base
の直後に、

mount_uploader :picture, PictureUploader

を追加します。さらに、app/views/ideas/_form.html.erb を開いて次のように編集します。

<%= f.text_field :picture %>
  ↓

<%= f.file_field :picture %>
場合によっては、 TypeError: can’t cast ActionDispatch::Http::UploadedFile to string というエラーが起きることもあります。エラーになった場合は、 app/views/ideas/_form.html.erb の

<%= form_for(@idea) do |f| %>
上記のコードを、以下のように変更してみてください。

<%= form_for @idea, :html => {:multipart => true} do |f| %>

画像をアップロードするとわかりますが、これだけでは見栄えのいいものではありません。ファイルのpathだけを表示してるので、これもいじってみましょう。

app/views/ideas/show.html.erb を開いて編集します。

<%= @idea.picture %>
  ↓

<%= image_tag(@idea.picture_url, width: 600) if @idea.picture.present? %>




# 章
## 節
### 見出し

