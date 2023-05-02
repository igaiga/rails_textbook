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
