file_name = "books_app/spec/rails_helper.rb"
src_regex = /RSpec\.configure do \|config\|/
dst = "RSpec.configure do |config|" + "\n" + "  config.before(:each, type: :system){ driven_by :selenium_chrome_headless }"

def replace(file_name:, src_regex:, dst:)
  body = File.open(file_name, "r") do |file|
    file.read
  end

  body.gsub!(src_regex, dst)

  File.open(file_name, "w") do |file|
    file.puts body
  end
end

replace(file_name: file_name, src_regex: src_regex, dst: dst)
