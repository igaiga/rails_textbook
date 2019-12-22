class AddAuthorToBooks < ActiveRecord::Migration[6.0]
  def change
    add_column :books, :author, :string
  end
end
