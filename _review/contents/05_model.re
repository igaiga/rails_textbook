
= モデル


この章ではデータの長期保存と、その際に使うモデルについて説明します。



説明に使うアプリは前の章でつくったものを引き続き使います。


== データの永続化


コード中で変数に代入したデータは、変数の有効範囲（スコープと言います）が終わると消えてしまいます。次のコードを見てみましょう。


//emlist[][ruby]{
def print_hello_world
  x = "Hello world!"
  puts x
end
//}


ここでの変数xのように、@などの記号が変数名の先頭についていない変数をローカル変数と呼びます。変数xの有効範囲（スコープ）は、そのメソッドの中だけです。この場合、メソッド@<tt>{print_hello_world}の実行が終わると変数xと、それが指すオブジェクトは消えてしまいます。



別の種類の変数として、前の章でも出てきた@bookのようなインスタンス変数（名前が@はじまりの変数）があります。インスタンス変数は、インスタンス（オブジェクト）がなくなると一緒に消えます。Railsの場合、@bookのようなコントローラのアクションで代入したインスタンス変数は、1つのリクエスト内が有効範囲だと考えることができます。おおまかには、あるページをブラウザで表示することが1回のリクエストだと考えて差し支えありません。別のページを表示したり、リロードを行ったりすると、新しい別のリクエストになります。コントローラのアクションでインスタンス変数に代入すると、コントローラからビューまで使うことができますが、その後なくなります。



それでも、つくったRailsアプリでは別のリクエストでも情報が見れますよね？　新規入力画面で情報を入力して一度登録してしまえば、その後ブラウザから何回アクセスしても、たとえば一覧画面で何回リロードしても表示されます。



つまり、複数のリクエストに渡ってデータが保存されていることになります。これはさきほどのインスタンス変数では実現できません。データがずっと残っているのは「データを保存する」仕事をしている「何かの仕組み」があるからなのです。



その仕組みがこの章の主役、モデル（Model）です。



この章はモデルについて説明します。また、この章では前の章につづいてCRUDのcreateの部分を題材に説明します。



//image[crud_create][この章の題材]{
//}




処理の流れはこの部分です。前の章でコントローラの処理の途中まで説明したので、そのつづきになります。



//image[create_flow_controller][処理の流れ]{
//}




コードではこの部分です。



app/controllers/books_controller.rb


//emlist[][ruby]{
@book = Book.new(book_params) # ⬅1. リクエストのパラメータを使って本のデータを作る

respond_to do |format|
  if @book.save # ⬅2. 本のデータを保存する
    # ⬅3a. 成功したらshow画面へ
    format.html { redirect_to book_url(@book), notice: "Book was successfully created." }
    format.json { render :show, status: :created, location: @book }
  else
    # ⬅3b. 保存失敗したらnew画面へ（元の画面）
    format.html { render :new, status: :unprocessable_entity }
    format.json { render json: @book.errors, status: :unprocessable_entity }
  end
end
//}


このコードの中で、モデルを利用しているところはこの部分です。


//emlist[][ruby]{
def create
  @book = Book.new(book_params) # ⬅BookクラスはModelという種族に属する
  respond_to do |format|
    if @book.save # ⬅ここで保存
      format.html { redirect_to book_url(@book), notice: "Book was successfully created." }
      format.json { render :show, status: :created, location: @book }
    else
      format.html { render :new, status: :unprocessable_entity }
      format.json { render json: @book.errors, status: :unprocessable_entity }
    end
  end
end
//}


では、モデルの仕事について見ていきましょう。


== モデルの基本的な使い方　その1　保存


モデルを使うとデータを保存することができます。以下の手順で保存できます。


//emlist[][ruby]{
book = Book.new(title: "RubyとRailsの学習ガイド", memo: "Rails関連技術地図とそれらの学習資料の紹介")
book.save!
//}


Book.newでBookモデルオブジェクトを作ります。このとき、タイトルとメモの情報を渡すことができます。Bookモデルオブジェクトはindexアクションでも出てた「本のデータを持ったオブジェクト」です。newメソッドの引数にタイトルとメモの情報を渡すことで、それらのデータを持つことができます。



