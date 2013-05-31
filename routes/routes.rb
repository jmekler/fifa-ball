require "erb"

# feel free to split up your routes into separate files, just remember to wrap them in a "routes do... end" block
routes do
  get "/" do
    erb :index
  end
end