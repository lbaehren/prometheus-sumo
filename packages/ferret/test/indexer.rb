
##__________________________________________________________
## Required modules

require 'rubygems'
require 'ferret'
require 'find'

include Ferret
 
##__________________________________________________________
## Process input from command line
 
infile = ARGV[0]
 
if infile.nil?
 puts "use: indexer.rb <infile>"
 exit
end
 
index = Index::Index.new(:default_field => 'content', :path => 'ferret-test')

# Start the timer
timeStart = Time.now
 
numFiles=0
 
Find.find(infile) do |path|
 
    puts "Indexing: #{path}"
 
    numFiles=numFiles+1
 
    if FileTest.file? path
 
        File.open(path) do |file|
 
            index.add_document(:file => path, :content => file.readlines)
 
        end
 
    end
 
end

# Stop the timer
timeElapsed = Time.now - timeStart
 
## Summary of used resources
puts "Files: #{numFiles}"
puts "Elapsed time: #{timeElapsed} secs\n"
