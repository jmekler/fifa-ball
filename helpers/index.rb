## use the "require_helpers" method to add helpers to your Sinatra app

## use rails-like "respond_to" blocks
require_helpers "sinatra/content_for"

## include a helper module in helpers folder (module should have the camelized name of the file)
## e.g. calling "require_helpers" on link_helper.rb will require the file and include the LinkHelper module
require_helpers "link_helper"

## add local modules using the "helpers" method
module Friendly
  def hi 
    "Hi!"
  end
end
helpers Friendly
