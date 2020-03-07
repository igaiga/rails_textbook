# カラー版。ノンブルは入らない。表紙は自動で挿入されない。
# 表紙、裏表紙は_figures/coversに置いてあるので、PDF作成後にmacのプレビューで画像を差し込む。
./copy_images.sh
./md_to_re.sh
./make_pdf_on_docker.sh