なお、モデル名（モデルのクラス名）は英語の単数形、大文字始まりにするルールがあります。ここではBookがモデル名で、単数形で大文字始まりになっています。また、すべて小文字のbookは変数名です。1つのBookモデルオブジェクトが代入されるため単数形を使います。



Bookモデルオブジェクトのsave!メソッドを呼び出すと保存できます。保存するメソッドはいくつかあり、他にもsave, create!, createメソッドなどがあります。saveとsave!の違いは、なんらかの理由で保存できなかったときの動作です。保存に失敗したとき、saveメソッドはfalseを返し、save!メソッドでは例外が投げられます。createとcreate!の違いも同様です。saveメソッドとcreateメソッドの違いは、saveメソッドは既にモデルオブジェクトがあるときの保存につかうのに対して、createメソッドはモデルオブジェクトを新しくつくって保存するときにつかいます。


== モデルの基本的な使い方　その2　読み込み


さきほど保存したデータを読み込んでみましょう。


//emlist[][ruby]{
books = Book.all.to_a
//}


Book.allで保存されているBookモデルの全データを取得できます。以前に説明した一覧画面（indexアクション）でこのメソッドが使われています。



@<tt>{Book.all.to_a}でArray（配列）にBookオブジェクトが詰まって返ってきます。@<tt>{to_a}はArrayオブジェクトへ変換するメソッドです。代入される変数名は小文字のbooksで、複数のBookオブジェクトが代入されるので複数形を使います。


== モデルの基本的な使い方　その3　検索

//emlist[][ruby]{
book = Book.where(title: "RubyとRailsの学習ガイド").first
book.title #=> "RubyとRailsの学習ガイド"
book.memo #=> "Rails関連技術地図とそれらの学習資料の紹介"
//}


whereメソッドを使うと検索ができます。タイトルが"RubyとRailsの学習ガイド"であるBookオブジェクトが返ります。検索結果が複数になることもあるので、firstメソッドで最初の1つを取得しています。取得するオブジェクトは1つなので、それを代入する変数名bookは単数形になっています。



取得したBookオブジェクトはtitleメソッドでタイトルを、memoメソッドでメモをそれぞれ返します。


== 実習 : rails consoleでモデルを使う


Railsにはrails consoleという、1行ずつ入力したコードを実行する機能があります。Rubyが持っているirbをつかって、1行ずつ入力したRailsのコードを実行することができます。rails consoleを起動するには、ターミナルでつくったアプリがあるフォルダへ移動して、@<tt>{rails c}と実行します。cはconsoleの頭文字です。


//emlist[][console]{
cd books_app
rails c
//}

//emlist[][console]{
$ rails c
Loading development environment (Rails 8.0.2)
books-app(dev)>
//}


rails consoleで以下のコードを実行してみてください。


//emlist[][ruby]{
book = Book.new(title: "some title", memo: "some memo") # モデルオブジェクト作成
book.save! # 保存
Book.last # 上で保存したデータの表示
//}


前に出てきたwhereでの検索も試してみてください。rails consoleを終了するときはexitと打ってください。



また、rails consoleで保存したデータは、ブラウザで保存したデータと同じ場所に格納され、同じように取り扱われます。ここで保存したデータはブラウザからも見ることができます。rails serverを起動して、ブラウザで http://localhost:3000/books へアクセスして、rails consoleで保存したデータが表示されることを確認してみましょう。


== モデルの仕組み


次は、モデルのコードを見てみましょう。モデルのコードはapp/models/フォルダ以下にあります。Bookモデルのコード@<tt>{app/models/book.rb}を見てみましょう。


//emlist[][ruby]{
class Book < ApplicationRecord
end
//}


Bookモデルにはコードがほとんどありません。



では、saveやallといったメソッドが使えるのはなぜでしょうか？　また、titleやmemoの情報があることをどこで知るのでしょうか？


=== 問: saveやallといったメソッドが使えるのはなぜでしょうか？


答えは @<tt>{ApplicationRecord} クラスを継承しているからです。 @<tt>{ApplicationRecord} クラス（およびさらに親のクラス）がモデルの仕事に必要な機能を持っています。それを継承しているBookクラスも同じ機能を持ちます。


=== 問: titleやmemoといった要素があることをどこで知るのでしょうか？


答えは「データベース（DB）から情報を得る」です。



