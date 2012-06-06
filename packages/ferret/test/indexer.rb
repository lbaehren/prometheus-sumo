
##__________________________________________________________
## Required modules

require 'rubygems'
require 'ferret'
require 'find'

include Ferret
 
##__________________________________________________________
## Process input from command line
 
infile  = ARGV[0]
outfile = ARGV[1]
 
if infile.nil?
 puts "use: indexer.rb <infile> <outfile>"
 exit
end

if outfile.nil?
  outfile="ferret-test"
end

##__________________________________________________________
## Initialize indexer
 
index = Index::Index.new(:default_field => 'content', :path => outfile)

# Start the timer
timeStart = Time.now
 
numFiles=0
 
Find.find(infile) do |path|
 
    numFiles=numFiles+1
 
    if FileTest.file? path
 
        File.open(path) do |file|
 
            index.add_document(:file => path, :content => file.readlines)
 
        end
 
    end
 
end

# Stop the timer
timeElapsed = Time.now - timeStart
 
##__________________________________________________________
## Summary of the indexing

puts "Index file   = #{outfile}\n"
puts "nof. files   = #{numFiles}\n"
puts "Elapsed time = #{timeElapsed} secs\n"
