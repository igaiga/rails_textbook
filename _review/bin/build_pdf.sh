# $ bin/build_pdf.sh
# カラー版PDF作成。ノンブルは入らない。
bundle install

bin/copy_images.sh
bin/md_to_re.sh

docker build -t review .
docker run --rm -v `pwd`:/work review /bin/sh -c "cd /work && rake pdf"

open mybook.pdf
