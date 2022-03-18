# 開発環境構築

2022年1月19日にRuby 3.1.0、Rails 7.0.1で動作確認をしている情報です。書籍の開発環境構築情報が古くなったときの手助けとして、このページを作成しています。

## Macに開発環境をつくる

開発環境づくりに必要なxcodeツールをインストールします。

```console
$ xcode-select --install
```

[Homebrew](https://brew.sh/) をインストールします。HomebrewはMacでさまざまな便利なプログラムをインストール、管理するためのツールです。以下のコマンド中の`-fsSL`の後ろに表示上は改行をいれていますが、実行するときは次の行とつなげて1行のコマンドとして実行してください。

```console
$ /bin/bash -c "$(curl -fsSL
    https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Homebrewを使ってrbenvをインストールします。rbenvはRubyをインストールして管理するための道具です。なおmacOS Catalinaからデフォルトのshellがbashからzshに変更されています。 `echo $SHELL` を実行した結果が `/bin/zsh` のようにzshであれば以下の通りですが、結果が `/bin/bash` のようにbashであるときは、以下の `.zshrc` を `.bash_profile` に置き換えて実行してください。

```console
$ brew update
$ brew install rbenv
$ echo 'eval "$(rbenv init -)"' >> ~/.zshrc
$ source ~/.zshrc
```

これでRubyとRailsをインストールするための準備ができました。つづいて「RubyとRailsをインストールする」へ進んでください。

もしも、Rails6.1以前のRailsをつかう場合や、JavaScriptのライブラリを利用する場合には、Webpackerと呼ばれるライブラリを利用することがあります。Webpackerをつかう場合には、以下の手順でyarnなどの必要なJavaScriptライブラリをインストールします。

```console
$ brew install yarn
```

## Windowsに開発環境をつくる

Windowsの場合はWSL2（Windows Subsystem for Linux 2、以下WSL）とrbenvを利用することで開発環境をつくることができます。インストールしたWSL上でLinux向けツールを利用して開発します。WSLを利用するためにはWindows10以降が必要です。もしもWindows10よりも前のバージョンを利用している場合や、WSLのインストールがうまく行かないときには、 [RailsGirlsガイド インストール・レシピ](https://railsgirls.jp/install) のページにある「Windows 用セットアップ（WSLが使えない方向け）」を参考にしてみてください。

WSLをインストールする方法は [Windows Subsystem for Linux Installation Guide for Windows 10 のページ](https://docs.microsoft.com/ja-jp/windows/wsl/install-win10) に書かれていますので、こちらの手順でインストールしてください。また、 [RailsGirlsガイド インストール・レシピ](https://railsgirls.jp/install) のページにも同様の手順がスクリーンショットをつかって丁寧に説明されています。インストールするLinuxを選ぶところでは好きなものを選んでもらって構いませんが、特になければデフォルトであるUbuntuを選択することをお勧めします。UbuntuのバージョンはUbuntu 20.04を想定しています。

WSLのインストール後、起動したアプリケーションはターミナルあるいはBashウィンドウと呼びます。ターミナルにはユーザー名とパスワードの入力を促す画面が表示されていますので、適当なユーザー名（半角英数小文字のみ）とパスワードを入力しましょう。パスワードは2回入力する必要があり、画面には表示されませんが正しく入力されています。

ターミナルで以下のコマンドを実行してください。sudo apt installコマンド中のlibyaml-devの後ろとlibgdbm-devの後ろに表示上は改行をいれていますが、実行するときは次の行とつなげて1行のコマンドとして実行してください。

なお、最初のコマンドを実行する際にパスワードの入力を求められますが、先程ターミナルに入力したパスワードを入力してください。Windowsのパスワードではないことに注意してください。 `sudo dpkg-reconfigure tzdata` を実行するとタイムゾーンを設定する画面が出ますので、「Asia」を矢印キーで移動して選択して、Tabキーを押してOkボタンに移動して、Enterキーを押してください。つづいて都市を選択する以下の画面が起動するので、「Tokyo」を矢印キーで移動して選択して、Tabキーを押してOkボタンに移動して、Enterキーを押してください。

```console
$ sudo dpkg-reconfigure tzdata
$ sudo apt update
$ sudo apt upgrade -y
$ sudo apt install autoconf bison build-essential libssl-dev libyaml-dev
    libreadline-dev zlib1g-dev libncurses5-dev libffi-dev libgdbm-dev
    libgdbm-compat-dev libdb-dev sqlite3 libsqlite3-dev -y
```

次はrbenvをインストールします。rbenvはRubyをインストールして管理するための道具です。以下のコマンドを実行してください。

```console
$ git clone https://github.com/rbenv/rbenv.git ~/.rbenv
$ git clone https://github.com/rbenv/ruby-build.git ~/.rbenv/plugins/ruby-build
$ echo 'export PATH="$HOME/.rbenv/bin:$PATH"' >> ~/.bashrc
$ echo 'eval "$(rbenv init -)"' >> ~/.bashrc
$ source ~/.bashrc
```

これでRubyとRailsをインストールするための準備ができました。つづいて「RubyとRailsをインストールする」へ進んでください。

もしも、Rails6.1以前のRailsをつかう場合や、JavaScriptのライブラリを利用する場合には、Webpackerと呼ばれるライブラリを利用することがあります。Webpackerをつかう場合には、以下の手順でyarnなどの必要なJavaScriptライブラリをインストールします。

```console
$ curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.1/install.sh | bash
$ source ~/.bashrc
$ nvm install --lts
$ nvm alias default lts/*
$ nvm use default
$ npm install --global yarn
```

## RubyとRailsをインストールする

rbenvを使ってRubyをインストールします。Rubyのバージョンは、より新しいものがあればそちらを利用して構いません。rbenvからインストール可能なRubyのバージョンは`rbenv install -l`で調べることができます。

```console
$ rbenv install 3.1.0
```

インストールしたRubyを利用するように設定します。

```console
$ rbenv global 3.1.0
```

以上でRubyのインストールは完了です。続いて、インストールしたRubyを使ってRailsをインストールします。

```console
$ gem i rails
```

確認のため、`rails -v`コマンドを実行してみましょう。

```console
$ rails -v
Rails 7.0.1
```

このようにインストールしたRailsのバージョンが表示されればインストール成功です。結果に表示されるバージョンの数字は、実行時の最新バージョンとなるため異なることがあります。

Railsは最新バージョンのものをつかって問題ありませんが、もしも問題が出て進められなくなったときには、`gem i rails -v 7.0.1`のようにバージョンを指定して、本書の内容と揃えることもできます。そのときには、以降のページで出てくる`rails new アプリ名`コマンドを実行するときに、つかうバージョンを指定し`rails _7.0.1_ new アプリ名`とします。

ここまででRubyとRailsの開発環境構築ができました。
