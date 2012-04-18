
require 'rake'
require 'rake/testtask'
require 'rdoc/task'

## === Project properties =======================================================

Project = {
  'name'    => 'prometheus-sumo',
  'version' => IO.readlines("VERSION")[0],
  'author'  => 'Lars Baehren',
  'basedir' => Dir.pwd
}

## === Display properties of this project =======================================

namespace :project do

  desc "Print name of the project"
  task :name do
    puts Project['name']
  end

  desc "Print version number of the project"
  task :version do
    puts Project['version']
  end

  desc "Print author of the project"
  task :author do
    puts Project['author']
  end

end

desc "Summary of project properties"
task :project do
    puts " Project summary:"
    puts " .. Name     = #{Project['name']}"
    puts " .. Version  = #{Project['version']}"
    puts " .. Author   = #{Project['author']}"
    puts " .. Base dir = #{Project['basedir']}"
end

## === Generation of documentation ==============================================

Rake::RDocTask.new do |rd|
    rd.main = "README"
    rd.rdoc_files.include("README", "documentation/*.rdoc")
    rd.rdoc_dir = "build/documentation/html"
end

## === Default target ===========================================================

task :default => ['project']
