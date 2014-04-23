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
# Converts the ElBiEn datebase to a constant table
# So that it could included in C++ project


if ARGV.size > 1 or ARGV.size == 0
  puts 'Please specify only file.'
else
  begin
    i =1
    file = File.new(ARGV[0], "r")
    print "static const Int_t ElBiEn [101][101] = {"
    while (line = file.gets)
      next if line.start_with? '#'

      print "{"
      line.gsub!(/^\s+/,'')
      line.gsub!(/\s+/,',')
      #      print "}\n\n"
      print line[0..line.length-2]
      test = line[0..line.length-2].split(',')
      #p "\n\n"
      #p test.length
      print "},"
      #p i
      #i=i+1
    end
    print "};"
    file.close
  rescue Exception => err
    puts "#{err}"
  end
end
