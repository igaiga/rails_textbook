## Webで閲覧
- http://igarashikuniaki.net/rails_textbook/

## ローカルで閲覧
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

## コントリビュートの方法
以下のコントリビュートポリシーにご同意いただいて、igaigaへご連絡いただくか、pull requestください。

### コントリビュートポリシー
コントリビュートいただきありがとうございます。本資料は将来、有料または無料の書籍にする可能性があります。その際には私の名前（と権利と責任）で書籍化しますので、ご了承の上コントリビュートいただければと思います。
