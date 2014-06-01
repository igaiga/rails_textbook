# ------------------------------------
# *** ATTENSION ***
# This file is NOT for Jekyll. It's modified for adapting Maliq(https://github.com/melborne/maliq) gem
# which is a EPUB generator.
# 'gem install pygments.rb' required.
# The original is from Jekyll 0.11.2(https://github.com/mojombo/jekyll/blob/master/lib/jekyll/tags/highlight.rb)
# By: kyoendo(a.k.a melborne) 2012
# Source URL: https://gist.github.com/4134497#file_highlight.rb
# ------------------------------------
#

module Jekyll

  class HighlightBlock < Liquid::Block
    include Liquid::StandardFilters

    # We need a language, but the linenos argument is optional.
    SYNTAX = /(\w+)\s?([\w\s=]+)*/

    def initialize(tag_name, markup, tokens)
      super
      if markup =~ SYNTAX
        @lang = $1
        if defined? $2
          tmp_options = {}
          $2.split.each do |opt|
            key, value = opt.split('=')
            if value.nil?
              if key == 'linenos'
                value = 'inline'
              else
                value = true
              end
            end
            tmp_options[key] = value
          end
          tmp_options = tmp_options.to_a.collect { |opt| opt.join('=') }
          # additional options to pass to Albino
          @options = { 'O' => tmp_options.join(',') }
        else
          @options = {}
        end
      else
        raise SyntaxError.new("Syntax Error in 'highlight' - Valid syntax: highlight <lang> [linenos]")
      end
    end

    def render(context)
      if context.registers[:site].pygments
        render_pygments(context, super)
      else
        render_codehighlighter(context, super)
      end
    end

    def render_pygments(context, code)
      output = add_code_tags(Albino.new(code, @lang).to_s(@options), @lang)
      output = context["pygments_prefix"] + output if context["pygments_prefix"]
      output = output + context["pygments_suffix"] if context["pygments_suffix"]
      output
    end

    def render_codehighlighter(context, code)
      #The div is required because RDiscount blows ass
      <<-HTML
<div>
  <pre><code class='#{@lang}'>#{h(code).strip}</code></pre>
</div>
      HTML
    end

    def add_code_tags(code, lang)
      # Add nested <code> tags to code blocks
      code = code.sub(/<pre>/,'<pre><code class="' + lang + '">')
      code = code.sub(/<\/pre>/,"</code></pre>")
    end

  end
end


#
# Followings are added for Maliq gem.
#

require 'pygments'

class Jekyll::HighlightBlock
  def render(context)
      render_pygments(context, super)
  end

  def render_pygments(context, code)
    @options[:encoding] = 'utf-8'
    
    output = add_code_tags(Pygments.highlight(code, :lexer => @lang, :options => @options), @lang)
    output = context["pygments_prefix"] + output if context["pygments_prefix"]
    output = output + context["pygments_suffix"] if context["pygments_suffix"]
    output
  end
end

# End of code for Mdpub

Liquid::Template.register_tag('highlight', Jekyll::HighlightBlock)