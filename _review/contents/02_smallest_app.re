
= 一番小さなRailsアプリづくり


ここではできるだけ小さい構成のRailsアプリを作ってみます。Railsアプリがどのように動作するのかの説明と、Railsによって作られたファイルがどのような役割なのか、機能と関連づけて説明していきます。


== 一番小さなRailsアプリをつくる

=== アプリの作成とWelcome画面


まずはターミナルを起動して、以下のコマンドを打ってみましょう。先頭の$マークはターミナルを表す印です。入力はしないでください。


//emlist[][bash]{
$ mkdir my_web_apps
$ cd my_web_apps
//}


mkdirはフォルダを作成するコマンド、cdはターミナル内で現在のフォルダを移動するコマンドです。Windowsで普段使いなれている「コンピューター（エクスプローラー）」を起動するには、ターミナルで@<tt>{explorer .}と打つと現在のフォルダを開くことができます。MacでFinderを開くにはターミナルから@<tt>{open .}と打ちます。mkdirコマンドで作成したフォルダが存在することを確認できます。フォルダはターミナルからとエクスプローラー（MacではFinder）からとどちらから作成しても違いはないので、どちらでも問題ありません。



それでは、アプリを作りましょう。最初に作るのは、ブラウザに"Hello world!"と表示させるアプリです。先ほど作成したフォルダ @<tt>{my_web_apps} の下に新しいアプリを作ってみましょう。ターミナルを起動して以下のコマンドを打ちます。


//emlist[][bash]{
$ rails new helloworld
//}


実行には少し時間がかかります。たくさんのメッセージが表示されます。


//emlist[][console]{
$ rails new helloworld
      create
      create  README.md
      create  Rakefile
 ...（略）
append  config/importmap.rb
//}


ターミナルの画面にこのように"append  config/importmap.rb"と表示されれば成功です。rails newコマンドはたくさんのフォルダとファイルを自動で作ります。rails newコマンドでやっていることはこの後のコラムで説明します。



もしもエラーなどでrails newコマンドが中断されたあとでリトライしたいときには、アプリのフォルダ、ここではhelloworldフォルダを削除してからもう一度実行してみてください。フォルダが残っていると問題が発生することがあります。



次は以下のコマンドを実行してみてください。@<tt>{rails s}コマンドはwebサーバを起動するコマンドで、sはserverの略です。省略したsでも、省略せずにserverでも、同じように動作します。


//emlist[][bash]{
$ cd helloworld
$ rails s
//}


うまく動作している場合は、以下のような表示になります。メッセージ中にあるバージョンの数字は異なる場合があります。


//emlist[][console]{
$ rails s
=> Booting Puma
=> Rails 7.0.1 application starting in development
=> Run `bin/rails server --help` for more startup options
Puma starting in single mode...
* Puma version: 5.5.2 (ruby 3.1.0-p0) ("Zawgyi")
*  Min threads: 5
*  Max threads: 5
*  Environment: development
*          PID: 9794
* Listening on http://127.0.0.1:3000
* Listening on http://[::1]:3000
Use Ctrl-C to stop
//}


では、ブラウザを起動して以下のURLを入力してアクセスしてみましょう。

 * http://localhost:3000



//image[welcome_rails][RAILS画面]{
//}




これは、Railsが起動し、あなたのブラウザからのリクエストを受け付けて、表示している画面です。ここまでのわずかな手順で、ブラウザでページを表示する機能を持つWebアプリをつくることができました。


=== コラム: @<tt>{rails new} コマンドでやっていること


rails newコマンドを実行すると、たくさんのメッセージが表示されました。このとき、何が行われているのでしょうか。最初に、Railsアプリとして動作するのに必要なファイルとフォルダを作成します。次に、利用するGemライブラリ（Rubyの便利なプログラム集）をダウンロードして利用可能にします。つづいて、JavaScriptのライブラリを利用可能にします。



rails newコマンドがエラーで中断されたときには、表示されるエラーメッセージを手がかりに問題を解決する必要がありますが、そのときにこれらの知識も役に立つかもしれません。また、rails newコマンドがエラーで中断したあとにリトライしたいときは、これらの処理が途中のどこかで止まっていることがあるので、アプリのフォルダを削除してからもう一度実行してみてください。


=== rails gコマンドでページを作る


ひきつづき、以下のコマンドを入力してみましょう。rails serverが起動している場合は、Ctrl-c（controlキーを押しながらcキー）で終了してからコマンドを打ってください。


