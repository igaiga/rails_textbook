require "uri"
require "selenium-webdriver"

class ScreenPhotographer
  def initialize
    options = Selenium::WebDriver::Chrome::Options.new
    options.add_argument('--headless')
    # headless指定すると普段Chromeで指定しているフォント指定が効かなくなる
    @driver = Selenium::WebDriver.for :chrome, options: options
  end

  def screenshot(html_path:, out_path:)
    # p file_url(html_path)
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
      #TODO: figure_sampleは不要
    end
  end

  # TODO: private
  def self.html_paths
    Dir.glob(File.join(html_base_path, "**/*.html"))
  end

  def self.out_filename(path)
    File.join(
      out_base_path,
      File.dirname(path).split("/").last, # Fileでできるとかっこいい
      File.basename(path, ".html") + ".png"
      )
  end
  
  def self.base_path
    Dir.pwd
  end

  def self.html_base_path
    File.join(base_path, "..", "..", "assets")
  end

  def self.out_base_path
    # TODO: 正しい位置へ移動
    File.join(base_path, "tmp_out")
  end
end

sp = ScreenPhotographer.new

FilePathMaker.htmls.each do |params|
  sp.screenshot(params)
end

sp.clear

#TODO: cropするクラスをつくる。screenshotの方と流用したい。
