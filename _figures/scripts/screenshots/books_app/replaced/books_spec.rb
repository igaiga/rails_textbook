require 'rails_helper'

RSpec.feature "/books", type: :system do
  describe "blank" do
    it "index" do
      visit books_path
      ss_file_path = page.save_screenshot 'books_index_blank.png'
      expect(page).to have_text('book') # OKにするだけ
    end
  end
  describe "1 data" do
    before do
      Book.create!(title: "RubyとRailsの学習ガイド", memo: "Rails関連技術地図とそれらの学習資料の紹介")
    end
    it "index" do
      visit books_path
      ss_file_path = page.save_screenshot 'books_index_data_1.png'
      expect(page).to have_text('book')
    end
    it "show" do
      visit book_path(Book.last)
      ss_file_path = page.save_screenshot 'books_show_data_1.png' # crud_4_pages.png生成につかう
      expect(page).to have_text('学習ガイド')
    end
    it "new" do
      visit new_book_path
      ss_file_path = page.save_screenshot 'books_new_data_1.png'
      expect(page).to have_text('book')
    end
    it "edit" do
      visit edit_book_path(Book.last)
      ss_file_path = page.save_screenshot 'books_edit_data_1.png' # crud_4_pages.png生成につかう
      expect(page).to have_text('book')
    end
    it "new + cerate" do
      visit new_book_path
      fill_in "Title", with: "RubyとRailsの学習ガイド"
      fill_in "Memo", with: "Rails関連技術地図とそれらの学習資料の紹介"
      click_button "Create Book"
      ss_file_path = page.save_screenshot 'books_created_data_1.png'
      expect(page).to have_text('successfully')
    end
  end
  describe "2 data" do
    before do
      Book.create!(title: "RubyとRailsの学習ガイド", memo: "Rails関連技術地図とそれらの学習資料の紹介")
      Book.create!(title: "Ruby超入門", memo: "Rubyのやさしい入門書")
    end
    it "index" do
      visit books_path
      ss_file_path = page.save_screenshot 'books_index_data_2.png'
      expect(page).to have_text('book')
    end
  end
end
