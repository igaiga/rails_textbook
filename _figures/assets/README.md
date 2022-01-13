## _figures/assets

- HTML/CSS で修正可能な図。
- サーバ起動せずとも HTML/CSS はそのまま静的なファイルとして読み込めます。
- figure-sample.html がマスターデータ一覧になっています。
- スタイルシートは scss ディレクトリ→ gulp でコンパイル→ css ディレクトリに保存
- css/style.cssをhtmlで読み込むようにしています。

### スタイルシートを追記修正する場合

Node.js と gulp をつかいます

gulp-cliをグローバルインストール

```
$ npm install -g gulp-cli
```

rails_textbookの_figures/assetsに移動し、（初回のみ）package.jsonに書かれたパッケージのインストール

```
$ cd rails_textbook/_figures/assets
$ npm install
```

（毎回） gulp を起動しscssファイルの変更を監視してcssに変換してくれます。

```
$ gulp
```

### scssディレクトリの構造

scss/ 

- common/  スタイルの基本的な部分の調整
- item/  パーツごとのスタイルの調整
- lib/  他からもらってきたスタイル
- _mixin.scss  いろいろまとめて include として使えるスタイル
- _variables.scss  色などの変数
- style.scss  すべてのscssを読み込むファイル

※ font-awesome や ress（リセットcss）は gulp 側で CSS 変換時に読み込むようにしています
（わかりづらいので後で変更するかもしれないです）

### 判別方法

部品のクラス名と item 内のファイル分けは対応するようになっています。
目印はクラス名のアンダーバー2つで区切った前側の部分です。

例：
class="files__item" なら、item/_item.scss に記述
class="box__flex-column" なら、item/_box.scss に記述

スタイルの追記が必要な場合にファイル分けがよくわからんという場合は、scss/style.scss の下に追記 or 声かけてください:pray:
