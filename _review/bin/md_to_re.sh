# $ bin/md_to_re.sh
# .mdから.reへ変換してcontentsフォルダへ配置するスクリプト

# 出力フォルダ作成
if [ ! -d contents ]; then
  mkdir contents
fi

# MarkdownファイルをReVIEWファイルへ変換
# $ gem i md2review
md2review ../_posts/01_preface.md > contents/01_preface.re
md2review ../_posts/02_smallest_app.md > contents/02_smallest_app.re
md2review ../_posts/03_crud.md > contents/03_crud.re
md2review ../_posts/04_new_create.md > contents/04_new_create.re
md2review ../_posts/05_model.md > contents/05_model.re
md2review ../_posts/06_gem.md > contents/06_gem.re
md2review ../_posts/07_picture_upload.md > contents/07_picture_upload.re
md2review ../_posts/08_postface.md > contents/08_postface.re
