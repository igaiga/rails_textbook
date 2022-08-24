
= Gemライブラリ


この章ではGemについて説明します。Gemfileやbundleコマンドについても説明をしていきます。


== Gemライブラリ


プログラミングの世界では便利なプログラムがたくさん公開されています。いろいろなプログラムで共通して使える便利な公開されたプログラムをライブラリと呼びます。



Rubyの世界にもライブラリがあり、Gemと呼ばれます。Gemは @<href>{https://rubygems.org,rubygems.org} で公開されていて、10万を越えるGemが登録されています。RailsはWebアプリをかんたんに作るGemの集合体として設計されています。


== Gemをインストールして利用する


Gemをインストールするにはgem iコマンドを利用します。gem iのiはinstallの省略形です。省略せずにgem installとすることもできます。例として、pメソッドをより見やすい形で拡張させたapメソッドを提供するawesome_printというGemをインストールしてみましょう。


//emlist[][bash]{
$ gem i awesome_print
//}

//emlist[][console]{
Fetching awesome_print-1.9.2.gem
Successfully installed awesome_print-1.9.2
1 gem installed
//}


コマンドを実行すると、上記のような表示が出てGemを使えるようになります。Gem名の後ろにハイフンで続く数字はバージョンです。実行したときの最新バージョンがインストールされるため、数字は異なることもあります。



インストールしたawesome_printは、きれいに表示するapというメソッドを提供します。irbを起動して試しに使ってみましょう。irbは対話形式でRubyプログラムを実行できる仕組みです。rails consoleもirbを利用しています。


//emlist[][bash]{
$ irb
//}

//emlist[][ruby]{
require "awesome_print"
ap [1,2,3]
//}

//emlist[][console]{
$ irb
> require "awesome_print"
=> true
> ap [1,2,3]
[
    [0] 1,
    [1] 2,
    [2] 3
]
=> nil
//}


このような形式で配列[1,2,3]が表示されれば成功です。Rubyが標準で持っているpメソッドも同等のことができますが、apメソッドの方がきれいに読み易い形で表示してくれます。



プログラムで最初に実行した@<tt>{require "awesome_print"}はapを使えるようにするためのコードです。Gemライブラリは、gem installしたあと、requireを実行することで利用できます。使い方はGemごとに異なるため、Gem名で検索してドキュメントを読んでみてください。GitHubのページが用意されていることが多いです。


== BundlerとGemfile


Gemは前述のように、gem installコマンドで簡単にインストールすることが可能ですが、この方法でたくさんのGemをインストールしようとすると、Gemの数だけコマンドを打たなくてはいけません。それは大変なので、Gemの管理をかんたんにするBundlerという仕組みが用意されています。



BundlerでGem群をインストールするには2つの手順を実行します。



1つ目はGemfileという名前のファイルに使用するGemを書くこと。2つ目はbundle installコマンドを実行することです。仕組みの名前はBundlerですが、コマンド名はbundleと最後にrが付かない点に注意です。



Railsアプリは最初からBundlerの仕組みを利用するようになっています。GemfileはRailsアプリの場合、Railsのルートフォルダに置いてあります。エディタで開いてみましょう。


//emlist[][ruby]{
source "https://rubygems.org"
git_source(:github) { |repo| "https://github.com/#{repo}.git" }

ruby "3.1.0"

# Bundle edge Rails instead: gem "rails", github: "rails/rails", branch: "main"
gem "rails", "~> 7.0.1"
...
//}


たくさんのgemが表示されました。Railsアプリは最初につくった状態ですでに10個以上のgemが登録されています。ここに、さきほどのawesome_print gemを追加してみましょう。書く場所はどこでも良いのですが、一番最後の行へ追加することにします。Gemfileへ次の一行を追加して保存します。


//emlist[][ruby]{
gem "awesome_print"
//}


追加して保存したら、以下のようにbundle installコマンドを実行します。このコマンドの実行時にはネットワークへ接続が必要なため、少し時間がかかります。また、各Gemのバージョンや、Bundle complete!につづけて表示される数字は異なることがあります。


//emlist[][console]{
$ bundle install
...
Using awesome_print 1.9.2
...
Bundle complete! 18 Gemfile dependencies, 83 gems now installed.
Use `bundle info [gemname]` to see where a bundled gem is installed.
//}


これでawesome_print gemを使う準備は完了です。試しにrails consoleを起動して、apメソッドを使ってみましょう。


//emlist[][console]{
$ rails c
> ap [1,2,3]
[
    [0] 1,
    [1] 2,
    [2] 3
]
=> nil
> ap Book.first
irb(main):002:0> ap Book.last
   (1.0ms)  SELECT sqlite_version(*)
Book Load (0.4ms)  SELECT "books".* FROM "books" ORDER BY "books"."id" ASC LIMIT ?  [["LIMIT", 1]] #<Book:0x0000000130c061c0> {
    :id => 1,
    :title => "RubyとRailsの学習ガイド",
    :memo => "Rails関連技術地図とそれらの学習資料の紹介",
    :created_at => Fri, 07 Jan 2022 02:06:03.593544000 UTC +00:00,
    :updated_at => Fri, 07 Jan 2022 02:06:03.593544000 UTC +00:00
}
=> nil
//}


