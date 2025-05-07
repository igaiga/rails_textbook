
= はじめに

//quote{
@<b>{Rubyは開発者を幸せにする言語。}



@<b>{もっと多くの開発者を Ruby で幸せにしたい。}



@<b>{- Matz}

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



本書はRailsの入門的な本やサイトを読んで難しいと感じた方に、そこまでの知識を埋められるように書いています。逆に言えば、他の入門書を読める力があれば、本書はやさしすぎると感じるかもしれません。具体的には、@<href>{https://railstutorial.jp/,Railsチュートリアル} を読み進められるようであれば、本書から得られるものは少ないのではないかと思います。


== 書式例


本書では以下のようにコードやターミナルコマンドを表現します。


=== コードの書式例

//emlist[][ruby]{
puts "Hello world!"
//}


Ruby、Rails、HTMLなどのコードの書式例です。


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



ターミナルでの実行結果の書式例は次のようになります。


//emlist[][console]{
=> Booting Puma
...（略）
* Listening on http://127.0.0.1:3000
* Listening on http://[::1]:3000
Use Ctrl-C to stop
//}

== サンプルコード


本書で使うサンプルコードは次のURLにあります。

 * @<href>{https://github.com/igaiga/rails_textbook_sample,https://github.com/igaiga/rails_textbook_sample}


== 読者サポートページ


正誤表は次のURLにあります。

 * 正誤表: @<href>{https://github.com/igaiga/rails_textbook/blob/master/documents/errata.md,https://github.com/igaiga/rails_textbook/blob/master/documents/errata.md}


== 開発環境


本書は2025年4月1日現在の最新バージョンであるRuby 3.4.2、Rails 8.0.2で動作確認をしています。



Webアプリのプログラムを書くための道具として、ターミナル、エディタ、ブラウザをつかいます。



ターミナルはコンピュータをコントロールするための道具です。自分で書いたプログラムをターミナルから実行することができます。ターミナルでRubyおよびRailsのプログラムを実行するためには、開発環境を作る必要があります。最初にMacとWindowsの場合それぞれでの環境構築方法を説明して、そのあとでどちらの環境でも共通であるRubyとRailsのインストール方法を説明します。また、Dev Container環境をつかって開発環境をつくる方法も説明しています。



エディタはプログラムを入力する道具です。エディタは好みのものがあればそれを利用してください。特にない場合は @<href>{https://code.visualstudio.com,Visual Studio Code} をお勧めします。Visual Studio Codeはマイクロソフトによって開発されたオープンソースのエディタで、無料で使うことができます。ライセンスはMITライセンスです。



ブラウザはつくったWebアプリへアクセスするための道具としてつかいます。お好きなものをご利用いただけますが、文中で説明につかわれている @<href>{https://www.google.co.jp/chrome/browser/,Chrome} を使うと分かりやすいです。



以降で開発環境のつくり方を説明しています。macOSに環境をつくる場合は、「macOSに開発環境をつくる」と「RubyとRailsをインストールする」を実行してください。Windowsに環境をつくる場合は、「Windowsに開発環境をつくる」と「RubyとRailsをインストールする」を実行してください。Dev Container環境をつかって環境をつくる場合は、「Dev Container開発環境をつくってVisual Studio Codeからつかう」を実行してください。


=== macOSに開発環境をつくる


開発環境づくりに必要なxcodeツールをインストールします。


//emlist[][console]{
$ xcode-select --install
//}


@<href>{https://brew.sh,Homebrew} をインストールします。HomebrewはmacOSでさまざまな便利なプログラムをインストール、管理するためのツールです。

 * Homebrew: @<href>{https://brew.sh,https://brew.sh}



以下のインストールコマンド中の@<tt>{-fsSL}の後ろに表示上は改行をいれていますが、実行するときは次の行とつなげて1行のコマンドとして実行してください。


//emlist[][console]{
$ /bin/bash -c "$(curl -fsSL
    https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
//}


@<tt>{==> Installation successful!} が表示されたあとに表示される @<tt>{==> Next steps:} のコマンドを実行してください。たとえば次のように表示されます。


//emlist{
==> Next steps:
- Run these commands in your terminal to add Homebrew to your PATH:
    echo >> /Users/igaiga/.zprofile
    echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> /Users/igaiga/.zprofile
    eval "$(/opt/homebrew/bin/brew shellenv)"
//}


次はHomebrewを使ってrbenvをインストールします。rbenvはRubyをインストールして管理するための道具です。なおmacOS Catalinaからデフォルトのshellがbashからzshに変更されています。 @<tt>{echo $SHELL} を実行した結果が @<tt>{/bin/zsh} のようにzshであれば以下の通りですが、結果が @<tt>{/bin/bash} のようにbashであるときは、以下の @<tt>{.zprofile} を @<tt>{.bash_profile} に置き換えて実行してください。


//emlist[][console]{
$ brew update
$ brew install rbenv
$ echo 'eval "$(rbenv init -)"' >> ~/.zprofile
$ source ~/.zprofile
//}


これでRubyとRailsをインストールするための準備ができました。つづいて「RubyとRailsをインストールする」へ進んでください。


=== Windowsに開発環境をつくる


Windowsの場合はWSL2（Windows Subsystem for Linux 2、以下WSL）とrbenvを利用することで開発環境をつくることができます。インストールしたWSL上でLinux向けツールを利用して開発します。WSLを利用するためにはWindows10以降が必要です。もしもWindows10よりも前のバージョンを利用している場合や、WSLのインストールがうまく行かないときには、 @<href>{https://railsgirls.jp/install,RailsGirlsガイド インストール・レシピ} のページにある「Windows 用セットアップ（WSLが使えない方向け）」を参考にしてみてください。



WSLをインストールする方法は @<href>{https://learn.microsoft.com/ja-jp/windows/wsl/install,WSL を使用して Windows に Linux をインストールする方法} に書かれていますので、こちらの手順でインストールしてください。また、 @<href>{https://railsgirls.jp/install,RailsGirlsガイド インストール・レシピ} のページにも同様の手順がスクリーンショットをつかって丁寧に説明されています。インストールするLinuxを選ぶところでは好きなものを選んでもらって構いませんが、特になければデフォルトであるUbuntuを選択することをお勧めします。

 * WSL を使用して Windows に Linux をインストールする方法
 ** @<href>{https://learn.microsoft.com/ja-jp/windows/wsl/install,https://learn.microsoft.com/ja-jp/windows/wsl/install}



WSLのインストール後、起動したアプリケーションはターミナルあるいはBashウィンドウと呼びます。ターミナルにはユーザー名とパスワードの入力を促す画面が表示されていますので、適当なユーザー名（半角英数小文字のみ）とパスワードを入力しましょう。パスワードは2回入力する必要があり、画面には表示されませんが正しく入力されています。



ターミナルで以下のコマンドを実行してください。sudo apt installコマンド中のlibyaml-devの後ろとlibgdbm-devの後ろに表示上は改行をいれていますが、実行するときは次の行とつなげて1行のコマンドとして実行してください。



なお、最初のコマンドを実行するときにパスワードの入力を求められますが、先程ターミナルに入力したパスワードを入力してください。Windowsのパスワードではないことに注意してください。 @<tt>{sudo dpkg-reconfigure tzdata} を実行するとタイムゾーンを設定する画面が出ますので、「Asia」を矢印キーで移動して選択して、Tabキーを押してOkボタンに移動して、Enterキーを押してください。つづいて都市を選択する以下の画面が起動するので、「Tokyo」を矢印キーで移動して選択して、Tabキーを押してOkボタンに移動して、Enterキーを押してください。


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


=== RubyとRailsをインストールする


rbenvを使ってRubyをインストールします。Rubyのバージョンは、より新しいものがあればそちらを利用して構いません。rbenvからインストール可能なRubyのバージョンは@<tt>{rbenv install -l}で調べることができます。


//emlist[][console]{
$ rbenv install 3.4.2
//}


インストールしたRubyを利用するように設定します。


//emlist[][console]{
$ rbenv global 3.4.2
//}


確認のため、@<tt>{ruby -v}コマンドを実行してみましょう。ruby 3.4.2ではないときは、ターミナルを開き直して再実行してみてください。


//emlist[][console]{
$ ruby -v
ruby 3.4.2 (2025-02-15 revision d2930f8e7a) +PRISM
//}


以上でRubyのインストールは完了です。続いて、インストールしたRubyを使ってRailsをインストールします。


//emlist[][console]{
$ gem i rails
//}


確認のため、@<tt>{rails -v}コマンドを実行してみましょう。


//emlist[][console]{
$ rails -v
Rails 8.0.2
//}


このようにインストールしたRailsのバージョンが表示されればインストール成功です。結果に表示されるバージョンの数字は、実行時の最新バージョンとなるため異なることがあります。



Railsは最新バージョンのものをつかって問題ありませんが、もしも問題が出て進められなくなったときには、@<tt>{gem i rails -v 8.0.2} のようにバージョンを指定して、本書の内容と揃えることもできます。そのときには、以降のページで出てくる@<tt>{rails new アプリ名}コマンドを実行するときに、つかうバージョンを指定し@<tt>{rails _8.0.2_ new アプリ名}とします。



ここまででRubyとRailsの開発環境構築ができました。次の章へ進んでください。


=== Dev Container開発環境をつくってVisual Studio Codeからつかう


ここまで説明した方法はRubyやRailsを自分のコンピュータへ直接インストールする方法でした。別の方法として、Dev Container環境でRailsアプリ開発環境をつくる方法もあります。macOSでもWindowsでもつかうことができます。Dev Container環境はRubyやRailsを自分のコンピュータへ直接インストールせずに、RailsアプリケーションをDockerコンテナ上で実行する開発環境です。Visual Studio Code(以下VS Code)をつかうと、Dev Container環境でつかうDockerコンテナの起動やコンテナ内のターミナル操作などをエディタ上からかんたんに行えます。ただし、開発環境の動作を理解するためにはコンテナ技術に関する基礎知識が必要になります。



以降は「Railsガイド Dev Containerでの開発ガイド」のページに沿って説明しています。こちらのページも参考にしてみてください。

 * Railsガイド Dev Containerでの開発ガイド
 ** @<href>{https://railsguides.jp/getting_started_with_devcontainer.html,https://railsguides.jp/getting_started_with_devcontainer.html}



最初にVS Code、Docker、rails-newをセットアップします。



VS Codeはマイクロソフトによって開発されたオープンソースのエディタで、無料でつかうことができます。ライセンスはMITライセンスです。公式ページからダウンロードしてインストールします。あわせてDev Containers拡張機能をマーケットプレイスからインストールしておきます。また、日本語化するためにはマーケットプレイスからJapanese Language Pack for Visual Studio Codeをインストールして「使用法」の欄の方法で日本語化します。

 * Visual Studio Code 公式ページ
 ** @<href>{https://code.visualstudio.com,https://code.visualstudio.com}
 * Visual Studio Code マーケットプレイス Dev Containers
 ** @<href>{https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers,https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers}
 * Visual Studio Code マーケットプレイス Japanese Language Pack for Visual Studio Code
 ** @<href>{https://marketplace.visualstudio.com/items?itemName=MS-CEINTL.vscode-language-pack-ja,https://marketplace.visualstudio.com/items?itemName=MS-CEINTL.vscode-language-pack-ja}



Dockerはコンテナと呼ばれる仮想環境パッケージをつかってアプリ実行環境（ここではRails開発環境）をつくることができるプラットフォームです。Docker Desktopなどをつかってインストールします。

 * Docker Desktop
 ** @<href>{https://docs.docker.com/desktop,https://docs.docker.com/desktop}



rails-newはRubyがインストールされていなくても新規Railsアプリケーションをつくることができるツールです。rails-newを次の方法でインストールします。



GitHubの@<href>{https://github.com/rails/rails-new/releases,リリースページ}から最新バージョンのAssets欄を表示して、つかっているプラットフォームのファイルをダウンロードしてください。macOSでは「rails-new-universal-apple-darwin.tar.gz」、Windowsでは「rails-new-x86_64-pc-windows-gnu.zip」となります。ダウンロード後に .tar.gz ファイルを解凍するとrails-new 実行可能ファイルを取得できます。このrails-newファイルをパスの通ったフォルダへ配置して、ターミナルから実行できるようにします。

 * Rails new リリースページ
 ** @<href>{https://github.com/rails/rails-new/releases,https://github.com/rails/rails-new/releases}



macOSではターミナルからrails-newコマンドを実行すると「"rails-new"は、開発元を検証できないため開けません。」と表示されます。ターミナルでrails-newファイルが置いてあるフォルダへ移動して、次のコマンドで実行可能にすることができます。このコマンドは「（セキュリティ上の警告を確認して問題ないので）実行を許可します」という変更をコマンドファイルに行います。


//emlist[][bash]{
$ xattr -d com.apple.quarantine ./rails-new
//}


ターミナルからrails-newコマンドをつかってRailsアプリをつくります。@<tt>{--devcontainer} オプションをつけることで、あわせてDev Container環境をつくります。次のコマンドではrails-newコマンドがRailsアプリ@<tt>{example_app}をつくり、アプリ名と同名の@<tt>{example_app}フォルダをつくります。


//emlist[][bash]{
$ rails-new example_app --devcontainer
//}


次に、VS Codeを起動してDev Container環境をつかってみます。VS Codeの「ファイル」メニューから「開く」を選び、さきほどrails-newコマンドでつくった@<tt>{example_app}フォルダを選びます。



左下の><ボタンで表示されるメニューから「コンテナーで再度開く」を選ぶとDocker環境を起動することができます。または、コマンドパレット機能（WindowsではCtrl+ShiftPキー、macOSではCommand+Shift+Pキー）から「開発コンテナー: コンテナーで再度開く」を選ぶことでもDocker環境を起動できます。



VS Code内のターミナル画面が表示されていないときは「ターミナル」メニューの「新しいターミナル」から開くことができます。Docker環境が起動できていれば、このターミナル画面はDocker環境で実行されていて、rubyコマンドやrailsコマンドほかRailsアプリ開発に必要なコマンドを実行することができます。@<tt>{rails --version} コマンドを実行して、たとえば@<tt>{Rails 8.0.2}のようにバージョンが表示されれば、開発環境は正常に起動しています。

