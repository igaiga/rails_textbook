# Author用書き換え
def replace(file_name:, src_regex:, dst:)
  body = File.open(file_name, "r") do |file|
    file.read
  end

  body.gsub!(src_regex, dst)

  File.open(file_name, "w") do |file|
    file.puts body
  end
end

def replace_form_html_erb
  file_name = "books_app/app/views/books/_form.html.erb"
  src_regex = /<div class="actions">/
  dst = %Q[<div class="field">\n    <%= form.label :author %>\n    <%= form.text_field :author %>\n  </div>\n\n  <div class="actions">]

  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_show_html_erb
  file_name = "books_app/app/views/books/show.html.erb"
  src_regex = /  <%= @book.memo %>/
  dst = %Q[  <%= @book.memo %>\n</p>\n\n<p>  \n  <strong>Author:</strong>\n  <%= @book.author %>]

  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_index_html_erb_1
  file_name = "books_app/app/views/books/index.html.erb"
  src_regex = /<th>Memo<\/th>/
  dst = %Q[<th>Memo</th>\n      <th>Author</th>]
  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_index_html_erb_2
  file_name = "books_app/app/views/books/index.html.erb"
  src_regex = /<td><%= book.memo %><\/td>/
  dst = %Q[<td><%= book.memo %></td>\n        <td><%= book.author %></td>]
  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

def replace_books_controller
  file_name = "books_app/app/controllers/books_controller.rb"
  src_regex = /params\.require\(:book\)\.permit\(:title, :memo\)/
  dst = %Q[params.require(:book).permit(:title, :memo, :author)]
  replace(file_name: file_name, src_regex: src_regex, dst: dst)
end

replace_form_html_erb
replace_show_html_erb
replace_index_html_erb_1
replace_index_html_erb_2
replace_books_controller
