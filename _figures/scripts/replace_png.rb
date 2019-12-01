require "fileutils"
class ReplacePng
  def self.run
    png_paths.each do |png_path|
      next unless target_png_path?(png_path)
      p png_path
      FileUtils.cp(png_path, out_filename(png_path))
    end
  end

  private_class_method def self.base_path
    Dir.pwd # 実行時カレントディレクトリ
  end

  private_class_method def self.png_base_path
    File.join(base_path, "..", "assets")
  end

  private_class_method def self.png_paths
    Dir.glob(File.join(png_base_path, "**/*.png"))
  end

  private_class_method def self.target_png_path?(path)
    check_folder = File.dirname(path).split("/").last
    target_png_folders.include?(check_folder)
  end

  private_class_method def self.target_png_folders
    ["smallest-app", "CRUD", "new-create", "model"]
  end
  
  private_class_method def self.out_base_path
    File.join(base_path, "..", "..", "assets")
  end

  private_class_method def self.out_filename(path)
    File.join(
      out_base_path,
      File.dirname(path).split("/").last,
      "figures",
      File.basename(path)
      #File.basename(path, ".html") + ".png"
    )
  end
end

ReplacePng.run

