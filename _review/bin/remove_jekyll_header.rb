# $ ruby bin/remove_jekyll_header.rb
# reviewファイルから、jekyll markdown 先頭にある余分な行を削除
# jekyllを消せたらこのファイルは不要になる
require "fileutils"

def remove_jekyll_header(file_name)
  p file_name
  pass = true
  FileUtils.cp(file_name, file_name + ".tmp")
  File.open(file_name + ".tmp", "r") do |f_read|
    File.open(file_name, "w") do |f_write|
      f_read.each_line do |line|
        if line == "== categories:\n" # この行まで削除
          pass = false
          next
        end
        next if pass
        f_write.puts line
      end
    end
  end
end

# ヘッダの除去
Dir.glob("contents/**/*.re") do |path|
  remove_jekyll_header(path)
end

# 作業ファイル削除
Dir.glob("contents/**/*.tmp") do |path|
  FileUtils.rm(path)
end
