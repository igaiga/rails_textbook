file_name = "helloworld/app/views/hello/index.html.erb"
src_regex = /Time\.current\.in_time_zone\('Asia\/Tokyo'\)/
dst = "@time"

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
