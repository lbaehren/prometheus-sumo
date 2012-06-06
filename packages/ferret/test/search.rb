#!/usr/bin/env ruby
require 'rubygems'
require 'ferret'
require 'find'

##__________________________________________________________
## Process input from command line

wot    = ARGV[0]
infile = ARGV[1]

if wot.nil?
 puts "use: search.rb <query>"
 exit
end

if infile.nil?
  infile="ferret-test"
end

##__________________________________________________________
## Load index into dearch engine

index = Ferret::Index::Index.new(:default_field => 'content', :path => infile)

ini = Time.now

nofDocuments=0
 
# uncomment line below for 10 first results, and comment the subsequent line.
 
# index.search_each(wot) do |doc, score| 

index.search_each(wot, options={:limit=>:all}) do |doc, score|
#   puts index[doc]['file'] + " score: "+score.to_s
    nofDocuments+=1
end
 
elapsed = Time.now - ini
 
##__________________________________________________________
## Summary of the search

puts "Search term     = #{wot}\n"
puts "Search index    = #{infile}\n"
puts "Elapsed time    = #{elapsed} secs\n"
puts "Documents found = #{nofDocuments}"
