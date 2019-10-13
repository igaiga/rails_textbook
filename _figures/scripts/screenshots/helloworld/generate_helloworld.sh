#!/bin/sh
# 一番小さなRailsアプリづくり helloworld app 作成＆スクショ生成
rails new helloworld
cd helloworld
bin/spring stop
bin/rails g controller hello index
cd ..

# rspec setup
ruby edit_00_setup_rspec.rb
cd helloworld
bundle install
bin/spring stop
bin/rails generate rspec:install
mkdir spec/systems
cp ../hello_spec.rb spec/systems/.
cd ..

# screenshot for generated "Hello#index"
cd helloworld
bundle exec rspec spec/systems/hello_spec.rb
cp tmp/capybara/hello_index.png ../screenshots/hello_index.png
cd ..

# screenshot for "Helloworld!"
ruby edit_01_view_hello_index_helloworld.rb
cd helloworld
bundle exec rspec spec/systems/hello_spec.rb
cp tmp/capybara/hello_index.png ../screenshots/hello_world.png
cd ..

# screenshot for "Time.current UTC"
ruby edit_02_view_hello_index_time_current.rb
cd helloworld
bundle exec rspec spec/systems/hello_spec.rb
cp tmp/capybara/hello_index.png ../screenshots/time_utc.png
cd ..

# screenshot for "Time.current JST"
ruby edit_03_view_hello_index_time_zone_tokyo.rb
cd helloworld
bundle exec rspec spec/systems/hello_spec.rb
cp tmp/capybara/hello_index.png ../screenshots/time_jst.png
cd ..

# Refactoring (no new screenshots)
# ruby edit_04_controller_index_action.rb
# ruby edit_04_view_hello_index_at_time.rb

# screemshots 切り出し
ruby screenshots_crop.rb

open screenshots
