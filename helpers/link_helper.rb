module LinkHelper

  def link_to(url, text=url, attrs={})
    attributes = url.nil? ? "" : "href=\"#{url}\" "
    attrs.each { |key, value| attributes << (key.to_s << "=\"" << value << "\" ") }  
    return "<a #{attributes}>#{text}</a>"
  end
  
  def external_link(url, text=url, attrs={})
    attrs[:target] = "_blank" unless url.nil?
    link_to(url, text, attrs)
  end
  
end