ApplicationRecordはデータベースから情報を得て、Bookモデルにtitle、memoという要素があることを知っています。その情報を使って、book.titleやbook.memoといったメソッドを提供します。



では、データベースとは何でしょうか？


=== データベース（DB）とは？


DBとは、データを保存したり、読み出したり、検索したりするために特化したプログラムです。



DBは高機能で堅牢、かつ高速です。しかし、DBへアクセスするには一般に専用の言語（SQLと言います）を用いるため、Rubyのコードからは扱いづらいという問題があります。モデルはDBを便利につかうための仕組みでもあり、RubyでDBを容易に扱うことができる機能も提供します。



//image[db][DBとは？]{
//}




では、DBはいつのまに作られたのでしょうか？


== DBはいつ作られたのか？


books appを作る一連のコマンドを入力した際に、以下のコマンドでDBを作成していました。


//emlist[][bash]{
$ rails g scaffold book title:string memo:text
$ rails db:migrate
//}


scaffoldコマンドはいろいろなものを作りますが、その1つとしてDBの設計書「マイグレーション（migration）ファイル」をつくります。


//emlist[][console]{
$ rails g scaffold book title:string memo:text
...
invoke  active_record
create    db/migrate/20211225013956_create_books.rb
create    app/models/book.rb
...
//}


そしてrails db:migrateコマンドを実行すると、さきほど作られた設計書を使ってDBを作ります。



設計書であるmigrationファイルから順に見ていきましょう。


== マイグレーション（migration）ファイル


DBの設計書をマイグレーションファイルと呼びます。マイグレーションファイルもRailsのコードで書かれています。



では、マイグレーションファイルを見てみましょう。ファイル名には"20211225013956"と実行した日付から作られた数字が入っているので、rails gコマンドを実行するごとに異なるファイル名になります。



@<tt>{db/migrate/20211225013956_create_books.rb}


//emlist[][ruby]{
class CreateBooks < ActiveRecord::Migration[8.0]
  def change
    create_table :books do |t|
      t.string :title
      t.text :memo

      t.timestamps
    end
  end
end
//}


1行目 @<tt>{ActiveRecord::Migration[8.0]} の末尾にある数字はRailsのバージョンを表します。Rails8.0.xではこのように8.0となります。



3行目 @<tt>{create_table :books} でbooksという名前のテーブルを作ります。DBはテーブルという単位でデータを管理します。ここでは、本に関するデータを保存するためにbooksという名前のテーブルを作っています。テーブル名はモデル名の複数形にするというルールがあります。



4行目 @<tt>{t.string :title} と5行目 @<tt>{t.text :memo} はテーブルの要素を作成しています。これでbooksテーブルにはtitleという要素と、memoという要素を持つことになります。この要素のことをDBの用語でカラムといいます。stringはデータの型の1つです。文字列を格納します。textもデータの型の1つで、stringよりも長い文字列を格納できる型です。



それに続く @<tt>{t.timestamps} は、@<tt>{created_at}（作成日時）、@<tt>{updated_at}（更新日時）を記録するカラムを作ります。



DBのテーブルはExcelをイメージすると分かり易いです。DBへデータを格納していくことは、title、memoといった列があるExcelのシートに1行ずつデータを格納していくイメージです。



//image[migration_excel][booksテーブルのイメージ]{
//}




ところで、 @<tt>{t.string :title} や @<tt>{t.text :memo} に見覚えがありませんか？



これらはscaffoldのコマンドで書かれていました。実は、scaffoldで指定していたのはテーブル名とカラム、データの型でした。scaffoldでは、booksテーブルにstring型であるtitleカラムとtext型であるmemoカラムを作成する、という指示を与えていたことになります。



ここまでで、scaffoldはDB設計書（migration）を作ることを説明しました。



//image[migration_created][scaffold は migration を作る]{
//}




では、migrationから実際にDBを作るにはどうすれば良いでしょうか？



//image[migration_how_to_make_db][migrationからDBを作るには？]{
//}




DB設計書（migration）からDBテーブルを作るのが @<tt>{rails db:migrate} コマンドです。 @<tt>{rails db:migrate}コマンドを実行すると、/db/migrateフォルダにあるマイグレーションファイルを実行してDBテーブルを作ります。



//image[migration_rails_db_migrate][rails db migrate コマンドがmigrationからDBを作る]{
//}