//emlist[][bash]{
$ rails g controller hello index
//}

//emlist[][console]{
$ rails g controller hello index
      create  app/controllers/hello_controller.rb
       route  get 'hello/index'
      invoke  erb
      create    app/views/hello
      create    app/views/hello/index.html.erb
      invoke  test_unit
      create    test/controllers/hello_controller_test.rb
      invoke  helper
      create    app/helpers/hello_helper.rb
      invoke    test_unit
//}


もしもrails gコマンドを打ち間違えて違うファイルをつくってしまったときは、打ち間違えたコマンドのgの部分をdにして再実行すると、rails gコマンドで作成したファイルをまとめて削除してくれます。たとえば、@<tt>{rails g controller hell index} とhelloをhellと打ち間違えた場合は、@<tt>{rails d controller hell index} コマンドを実行することで間違えてつくったファイル群を削除することができます。ターミナルでカーソルキーの↑キーを押すと、さきほど入力した内容が出てくるので、それを利用してgをdに直すと楽に実行できます。dはdestroyの略です。



再びrails serverを起動させましょう。


//emlist[][bash]{
$ rails s
//}

//emlist[][console]{
$ rails s
=> Booting Puma
...（略）
* Listening on http://127.0.0.1:3000
* Listening on http://[::1]:3000
Use Ctrl-C to stop
//}


ブラウザを使い、以下のURLへアクセスします。

 * http://localhost:3000/hello/index



//image[hello_index][hello/index]{
//}




この画面が出れば、ここまで意図通りに動作しています。さきほど実行したrails gコマンドはこのページ、/hello/indexを作るものでした。どのような仕組みで動作しているかは後ほどまた説明しますので、今はこのページに"Hello world!"と表示させてみることにしましょう。



@<tt>{app/views/hello/index.html.erb} ファイルをエディタで開いてみてください。以下のような内容になっています。


//emlist[][erb]{
<h1>Hello#index</h1>
<p>Find me in app/views/hello/index.html.erb</p>
//}


これを以下のように変更して、ブラウザで同じURLへアクセスしてみてください。-の行を削除して、+の行を追加してください。先頭の-や+は入力しません。（rails sは起動したままで大丈夫です。もしもrails sを一度終了していた場合は、rails sコマンドでもう一度起動してからアクセスしてください）。


//emlist[][diff]{
- <h1>Hello#index</h1>
- <p>Find me in app/views/hello/index.html.erb</p>
+ <p>Hello world!</p>
//}


//image[hello_world][Hello world]{
//}




"Hello world!"の文字が表示されましたか？これで一番小さなRailsアプリができあがりました。ここへ、少しだけRubyのコードを書いて、現在時刻を表示する機能を追加してみましょう。以下のように、+の行を追加してください。


//emlist[][diff]{
<p>Hello world!</p>
+ <p>現在時刻: <%= Time.current %></p>
//}


//image[time_utc][現在時刻表示]{
//}




表示されましたか？ブラウザをリロードすると、現在時刻が更新される、アクセスしたそのときの時刻が表示されるアプリになりました。



ところで、現在時刻が9時間ずれていると思われた方もいるかと思います。これは異なるタイムゾーンで表示されているためです。この時刻はUTCタイムゾーンでの時刻です。UTCは協定世界時と呼ばれ、基準となるタイムゾーンとして使われています。日本での時刻はUTCよりも9時間早い時刻になります。プログラムを書き換えて、日本時間での現在時刻を表示させてみましょう。


//emlist[][diff]{
- <p>現在時刻: <%= Time.current %></p>
+ <p>現在時刻: <%= Time.current.in_time_zone('Asia/Tokyo') %></p>
//}


//image[time_jst][現在時刻表示]{
//}




最後に、このままでもいいのですが、コードのロジックの部分をビューに書くのではなく、コントローラで書くことにしましょう。動作は同じまま、コードを書き換えます。



コントローラを次のように変更します。



@<tt>{app/controllers/hello_controller.rb}


//emlist[][diff]{
class HelloController < ApplicationController
  def index
+   @time = Time.current.in_time_zone('Asia/Tokyo')
  end
end
//}


そして、ビューを変更します。



@<tt>{app/views/hello/index.html.erb}


//emlist[][diff]{
- <p>現在時刻: <%= Time.current.in_time_zone('Asia/Tokyo') %></p>
+ <p>現在時刻: <%= @time %></p>
//}


