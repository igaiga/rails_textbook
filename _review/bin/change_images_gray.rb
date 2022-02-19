# $ ruby bin/change_images_gray.rb
# モノクロ版作成用。カラー画像をモノクロ化。
# imagemagickのconvertコマンドを利用
Dir.glob("images/**/*.*").each do |filename|
  system("convert -type GrayScale #{filename} #{filename}")
end
