# 画像を指定のフォルダへコピー
require "fileutils"

class Replacer
  private_class_method def self.base_path
    Dir.pwd # 実行時カレントディレクトリ
  end

  private_class_method def self.in_base_path
    File.join(base_path, "tmp")
  end

  private_class_method def self.in_file_paths
    Dir.glob(File.join(in_base_path, "**/*.png"))
  end

  private_class_method def self.out_base_path
    File.join(base_path, "..", "..", "..", "assets")
  end

  private_class_method def self.out_filename(path)
    File.join(
      out_base_path,
      File.dirname(path).split("/").last,
      "figures",
      File.basename(path)
    )
  end

  def self.cp
    in_file_paths.each do |in_path|
      p in_path
      p out_filename(in_path)
      FileUtils.cp(in_path, out_filename(in_path))
    end
  end
end

Replacer.cp

