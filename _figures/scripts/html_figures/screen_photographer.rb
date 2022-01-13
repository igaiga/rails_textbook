require "uri"
require "selenium-webdriver"

# スクリーンショットを撮って指定した出力先へpng出力
class ScreenPhotographer
  def initialize
    options = Selenium::WebDriver::Chrome::Options.new
    # headless指定すると普段Chromeで指定しているフォント指定が効かなくなる
    options.add_argument("--headless")
    # options.add_argument("--window-size=900,800") # macでの画像サイズはこれの2倍になる
    options.add_argument("--window-size=1200,800") # 調整前なので仮で大きめ
    @driver = Selenium::WebDriver.for :chrome, options: options
  end

  def screenshot(html_path:, out_path:)
    return if FilePathMaker.needless?(html_path)
    @driver.get(file_url(html_path))
    @driver.save_screenshot(out_path)
  end

  def clear
    @driver.quit
  end

  private

  def file_url(path)
    URI.join("file:", path)
  end
end

# ScreenPhotographerへ渡すための入力HTMLパスと出力pngパスを作成
class FilePathMaker
  def self.htmls
    html_paths.map do |path|
      { html_path: path,   
        out_path: out_filename(path) }
    end
  end

  def self.needless?(path)
    needless_htmls = ["figure-sample.html"]
    needless_htmls.include?(File.basename(path))
  end
  
  private_class_method def self.base_path
    Dir.pwd # 実行時カレントディレクトリ
  end

  private_class_method def self.html_base_path
    File.join(base_path, "..", "..", "assets")
  end

  private_class_method def self.html_paths
    Dir.glob(File.join(html_base_path, "**/*.html"))
  end

  private_class_method def self.out_base_path
    File.join(base_path, "tmp")
  end

  private_class_method def self.out_filename(path)
    File.join(
      out_base_path,
      File.dirname(path).split("/").last,
      File.basename(path, ".html") + ".png"
    )
  end

  private_class_method def self.out_dirs
    dirs = ["crud", "model", "new-create", "smallest-app"]
    dirs.map do |dir_name|
      File.join(out_base_path, dir_name)
    end
  end

  def self.mkdir_out_dirs
    mkdir([out_base_path])
    mkdir(out_dirs)
  end

  def self.mkdir(paths)
    paths.each do |path|
      Dir.mkdir path
    rescue Errno::EEXIST => _e
    end
  end
end

FilePathMaker.mkdir_out_dirs

sp = ScreenPhotographer.new

FilePathMaker.htmls.each do |params|
  sp.screenshot(**params)
end

sp.clear
