# $ ruby bin/change_images_gray.rb
# モノクロ版作成用。カラー画像をモノクロ化。
Dir.glob("images/**/*.*").each do |filename|
  # imagemagickのconvert機能をつかう
  system("magick -type GrayScale #{filename} #{filename}")
end
