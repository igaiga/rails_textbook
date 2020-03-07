# モノクロ版。ノンブル入り。表紙は自動で挿入されない。
./copy_images.sh
ruby change_images_gray.rb
./md_to_re.sh
./make_pdf_on_docker_with_nombre.sh