これでブラウザからアクセスすると、先ほどと同じように現在時刻が表示されているかと思います。



次の節から、このアプリがどのように動作しているのかを説明していきます。


=== コラム: タイムゾーンの設定


今回の @<tt>{Time.current.in_time_zone('Asia/Tokyo')} はこの場所で使う時刻だけを日本時間へ変更しました。この方法のほかに、アプリ全体でタイムゾーンを日本時間に設定する方法もあります。その場合はconfig/application.rbファイル中に @<tt>{config.time_zone = 'Asia/Tokyo'} と設定します。この方法の利点は、プログラムの中のあちこちで @<tt>{in_time_zone('Asia/Tokyo')} を書かずに済み、config/application.rbファイルの1カ所にまとめることができることです。


== Webアプリはどのように動作しているか


ここで、普段ブラウザからつかっているWebアプリがどのように動作しているかを見てみましょう。アドレス入力欄にURLを入力してエンターキーを押すと、「リクエスト」がURL先のサーバへ向けて飛んでいきます。たとえば @<tt>{https://cookpad.com/} と入力した場合は、クックパッドのサーバへ向けてリクエストが飛んでいきます。リクエストは追って説明していきますが、ざっくりと「そのページを見たいという要求（リクエスト）」とイメージしてもらえばOKです。



//image[request][リクエスト]{
//}




Webサーバ上で動作しているWebアプリはリクエストを受け取ると、「レスポンス」としてHTMLで書かれたテキストを作ってブラウザへ返します。レスポンスは「Webアプリが返してきた情報群（HTMLで書かれた表示するための情報を含む）」とイメージできます。



//image[response][レスポンス]{
//}




ブラウザはHTMLを解釈して、私たちにとって見やすい、いつも見慣れたWebページを表示します。HTMLはHyperText Markup Languageのことで、Webページを記述するための言語です。



//image[result][HTMLを表示]{
//}




HTMLはブラウザからも見ることができます。Chromeの場合は、どこかのサイト（たとえば @<tt>{https://cookpad.com/}）へアクセスしたあと、右クリックメニューから「ページのソースを表示」を選ぶとHTMLで書かれたそのページを閲覧することができます。



//image[right_click][右クリック]{
//}




//image[html][HTML(抜粋)]{
//}




ここまでで説明した以下の2つが、ブラウザの主な仕事です。

 * リクエストをWebサーバへ投げる
 * レスポンスで返ってきたHTMLを解釈して表示する


=== コラム: Webサーバ


Webサーバとはなにものなのでしょうか？Webサーバは「Webサービスを提供する場合に必要な共通の機能を提供するもの」と言えます。Webアプリはブラウザとのやりとりで必要な機能のうち、どのサービスでも使う機能はWebサーバに仕事をまかせ、自分のサービスで必要なオリジナルな機能を提供することに注力します。Railsで開発するときにはpumaというWebサーバを利用する設定になっていて、@<tt>{rails s}を実行すると起動します。Webサービスを運用する場合は、nginxやApacheといった別の種類のWebサーバを組み合わせて使うことも多いです。


== インターネットの向こう側とこちら側


ブラウザからWebサービスにアクセスするとき、通常、Webアプリはインターネット上にあります。ブラウザだけが自分のPCにあります。



//image[internet_and_local][インターネット上のサービスにアクセス]{
//}




しかし、開発中は自分が作っているアプリをわざわざインターネット上へ置く必要はなく、自分のPCでWebアプリを動作させ、同じく自分のPCにあるブラウザからアクセス可能です。



//image[local][開発中は自分のPCでつくることができる]{
//}



== 今回つくったRailsアプリの動作まとめ


今回つくったRailsアプリの動作を図にすると次のようになります。



//image[smallest_app][今回つくったRailsアプリの動作]{
//}




ブラウザのURL欄にアドレスを入力してEnterを押すとリクエストが飛びます。リクエストを受け取ったRailsアプリはHTMLをつくり、レスポンスとして返します。レスポンスを受け取ったブラウザはHTMLを解釈し、画面に表示します。


== Railsでの開発の進め方


Railsでの基本的な開発の進め方は以下の2つを繰り返すサイクルになります。

 * ひな形になるファイル（ソースコードや設定ファイル）の生成
 * つくっているアプリ用にファイルを変更、追記



実は、さきほどつくったアプリもこの手順で進めていました。


//emlist[][bash]{
$ rails new helloworld
$ rails g controller hello index
//}


これらのコマンドは「ひな形になるファイルの生成」を行っていました。そのあと、@<tt>{app/views/hello/index.html.erb} を編集して、


//emlist[][erb]{
<p>Hello world!</p>
//}


という内容に変更しました。このように、rails gコマンドなどでひな形となるファイルを生成し、それをそのアプリで使いたい形へ変えていく、Railsアプリ開発ではこれを繰り返してつくっていきます。



rails gコマンドはひな形を作成しますが、場合によってはこの手順を飛ばして、ゼロから手で書いても構いません。どちらの手順をつかっても、アプリをつくることが可能です。多くの場合、rails gコマンドを使った方が、楽につくれたり、ミスをしづらくなるので便利です。


== Railsが生成するファイル

=== rails newコマンド


では、Railsはどのようなファイルを生成するのでしょうか。最初のrails newコマンドを実行したとき、以下のようにcreate ...という表示がずらっとされたと思います。railsが生成したファイルとフォルダの名前を表示していたのです。


//emlist[][console]{
$ rails new helloworld
create
create  README.md
create  Rakefile
... (略)
create  app
create  app/assets/config/manifest.js
create  app/assets/stylesheets/application.css
... (略)
//}


これらのファイル群によって、rails newをしただけで（何もコードを書かなくても）Webアプリとして動作します。たくさんのファイルがつくられていますね。Railsアプリの基本的なフォルダとファイル群を書いたものが次の図です。いきなりすべてを説明するのは難しいので、順番に説明していきます。役割ごとにフォルダが分かれていますが、それぞれの役割についてはこのあと説明していきます。



//image[rails_files][Railsアプリの基本的なフォルダ・ファイル群（一部抜粋）]{
//}



=== rails gコマンド


次に実行したrails gコマンドで作られたファイルを見てみましょう。


//emlist[][bash]{
$ rails g controller hello index
//}

//emlist[][console]{
$ rails g controller hello index
      create  app/controllers/hello_controller.rb
       route  get 'hello/index'
      invoke  erb
      create    app/views/hello
      create    app/views/hello/index.html.erb
      invoke  test_unit
      create    test/controllers/hello_controller_test.rb
      invoke  helper
      create    app/helpers/hello_helper.rb
      invoke    test_unit
//}


ここで実行したrails g controllerコマンドは、URLのパスが/hello/indexであるページを表示するためのファイル群を作ります。gはgenerateの略です。rails g controllerの後ろのhelloとindexが、生成するページのパスを指定していることが分かります。ほかにもいくつかのgenerateコマンドが用意されているので、またあとで説明します。もしも、コマンドを間違えて生成したファイルをまとめて削除したい場合は、gをdに替えたコマンドを実行すると、まとめて削除することができます。



ここで生成、追記されたファイルのうち、特に重要なのは以下の3つのファイルです。

 * app/controllers/hello_controller.rb
 * app/views/hello/index.html.erb
 * config/routes.rb



//image[rails_g_controller][rails g controller hello index コマンドで生成されるファイル]{
//}




これらのファイルがどのような働きをしているのかを、次の節でRailsがリクエストを受けてからレスポンスを返すまでの基本的な処理の順序を追いかけながら説明していきます。


== Railsアプリの処理の流れ


ブラウザからアクセスしたときに、Railsアプリはどのように動作しているのでしょうか？次の図は、今回つくったRailsアプリの動作を示したものです。前に出てきた動作の図から少し詳しくしています。



//image[rails_app_semantics][Railsアプリの動作]{
//}




ここでは、この図のRails Appの部分について詳しく説明していきます。対象箇所を抜き出したのが次の図です。



//image[rails_app_request_to_response][Railsアプリがリクエストを受けてレスポンスを返すまで]{
//}




リクエストを受けたRailsアプリは、Routes, Controller, Viewの3つのコードを通過します。それぞれの場所で処理を行い、レスポンスとしてHTMLを生成して返します。各所ではそれぞれ仕事の分担が決まっていて、自分の担当の処理を行います。Routes, Controller, Viewでそれぞれどのような処理が行われているのか、順に見ていきましょう。


=== Routes


Routesは「リクエストのURLとHTTPメソッド」に応じて次に処理を行う先を決めるのが仕事です。URLは前に出てきましたが、HTTPメソッドとは何でしょうか？

 * リクエスト
 ** URL : http://localhost:3000/hello/index
 ** HTTPメソッド：GET



リクエストを構成する要素のうち、重要なものがURLとHTTPメソッドです。URLはインターネット上の住所を表し、アクセスする先を指定するものです。もう一方のHTTPメソッドは、そのURLに対して「何をするか」を指示するものです。ブラウザのアドレス欄へURLを入力しEnterを押すと、HTTPメソッド "GET" でリクエストが飛びます。GETは「ページを取得する」指示です。GETのほかにもHTTPメソッドはいくつかあり、Railsアプリでよく使うものは4つです。GET以外のHTTPメソッドは次の章以降で説明していきます。



まとめると、リクエストは「URL」でアクセス先を、「HTTPメソッド」でなにをするかを指示します。



最初に、Routesは「リクエストのURLとHTTPメソッド」に応じて次に処理を行う先を決めるのが仕事だと書きました。RailsではRoutesの処理が終わると、次はコントローラのアクションへ処理が移ります。アクションとはコントローラに書かれているメソッドのうち、publicなメソッドのことです。「Routesから呼び出せるメソッド」と言っても良いでしょう。ここでのメソッドはRubyでのメソッドのことで、処理を集めて名前をつけたものです。HTTPメソッドとは別のものです。RoutesはリクエストのURLとHTTPメソッドから、処理の進み先であるコントローラのアクションを決定します。RoutesはリクエストとControllerのアクションとの対応表と言えます。



//image[routes_mapping][Routes]{
//}




では、対応表であるRoutes表を見て見ましょう。rails serverを起動させて @<tt>{/rails/info/routes} へアクセスしてみてください。Routes表の見方を説明したのが次の図です。



//image[routes][Routes表]{
//}




表中の "HTTP Verb" がHTTPメソッドです。"Path"（パス）はURLの後半部分に相当します。URLが"http://localhost:3000/hello/index"である場合、パスは"/hello/index"になります。(表示されたパスの後半部分の"(.:format)"は省略できる記述で、レスポンスで返すフォーマットを指定するための機能です。省略した場合はHTMLを返すのが普通です。)



右端の"Controller#Action"が処理の移るコントローラとアクションを示しています。ここでは "hello#index" と書かれていますが、#の左側がコントローラ名、右側がアクション名です。この場合は、「HelloControllerのindexアクション」を示しています。



この対応表を解釈すると、「リクエストのHTTPメソッドが"GET"、パスが"/hello/index"のとき、次の処理は"HelloController"の"index"アクションになる」となります。



ここで表示されたRoutesは@<tt>{config/routes.rb}ファイルから生成されています。このファイルには次のような記述があります。


//emlist[][ruby]{
get 'hello/index'
//}


これがRoutesのコード部分で、この1行からさきほど説明した対応表が生成されています。「パス"hello/index"へのGETでのアクセスでHelloControllerのindexアクションが呼ばれる」という文です。Routesの書き方はまた追って説明していきます。



Routesについてまとめると、「RoutesはリクエストのパスとHTTPメソッドによって次の処理先であるコントローラとアクションを決める対応表」となります。



それでは、次の処理が行われるコントローラをみてみましょう。


=== コントローラ


コントローラではさまざまな処理を行い、次のビューでつかうデータをつくって渡します。コントローラのファイルは@<tt>{app/controllers/}へ置きます。さきほどのRoutesで次の処理先として指定されたHelloControllerは、@<tt>{app/controller/hello_controller.rb} というファイルです。


//emlist[][ruby]{
class HelloController < ApplicationController
  def index
    @time = Time.current.in_time_zone('Asia/Tokyo')
  end
end
//}


HelloControllerのindexアクションが呼び出されます。@<tt>{def index}から@<tt>{end}までがindexアクションです。コントローラにあるpublicなメソッドをアクションと呼びます。アクションはRoutesから次の処理先として指示される可能性があります。



このindexアクションでは@<tt>{@time}というインスタンス変数に現在時刻を代入しています。アクションの中のプログラム、ここでは @<tt>{@time = Time.current.in_time_zone('Asia/Tokyo')} は、インデント（字下げ）されて書かれます。



変数は名札のようなもので、代入したものをあとから使えるように名前をつける仕組みです。変数のうち、@はじまりの変数のことをインスタンス変数といいます。インスタンス変数を使うと、コントローラから、このあとの処理先であるビューへ情報を伝えることができます。ちなみに、@はじまりではない変数はローカル変数と呼ばれ、このメソッド（アクション）を抜けると役目を終えて使えなくなります。つまり、ローカル変数へ代入してもビューから使うことはできません。ビューで使うためには、@はじまりのインスタンス変数を利用します。



//image[instance_variable][インスタンス変数を使うとビューへ情報を渡すことができる]{
//}




次にどのビューへ処理が進むかはコントローラで指定することができますが、今回は何も指定がありません。指定がないときは、コントローラおよびアクションと同名のビューを選択します。今回はHelloControllerのindexアクションなので、次の処理先であるビューのファイルはapp/views/hello/index.html.erbになります。



コントローラについてまとめてみましょう。コントローラではさまざまな処理を行い、次のビューに処理を渡します。ビューへ情報を伝えるためには@はじまりのインスタンス変数へ代入しておきます。次の処理先となるビューはコントローラで指定することができますが、指定していないときはコントローラおよびアクションと同名のビューを選択します。



それでは次の処理が行われるビューを見てみましょう。


=== ビュー


ビューではHTMLなど、ユーザーの目に届く部分を作ります。作られたHTMLは、レスポンスとしてブラウザへ送られます。



ビューのファイルであるindex.html.erbは、HTMLのもとになるファイルです。ブラウザで表示させるための言語HTMLをそのまま書くことができます。さらに、普通のHTMLとの違いとして、Rubyのコードを実行した結果を埋め込むこともできます。このようなファイルをテンプレートと呼びます。ここではerbという種類のテンプレートが使われています。書かれているHTMLと、埋め込まれたRubyのコードを実行した結果をあわせてHTMLを作ります。では、ビューのファイルを見てみましょう。



@<tt>{app/views/hello/index.html.erb}


//emlist[][erb]{
<p>現在時刻: <%= @time %></p>
//}


HTMLのpタグがあります。その中にHTMLではない @<tt>{<%=} と @<tt>{%>} というタグがあります。これがRubyのコードを実行するためのタグです。ここではその中にある @<tt>{@time} が実行されます。@timeインスタンス変数にはコントローラで実行された現在時刻 @<tt>{Time.current.in_time_zone('Asia/Tokyo')} の結果が代入されているので、これがHTMLへ埋め込まれます。



ビューで作られたHTMLは、Railsがその他の加工を加えてレスポンスとして送出され、ブラウザに表示されます。作られたHTMLはブラウザで「ページのソースを表示」機能をつかって確認することができます。



//image[time_jst][ブラウザからビューがつくったHTMLを確認]{
//}




ビューについての動作をまとめてみましょう。ビューはHTMLなど、ユーザーの目に届く部分をつくります。erbはテンプレートと呼ばれるHTMLのもとになるファイルで、Rubyのコードを実行した結果を埋め込むことができます。ビューで使う情報をコントローラから送ってもらうときは、インスタンス変数を使います。作られたHTMLは、Railsがその他の加工を加えてレスポンスとして送出します。


=== まとめ


最小構成のRailsアプリをつくり、リクエストを受けてレスポンスを返すまでの動作について説明しました。ポイントをまとめると以下のようになります。

 * Routes、コントローラ、ビューの順番で処理を行い、HTMLを作ってブラウザへレスポンスを返す
 * RoutesはリクエストのURLとHTTPメソッドに応じて、処理をするコントローラとアクションを決める対応表
 * コントローラはさまざまな処理を行い、ビューでつかう情報を@はじまりのインスタンス変数を使って渡す
 * ビューはテンプレートに書かれたRubyのコードを実行して埋め込み、HTMLを作る



//image[rails_app_request_to_response][Railsアプリがリクエストを受けてレスポンスを返すまで]{
//}



== さらに学びたい場合は
 * @<href>{https://railsguides.jp/routing.html,Rails ガイド: Rails のルーティング}
 ** Routesについての詳しい説明です。
 * @<href>{https://railsguides.jp/action_controller_overview.html,Rails ガイド: Action Controller の概要}
 ** コントローラについての詳しい説明です。
 * @<href>{https://railsguides.jp/action_view_overview.html,Rails ガイド: Action View の概要}
 ** ビューについての詳しい説明です。
 * @<href>{https://railsguides.jp/layouts_and_rendering.html,Rails ガイド: レイアウトとレンダリング}
 ** コントローラから次のビューを指定する方法や、ビューを整理して書くための情報などが説明されています。

