if [ -e tmp ]; then
  rm -rf tmp
fi
ruby screen_photographer.rb
ruby cropper.rb
ruby replacer.rb
