# Picture upload用書き換え
def replace(file_name:, src_regex:, dst:)
  body = File.open(file_name, "r") do |file|
    file.read
  end

  body.gsub!(src_regex, dst)

  File.open(file_name, "w") do |file|
    file.puts body
  end
end

def replace_gemfile
  file_name = "books_app/Gemfile"
  src_regex = /\z/
  dst = "gem 'carrierwave'"
  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_book_model
  file_name = "books_app/app/models/book.rb"
  src_regex = /end/
  dst = %Q[  mount_uploader :picture, PictureUploader\nend]
  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_form_html_erb
  file_name = "books_app/app/views/books/_form.html.erb"
  src_regex = /<%= form.submit %>/
  dst = %Q[<div>\n    <%= form.label :picture, style: "display: block" %>\n    <%= form.file_field :picture %>\n  </div>\n\n  <div>\n    <%= form.submit %>]

  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_partial_book_html_erb
  file_name = "books_app/app/views/books/_book.html.erb"
  src_regex = /    <%= book.author %>/
  dst = %Q[    <%= book.author %>\n  </p>\n\n  <p>  \n    <strong>Picture:</strong>\n    <%= image_tag(book.picture_url) if book.picture.present? %>]

  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_books_controller
  file_name = "books_app/app/controllers/books_controller.rb"
  src_regex = Regexp.new(Regexp.escape("params.expect(book: [ :title, :memo, :author ])"))
  dst = %Q[params.expect(book: [ :title, :memo, :author, :picture ])]
  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

replace_gemfile
replace_book_model
replace_form_html_erb
replace_partial_book_html_erb
replace_books_controller
