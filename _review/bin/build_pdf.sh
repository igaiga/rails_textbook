# $ bin/build_pdf.sh
# カラー版PDF作成。ノンブルは入らない。
bin/copy_images.sh
bin/md_to_re.sh
bin/make_pdf_on_docker.sh
# TODO bin/make_pdf_on_docker.sh を消して以下のようにここに展開
# docker run --rm -v $PWD:/work kauplan/review2.5 /bin/bash -c "cd /work; rake pdf"
# open mybook.pdf