== 保存したあとの処理


それでは、コントローラでの処理の話に戻りましょう。@<tt>{@book.save} に関する動作を見て行きます。次のプログラム「2.本のデータを保存する」の部分です。



app/controllers/books_controller.rb


//emlist[][ruby]{
@book = Book.new(book_params) # ⬅1. リクエストのパラメータを使って本のデータを作る

respond_to do |format|
  if @book.save # ⬅2. 本のデータを保存する
    # ⬅3a. 成功したらshow画面へ
    format.html { redirect_to book_url(@book), notice: "Book was successfully created." }
    format.json { render :show, status: :created, location: @book }
  else
    # ⬅3b. 保存失敗したらnew画面へ（元の画面）
    format.html { render :new, status: :unprocessable_entity }
    format.json { render json: @book.errors, status: :unprocessable_entity }
  end
end
//}


長いので、着目するところだけ残して短くしましょう。まず、@<tt>{respond_to do |format|}はリクエストされたレスポンスの形式によって分岐させる文です。ブラウザでnew画面に内容を入力してリクエストを飛ばした場合は@<tt>{format.html}が選ばれます。もう一方のjsonはデータ形式の1つで、たとえばスマートフォンアプリなど、ブラウザ以外で表示させるときによく利用されます。HTMLだけに着目してformatの処理を取り除くと、次のようになります。


//emlist[][ruby]{
@book = Book.new(book_params)
if @book.save
  redirect_to @book, notice: 'Book was successfully created.'
else
  render :new, status: :unprocessable_entity
end
//}


@<tt>{@book.save}は成功するとtrue、失敗するとfalseを返します。 @<tt>{@book.save}の前に書いてあるifは分岐させる命令です。ifのあとに書かれた処理（ここでは@<tt>{@book.save}）がtrueのときはその後ろからelseまでを、falseのときはelse以降endまでを実行します。



@<tt>{@book.save}に成功するとtrueを返すので、@<tt>{redirect_to @book, notice: 'Book was successfully created.'}が実行されます。redirect_toはリダイレクト（新たにリクエストを発行して画面遷移させる）指示で、ここではshowアクションへのリクエストが発生します。保存した本の詳細ページ（BooksControllerのshowアクション）を表示します。後ろのnotice部は画面に表示させる文を設定しています。ブラウザでは次のような表示になります。



//image[books_created_data_1][リダイレクト後のshowアクション画面とnoticeの表示]{
//}




一方、@<tt>{@book.save}に失敗するとfalseを返すので、ifのelse節、@<tt>{render :new}が実行されます。renderはコントローラの次の処理であるビューを指定します。ここでは@<tt>{app/views/books/new.html.erb}がビューとして使われ、新規入力画面、つまり直前で入力していたページが表示されます。



