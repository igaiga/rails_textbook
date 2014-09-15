class HelloController < ApplicationController
  def index
    @time = Time.now
  end
end
