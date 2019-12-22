require 'rails_helper'

RSpec.feature "/books", type: :system do
  describe "new" do
    it "new + create" do
      visit new_book_path
      fill_in "Title", with: "RubyとRailsの学習ガイド"
      fill_in "Memo", with: "Rails関連技術地図とそれらの学習資料の紹介"
      fill_in "Author", with: "五十嵐邦明"
      ss_file_path = page.save_screenshot 'books_with_upload_new.png'
      attach_file "Picture", "spec/systems/rrsg_hyou1_small.png"
      click_button "Create Book"
      ss_file_path = page.save_screenshot 'books_with_upload_created.png'
      expect(page).to have_text('successfully')
    end
  end
end
