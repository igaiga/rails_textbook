# Railsの教科書

## サンプルコード
- https://github.com/igaiga/rails_textbook_sample/

## 電子書籍版: 達人出版会
- https://tatsu-zine.com/books/rails-textbook

## 紙書籍版: BOOTH
- https://igaigarb.booth.pm/items/1848429

## 誤記などの報告方法
- 以下のコントリビュートポリシーにご同意いただいて、IssuesまたはPull requestsを作成いただくか、igaigaまでご連絡ください。
- 文章は `_posts/*.md` ファイルに書かれています。Pull requestsを作成するときはこちらのファイル群を修正してください。

## コントリビュートポリシー
- ご報告、コントリビュートいただきありがとうございます。本資料は有償の書籍、資料として利用されております。ご了承の上コントリビュートいただければと思います。

## 利用可能範囲
- 私的な利用、および公的な学校、コミュニティでの利用はOKです。
- 商用での利用については許可していませんが、別途有償ライセンスの準備がありますので [igaiga](https://github.com/igaiga) へご連絡ください。

# 正誤表
## 2020年2月29日 技術書典8 v2.0.0
### Page.100 7.1 画像情報を格納するための DB カラムを追加
後ろから2つ目の文「pictureカラム」であるところが「authorカラム」となっている
- 誤: books テーブルへ author カラムを string 型で追加する
- 正: books テーブルへ picture カラムを string 型で追加する

# サンプルコード生成

- 本体リポジトリ: https://github.com/igaiga/rails_textbook
  - サンプルコード生成スクリプトは本体側に置いてある
- サンプルコードリポジトリ: https://github.com/igaiga/rails_textbook_sample/

# 各種スクリプト群

- rails_textbook/_figures/scripts/screenshots 以下のスクリーンショット用スクリプトを動かす
  - 事前に生成したいバージョンのRubyとRailsを実行可能にしておく
    - サンプルコードが作成されるのでそれをサンプルコード用リポジトリへ置く
  - rails_textbook/_figures/scripts/screenshots/helloworld/generate_helloworld.sh
  - rails_textbook/_figures/scripts/screenshots/books_app/generate_books_app.sh
    - books_appはauthorとcarrierwaveまで込みでスクリプトで作成してくれる

# 書籍内で利用している画像の説明

生成方法によって何種類かの画像ファイルがあります。

- HTMLからレンダリングしたファイル
  - _figures/aseets/ 以下のフォルダにhtmlファイルがあるもの
  - レンダリングスクリプトは _figures/scripts/html_figures 以下
- Adobe Illustrator で作成した変更されないファイル
  - _figures/aseets/ 以下のフォルダに画像がそのまま置いてあるもの
  - assetsへのコピースクリプトは書いていない
- アプリで撮影したスクリーンショット
  - レンダリングスクリプトは _figures/scripts/screenshots 以下
- chrome_dev_toolのスクリーンショットを加工したもの
  - _figures/chrome_dev_tool 以下にあるもの
  - assetsへのコピースクリプトは書いていない
- 表紙
  - _figures/covers/rails_textbook_cover.png

# ReVIEW

- [ReVIEW Starter](https://kauplan.org/reviewstarter/) を利用しています
- _reviewフォルダ以下に関連ファイル群が置かれています

# HTML

## jekyllを利用してローカルで閲覧
- $ git clone https://github.com/igaiga/rails_textbook.git
- $ cd rails_textbook
- $ bundle install
- $ jekyll serve --watch --baseurl ''
- http://localhost:4000/rails_textbook/ へアクセス

# textlint

文章をチェックするためにtextlintが利用可能です。

## コマンドラインでの実行

- $ `npm i textlint`   # textlintのインストール
- $ `npm test`         # 文章全体のチェック
- $ `npm run textlint _posts/2014-04-01-preface.md`  # 単独のファイルをチェック
