# 画像を指示したサイズに切り取り
class Cropper
  def self.width_height(file_path)
    dir_name, file_name = file_path.split("/").last(2)
    wh = {
      "screenshots" => {
        "books_created_data_1.png" => [800, 400],
        "books_edit_data_1.png" => [500, 490],
        "books_index_blank.png" => [340, 310],
        "books_index_data_1.png" => [1290, 400],
        "books_index_data_2.png" => [1290, 720],
        "books_new_blank.png" => [420, 500],
        "books_new_data_1.png" => [420, 580],
        "books_show_data_1.png" => [780, 290],
        "books_with_author_new.png" => [440, 600],
        "books_with_upload_created.png" => [860, 1200],
        "books_with_upload_new.png" => [480, 680],
      },
    }
    wh[dir_name][file_name]
  end

  def self.crop
    Dir.glob("screenshots/*.png") do |file_path|
      width, height = width_height(file_path)
      if width.nil? || height.nil?
        puts "width_heightメソッドに #{file_path} の画像サイズを追加してください"
        next
      end
      puts "#{file_path}: #{width}, #{height}"
      crop_exec(file_path, width, height)
    end
  end

  private_class_method def self.crop_exec(file_path, width, height)
    # imagemagickのconvert機能をつかう
    system "magick #{file_path} -crop #{width}x#{height}+0+0 #{file_path}"
  end
end

#system "rm -rf screenshots; cp -r screenshots_org screenshots" # 実装用 バックアップから復元
#system "cp -r screenshots screenshots_org" # バックアップ

Cropper.crop
