require "selenium-webdriver"

options = Selenium::WebDriver::Chrome::Options.new
#options.add_argument('--headless')
# headless指定すると普段Chromeで指定しているフォント指定が効かなくなる

driver = Selenium::WebDriver.for :chrome, options: options
#driver.get("https://igarashikuniaki.net/diary/")
driver.get("file:///box/github_repos/github.com/igaiga/rails_textbook/_figures/assets/test.html")
driver.save_screenshot("ss.png")
driver.quit
