require "sinatra/base"
require "sinatra/activerecord"
require "json"
require 'rufus-scheduler'
require 'ruby_spark'
require_relative "live_score"
require_relative "models/Match"

# EXPORT ENVIRONMENTAL VARS IN .env USING: export $(cat .env | xargs)     

class App < Sinatra::Base
  # extensions
  register Sinatra::ActiveRecordExtension
  
  # configuration
  set :database, { adapter: "sqlite3", database: "db/db.sqlite3" }
  set :scheduler, Rufus::Scheduler.new
  RubySpark.configuration {|config| config.access_token = ENV["SPARK_ACCESS_TOKEN"]}  
  set :core, RubySpark::Core.new(ENV["SPARK_CORE_ID"])
  ActiveRecord::Base.logger = nil

  # schedule live score updates
  settings.scheduler.every "5s" do
    matches = LiveScore.get_fifa_scores
    App.log "Checking for score updates"
    
    unless matches.empty?
      # interate through the matches looking for an update
      matches.each do |m|   
        App.log "Updating #{m[:home_team]} v. #{m[:away_team]}"
        if match = Match.find_by_home_team_and_away_team(m[:home_team], m[:away_team])            
          # update scores
          match.home_score = m[:home_score]
          match.away_score = m[:away_score]
          
          # check for score changed
          begin        
            if match.changed?
              if match.home_score_changed?
                App.log "Goal by #{match.home_team}!"
                match.save
                settings.core.function("goal", match.home_team)
  
              elsif match.away_score_changed?
                App.log "Goal by #{match.away_team}!"
                match.save
                settings.core.function("goal", match.away_team)
              end
            end
          end
                  
        else
          # create the match in the db
          match = Match.create(m)        
        end
      end
    end
  end
  
  get "/" do
    settings.core.info.to_json
  end
  
  get "/scores/?" do 
  	matches = {espn: LiveScore.get_espn_scores, fifa:LiveScore.get_fifa_scores}
  	content_type :json
  	matches.to_json
  end
  
  # route for debugging
  get "/:function/:command" do
    content_type :json
    begin      
      return settings.core.function(params[:function], params[:command]).to_json
    rescue RubySpark::Core::ApiError => e
      return "API Error :(".to_json
    end
  end
  
  def self.log(msg)
    puts "[#{Time.now}]: #{msg}"
  end
end