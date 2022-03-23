
= はじめに

//quote{
@<b>{Rubyは開発者を幸せにする言語。}



@<b>{もっと多くの開発者を Ruby で幸せにしたい。}



@<b>{- matz}

//}


ブラウザを使って買い物をする、SNSを読み書きする、料理のレシピを検索する。Webアプリが提供するサービスは私たちの生活に深く根ざしています。それらを使うだけではなくて、どうやって動いているか知りたい、自分でも作ってみたい。本書はその第一歩を踏み出すための資料です。


== 本書の目的


本書の目的の1つはWebアプリ作成のための便利なフレームワークRuby on Rails（以下、Rails）を使い、題材として写真や文書を投稿できるミニブログアプリを作って動かし、その仕組みを学ぶことです。Webアプリがどういうものなのか、何ができるのか、どのような仕組みで動いているのかを説明していきます。できるだけ簡単なサンプルアプリを用意し、その仕組みを説明することで、RailsおよびWebアプリの基礎を説明していきます。



また、本書の目的のもう1つは、世の中にあるたくさんの情報を読むために前提となる基礎知識を身につけることです。Railsを学ぶための良い資料として、@<href>{https://railsguides.jp/,Railsガイド} や @<href>{https://railstutorial.jp/,Railsチュートリアル} があります。本書を読み進めると、これらの資料を読み進めるための基礎知識が身についてきます。実践的なRailsアプリを作るために必要なさまざまな資料を読むための入り口として本書はあります。


== 本書の対象読者


本書が対象としている読者は以下のような方々です。

 * プログラミングは初めてである
 * Webプログラミングは初めてである
 * Railsプログラミングは初めてである
 * Railsプログラミングを講義で教えたい



プログラミングは初めての方も安心してください。プログラミングの世界へようこそ！本書は筆者が作成した一橋大学社会学部での半期分の講義資料をもとに書いています。講義では初めてプログラムを書く学生さんが多数派でした。学生さんたちがつまづいた箇所について補足をして、資料を加筆していきました。プログラミングが初めての方に読んでいただけるように、丁寧に説明をしていきます。



プログラミングの世界、Webの世界は広大です。本書ではHTML（ブラウザで表示するための言語）とCSS（HTMLと一緒に使う、装飾するための言語）については最低限の説明のみにとどめています。学習したい方へ、巻末にHTMLとCSSを学習する資料を載せています。もしもあなたがデザイナーであり、HTMLコーディングはおてのもの、という場合は大きなアドバンテージがあります。本書の知識と組み合わせることで鮮やかなWebアプリを作ることができるようになるでしょう。



また、プログラミングが初めての方で、本書を読んで「プログラムの基礎をもっと学んでから挑戦したい」「プログラムを読んで理解はできるが、自分で考えて書くのが難しい」と感じた方は、筆者の別著書である「ゼロからわかる Ruby超入門」（書籍情報はあとがきの章にあります）をお勧めします。「ゼロからわかる Ruby超入門」は、初めてプログラミングをする方へ向けたRubyプログラミングの入門書です。プログラミングの基礎である条件分岐、繰り返しなどの概念を図解を入れて丁寧に説明します。また、Railsで使う知識を広くカバーするように書いています。



もしもあなたが他の言語でプログラミングをした経験があれば、これも大きなアドバンテージです。特にJavaScript（ブラウザ上で動作するプログラミング言語）の経験がある方は、本書の知識をつかってインタラクティブで格好良いWebアプリを作ることができるようになるでしょう（本書ではJavaScriptについては説明しません）。また、Rubyの経験がある方は、本書の内容を越えた範囲について、いままでの知識をつかって早く成長することができるでしょう。



そして、Railsプログラミングを講義で教えたい方もいらっしゃると思います。本書はWebアプリがどういうものなのかを手を動かしながら学ぶ構成になっています。大学で行った講義の資料を元に書いており、プログラミングが初めての学生さんらに向けて行った、1回90分の講義10回分の内容です。その後、3回の講義時間を使って自由にWebアプリを作る実習を行ったところ、彼ら彼女らは自分で考えた、実用的であったり、たのしさにあふれたりする、独創性のあるプログラムを作りあげて発表してくれました。本書はできるだけやさしい説明を心がけますが、Rubyのことやターミナルのこと、プログラミングでしか使わない記号など、つまづいたときにサポートの手を差し伸べられる状況を作っておくと順調に前へ進めるようになります。



一方で、本書の対象から外れるのは以下のような方です。

 * Railsの基礎はわかっている



本書はRailsの入門的な本やサイトを読んで難しいと感じた方に、そこまでの知識を埋められるように書いています。逆に言えば、他の入門書を読める力があれば、本書は易しすぎると感じるかもしれません。具体的には、@<href>{https://railstutorial.jp/,Railsチュートリアル} を読み進められるようであれば、本書から得られるものは少ないのではないかと思います。


== 書式例


本書では以下のようにコードやターミナルコマンドを表現します。


=== rubyおよびrailsコードの書式例

//emlist[][ruby]{
puts "Hello world!"
//}

=== 差分がある場合の書式例

//emlist[][diff]{
class HelloController < ApplicationController
  def index
-   @time = Time.current
+   @time = 1.day.ago
  end
end
//}


-, +印が付いている場合はその行について変更を行うことを示します（-, + がついていない部分はそのままです）。-で始まる行を削除し、+で始まる行を追加してください。


=== ターミナルコマンドの書式例

//emlist[][bash]{
$ rails s
//}


先頭の$マークはターミナルを表す印です。入力する必要はありません。入力するとエラーになるので気をつけてください。


=== ターミナルの実行結果の書式例

//emlist[][console]{
=> Booting Puma
...（略）
* Listening on http://127.0.0.1:3000
* Listening on http://[::1]:3000
Use Ctrl-C to stop
//}

== サンプルコード


本書で使うサンプルコードは以下に置いてあります。



@<href>{https://github.com/igaiga/rails_textbook_sample,https://github.com/igaiga/rails_textbook_sample}


== 開発環境


本書は2022年1月19日現在の最新バージョンであるRuby 3.1.0、Rails 7.0.1で動作確認をしています。



Webアプリのプログラムを書くための道具として、ターミナル、エディタ、ブラウザをつかいます。



ターミナルはコンピュータをコントロールするための道具です。自分で書いたプログラムをターミナルから実行することができます。ターミナルでRubyおよびRailsのプログラムを実行するためには、開発環境を作る必要があります。最初にMacとWindowsの場合それぞれでの環境構築方法を説明して、そのあとでどちらの環境でも共通であるRubyとRailsのインストール方法を説明します。



エディタはプログラムを入力する道具です。エディタは好みのものがあればそれを利用してください。特にない場合は @<href>{https://code.visualstudio.com/,Visual Studio Code} をお勧めします。Visual Studio Codeは無料で使うことができます。ライセンスはMITライセンスです。



ブラウザはつくったWebアプリへアクセスするための道具としてつかいます。お好きなものをご利用いただけますが、文中で説明につかわれている @<href>{https://www.google.co.jp/chrome/browser/,Chrome} を使うと分かりやすいです。



また、今後のRubyおよびRailsなどのバージョンアップによってここに書いている内容では動かなくなることもあります。 @<href>{https://github.com/igaiga/rails_textbook,読者サポートページ} にある「環境構築」のページにより新しい情報があれば、そちらも参考にしてください。


=== Macに開発環境をつくる


開発環境づくりに必要なxcodeツールをインストールします。


//emlist[][console]{
$ xcode-select --install
//}


@<href>{https://brew.sh/,Homebrew} をインストールします。HomebrewはMacでさまざまな便利なプログラムをインストール、管理するためのツールです。以下のコマンド中の@<tt>{-fsSL}の後ろに表示上は改行をいれていますが、実行するときは次の行とつなげて1行のコマンドとして実行してください。


//emlist[][console]{
$ /bin/bash -c "$(curl -fsSL
    https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
//}


Homebrewを使ってrbenvをインストールします。rbenvはRubyをインストールして管理するための道具です。なおmacOS Catalinaからデフォルトのshellがbashからzshに変更されています。 @<tt>{echo $SHELL} を実行した結果が @<tt>{/bin/zsh} のようにzshであれば以下の通りですが、結果が @<tt>{/bin/bash} のようにbashであるときは、以下の @<tt>{.zshrc} を @<tt>{.bash_profile} に置き換えて実行してください。


//emlist[][console]{
$ brew update
$ brew install rbenv
$ echo 'eval "$(rbenv init -)"' >> ~/.zshrc
$ source ~/.zshrc
//}


これでRubyとRailsをインストールするための準備ができました。つづいて「RubyとRailsをインストールする」へ進んでください。



もしも、Rails6.1以前のRailsをつかう場合や、JavaScriptのライブラリを利用する場合には、Webpackerと呼ばれるライブラリを利用することがあります。Webpackerをつかう場合には、以下の手順でyarnなどの必要なJavaScriptライブラリをインストールします。


//emlist[][console]{
$ brew install yarn
//}

=== Windowsに開発環境をつくる


Windowsの場合はWSL2（Windows Subsystem for Linux 2、以下WSL）とrbenvを利用することで開発環境をつくることができます。インストールしたWSL上でLinux向けツールを利用して開発します。WSLを利用するためにはWindows10以降が必要です。もしもWindows10よりも前のバージョンを利用している場合や、WSLのインストールがうまく行かないときには、 @<href>{https://railsgirls.jp/install,RailsGirlsガイド インストール・レシピ} のページにある「Windows 用セットアップ（WSLが使えない方向け）」を参考にしてみてください。



WSLをインストールする方法は @<href>{https://docs.microsoft.com/ja-jp/windows/wsl/install-win10,Windows Subsystem for Linux Installation Guide for Windows 10 のページ} に書かれていますので、こちらの手順でインストールしてください。また、 @<href>{https://railsgirls.jp/install,RailsGirlsガイド インストール・レシピ} のページにも同様の手順がスクリーンショットをつかって丁寧に説明されています。インストールするLinuxを選ぶところでは好きなものを選んでもらって構いませんが、特になければデフォルトであるUbuntuを選択することをお勧めします。UbuntuのバージョンはUbuntu 20.04を想定しています。



WSLのインストール後、起動したアプリケーションはターミナルあるいはBashウィンドウと呼びます。ターミナルにはユーザー名とパスワードの入力を促す画面が表示されていますので、適当なユーザー名（半角英数小文字のみ）とパスワードを入力しましょう。パスワードは2回入力する必要があり、画面には表示されませんが正しく入力されています。



ターミナルで以下のコマンドを実行してください。sudo apt installコマンド中のlibyaml-devの後ろとlibgdbm-devの後ろに表示上は改行をいれていますが、実行するときは次の行とつなげて1行のコマンドとして実行してください。



なお、最初のコマンドを実行する際にパスワードの入力を求められますが、先程ターミナルに入力したパスワードを入力してください。Windowsのパスワードではないことに注意してください。 @<tt>{sudo dpkg-reconfigure tzdata} を実行するとタイムゾーンを設定する画面が出ますので、「Asia」を矢印キーで移動して選択して、Tabキーを押してOkボタンに移動して、Enterキーを押してください。つづいて都市を選択する以下の画面が起動するので、「Tokyo」を矢印キーで移動して選択して、Tabキーを押してOkボタンに移動して、Enterキーを押してください。


//emlist[][console]{
$ sudo dpkg-reconfigure tzdata
$ sudo apt update
$ sudo apt upgrade -y
$ sudo apt install autoconf bison build-essential libssl-dev libyaml-dev
    libreadline-dev zlib1g-dev libncurses5-dev libffi-dev libgdbm-dev
    libgdbm-compat-dev libdb-dev sqlite3 libsqlite3-dev -y
//}


次はrbenvをインストールします。rbenvはRubyをインストールして管理するための道具です。以下のコマンドを実行してください。


//emlist[][console]{
$ git clone https://github.com/rbenv/rbenv.git ~/.rbenv
$ git clone https://github.com/rbenv/ruby-build.git ~/.rbenv/plugins/ruby-build
$ echo 'export PATH="$HOME/.rbenv/bin:$PATH"' >> ~/.bashrc
$ echo 'eval "$(rbenv init -)"' >> ~/.bashrc
$ source ~/.bashrc
//}


これでRubyとRailsをインストールするための準備ができました。つづいて「RubyとRailsをインストールする」へ進んでください。



もしも、Rails6.1以前のRailsをつかう場合や、JavaScriptのライブラリを利用する場合には、Webpackerと呼ばれるライブラリを利用することがあります。Webpackerをつかう場合には、以下の手順でyarnなどの必要なJavaScriptライブラリをインストールします。


//emlist[][console]{
$ curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.1/install.sh | bash
$ source ~/.bashrc
$ nvm install --lts
$ nvm alias default lts/*
$ nvm use default
$ npm install --global yarn
//}

=== RubyとRailsをインストールする


rbenvを使ってRubyをインストールします。Rubyのバージョンは、より新しいものがあればそちらを利用して構いません。rbenvからインストール可能なRubyのバージョンは@<tt>{rbenv install -l}で調べることができます。


//emlist[][console]{
$ rbenv install 3.1.0
//}


インストールしたRubyを利用するように設定します。


//emlist[][console]{
$ rbenv global 3.1.0
//}


以上でRubyのインストールは完了です。続いて、インストールしたRubyを使ってRailsをインストールします。


//emlist[][console]{
$ gem i rails
//}


確認のため、@<tt>{rails -v}コマンドを実行してみましょう。


//emlist[][console]{
$ rails -v
Rails 7.0.1
//}


このようにインストールしたRailsのバージョンが表示されればインストール成功です。結果に表示されるバージョンの数字は、実行時の最新バージョンとなるため異なることがあります。



Railsは最新バージョンのものをつかって問題ありませんが、もしも問題が出て進められなくなったときには、@<tt>{gem i rails -v 7.0.1}のようにバージョンを指定して、本書の内容と揃えることもできます。そのときには、以降のページで出てくる@<tt>{rails new アプリ名}コマンドを実行するときに、つかうバージョンを指定し@<tt>{rails _7.0.1_ new アプリ名}とします。



ここまででRubyとRailsの開発環境構築ができました。

