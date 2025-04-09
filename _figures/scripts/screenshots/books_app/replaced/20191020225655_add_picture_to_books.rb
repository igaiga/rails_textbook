class AddPictureToBooks < ActiveRecord::Migration[8.0]
  def change
    add_column :books, :picture, :string
  end
end
