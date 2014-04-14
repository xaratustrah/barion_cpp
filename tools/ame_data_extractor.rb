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
# extracts desired data from the AME table
# can be used for further processing and programs
# Just provide the AME table in the same directory
# e.g. mass.mas12 file.
# you may use grep to extract data directly
#

begin
    raise "Please provide AME data file:\n         ./ame_data_extractor.rb mass.mas12" if not ARGV.size == 1
    
    Filename = ARGV[0].to_s
    file = File.new(Filename, 'r')
    
    line=Array.new
    output=Array.new
    
    counter = 0;
    
    #				  1  2  3  4  5    6   7     8    9      10   11      12  13     14    15     16   17
    #   format    :  a1,i3,i5,i5,i5,1x,a3,a4,1x,f13.5,f11.5,f11.3,f9.3,1x,a2,f11.3,f9.3,1x,i3,1x,f12.5,f11.3,1x
    #                cc NZ  N  Z  A    el  o     mass  unc binding unc     B  beta  unc    atomic_mass   unc
    # 1N-Z    N    Z   A  EL    O     MASS EXCESS       BINDING ENERGY/A        BETA-DECAY ENERGY         ATOMIC MASS          V/S
    
    # Print header
    
    #print "A,Name,Z,Mass [amu],Experimental?\n"
	
    # start through lines
    
    while line=file.gets
        counter = counter  + 1
        next if counter < 40
        
        exp = 1
        line.gsub!("#",".") and exp=0 if line.include?("#")
        o1 = line[0] # cc
        o2 = line[1..3].to_i # NZ
        nn = line[4..8].to_i # N
        zz = line[9..13].to_i # Z
        aa = line[14..18].to_i # A
        # here comes one space character
        name = line[20..22].to_s.gsub!(/\s/, '') # element name
        o7 = origin = line[23..26].to_s.gsub!(/\s/, '') # origin
        # here comes one space character
        mass_exess_kev = line[28..40].to_f # Atomic mass excess [keV]
        mass_exess_unc_kev = line[41..51].to_f # Atomic mass excess uncertainty [keV]
        beu_kev = line[52..62].to_f # Binding energy per nucleon [keV]
        beu_unc_kev = line[63..71].to_f # Binding energy per nucleon uncertainty [keV]
        # here comes one space character
        decay_type = line[73..74].to_s # Beta decay type
        decay_e_kev = line[75..85].to_f # Beta decay energy [keV]
        decay_e_unc_kev = line[86..94].to_f # Beta decay energy uncertainty[keV]
        # here comes one space character
        am_u = line[96..98].to_i #Atomic mass [u]
        # here comes one space character
        am_fraction_u = line[100..111].to_f * 1e-6 # Atomic mass [u]
        am_unc_u = line[112..122].to_f * 1e-6 # Atomic mass [u] uncertainty
        # here comes one space character
        
        # change format here if needed.
        print "#{aa}    #{zz}    #{am_u+am_fraction_u}    #{am_unc_u}    #{mass_exess_kev}    #{mass_exess_unc_kev}    #{beu_kev}    #{beu_unc_kev}    #{decay_e_kev}    #{decay_e_unc_kev}    #{exp}    #{decay_type}    #{name}\n"
        
    end
    rescue Exception => err
    puts "#{err}"
end
