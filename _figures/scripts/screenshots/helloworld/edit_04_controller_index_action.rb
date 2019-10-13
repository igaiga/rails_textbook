file_name = "helloworld/app/controllers/hello_controller.rb"
src_regex = /def index\n/
dst = "def index\n    @time = Time.current.in_time_zone('Asia/Tokyo')\n"

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
