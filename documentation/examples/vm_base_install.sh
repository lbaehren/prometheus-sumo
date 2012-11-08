#!/bin/bash

## Update the installed system packages

sudo apt-get update
sudo apt-get upgrade

## Install development packages

sudo apt-get install build-essential cmake git-svn subversion doxygen
sudo apt-get install ruby1.8-dev libboost-all-dev

## Install database server

sudo apt-get install mysql-server

## Prepare directory structure for code development

cd
mkdir Development

cd Development
git clone git://github.com/lbaehren/prometheus-sumo.git prometheus-sumo
git clone git://github.com/prometheus-ev/promhp.git promhp
git svn clone -s http://prometheus-srv.uni-koeln.de/svn/pandora pandora
