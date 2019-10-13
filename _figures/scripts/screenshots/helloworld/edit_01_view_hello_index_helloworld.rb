file_name = "helloworld/app/views/hello/index.html.erb"
dst = "<p>Hello world!</p>"

def replace(file_name:, dst:)
  File.open(file_name, "w") do |file|
    file.puts dst
  end
end

replace(file_name: file_name, dst: dst)
