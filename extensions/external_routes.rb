module Sinatra
  module ExternalRoutes
    def self.registered(app)
      @@app = app
    end
    
    def self.app
      @@app || nil      
    end
  end
  
  register ExternalRoutes
end

def routes(&blk)
  Sinatra::ExternalRoutes.app.instance_eval(&blk)
end