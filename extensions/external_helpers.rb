module Sinatra
  module ExternalHelpers
    def self.registered(app)      
      @@app = app
    end
    
    def self.app
      @@app || nil      
    end
  end
  
  register ExternalHelpers
end

def helpers(helper_module)
  Sinatra::ExternalHelpers.app.helpers(helper_module)
end

def require_helpers(module_name)
  # load the module
  begin
    require module_name
  rescue LoadError
    require File.join(Sinatra::ExternalHelpers.app.settings.root, "helpers", module_name)
  end
  
  # require the module
  helpers module_name.camelize.constantize
end