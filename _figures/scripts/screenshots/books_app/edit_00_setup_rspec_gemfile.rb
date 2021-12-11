file_name = "books_app/Gemfile"
src_regex = /group :development, :test do/
dst = "group :development, :test do\n  gem 'rspec-rails'"

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
