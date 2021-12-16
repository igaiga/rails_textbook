require 'rails_helper'

RSpec.feature "/books", type: :system do
  describe "new" do
    it "new" do
      visit new_book_path
      fill_in "Title", with: "RubyとRailsの学習ガイド"
      fill_in "Memo", with: "Rails関連技術地図とそれらの学習資料の紹介"
      fill_in "Author", with: "五十嵐邦明"
      ss_file_path = page.save_screenshot 'books_with_author_new.png'
      expect(page).to have_text('book')
    end
  end
end
