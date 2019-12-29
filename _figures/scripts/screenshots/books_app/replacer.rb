# 画像を指定のフォルダへコピー
require "fileutils"

class Replacer
  private_class_method def self.base_path
    Dir.pwd # 実行時カレントディレクトリ
  end

  private_class_method def self.in_base_path
    File.join(base_path, "screenshots")
  end

  private_class_method def self.in_file_paths
    Dir.glob(File.join(in_base_path, "**/*.png"))
  end

  private_class_method def self.out_base_path
    File.join(base_path, "..", "..", "..", "..", "assets")
  end

  private_class_method def self.out_filename(path)
    out_middle_path = out_middle_path(path)
    return nil unless out_middle_path
    File.join(
      out_base_path,
      out_middle_path,
      "app_ss",
      File.basename(path)
    )
  end

  private_class_method def self.out_middle_path(path)
    filename = File.basename(path)
    # コピー先のassets 以下のパスを得る
    out_path_hash = {
      "books_index_data_2.png" => "crud",
      "books_created_data_1.png" => "crud", # modelのページでも使っている
      "books_index_blank.png" => "crud",
      "books_new_data_1.png" => "new-create",
      "books_with_author_new.png" => "model",
      "books_with_upload_created.png" => "picture-upload",
      "books_with_upload_new.png" => "picture-upload",
    }
    out_path_hash[filename]
  end

  def self.cp
    in_file_paths.each do |in_path|
      p in_path
      p out_filename(in_path)
      unless out_filename(in_path)
        puts "コピー先フォルダがout_middle_pathメソッドで指定されていません"
        next
      end
      if out_filename(in_path)
      end
      FileUtils.cp(in_path, out_filename(in_path))
    end
  end
end

Replacer.cp
