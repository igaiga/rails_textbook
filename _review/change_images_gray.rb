Dir.glob("images/**/*.*").each do |filename|
  system("convert -type GrayScale #{filename} #{filename}")
end
