# 新しいRuby, Railsでの動作確認

- 対象バージョンのRubyとRailsを実行可能にする
- 後述のサンプルアプリの生成とスクリーンショット作成のスクリプトコードを実行すればSystem specで動作確認できる
  - rails_textbook/_figures/scripts/screenshots/helloworld/generate_helloworld.sh
  - rails_textbook/_figures/scripts/screenshots/books_app/generate_books_app.sh
- エラーが出ないことを確認
- スクリーンショットが正しくできていることを確認

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
  - _figures/covers/rails_textbook_cover_ura.pdf
    - 同名のpngをPDF化したもの
    - Re:VIEW で結合するときにpngよりもPDFの方がかんたんなため

# ReVIEW

## 概要

- https://github.com/vvakame/docker-review を利用しています
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
  - 現状のbin以下にあるスクリプトは、Re:VIEWだけコンテナで実行し、他のスクリプトはネイティブで実行します
- Docker環境が必要です
- Acrobat Reader で表示してエラーが出ないことを確認してください

### build_pdf.sh カラー版PDF作成（電子書籍向け）

- スクリプトファイル群を実行して必要なファイルを収集してPDFを作成します
- _reviewフォルダで実行
- $ _review/bin/build_pdf.sh

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
