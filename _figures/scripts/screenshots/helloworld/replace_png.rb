require 'fileutils'

class FilePathMaker
  def self.copy_files
    Dir.glob(from_filenames).each do |from_filename|
      FileUtils.cp(from_filename, to_filename(from_filename))
    end
  end

  private_class_method def self.base_path
    Dir.pwd # 実行時カレントディレクトリ
  end

  private_class_method def self.from_path
    File.join(base_path, "screenshots")
  end

  private_class_method def self.from_filenames
    File.join(from_path, "**/*.png")
  end

  private_class_method def self.to_base_path
    File.join(base_path, "..", "..", "..", "..", "assets")
  end

  private_class_method def self.to_filename(path)
    File.join(
      to_base_path,
      "smallest-app",
      File.basename(path)
    )
  end
end

FilePathMaker.copy_files
