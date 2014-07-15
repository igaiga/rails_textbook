---
layout: post
unique_identifier:
 - 'http:/example.jp/bookid_in_url'
 - 'BookID'
 - 'URL'
title: 'new, create アクション'
creator: '五十嵐邦明'
date: '2014-08-01'
categories:
---

# new, create アクション

この章ではCRUDのCにあたる新規登録を行うための2つのアクション、new と create について説明していきます。

説明に使うアプリは前の章でつくったものを引き続き使います。

## 概略

前の章での「CRUD遷移図」において、new とcreate はこの部分になります。

{% image path: assets/new-create/crud-transition-diagram-new-create.png, description: CRUD画面遷移図(newとcreate) %}

おおまかな流れは以下のようになります。

{% image path: assets/new-create/new-create-overview.png, description: おおまかな流れ %}

まず、newアクションが実行され新規入力画面が表示されます。ここで本のタイトルとメモを入力します。Create Book ボタンを押すと、次に画面のない create アクションが実行されます。createアクションで、前のステップで入力されたタイトルとメモで本のデータを新規登録します。

## new アクション

最初に、新規入力画面が表示されるまでの処理の流れを見ていきましょう。

{% image path: assets/new-create/new_page.png, description: 新規入力画面 %}

新規入力画面は new アクションで表示されます。newアクションも前章で説明したindexアクションと同じく、Routes、コントローラ、ビューの各処理を経て画面が表示されます。

{% image path: assets/new-create/new-flow.png, description: new(新規入力)画面が表示されるまで %}




