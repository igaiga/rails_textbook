# $ bin/build_pdf_for_print.sh
# モノクロ版。ノンブル入り。
bin/copy_images.sh
ruby bin/change_images_gray.rb
bin/md_to_re.sh

# ノンブル入りを作るときは先にrakd pdfを1回実行しておく必要があるようなので実行
docker run --rm -v $PWD:/work kauplan/review2.5 /bin/bash -c "cd /work; rake pdf"
# rake pdf:nombreでノンブル（通し番号)付きでPDF出力
docker run --rm -v $PWD:/work kauplan/review2.5 /bin/bash -c "cd /work; rake pdf:nombre"

open mybook.pdf
