---
layout: post
title:  "Ruby Sample Code"
date:   2014-04-01 08:03:50
categories: 
---

# Hello Ruby!

これはRubyのサンプルコードです。

##Try Ruby
{% highlight ruby linenos %}
class Person
  def initialize(name)
    @name = name
  end

  def hello
    "Hello, friend!\nMy name is #{@name}!"
  end
end

charlie = Person.new('Charlie')
puts charlie.hello

# >> Hello, friend!
# >> My name is Charlie!
{% endhighlight %}

# 章
## 節
### 見出し

