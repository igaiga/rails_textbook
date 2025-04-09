class AddAuthorToBooks < ActiveRecord::Migration[8.0]
  def change
    add_column :books, :author, :string
  end
end
