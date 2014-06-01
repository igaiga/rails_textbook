# A Liquid tag for Maliq that enable adding CSS signatures.
# by: Kyo Endo
# Source URL: https://gist.github.com/
#
# Example usage:
#   text = <<-EOS
#   {% csssig h2 id='hello' class='header' %}
#   ##Hello
#   this is test.
#   {% endcsssig %}
#
#   => <h2 id="hello" class="header">Hello</h2>
#
#      <p>this is test.</p>
#
require "liquid"
require "rdiscount"
require "nokogiri"

class CSSSignature < Liquid::Block
  def initialize(tag_name, text, token)
    super
    @text = text
  end

  def render(context)
    tag, *signs = @text.split
    _SIG_REG_ = /(\w+)\s*=\s*(?:["']([\w ]*)?["']|(\w+))/
    signs = signs.join(' ').scan(_SIG_REG_).map(&:compact)
    
    html = Nokogiri::HTML.fragment RDiscount.new(super).to_html
    if target = html.at_css(tag)
      signs.each { |attr, val| target[attr] = val }
    end  
    html.to_html
  end
end

Liquid::Template.register_tag('csssig', CSSSignature)

if __FILE__ == $0
  text = <<-EOS
{% csssig h2 id='hello' class='header hi' %}
##Hello
this is test.
{% endcsssig %}
EOS
  puts Liquid::Template.parse(text).render
end
