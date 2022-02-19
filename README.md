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

## ライセンスと利用可能範囲
- 私的な利用、および公的な学校、コミュニティでの利用はOKです。
- 商用での利用については許可していませんが、別途有償ライセンスの準備がありますので [igaiga](https://github.com/igaiga) へご連絡ください。

# 正誤表
## 2020年2月29日 技術書典8 v2.0.0
### Page.100 7.1 画像情報を格納するための DB カラムを追加
後ろから2つ目の文「pictureカラム」であるところが「authorカラム」となっている
- 誤: books テーブルへ author カラムを string 型で追加する
- 正: books テーブルへ picture カラムを string 型で追加する

# サンプルアプリとスクリーンショットの生成

- rails_textbook/_figures/scripts
  - サンプルアプリを生成して、スクリーンショットを作成するコード群の置き場
  - 事前に生成したいバージョンのRubyとRailsを実行可能にしておく
  - helloworld サンプルアプリの生成とスクリーンショット作成のスクリプトコード
    - rails_textbook/_figures/scripts/screenshots/helloworld/generate_helloworld.sh
    - 生成されたスクリーンショットは、最後に実行するreplace_png.rbでassetsフォルダ以下へコピーされる
  - books_app サンプルアプリの生成とスクリーンショット作成のスクリプトコード
    - rails_textbook/_figures/scripts/screenshots/books_app/generate_books_app.sh
    - 生成されたスクリーンショットは、最後に実行するreplacer.rbでassetsフォルダ以下へコピーされる
  - この作業の結果、サンプルコードも作成されるので、できあがったコードをサンプルコード用リポジトリへ置く
    - https://github.com/igaiga/rails_textbook_sample

# 新しいRuby, Railsでの動作確認

- 対象バージョンのRubyとRailsを実行可能にする
- 上記のサンプルアプリの生成とスクリーンショット作成のスクリプトコードを実行すればSystem specで動作確認できる
  - rails_textbook/_figures/scripts/screenshots/helloworld/generate_helloworld.sh
  - rails_textbook/_figures/scripts/screenshots/books_app/generate_books_app.sh
- エラーが出ないことを確認
- スクリーンショットが正しくできていることを確認

# 書籍内で利用している画像の説明

生成方法によって何種類かの画像ファイルがあります。_figures/assets/README.mdも参照。

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
  - _figures/covers/rails_textbook_cover_omote.png
  - _figures/covers/rails_textbook_cover_ura.png

# ReVIEW

## 概要

- [ReVIEW Starter](https://kauplan.org/reviewstarter/) を利用しています
- _reviewフォルダ以下に関連ファイル群が置かれています
- _review/binフォルダ以下に生成に関するスクリプト群が置かれています
- bin/build_pdf.shなどを実行したときに以下のファイル群が生成または配置されます
  - _review/contents reファイル置き場
    - bin/md_to_re.shでmd2review gemのコマンドをつかって_postsフォルダのmdから変換します
  - _review/images 画像ファイル置き場
    - bin/copy_images.shでassetsフォルダからコピーされます

## PDFの作り方

### カラーモノクロ共通作業

- _reviewフォルダ以下に.ruby_version, Gemfile, Gemfile.lockが置いてあるので、_reviewフォルダでbundle installを実行してください
- docker環境が必要です
- 最後に余分なページが入るので、macOSのプレビューアプリなどで削除する
- Acrobat Reader で表示してエラーが出ないことを確認する

### build_pdf.sh カラー版PDF作成（電子書籍向け）

- スクリプトファイル群を実行して必要なファイルを収集してPDFを作成します
- _reviewフォルダで実行
- $ bin/build_pdf.sh

### build_pdf_for_print.sh モノクロ版PDF作成（印刷書向け）

- build_pdf.shの書籍印刷用モノクロ版で、ノンブル（通し番号）が付きます。
- _reviewフォルダで実行
- $ bin/build_pdf_for_print.sh

## 内部でつかっているスクリプト群

### change_images_gray.rb

- カラー画像をモノクロ化

### copy_images.sh

- ReVIEWで必要な画像ファイル群をimagesフォルダ以下へコピー

### md_to_re.sh

- .mdから.reへ変換してcontentsフォルダへ配置するスクリプト

# textlint

文章をチェックするためにtextlintが利用可能です。

## コマンドラインでの実行

- $ `npm i textlint`   # textlintのインストール
- $ `npm test`         # 文章全体のチェック
- $ `npm run textlint _posts/01_preface.md`  # 単独のファイルをチェック
