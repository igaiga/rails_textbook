require "uri"
require "selenium-webdriver"

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

  private_class_method def self.out_base_path
    File.join(base_path, "..", "..", "..", "assets")
  end

  private_class_method def self.html_paths
    Dir.glob(File.join(html_base_path, "**/*.html"))
  end

  private_class_method def self.out_filename(path)
    File.join(
      out_base_path,
      File.dirname(path).split("/").last,
      "figures",
      File.basename(path, ".html") + ".png"
    )
  end
end

sp = ScreenPhotographer.new

FilePathMaker.htmls.each do |params|
  sp.screenshot(params)
end

sp.clear

#TODO: cropするクラスをつくる。screenshotの方と流用したい。
