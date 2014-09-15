class Entry < ActiveRecord::Base
  mount_uploader :picture, PictureUploader
end
