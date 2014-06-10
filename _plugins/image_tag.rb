module Jekyll
  class ImageTag < Liquid::Tag
    def initialize(tag_name, params, tokens)
      super
      h = Hash[ *params.split(/:|,/).map(&:strip) ]
      @description = h["description"]
      @path = h["path"]
    end
    def render(context)
      # 相対パスで書いている。
      # もしかするとここでsite.baseurl とか　site_url が取れればそれを使った方がいいのかもしれない。
      "<div class ='image-picture'><p><img src='#{@path}' alt='#{@description}'></p></div>" +
        "<div class ='image-description'><p>図 : #{@description} </p></div>"
    end
  end
end

Liquid::Template.register_tag('image', Jekyll::ImageTag)
