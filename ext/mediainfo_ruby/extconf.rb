#!/usr/bin/env ruby
require 'rubygems'
require 'mkmf-rice'

#require 'ruby-debug'
#Debugger.start

if RUBY_PLATFORM == "universal-darwin10.0"
  # TODO Set the archflags to -arch x86_64 ONLY if it's a 64-bit snow leopard machine.
  ENV['ARCHFLAGS'] = "-arch x86_64"
  #$CFLAGS.sub!("-arch x86_64", "")
end

MEDIAINFO_HEADER_FILE="MediaInfoDLL/MediaInfoDLL_Static.h"

HEADER_DIRS = [
	"#{ENV['MEDIAINFO_DIR']}/Source",
	'/usr/local/src/mediainfolib/Source',
  '/opt/local/include',
	'/usr/local/include',
	'/usr/include'
]
HEADER_DIRS.shift if ENV['MEDIAINFO_DIR'].nil?

LIB_DIRS = [
	"#{ENV['MEDIAINFO_DIR']}/Source",
  '/opt/local/lib',
	'/usr/local/lib',
	'/usr/local', # For whatever reason, building mediainfo on Mac OSX put it here.
	'/usr/lib'
]
LIB_DIRS.shift if ENV['MEDIAINFO_DIR'].nil?
dir_config("mediainfo", HEADER_DIRS, LIB_DIRS)
have_library("stdc++")
have_header "MediaInfoDLL/MediaInfoDLL_Static.h"
have_library("mediainfo", "MediaInfo_New", ['string.h', MEDIAINFO_HEADER_FILE])

create_makefile('mediainfo_ruby')

