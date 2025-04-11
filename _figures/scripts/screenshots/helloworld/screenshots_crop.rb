system "cp -r screenshots screenshots_org"

def width(file_path)
  720
end

def height(file_path)
  case file_path
  when /hello_index/
    300
  when /hello_world/
    120
  else
    200
  end
end

Dir.glob("screenshots/**/*.png") do |file_path|
  # imagemagickのconvert機能をつかう
  system "magick #{file_path} -crop #{width(file_path)}x#{height(file_path)}+0+0 #{file_path}"
end
