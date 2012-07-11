
require 'test/unit'
require 'exifr'

##____________________________________________________________________
## Check the input from the command line

if ARGV.length == 0
  puts "[TestEXIF] Please specify a filename"
  Process.exit
end

image_file = ARGV.first
exif_info = nil

case image_file.downcase
  when /.jpg\Z/
    exif_info = EXIFR::JPEG.new(image_file)
  when /.tiff?\Z/
    exif_info = EXIFR::TIFF.new(image_file)
end

##____________________________________________________________________
## Header for the summary of EXIF information

puts "Standard items".center(72)
puts "=" * 72
puts "                          File : #{image_file}"
puts "                        Height : #{exif_info.height}"
puts "                         Width : #{exif_info.width}"
puts

if exif_info.exif? then
  puts "EXIF information".center(72)
  puts "=" * 72
  h = exif_info.exif.to_hash
  h.each_pair do |k,v|
    puts "#{k.to_s.rjust(30)} : #{v}"
  end
else
  puts "No EXIF information in this image"
end
