require 'rails_helper'

RSpec.feature "/books", type: :system do
  describe "new" do
    it "new + create" do
      visit new_book_path
      fill_in "Title", with: "RubyとRailsの学習ガイド"
      fill_in "Memo", with: "Rails関連技術地図とそれらの学習資料の紹介"
      fill_in "Author", with: "五十嵐邦明"
      attach_file "Picture", "spec/systems/rrsg_small.png"
      page.save_screenshot 'books_with_upload_new.png'
      click_button "Create Book"

      expect(page).to have_text('successfully')
      page.save_screenshot 'books_with_upload_created.png'
    end
  end
end
