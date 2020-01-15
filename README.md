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

- $ `npm i textlint`   # textlintのインストール
- $ `npm test`         # 文章全体のチェック
- $ `npm run textlint _posts/2014-04-01-preface.md`  # 単独のファイルをチェック

### atomエディタでの実行

- $ `apm install linter`
- $ `apm install linter-textlint`
- atomエディタでファイルを開くと画面下部にエラーが表示されます

## 誤記などの報告方法
以下のコントリビュートポリシーにご同意いただいて、issuesまたはpull requestを作成いただくか、igaigaまでご連絡ください。

### コントリビュートポリシー
ご報告、コントリビュートいただきありがとうございます。本資料は書籍版とWeb版で情報を共有しております。原則として、両方へ変更が反映されていきます。ご了承の上コントリビュートいただければと思います。

## 利用可能範囲

私的な利用、および公的な学校、コミュニティでの利用はOKです。
商用での利用については許可していませんが、別途有償ライセンスの準備がありますので [igaiga](https://github.com/igaiga) へご連絡ください。

## 画像に関するメモ

生成方法によって何種類かの画像ファイルがあります。

- HTMLからレンダリングしたファイル
  - _figures/aseets/ 以下のフォルダにhtmlファイルがあるもの
  - レンダリングスクリプトは _figures/scripts/html_figures 以下
- イラストレーターで作成した変更されないファイル
  - _figures/aseets/ 以下のフォルダに画像がそのまま置いてあるもの
  - assetsへのコピースクリプトは書いていない
- アプリのスクショ
  - レンダリングスクリプトは _figures/scripts/screenshots 以下
- chrome_dev_toolのスクショを加工したもの
  - _figures/chrome_dev_tool 以下にあるもの
  - assetsへのコピースクリプトは書いていない
