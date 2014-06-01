# *** ATTENSION ***
# This file is NOT for Jekyll. It's modified for adapting Maliq(https://github.com/melborne/maliq) gem
# which is a EPUB generator.
# 'gem install ruby-aaws' required.
# By: kyoendo(a.k.a melborne) 2012
# Source URL: https://gist.github.com/4134497#file_amazon_liquid_tags.rb
# ------------------------------------
#

# Amazon liquid filters for jekyll - base0.net http://base0.net/posts/amazon-liquid-filters-for-jekyll/
# By:  Michael Janssen

require 'amazon/aws'
require 'amazon/aws/search'
require 'cgi'

module Jekyll
  class AmazonResultCache
    def initialize
      @result_cache = {}
    end

    @@instance = AmazonResultCache.new

    def self.instance
      @@instance
    end

    def item_lookup(asin)
      strip = asin.to_s.strip
      return @result_cache[asin] if @result_cache.has_key?(asin)
      il = Amazon::AWS::ItemLookup.new('ASIN', {'ItemId' => asin})
      resp = Amazon::AWS::Search::Request.new.search(il)
      @result_cache[asin] = resp
      return resp
    end

    private_class_method :new
  end

  module Filters
    def amazon_link(text)
      resp = AmazonResultCache.instance.item_lookup(text)
      item = resp.item_lookup_response[0].items[0].item[0]
      url = CGI::unescape(item.detail_page_url.to_s)
      title = item.item_attributes.title.to_s.gsub(/ \[Blu-ray\]/, '').gsub(/ \(Ultimate Edition\)/, '')
      '<a href="%s">%s</a>' % [url, title]
    end

    def amazon_authors(text)
      resp = AmazonResultCache.instance.item_lookup(text)
      item = resp.item_lookup_response[0].items[0].item[0]
      authors = item.item_attributes.author.collect(&:to_s)
      array_to_sentence_string(authors)
    end

    def amazon_medium_image(text)
      resp = AmazonResultCache.instance.item_lookup(text)
      item = resp.item_lookup_response[0].items[0].item[0]
      url = CGI::unescape(item.detail_page_url.to_s)
      image_url = save_image item.image_sets.image_set[0].medium_image.url
      '<a href="%s"><img class="amazon" src="%s" /></a>' % [url, image_url]
    end

    def amazon_large_image(text)
      resp = AmazonResultCache.instance.item_lookup(text)
      item = resp.item_lookup_response[0].items[0].item[0]
      url = CGI::unescape(item.detail_page_url.to_s)
      image_url = save_image item.image_sets.image_set[0].large_image.url
      '<a href="%s"><img class="amazon" src="%s" /></a>' % [url, image_url]
    end

    def amazon_small_image(text)
      resp = AmazonResultCache.instance.item_lookup(text)
      item = resp.item_lookup_response[0].items[0].item[0]
      url = CGI.escapeHTML(item.detail_page_url.to_s)
      image_url = save_image item.image_sets.image_set[0].small_image.url
      '<a href="%s"><img class="amazon" src="%s" /></a>' % [url, image_url]
    end

    def amazon_release_date(text)
      resp = AmazonResultCache.instance.item_lookup(text)
      item = resp.item_lookup_response[0].items[0].item[0]
      item.item_attributes.theatrical_release_date.to_s
    end

    # Movie specific
    def amazon_actors(text)
      resp = AmazonResultCache.instance.item_lookup(text)
      item = resp.item_lookup_response[0].items[0].item[0]
      actors = item.item_attributes.actor.collect(&:to_s)
      array_to_sentence_string(actors)
    end

    def amazon_director(text)
      resp = AmazonResultCache.instance.item_lookup(text)
      item = resp.item_lookup_response[0].items[0].item[0]
      item.item_attributes.director.to_s
    end

    def amazon_running_time(text)
      resp = AmazonResultCache.instance.item_lookup(text)
      item = resp.item_lookup_response[0].items[0].item[0]
      item.item_attributes.running_time.to_s + " minutes"
    end
  end
end


# Followings are added for Maliq gem.

require "open-uri"

class CGI
  class << self
    alias :unescape :escapeHTML
  end
end

module Jekyll
  module Filters
    def save_image(url, img_dir='images')
      url = url[0].to_s
      Dir.mkdir(img_dir) unless Dir.exist?(img_dir)
      path = "#{img_dir}/#{File.basename(url)}"
      unless File.exist?(path)
        puts "Image downloading..."
        File.open(path, 'w') do |f|
          open(url) { |img| f.write img.read }
        end
      end
      path
    end
  end
end

Liquid::Template.register_filter(Jekyll::Filters)