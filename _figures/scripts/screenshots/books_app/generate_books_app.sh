#!/bin/sh
# books_app 作成＆スクショ生成
rm -rf screenshots # スクリーンショット収集用フォルダ
mkdir screenshots

# rails new, rails generate
rm -rf books_app
rails new books_app
cd books_app
# bin/spring stop # spring has removed at Rails7.0
bin/rails g scaffold book title:string memo:text
bin/rails db:migrate
cd ..

# rspec setup
ruby edit_00_setup_rspec_gemfile.rb
cd books_app
bundle install
# bin/spring stop # spring has removed at Rails7.0
bin/rails generate rspec:install
mkdir spec/systems
cp ../replaced/*_spec.rb spec/systems/.
cd ..
ruby edit_00_setup_rspec_rails_helper.rb # rails g rspec:install 生成ファイルの書き換え

# screenshot 1st for generated Books CRUD
cd books_app
bundle exec rspec spec/systems/books_spec.rb
cd ..

# Chrome Dev Tools用のスクリーンショットアプリ作成時はここまでで終わりにする
# exit

# screenshot 2nd for Books with author
ruby edit_10_replace_for_author.rb
cd books_app
cp ../replaced/*_add_author_to_books.rb db/migrate/.
bin/rails db:migrate
# bin/spring stop # spring has removed at Rails7.0
# screenshot with Author
bundle exec rspec spec/systems/books_author_spec.rb
cd ..

# screenshot 3rd for Books with picture upload
ruby edit_20_replace_for_picture_upload.rb
cd books_app
# bin/spring stop # spring has removed at Rails7.0
bundle install
bin/rails g uploader Picture
cp ../replaced/*_add_picture_to_books.rb db/migrate/.
cp ../replaced/*.png spec/systems/.
bin/rails db:migrate
# bin/spring stop # spring has removed at Rails7.0
# screenshot with file upload
bundle exec rspec spec/systems/books_upload_spec.rb
cd ..

# ファイルコピー
rm -rf screenshots
cp -r books_app/tmp/capybara screenshots

# screemshots 切り出し
cp -r screenshots screenshots_org #backup
# open screenshots_org
ruby cropper.rb
open screenshots # 確認用

# 作成されたpngファイルを配置
ruby replacer.rb
