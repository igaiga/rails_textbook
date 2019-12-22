class AddPictureToBooks < ActiveRecord::Migration[6.0]
  def change
    add_column :books, :picture, :string
  end
end
