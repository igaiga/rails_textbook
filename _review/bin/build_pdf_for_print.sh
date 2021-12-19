# $ bin/build_pdf_for_print.sh
# モノクロ版。ノンブル入り。
bin/copy_images.sh
ruby bin/change_images_gray.rb
bin/md_to_re.sh
bin/make_pdf_on_docker_with_nombre.sh