ところで、saveメソッドが失敗するのはどんなときでしょうか？DBへの接続エラーなどのアクシデントで失敗することもありますが、モデルにある検証機能「バリデーション」を使って、想定外の入力に対して保存を失敗させることもあります。たとえば、数字を期待している郵便番号入力欄に想定外である数字以外の文字が入力されるようなケースは、バリデーションを実装することで保存を失敗させ、入力画面へ戻しユーザーに再入力を促すことができます。バリデーションについてはここでは説明しませんが、便利な機能なので @<href>{https://railsguides.jp/active_record_validations.html,Rails ガイド: Active Record バリデーション} などの説明を参考にしてみてください。


== まとめ

=== scaffoldで作られるmodel、migration


では、scaffoldで作られるmodel、migrationをまとめます。



scaffoldコマンドを実行すると、ファイルがつくられます。



//image[summary_scaffold_make_files][scaffoldコマンドがファイルを作る]{
//}




つづいてrails db:migrateコマンドを実行すると、DBがつくられます。



//image[summary_rails_db_migrate][rails db migrateコマンドがDBを作る]{
//}




できたモデルとDBをつかってアプリが動きます。



//image[summary_model_db][モデルとDBでアプリは動く]{
//}



=== モデルの使い方

//emlist[][ruby]{
book = Book.new(title: "RubyとRailsの学習ガイド",
                memo: "Rails関連技術地図とそれらの学習資料の紹介")
//}


Book.newでBookモデルオブジェクトを作ります。モデル名は大文字はじまりで、単数形にするルールがあります。引数でtitle、memoといった各カラムのデータを渡せます。


//emlist[][ruby]{
book.save
//}


saveメソッドを呼ぶと保存できます。成功するとtrueを、失敗するとfalseを返します。


//emlist[][ruby]{
books = Book.all.to_a
//}


Book.allでDBに保存されているBook Modelの全データを取得できます。Book.all.to_aを実行すると、ArrayにBookオブジェクトが詰まって返ってきます。


//emlist[][ruby]{
book = Book.where(title: "RubyとRailsの学習ガイド").first
book.title #=> "RubyとRailsの学習ガイド"
book.memo #=> "Rails関連技術地図とそれらの学習資料の紹介"
//}


whereメソッドを使うと検索ができます。タイトルが"RubyとRailsの学習ガイド"であるBookオブジェクトを取得します。取得したBookオブジェクトは、titleメソッドでタイトルを、memoメソッドでメモを返します。



ポイントをまとめると次のようになります。

 * DBはデータの保存、読み込み、検索に特化したプログラム
 * モデルはDBを便利に使うための道具。DBとモデルはセットで使われる
 * マイグレーション（migration）ファイルはDBを作るための設計書
 * rails db:migrateはマイグレーションファイルからDBを作るコマンド


== さらに学びたい場合は


モデルは多くの機能を持っています。RailsGuidesにもたくさんの説明ページがあります。上手に使うことで便利な機能をかんたんに作ることができるのです。

 * @<href>{https://railsguides.jp/active_record_basics.html,Rails ガイド: Active Record の基礎}
 ** モデルに関する詳しい説明です。
 * @<href>{https://railsguides.jp/active_record_migrations.html,Rails ガイド: Active Record マイグレーション}
 ** DBのマイグレーションに関する詳しい説明です。
 * @<href>{https://railsguides.jp/active_record_querying.html,Rails ガイド: Active Record クエリインターフェイス}
 ** モデルの中で、検索に関する詳しい説明です。
 * @<href>{https://railsguides.jp/active_record_validations.html,Rails ガイド: Active Record バリデーション}
 ** モデルには「バリデーション」と呼ばれる、値のチェック機能がついています。実際のアプリを作るときによく使う便利な機能なので、ぜひチャレンジしてみてください。
 * @<href>{https://railsguides.jp/association_basics.html,Rails ガイド: Active Record の関連付け}
 ** 複数のモデルを結び付ける「関連付け」の機能は強力でアプリを作るときによく利用します。ぜひチャレンジしてみてください。



また、発展的な内容を以降に書きますので、あわせて参考にしてみてください。


== 既存のDBテーブルにカラムを増やすには？


既存のDBテーブルにカラムを増やすにはどうすれば良いでしょうか？前につくったmigrationファイルを変更してもうまくいきません。各migrationファイルは1回だけ実行される仕組みなので、過去に実行されたmigrationファイルを変更しても、そのファイルは実行されないからです。そこで、新しいカラムを追加するには、新しいmigrationファイルをつくります。



rails gコマンドにmigrationを指定するとmigrationファイルだけを生成できます。たとえば、booksテーブルにstring型のauthorを加えるには以下のようにします（ファイル名中の"20220107022320"は実行するごとに異なります）。


//emlist[][bash]{
$ rails g migration AddAuthorToBooks author:string
//}

//emlist[][console]{
$ rails g migration AddAuthorToBooks author:string
invoke  active_record
create    db/migrate/20220107022320_add_author_to_books.rb
//}


rails g migrationコマンドの基本形は以下になります。


//emlist[][bash]{
$ rails g migration Addカラム名Toテーブル名 カラム名:型名
//}


作成されたmigrationファイルは以下のようになっています。


//emlist{
20220107022320_add_author_to_books.rb
//}

//emlist[][ruby]{
class AddAuthorToBooks < ActiveRecord::Migration[8.0]
  def change
    add_column :books, :author, :string
  end
end
//}


生成されたmigrationファイルには、booksテーブルへauthorカラムをstring型で追加する指示が書かれています。



migrationファイルを作成したら、@<tt>{rails db:migrate}コマンドでDBへ内容を反映します。


//emlist[][bash]{
$ rails db:migrate
//}

//emlist[][console]{
== 20220107022320 AddAuthorToBooks: migrating =================================
-- add_column(:books, :author, :string)
   -> 0.0007s
== 20220107022320 AddAuthorToBooks: migrated (0.0007s) ========================
//}


これで、DBのbooksテーブルへauthorカラムが追加されました。



ここまでの作業をまとめると、以下のようになります。



//image[migration_new_column_author][booksテーブルにstring型のauthorを加えるmigration]{
//}




ちなみに、Railsのgenerate機能は開発をアシストする機能なので、使わないで0から手でコードを書いても同様に動きます。つまり、rails gを使ってファイルを自動生成してから変更しても、0から手でコードを書いても、どちらも同じ結果になります。他のrails gコマンド、scaffoldやcontrollerなどもすべて同様です。


== 新しいモデルとmigrationを一緒に作るには？


rails gコマンドにmodelを指定するとmodelとmigrationを生成できます。


//emlist[][ruby]{
rails g model book title:string memo:text
//}

//emlist[][console]{
db/migrate/20220107022320_add_author_to_books.rb
app/models/book.rb
//}

== rails gコマンドまとめ


rails gコマンドの一覧をまとめます。



rails g migration: migration


//emlist[][bash]{
$ rails g migration AddAuthorToBooks author:string
//}


rails g model: model + migration


//emlist[][bash]{
$ rails g model book title:string memo:text
//}


rails g controller: routes + controller + view


//emlist[][bash]{
$ rails g controller books index
//}


rails g scaffold: model + migration + routes + controller + view


//emlist[][bash]{
$ rails g scaffold book title:string memo:text
//}

== scaffoldでつくった既存テーブルへカラムを追加するには？


すでにあるbooksテーブルにstring型のauthorを加えて、ブラウザから入力できるようにしてみましょう。


==== booksテーブルにstring型のauthorを加える

//emlist[][bash]{
$ rails g migration AddAuthorToBooks author:string
//}

//emlist[][console]{
$ rails g migration AddAuthorToBooks author:string
invoke  active_record
create    db/migrate/20220107022320_add_author_to_books.rb
//}


作成されたファイルは以下のようになっています。



@<tt>{db/migrate/20220107022320_add_author_to_books.rb}


//emlist[][ruby]{
class AddAuthorToBooks < ActiveRecord::Migration[8.0]
  def change
    add_column :books, :author, :string
  end
end
//}

==== migrationからDBを作る

//emlist[][bash]{
$ rails db:migrate
//}

//emlist[][console]{
== 20220107022320 AddAuthorToBooks: migrating =================================
-- add_column(:books, :author, :string)
   -> 0.0007s
== 20220107022320 AddAuthorToBooks: migrated (0.0007s) ========================
//}

==== フォームパーシャルビューファイルを修正


@<tt>{app/views/books/_form.html.erb}


//emlist[][diff]{
<%= form_with(model: book) do |form| %>
...
  <div>
    <%= form.label :title, style: "display: block" %>
    <%= form.text_field :title %>
  </div>

  <div>
    <%= form.label :memo, style: "display: block" %>
    <%= form.textarea :memo %>
  </div>

+  <div>
+    <%= form.label :author, style: "display: block"  %>
+    <%= form.text_field :author %>
+  </div>

  <div>
    <%= form.submit %>
  </div>
<% end %>
//}

==== 詳細表示画面のビューファイルを修正


@<tt>{app/views/books/_book.html.erb}


//emlist[][diff]{
<div id="<%= dom_id book %>">
  <p>
    <strong>Title:</strong>
    <%= book.title %>
  </p>

  <p>
    <strong>Memo:</strong>
    <%= book.memo %>
  </p>

+<p>
+  <strong>Author:</strong>
+  <%= book.author %>
+</p>

</div>
//}

==== controllerを修正


StrongParametersにauthorを追加します。



@<tt>{app/controllers/books_controller.rb}


//emlist[][diff]{
class BooksController < ApplicationController
...
    def book_params
-      params.expect(book: [ :title, :memo ])
+      params.expect(book: [ :title, :memo, :author ])
    end
end
//}

==== 動作確認


rails serverを起動して動作を確認してみましょう。new、show、indexの各画面にAuthor欄が追加されて、登録できるようになりました。



//image[books_with_author_new][新規入力画面]{
//}


