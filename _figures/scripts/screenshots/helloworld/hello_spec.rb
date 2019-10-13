require 'rails_helper'

RSpec.feature "/hello/index", type: :system do
  before do
    visit hello_index_path
  end
  it do
    ss_file_path = page.save_screenshot 'hello_index.png'
    p ss_file_path
    expect(page).to have_text('Hello')
  end
end
