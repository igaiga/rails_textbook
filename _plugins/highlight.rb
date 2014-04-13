module Jekyll
  module Tags
    class HighlightBlock < Liquid::Block
      def render_codehighlighter(context, code)
        #The div is required because RDiscount blows ass
        <<-HTML
  <div>
    <pre class='#{@lang}'><code class='#{@lang}'>#{h(code).strip}</code></pre>
  </div>
        HTML
      end

      def add_code_tags(code, lang)
        # Add nested <code> tags to code blocks
        code = code.sub(/<pre>/,'<pre class="' + lang + '"><code class="' + lang + '">')
        code = code.sub(/<\/pre>/,"</code></pre>")
      end

    end
  end
end
