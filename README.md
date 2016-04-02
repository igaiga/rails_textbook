# Railsの教科書

## Webで閲覧
- http://igarashikuniaki.net/rails_textbook/

## 達人出版会で電子書籍版を購入
- http://tatsu-zine.com/books/rails-textbook

## ローカルで閲覧
- $ git clone https://github.com/igaiga/rails_textbook.git
- $ cd rails_textbook
- $ bundle install
- $ jekyll serve --watch --baseurl ''
- http://localhost:4000/rails_textbook/ へアクセス

## textlintで文章をチェック

### コマンドラインでの実行

- $ `npm i`             ## textlintのインストール
- $ `npm test`          ## 文章全体のチェック
- $ `npm run textlint _posts/2014-04-01-preface.md`  ## 単独のファイルをチェック

### atomエディタでの実行

- $ `apm install linter`
- $ `apm install linter-textlint`
- atomエディタでファイルを開くと画面下部にエラーが表示されます

## 誤記などの報告方法
以下のコントリビュートポリシーにご同意いただいて、issuesまたはpull requestを作成いただくか、igaigaまでご連絡ください。

### コントリビュートポリシー
ご報告、コントリビュートいただきありがとうございます。本資料は書籍版とWeb版で情報を共有しております。原則として、両方へ変更が反映されていきます。ご了承の上コントリビュートいただければと思います。

