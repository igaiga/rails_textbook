# 出力フォルダ作成
if [ ! -d contents ]; then
  mkdir contents
fi

# MarkdownファイルをReVIEWファイルへ変換
# $ gem i md2review
md2review ../_posts/2014-04-01-preface.md > contents/01_preface.re
md2review ../_posts/2014-06-01-smallest-app.md > contents/02_smallest_app.re
md2review ../_posts/2014-07-01-crud.md > contents/03_crud.re
md2review ../_posts/2014-08-01-new-create.md > contents/04_new_create.re
md2review ../_posts/2014-09-01-model.md > contents/05_model.re
md2review ../_posts/2016-01-11-gem.md > contents/06_gem.re
md2review ../_posts/2016-01-12-picture-upload.md > contents/07_picture_upload.re
md2review ../_posts/2016-02-17-postface.md > contents/08_postface.re

# 変換後にreファイルからヘッダ情報の除去
# Jekyllを削除したらこの処理を削除できる
ruby remove_jekyll_header.rb
