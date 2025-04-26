# 新しいRuby, Railsでの動作確認

- 対象バージョンのRubyとRailsを実行可能にする
- 後述のサンプルアプリの生成とスクリーンショット作成のスクリプトコードを実行すればSystem specで動作確認できる
  - _figures/scripts/screenshots/helloworld/generate_helloworld.sh
  - _figures/scripts/screenshots/books_app/generate_books_app.sh
- エラーが出ないことを確認
- スクリーンショットが正しくできていることを確認

# サンプルアプリとスクリーンショットの生成

- _figures/scripts
  - サンプルアプリを生成して、スクリーンショットを作成するコード群の置き場
- 事前に生成したいバージョンのRubyとRailsを実行可能にしておく
- helloworld サンプルアプリの生成とスクリーンショット作成のスクリプトコード
  - $ cd _figures/scripts/screenshots/helloworld
  - ./generate_helloworld.sh
  - 生成されたスクリーンショットは、最後に実行するreplace_png.rbでassetsフォルダ以下へコピーされる
- books_app サンプルアプリの生成とスクリーンショット作成のスクリプトコード
  - $ cd _figures/scripts/screenshots/books_app
  - ./generate_books_app.sh
  - 生成されたスクリーンショットは、最後に実行するreplacer.rbでassetsフォルダ以下へコピーされる
- この作業の結果、サンプルコードも作成されるので、できあがった以下のフォルダをサンプルコード用リポジトリへ置く
  - helloworld: _figures/scripts/screenshots/helloworld/helloworld
  - books_app: _figures/scripts/screenshots/books_app/books_app
  - サンプルコードリポジトリ: https://github.com/igaiga/rails_textbook_sample

# Docked Rails CLI用動作確認

- 上記のスクリーンショット作成スクリプトコードから動作させる部分だけ抜き出してDocked Rails CLIで動く用に修正
- helloworld: _figures/scripts/screenshots/helloworld/docked_rails_cli_generate_helloworld.sh
- books_app: _figures/scripts/screenshots/books_app/docked_rails_cli_generate_books_app.sh

# 書籍内で利用している画像の説明

生成方法によって何種類かの画像ファイルがあります。_figures/assets/README.mdも参照。

- HTMLからレンダリングしたファイル
  - _figures/aseets/ 以下のフォルダにhtmlファイルがあるもの
  - _figures/assets/README.mdも参照
  - レンダリングスクリプトは _figures/scripts/html_figures/ 以下
    - $ cd _figures/scripts/html_figures
    - $ ./all_run.sh
- Adobe Illustrator で作成した変更されないファイル
  - _figures/aseets/ 以下のフォルダに画像がそのまま置いてあるもの
  - assetsへのコピースクリプトは書いていない
- アプリで撮影したスクリーンショット
  - レンダリングスクリプトは _figures/scripts/screenshots 以下
    - helloworld
      - $ cd _figures/scripts/screenshots/helloworld
      - $ ./generate_helloworld.sh
    - books_app
      - $ cd _figures/scripts/screenshots/books_app
      - $ ./generate_books_app.sh
- chrome_dev_toolのスクリーンショットを加工したもの
  - _figures/chrome_dev_tool 以下にあるもの
  - assetsへのコピースクリプトは書いていない
- 表紙
  - _figures/covers/rails_textbook_cover_omote.png
  - _figures/covers/rails_textbook_cover_ura.png
  - _figures/covers/rails_textbook_cover_ura.pdf
    - 同名のpngをPDF化したもの
    - Re:VIEW で結合するときにpngよりもPDFの方がかんたんなため
