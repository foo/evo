cities = ARGV[0].to_i

if (cities - 1) % 3 != 0
  puts '%3!'
else
  
  print "#{cities}\n"
  
  cities.times do
    cities.times do
      print "#{rand(120)+1} "
    end
    print "\n"
  end
end