ターミナルに改行されて色がついて読み易く表示されているかと思います。またRailsアプリではrequireを書く必要がありません。ちなみに、書いても問題ありません。requireは複数回実行しても問題ないためです。



公開されているRubyで書かれたプログラムにGemfileが添えられていたときにはbundle installコマンドを実行してからプログラムを実行してみましょう。多くの場合、ドキュメントにその旨が書かれていますが、暗黙の了解で省略されていることもあります。



また、Gemfileを変更してbundle installコマンドを実行すると、Gemfile.lockというファイルが作成されます。Gemfile.lockには、使われているGem名とそのバージョン情報が記録されています。Gemfile.lockは自動で作られるものなので、編集する必要はありません。ソースコードを保管するときは、GemfileとGemfile.lockの両方のファイルを保管してください。



2つのファイルの違いを例え話で説明すると、GemfileはGemをインストールするための発注書です。Gemfileに使いたいGem名を書いて、bundle installコマンドを実行すると、発注書に従ってGemがインストールされます。Gemfile.lockは納品書です。発注書にもとづいて実際にインストールされたGemとそのバージョン情報などが書かれています。


== Gemfileに書かれたGemのバージョンアップ


各Gemは随時、新しいバージョンがリリースされます。Gemfileに書かれたGemの新しいバージョンをインストールしたい場合は@<tt>{bundle update}コマンドを使います。実行すると、新しいバージョンのGemがあればインストールして、Gemfile.lockファイルを更新します。@<tt>{bundle update}コマンドを実行すると、Gemfile中のすべてのGemがバージョンアップ対象となります。



特定のGemだけをバージョンアップしたい場合は、@<tt>{bundle update Gem名} とGem名をつけて実行すればOKです。指定したGemが利用している他のGemがある場合は、セットでバージョンアップされます。


== Gemfileに書かれたGemを使って実行する


bundle updateの結果、新しいバージョンのGemがインストールされた場合、古いバージョンのGemはアンインストールされないので、同じGemの複数のバージョンがインストールされた状態になります。通常は新しいバージョンのGemが利用され、それで問題がないケースが多いのですが、GemfileとGemfile.lockに書かれた（古い）バージョンのGemを使って実行したいケースもあります。



そのような場合は、bundle execコマンドを使うことでGemfileとGemfile.lockに書かれたGemバージョンでRubyのプログラムを実行することができます。


//emlist{
bundle exec rake -T
//}


このように、実行したいコマンドの前にbundle execと書くことで、Gemfile, Gemfile.lockに書かれたバージョンのGemを使って実行します。bundle execに続けて、railsコマンドのほか、rubyコマンド、rakeコマンド、irbコマンドなど、Rubyに関係するあらゆるコマンドを書くことができます。



ところで、ここまでrailsコマンドを使ってきましたが、ここにbundle execを書かなくてもいいのでしょうか？答えは、「書く必要はない」です。railsコマンドを実行すると、bin/railsファイルが実行され、その中でbundle exec相当の処理を行っています。


== Gemfileでのバージョン指定


利用するバージョンを指定したい場合は、Gemfileにバージョンを追記します。RailsアプリのGemfileを見ると、いくつかバージョンがすでに指定してあるものがあります。


//emlist[][ruby]{
gem 'capybara', '>= 2.15'
//}


これは「capybara Gemのバージョンは、2.15以上」という意味の指定になります。これは数式の意味と同じですね。一方、こんな見慣れないバージョン指定表記があります。


//emlist[][ruby]{
gem 'sqlite3', '~> 1.4'
//}


 ~> という記号、このケースでは、@<tt>{>= 1.4.0} かつ @<tt>{< 1.5} という意味になります。小さいバージョンアップは受け入れて、大きなバージョンアップは受け入れない、という記号です。



バージョンの表記の仕様は @<href>{https://bundler.io/gemfile.html,Bundlerのページ} に解説されています。


== まとめ


ポイントをまとめます。

 * いろんなプログラムから使える便利な公開されたプログラムをライブラリと呼ぶ
 * GemはRubyの世界のライブラリ
 * Gemをインストールするにはgem iコマンド（gem installの省略形）を使う
 * Bundlerは複数のGemをかんたんに管理する仕組み
 * BundlerではGemfileという名前のファイルに使用するGemを書く
 * Gemfileを作成しbundle installコマンドを実行すると、Gem群がインストールされる
 * bundle installコマンドを実行するとGemfileをもとにGemfile.lockファイルが生成されるので、両方をソース管理対象にする
 * Gemfileは発注書、Gemfile.lockは納品書に相当する

