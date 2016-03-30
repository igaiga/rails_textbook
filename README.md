# Railsの教科書

## Webで閲覧
- http://igarashikuniaki.net/rails_textbook/

## 内容に誤りをみつけた場合は

このページのissuesまでご報告いただくか、pull requestください。

### コントリビュートポリシー
ご報告、コントリビュートいただきありがとうございます。本資料は書籍版とWeb版で情報を共有しております。原則として、両方へ変更が反映されていきます。ご了承の上コントリビュートいただければと思います。

## ローカルで閲覧する方法
- $ git clone https://github.com/igaiga/rails_textbook.git
- $ cd rails_textbook
- $ bundle install
- $ jekyll serve --watch --baseurl ''
- http://localhost:4000/rails_textbook/ へアクセス

## textlintで文章をチェック

### コマンドラインでの実行

- $ `npm i`             ## textlintのインストール
- $ `npm test`          ## 文章全体のチェック（しばらくは数百のエラーが出るので心が折れないよう気をつける）
- $ `npm run textlint _posts/2014-04-01-preface.md`  ## 単独のファイルをチェック

### atomエディタでの実行

- $ `apm install linter`
- $ `apm install linter-textlint`
- atomエディタでファイルを開く→画面下部にエラーが表示される
