require "sinatra/base"
require "sinatra/asset_pipeline"
require_relative "extensions/external_routes"
require_relative "extensions/external_helpers"

class App < Sinatra::Base
  # register extensions
  register Sinatra::ExternalRoutes
  register Sinatra::ExternalHelpers
  register Sinatra::AssetPipeline

  # configuration
  set :logging, true
  set :public_folder, File.join(root, "public")
  set :views, File.join(root, "views")
  
  # get routes
  Dir[File.join(root, "routes", "*.rb")].each { |file| require file }
  
  # get helpers
  require File.join(root, "helpers", "index.rb")
end