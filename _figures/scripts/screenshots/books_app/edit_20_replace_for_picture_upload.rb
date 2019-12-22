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
  src_regex = /<div class="actions">/
  dst = %Q[<div class="field">\n    <%= form.label :picture %>\n    <%= form.file_field :picture %>\n  </div>\n\n  <div class="actions">]

  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_show_html_erb
  file_name = "books_app/app/views/books/show.html.erb"
  src_regex = /  <%= @book.author %>/
  dst = %Q[  <%= @book.author %>\n</p>\n\n<p>  \n  <strong>Picture:</strong>\n  <%= image_tag(@book.picture_url) if @book.picture.present? %>]

  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_index_html_erb_1
  file_name = "books_app/app/views/books/index.html.erb"
  src_regex = /<th>Author<\/th>/
  dst = %Q[<th>Author</th>\n      <th>Picture</th>]
  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_index_html_erb_2
  file_name = "books_app/app/views/books/index.html.erb"
  src_regex = /<td><%= book.author %><\/td>/
  dst = %Q[<td><%= book.author %></td>\n        <td><%= book.picture %></td>]
  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_books_controller
  file_name = "books_app/app/controllers/books_controller.rb"
  src_regex = /params\.require\(:book\)\.permit\(:title, :memo, :author\)/
  dst = %Q[params.require(:book).permit(:title, :memo, :author, :picture)]
  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

replace_gemfile
replace_book_model
replace_form_html_erb
replace_show_html_erb
replace_index_html_erb_1
replace_index_html_erb_2
replace_books_controller
