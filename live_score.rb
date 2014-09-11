require 'nokogiri'
require 'open-uri'

module LiveScore  
  def self.get_espn_scores()
    id = 4
    matches = []
  
    # load in the document
    url = "http://www.espnfc.us/fifa-world-cup/#{id}/scores"
    doc = Nokogiri::HTML(open(url))
    
    # parse each live score
    doc.css(".scores .score.live").each_with_index do |box, i|      	
    	# get teams
    	teams = box.css('.team-name').map {|team| team.css('span').text;}
    	
    	# get scores
    	scores = box.css('.team-score').map {|score| score.css('span').text; }
    	      	
    	# build object
    	matches[i] = {home_team: teams[0], away_team: teams[1], home_score: scores[0], away_score: scores[1]}
    end 
    
    # return matches
    matches
  end

  def self.get_fifa_scores()
    # load in the document
    url = "http://www.fifa.com/worldcup/matches/index.html"
    doc = Nokogiri::HTML(open(url))
    
    # parse each live score
    matches = []
    date = Time.now.strftime("%Y%m%d")
    doc.css(".match-list-date[id=\"#{date}\"] .mu.live").each_with_index do |box, i|      	
    	# get teams
    	ht = box.css('.home .t-nText').text
    	at = box.css('.away .t-nText').text
    	scores = box.css('.s-scoreText').text.match(/(\d+)-(\d+)/);   	
    	hs = scores[1]
    	as = scores[2]
    	
    	# build object
    	matches[i] = {home_team: ht, away_team: at, home_score: hs, away_score: as}
    end 
    
    # return matches
    matches
  end
end