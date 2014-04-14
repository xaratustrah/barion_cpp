#!/usr/bin/ruby
# This file is part of barion project.
#
# (c) Copyright M. Shahab SANJARI 2014
#
# barion is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# barion is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
#
# along with barion.  If not, see <http://www.gnu.org/licenses/>.
#
#
# build icons
# some versions do not support 1024x1024
# also pay attention that 64x64 is not available in the list
#

begin
    raise 'Please specify the icon file.' if not ARGV.size == 1
    file=ARGV[0].to_s
    puts "Processing icon file #{file}."
    system('mkdir icon.iconset')
    [512,256,128, 32, 16].each do |i|
        system("convert #{file} -resize #{i}x#{i} icon.iconset/icon_#{i}x#{i}.png")
        system("convert #{file} -resize #{i}x#{i} icon.iconset/icon_#{i}x#{i}@2x.png")
    end
    system("iconutil -c icns icon.iconset")
    system("rm -rf icon.iconset/")
    
    rescue Exception => err
    puts "#{err}"
end
