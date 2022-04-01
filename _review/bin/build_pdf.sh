# $ bin/build_pdf.sh
# カラー版PDF作成。ノンブルは入らない。
pushd _review
bin/copy_images.sh
bin/md_to_re.sh
popd

docker build -t review .
docker run --rm -v `pwd`/_review:/work review /bin/sh -c "cd /work && rake pdf"

open _review/mybook.pdf
